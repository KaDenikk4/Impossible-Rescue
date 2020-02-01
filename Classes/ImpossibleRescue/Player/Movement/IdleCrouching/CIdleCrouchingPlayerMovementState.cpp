//Name of class:	CIdleCrouchingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player crouching
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CIdleCrouchingPlayerMovementState.h"
#include "../Walking/CWalkingPlayerMovementState.h"
#include "../Jumping/CJumpingPlayerMovementState.h"
#include "../CPlayerMovementStates.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

USING_NS_CC;

CIdleCrouchingPlayerMovementState::CIdleCrouchingPlayerMovementState()
	: m_psfxIdleCrouching(nullptr)
{
}

CIdleCrouchingPlayerMovementState::~CIdleCrouchingPlayerMovementState()
{
	CleanupSoundEffects();
}

void CIdleCrouchingPlayerMovementState::VInitialise( )
{
	CPlayerMovementState::VInitialise();
	
	// Clean up existing sound effects
	CleanupSoundEffects();
	
	m_psfxIdleCrouching = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerIdle);
}

//State beginning transition. Called once when player movement state is set to this state.
void CIdleCrouchingPlayerMovementState::VEnter(CPlayer& player)
{
	CPlayerMovementState::VEnter(player);
}

void CIdleCrouchingPlayerMovementState::VExit( CPlayer& player )
{
	m_psfxIdleCrouching->VStop();
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CIdleCrouchingPlayerMovementState::VUpdate(CPlayer& player)
{
	CPlayerMovementState::VUpdate(player);
	
	if( !GetStateIsTransitioning(  ) )
	{
		if (!player.GetPlayerIsGrounded())
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingCrouchPlayerMovementState();
		}
	}
	else
	{
		SetStateIsTransitioning(false);
	}

	// Set the animation speed so that it synchronizes with movement
	SetAnimationSpeed(1.0f);

	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CIdleCrouchingPlayerMovementState::VHandleInput(CPlayer& player, TGCController<EPlayerActions>& input)
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
	
	// If the player moves enter the walking state
	if (abs(fLeftStickDeadZoned) > GetRunningThreshold()
		|| input.ButtonIsPressed(EPlayerActions::MoveLeft)
		|| input.ButtonIsPressed(EPlayerActions::MoveRight))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetCrouchingPlayerMovementState();
	}

	//Walk
	if(input.ButtonHasJustBeenPressed( EPlayerActions::Crouch ) && player.GetCanPlayerStand())
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
	}
	
	//Walk
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Jump) && player.GetCanPlayerStand())
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
	}

	return nullptr;
}

const char* CIdleCrouchingPlayerMovementState::VGetAnimationName( ) const
{
	return mk_pszAnim_DanielleIdleCrouching;
}

const char* CIdleCrouchingPlayerMovementState::VGetPhysicsShapeName( ) const
{
	return mk_pszPhys_DanielleIdleCrouching;
}

void CIdleCrouchingPlayerMovementState::CleanupSoundEffects( )
{
	if (m_psfxIdleCrouching)
	{
		delete(m_psfxIdleCrouching);
		m_psfxIdleCrouching = nullptr;
	}
}
