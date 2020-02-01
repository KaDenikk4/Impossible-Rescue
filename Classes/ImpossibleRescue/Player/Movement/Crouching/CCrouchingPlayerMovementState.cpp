//Name of class:	CCrouchingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player crouching
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CCrouchingPlayerMovementState.h"
#include "../Walking/CWalkingPlayerMovementState.h"
#include "../Jumping/CJumpingPlayerMovementState.h"
#include "../CPlayerMovementStates.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

USING_NS_CC;

CCrouchingPlayerMovementState::CCrouchingPlayerMovementState()
	: m_psfxCrouchSound(nullptr)
	, m_psfxStandUpSound(nullptr)
{
}

CCrouchingPlayerMovementState::~CCrouchingPlayerMovementState()
{
	CleanupSoundEffects( );
}

void CCrouchingPlayerMovementState::VInitialise( )
{
	CPlayerMovementState::VInitialise();
	// Clean up existing sound effects
	CleanupSoundEffects();
	
	m_psfxCrouchSound = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerCrouch);
	m_psfxStandUpSound = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerStandsUp);
}

//State beginning transition. Called once when player movement state is set to this state.
void CCrouchingPlayerMovementState::VEnter(CPlayer& player)
{
	CPlayerMovementState::VEnter(player);
	
	m_psfxCrouchSound->VPlay(); 
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CCrouchingPlayerMovementState::VUpdate(CPlayer& player)
{
	CPlayerMovementState::VUpdate(player);

	if( !GetStateIsTransitioning(  ) )
	{
		if (!player.GetPlayerIsGrounded())
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingCrouchPlayerMovementState();
		}

		if( abs(GetControlForceDirection(  ).x) <= 0.0f )
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleCrouchingPlayerMovementState();
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
	v2TotalForce.x = GetControlForceDirection().x * player.GetMaximumGroundedCrouchingHorizontalMovementForce( );

	player.SetVelocity( Vec2( v2TotalForce.x, player.GetVelocity().y ) );
	
	// Animation speed to fit the speed of the player movement
	const float fAnimationSpeed = 1.5f;

	// Set the animation speed so that it synchronizes with movement
	SetAnimationSpeed(fAnimationSpeed);

	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CCrouchingPlayerMovementState::VHandleInput(CPlayer& player, TGCController<EPlayerActions>& input)
{
	// * calculate the control force direction
	SetControlForceDirectionX(0.0f);
	SetControlForceDirectionY(0.0f);

	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame
	//f32 fIsInputInactive = 1.0f;
	player.SetIsInputInactive(1.0f);

	//Move the player left/right with the analogue stick
	const f32 fLeftStickDeadZoned = input.GetCurrentAxisDeadzoned(EPlayerActions::MoveXAxis, GetXAxisDeadzone( ));
	
	SetControlForceDirectionX(fLeftStickDeadZoned);
	
	if(abs( fLeftStickDeadZoned ) > 0.0f )
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

	//Walk
	if(input.ButtonHasJustBeenPressed( EPlayerActions::Crouch ) && player.GetCanPlayerStand())
	{
		m_psfxStandUpSound->VPlay();
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetWalkingPlayerMovementState();
	}
	
	//Walk
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Jump) && player.GetCanPlayerStand())
	{
		m_psfxStandUpSound->VPlay();
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetWalkingPlayerMovementState();
	}

	return nullptr;
}

const char* CCrouchingPlayerMovementState::VGetAnimationName( ) const
{
	return mk_pszAnim_DanielleCrouching;
}

const char* CCrouchingPlayerMovementState::VGetPhysicsShapeName( ) const
{
	return mk_pszPhys_DanielleCrouching;
}


void CCrouchingPlayerMovementState::CleanupSoundEffects()
{
	if (m_psfxCrouchSound)
	{
		delete(m_psfxCrouchSound);
		m_psfxCrouchSound = nullptr;
	}
	if (m_psfxStandUpSound)
	{
		delete(m_psfxStandUpSound);
		m_psfxStandUpSound = nullptr;
	}
}
