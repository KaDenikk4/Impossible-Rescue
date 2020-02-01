//Name of class:	CJumpingCrouchPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player crouching whilst jumping
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CJumpingCrouchPlayerMovementState.h"
#include "../Walking/CWalkingPlayerMovementState.h"
#include "../CPlayerMovementStates.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

USING_NS_CC;

CJumpingCrouchPlayerMovementState::CJumpingCrouchPlayerMovementState()
	: m_psfxStandUp(nullptr)
{
}

CJumpingCrouchPlayerMovementState::~CJumpingCrouchPlayerMovementState()
{
	CleanupSoundEffects();	
}

void CJumpingCrouchPlayerMovementState::VInitialise( )
{
	CPlayerMovementState::VInitialise();
	
	CleanupSoundEffects();
	 
	m_psfxStandUp = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerStandsUp);
}

//State beginning transition. Called once when player movement state is set to this state.
void CJumpingCrouchPlayerMovementState::VEnter(CPlayer& player)
{
	CPlayerMovementState::VEnter(player);
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CJumpingCrouchPlayerMovementState::VUpdate(CPlayer& player)
{
	CPlayerMovementState::VUpdate(player);

	if( !GetStateIsTransitioning(  ) )
	{
		// If the player is grounded enter a grounded state
		if (player.GetPlayerIsGrounded())
		{
			PlayLandedSound();
			// If the player isn't moving, enter the idle state
			if (abs(GetControlForceDirection( ).x) <= 0.0f)
			{
				return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleCrouchingPlayerMovementState();
			}
			// If the player is moving, enter the walking state
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetCrouchingPlayerMovementState();
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

	player.SetVelocity( Vec2(v2TotalForce.x, player.GetVelocity().y) );
	
	SetAnimationSpeed(1.0f);

	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CJumpingCrouchPlayerMovementState::VHandleInput(CPlayer& player, TGCController<EPlayerActions>& input)
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

	//Walk
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Crouch) && player.GetCanPlayerStand())
	{
		m_psfxStandUp->VPlay();
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingWalkPlayerMovementState();
	}

	//Walk
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Jump) && player.GetCanPlayerStand())
	{
		m_psfxStandUp->VPlay();
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingWalkPlayerMovementState();
	}

	return nullptr;
}

const char* CJumpingCrouchPlayerMovementState::VGetAnimationName( ) const
{
	return mk_pszAnim_DanielleJumpingCrouching;
}

const char* CJumpingCrouchPlayerMovementState::VGetPhysicsShapeName( ) const
{
	return mk_pszPhys_DanielleJumping;
}

void CJumpingCrouchPlayerMovementState::CleanupSoundEffects( )
{
	if (m_psfxStandUp)
	{
		delete(m_psfxStandUp);
		m_psfxStandUp = nullptr;
	}
}
