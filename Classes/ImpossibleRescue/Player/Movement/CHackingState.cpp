//Name of class:	CHackingState
//Summary:			This class is not used in the game. When plugged in to the player, it
//					would put him in the HackingState, which would allow hacking, hacking animation and
//					hacking physics body to be applied to the player. At the time of final build, animation
//					didn't align, so this class was never used.
//Functions:		VInitialise, VEnter, VExit, VUpdate, VHandleInput, VGetAnimationName,
//					VGetAnimationName, VGetPhysicsShapeName, CleanupSoundEffects

#include "CHackingState.h"
#include "AppDelegate.h"

#include "ImpossibleRescue/Player/Movement/CPlayerMovementStates.h"

CHackingState::CHackingState()
{
}


CHackingState::~CHackingState()
{
	CleanupSoundEffects();
}

USING_NS_CC;

void CHackingState::VInitialise()
{
	CPlayerMovementState::VInitialise();

	// Clean up existing sound effects
	CleanupSoundEffects();
}

//State beginning transition. Called once when player movement state is set to this state.
void CHackingState::VEnter( CPlayer& player )
{
	CPlayerMovementState::VEnter( player );

}

void CHackingState::VExit( CPlayer& player )
{
	CPlayerMovementState::VExit( player );
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerMovementState* CHackingState::VUpdate( CPlayer& player )
{
	CPlayerMovementState::VUpdate( player );

	if( !GetStateIsTransitioning() )
	{
		if( !player.GetPlayerIsGrounded() )
		{
			return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingWalkPlayerMovementState();
		}
	}
	else
	{
		SetStateIsTransitioning( false );
	}

	// we accumulate total force over the frame and apply it at the end
	Vec2 v2TotalForce = Vec2::ZERO;

	// accumulate the force from input
	// multiply the control vector and by movement force
	v2TotalForce.x = GetControlForceDirection().x * player.GetMaximumGroundedHorizontalMovementForce();

	player.SetVelocity( Vec2( v2TotalForce.x, player.GetVelocity().y ) );

	// Decimal percentage of full speed
	const float fAnimationSpeed = 1.0f;

	// Set the animation speed so that it synchronizes with movement
	SetAnimationSpeed( fAnimationSpeed );

	CCLOG( "IN THE HACKING STATE" );

	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerMovementState* CHackingState::VHandleInput( CPlayer& player, TGCController<EPlayerActions>& input )
{
	// * calculate the control force direction
	SetControlForceDirectionX( 0.0f );
	SetControlForceDirectionY( 0.0f );

	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame
	player.SetIsInputInactive( 1.0f );

	//Move the player left/right with the analogue stick
	const f32 fLeftStickDeadZoned = input.GetCurrentAxisDeadzoned( EPlayerActions::MoveXAxis, GetXAxisDeadzone() );

	SetControlForceDirectionX( fLeftStickDeadZoned );

	//CCLOG("%f", abs(fLeftStickDeadZoned));

	if( abs( fLeftStickDeadZoned ) > 0.0f )
	{
		player.SetIsInputInactive( 0.0f );
	}

	// If the player moves enter the walking state
	if( abs( fLeftStickDeadZoned ) > 0.0f
		|| input.ButtonIsPressed( EPlayerActions::MoveLeft )
		|| input.ButtonIsPressed( EPlayerActions::MoveRight ) )
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetWalkingPlayerMovementState();
	}

	// Move the player left with the d-pad
	if( input.ButtonIsPressed( EPlayerActions::MoveLeft ) )
	{
		SetControlForceDirectionX( -1.0f );
		player.SetIsInputInactive( 0.0f );
	}

	// Move the player right with the d-pad
	if( input.ButtonIsPressed( EPlayerActions::MoveRight ) )
	{
		SetControlForceDirectionX( 1.0f );
		player.SetIsInputInactive( 0.0f );
	}

	//Crouch
	if( input.ButtonHasJustBeenPressed( EPlayerActions::Crouch ) )
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetCrouchingPlayerMovementState();
	}

	//If player hacking is interrupted or finished, exit the hacking state to idle movement state.
	//
	//if( !player.GetPlayerIsHacking() )
	//{
	//	return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
	//}
	
	//Jump
	if( input.ButtonHasJustBeenPressed( EPlayerActions::Jump ) )
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetJumpingPlayerMovementState();
	}

	//When hacking button is released, exit to idle standing state.
	if ( input.ButtonHasJustBeenReleased(EPlayerActions::Hack))
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->GetIdleStandingPlayerMovementState();
	}

	return nullptr;
}

const char* CHackingState::VGetAnimationName() const
{
	return mk_pszAnim_DanielleHacking;
}

const char* CHackingState::VGetAnimationName()
{
	return mk_pszAnim_DanielleHacking;
}

const char* CHackingState::VGetPhysicsShapeName() const
{
	return mk_pszPhys_DanielleHacking;
}

void CHackingState::CleanupSoundEffects()
{
	
}