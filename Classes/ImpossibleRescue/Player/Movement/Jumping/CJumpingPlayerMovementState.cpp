//Name of class:	CJumpingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player jumping
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput, DoJump

#include "CJumpingPlayerMovementState.h"
#include "../Walking/CWalkingPlayerMovementState.h"
#include "../CPlayerMovementStates.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "AppDelegate.h"

USING_NS_CC;


CJumpingPlayerMovementState::CJumpingPlayerMovementState( )
	: m_psfxJumping( nullptr )
	, m_psfxCrouching(nullptr)
{
}

CJumpingPlayerMovementState::~CJumpingPlayerMovementState( )
{
	CleanupSoundEffects();
}

void CJumpingPlayerMovementState::VInitialise( )
{
	CPlayerMovementState::VInitialise();

	// Clean up existing sound effects
	CleanupSoundEffects();
	
	m_psfxJumping = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerJumping);
	m_psfxCrouching = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerCrouch);
}

//State beginning transition. Called once when player movement state is set to this state.
void CJumpingPlayerMovementState::VEnter( CPlayer& player )
{
	CPlayerMovementState::VEnter(player);
	
	m_psfxJumping->VPlay();
	
	DoJump(player);
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CJumpingPlayerMovementState::VUpdate( CPlayer& player )
{
	CPlayerMovementState::VUpdate(player);

	if( !GetStateIsTransitioning(  ) )
	{
		// If the player is grounded enter a grounded state
		if (player.GetPlayerIsGrounded (  ))
		{
			PlayLandedSound();
			// If the player isn't moving, enter the idle state
			if(abs(GetControlForceDirection().x) <= 0.0f)
			{
				return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
			}
			// If the player is moving, enter the walking state
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetWalkingPlayerMovementState();
		}
	}
	else
	{
		SetStateIsTransitioning(false);
	}

	// we accumulate total force over the frame and apply it at the end
	Vec2 v2TotalForce = Vec2::ZERO;

	// accumulate the force from input
	// multiply the control vector and by movement force
	v2TotalForce.x = GetControlForceDirection().x * player.GetMaximumGroundedHorizontalMovementForce();
	v2TotalForce.y = GetControlForceDirection().y * player.GetMaximumJumpingVerticalMovementForce();

	player.SetVelocity( Vec2(v2TotalForce.x, player.GetVelocity().y) );

	// physics calcs handled by box 2d based on force applied
	//ToDo 
	player.ApplyForceToCenter(Vec2(0.0f, v2TotalForce.y));

	// Set the animation speed so that it synchronizes with movement
	SetAnimationSpeed(1.0f);
	
	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CJumpingPlayerMovementState::VHandleInput( CPlayer& player, TGCController<EPlayerActions>& input )
{
	// * calculate the control force direction
	SetControlForceDirectionX(0.0f);
	SetControlForceDirectionY(0.0f);

	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame
	//f32 fIsInputInactive = 1.0f;
	player.SetIsInputInactive(1.0f);

	//Move the player left/right with the analogue stick
	const f32 fLeftStickDeadZoned = input.GetCurrentAxisDeadzoned(EPlayerActions::MoveXAxis, GetXAxisDeadzone());
	
	SetControlForceDirectionX(fLeftStickDeadZoned);

	if (abs(fLeftStickDeadZoned) > 0.0f)
	{
		player.SetIsInputInactive(0.0f);
	}

	//Move the player left with the d-pad
	if (input.ButtonIsPressed(EPlayerActions::MoveLeft))
	{
		SetControlForceDirectionX(-1.0f);
		player.SetIsInputInactive(0.0f);
	}
	//Move the player right with the d-pad
	if (input.ButtonIsPressed(EPlayerActions::MoveRight))
	{
		SetControlForceDirectionX(1.0f);
		player.SetIsInputInactive(0.0f);
	}
	
	//Crouch
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Crouch))
	{
		m_psfxCrouching->VPlay();
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingCrouchPlayerMovementState();
	}

	return nullptr;
}

const char* CJumpingPlayerMovementState::VGetAnimationName( ) const
{
	return mk_pszAnim_DanielleJumping;
}

const char* CJumpingPlayerMovementState::VGetPhysicsShapeName( ) const
{
	return mk_pszPhys_DanielleJumping;
}

bool CJumpingPlayerMovementState::VGetIsAnimationLooping( )
{
	return false;
}

//Make the player jump
void CJumpingPlayerMovementState::DoJump( CPlayer& player )
{
	SetControlForceDirectionY(1.0f);
	
	player.SetIsInputInactive(0.0f);
}

void CJumpingPlayerMovementState::CleanupSoundEffects( )
{
	if (m_psfxJumping)
	{
		delete m_psfxJumping;
		m_psfxJumping = nullptr;
	}
	if (m_psfxCrouching)
	{
		delete m_psfxCrouching;
		m_psfxCrouching = nullptr;
	}
}
