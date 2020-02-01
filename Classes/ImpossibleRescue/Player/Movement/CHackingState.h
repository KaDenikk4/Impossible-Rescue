//Name of class:	CHackingState
//Summary:			This class is not used in the game. When plugged in to the player, it
//					would put him in the HackingState, which would allow hacking, hacking animation and
//					hacking physics body to be applied to the player. At the time of final build, animation
//					didn't align, so this class was never used.
//Functions:		VInitialise, VEnter, VExit, VUpdate, VHandleInput, VGetAnimationName,
//					VGetAnimationName, VGetPhysicsShapeName, CleanupSoundEffects

#ifndef  _CHACKING_STATE_H_
#define  _CHACKING_STATE_H_

#include "ImpossibleRescue/Player/Movement/CPlayerMovementState.h"

class CHackingState :
	public CPlayerMovementState
{
public:
	CHackingState();
	virtual ~CHackingState();

	// Initialise the movement state.
	virtual void VInitialise() override;

	//State beginning transition. Called once when player movement state is set to this state.
	virtual void VEnter( CPlayer& player ) override;

	//state exit
	virtual void VExit( CPlayer& player ) override;

	//Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VUpdate( CPlayer& player ) override;

	//Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VHandleInput( CPlayer& player, TGCController< EPlayerActions >& input ) override;

	virtual const char* VGetAnimationName();

protected:

	virtual const char* VGetAnimationName() const override;
	virtual const char* VGetPhysicsShapeName() const override;

private:

	void CleanupSoundEffects();

	const char*   mk_pszAnim_DanielleHacking = "Hacking";
	const char*   mk_pszPhys_DanielleHacking = "Danielle_Idle_Standing";
};

#endif // end of _CHACKING_STATE_H_