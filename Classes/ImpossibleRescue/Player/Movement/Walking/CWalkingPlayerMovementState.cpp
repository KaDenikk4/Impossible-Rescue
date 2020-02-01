//Name of class:	CWalkingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player walking
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CWalkingPlayerMovementState.h"
#include "../Jumping/CJumpingPlayerMovementState.h"
#include "../CPlayerMovementStates.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

USING_NS_CC;

CWalkingPlayerMovementState::CWalkingPlayerMovementState()
	: m_psfxWalking(nullptr)
{
}

CWalkingPlayerMovementState::~CWalkingPlayerMovementState ( )
{
	CleanupSoundEffects();
}

void CWalkingPlayerMovementState::VInitialise( )
{
	CPlayerMovementState::VInitialise();
	
	// Clean up existing sound effects
	CleanupSoundEffects( );
	
	m_psfxWalking = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::Footsteps);
}

//State beginning transition. Called once when player movement state is set to this state.
void CWalkingPlayerMovementState::VEnter(CPlayer& player)
{
	CPlayerMovementState::VEnter(player);

	m_psfxWalking->VStop();
	
	m_psfxWalking->VPlay(true);
}

void CWalkingPlayerMovementState::VExit(CPlayer& player)
{
	m_psfxWalking->VStop();
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CWalkingPlayerMovementState::VUpdate ( CPlayer& player )
{
	CPlayerMovementState::VUpdate( player );

	if( !GetStateIsTransitioning(  ) )
	{
		if (!player.GetPlayerIsGrounded())
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingWalkPlayerMovementState();
		}

		if (abs(GetControlForceDirection( ).x) <= 0.0f)
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
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
	v2TotalForce.x = GetControlForceDirection( ).x * player.GetMaximumGroundedHorizontalMovementForce();

	player.SetVelocity( Vec2(v2TotalForce.x, player.GetVelocity().y) );
	
	// Decimal percentage of full speed
	const float fAnimationSpeed = abs(player.GetVelocity().x / GetMaxGroundedVelocityX());

	// Set the animation speed so that it synchronizes with movement
	SetAnimationSpeed( fAnimationSpeed );

	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CWalkingPlayerMovementState::VHandleInput ( CPlayer& player, TGCController<EPlayerActions>& input )
{
	// * calculate the control force direction
	SetControlForceDirectionX(0.0f);
	SetControlForceDirectionY(0.0f);

	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame
	player.SetIsInputInactive(1.0f);

	//Move the player left/right with the analogue stick
	const f32 fLeftStickDeadZoned = input.GetCurrentAxisDeadzoned(EPlayerActions::MoveXAxis, GetXAxisDeadzone( ));

	SetControlForceDirectionX(fLeftStickDeadZoned);

	//CCLOG("%f", abs(fLeftStickDeadZoned));
	
	if (abs(fLeftStickDeadZoned) > 0.0f)
	{
		player.SetIsInputInactive( 0.0f );
	}

	// Move the player left with the d-pad
	if (input.ButtonIsPressed(EPlayerActions::MoveLeft))
	{
		SetControlForceDirectionX( -1.0f );
		player.SetIsInputInactive(0.0f);
	}
	
	// Move the player right with the d-pad
	if (input.ButtonIsPressed(EPlayerActions::MoveRight))
	{
		SetControlForceDirectionX( 1.0f );
		player.SetIsInputInactive(0.0f);
	}

	if(abs(GetControlForceDirection( ).x) < GetRunningThreshold(  ))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
	}
	
	//Crouch
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Crouch))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetCrouchingPlayerMovementState();
	}
	
	//Jump
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Jump))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingPlayerMovementState();
	}	

	return nullptr;
}

const char* CWalkingPlayerMovementState::VGetAnimationName( ) const
{
	return mk_pszAnim_DanielleWalking;
}

const char* CWalkingPlayerMovementState::VGetPhysicsShapeName( ) const
{
	return mk_pszPhys_DanielleJumpingWalking;
}

void CWalkingPlayerMovementState::CleanupSoundEffects()
{
	if (m_psfxWalking)
	{
		delete m_psfxWalking;
		m_psfxWalking = nullptr;
	}
}
