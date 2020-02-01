//Name of class:	CJumpingWalkPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player walking whilst jumping
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#ifndef	_CJUMPINGWALKPLAYERMOVEMENTSTATE_H_
#define	_CJUMPINGWALKPLAYERMOVEMENTSTATE_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "../CPlayerMovementState.h"

class CJumpingWalkPlayerMovementState
	: public CPlayerMovementState
{
public:
	CJumpingWalkPlayerMovementState();

	virtual ~CJumpingWalkPlayerMovementState() override;

	// Initialise the movement state.
	virtual void VInitialise() override;

	//State beginning transition. Called once when player movement state is set to this state.
	virtual void VEnter(CPlayer& player) override;

	//Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VUpdate(CPlayer& player) override;

	//Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VHandleInput(CPlayer& player, TGCController< EPlayerActions >& input) override;

protected:

	virtual const char* VGetAnimationName() const override;
	virtual const char* VGetPhysicsShapeName() const override;

private:
	
	const char* mk_pszAnim_DanielleJumpingWalking = "JumpingWalk";
	const char* mk_pszPhys_DanielleJumpingWalking = "Danielle_Jumping_Walk";
};

#endif