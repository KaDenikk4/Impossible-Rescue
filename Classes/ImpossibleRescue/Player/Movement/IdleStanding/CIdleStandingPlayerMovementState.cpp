//Name of class:	CIdleStandingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player walking
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CIdleStandingPlayerMovementState.h"
#include "../Jumping/CJumpingPlayerMovementState.h"
#include "../CPlayerMovementStates.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

USING_NS_CC;

CIdleStandingPlayerMovementState::CIdleStandingPlayerMovementState()
	: m_psfxIdleStanding(nullptr)
{
}

CIdleStandingPlayerMovementState::~CIdleStandingPlayerMovementState ( )
{
	CleanupSoundEffects();
}

void CIdleStandingPlayerMovementState::VInitialise( )
{
	CPlayerMovementState::VInitialise();

	// Clean up existing sound effects
	CleanupSoundEffects();
	
	m_psfxIdleStanding = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerIdle);
}

//State beginning transition. Called once when player movement state is set to this state.
void CIdleStandingPlayerMovementState::VEnter(CPlayer& player)
{
	CPlayerMovementState::VEnter(player);
}

void CIdleStandingPlayerMovementState::VExit(CPlayer& player)
{
	CPlayerMovementState::VExit(player);
	m_psfxIdleStanding->VStop();
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CIdleStandingPlayerMovementState::VUpdate ( CPlayer& player )
{
	CPlayerMovementState::VUpdate(player);
	
	if( !GetStateIsTransitioning(  ) )
	{
		if (!player.GetPlayerIsGrounded())
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingWalkPlayerMovementState();
		}
	}
	else
	{
		SetStateIsTransitioning(false);
	}

	SetAnimationSpeed(1.0f);
	
	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CIdleStandingPlayerMovementState::VHandleInput ( CPlayer& player, TGCController<EPlayerActions>& input )
{
	// * calculate the control force direction
	SetControlForceDirectionX(0.0f);
	SetControlForceDirectionY(0.0f);

	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame

	player.SetIsInputInactive(1.0f);

	// Move the player left/right with the analogue stick
	const f32 fLeftStickDeadZoned = input.GetCurrentAxisDeadzoned(EPlayerActions::MoveXAxis, GetXAxisDeadzone( ));

	SetControlForceDirectionX(fLeftStickDeadZoned);

	// If the player moves enter the walking state
	if ( abs(fLeftStickDeadZoned) >= GetRunningThreshold()
		|| input.ButtonIsPressed(EPlayerActions::MoveLeft)
		|| input.ButtonIsPressed(EPlayerActions::MoveRight))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetWalkingPlayerMovementState();
	}
	
	// Crouch
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Crouch))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleCrouchingPlayerMovementState();
	}
	
	// Jump
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Jump))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingPlayerMovementState();
	}	

	return nullptr;
}

const char* CIdleStandingPlayerMovementState::VGetAnimationName( ) const
{
	return mk_pszAnim_DanielleIdleStanding;
}

const char* CIdleStandingPlayerMovementState::VGetPhysicsShapeName( ) const
{
	return mk_pszPhys_DanielleIdleStanding;
}

void CIdleStandingPlayerMovementState::CleanupSoundEffects( )
{
	if (m_psfxIdleStanding)
	{
		delete m_psfxIdleStanding;
		m_psfxIdleStanding = nullptr;
	}
}
