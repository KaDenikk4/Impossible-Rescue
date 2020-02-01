//Name of class:	CDoubleJumpingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player double jumping
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput, DoJump

#ifndef	_CDOUBLEJUMPINGPLAYERMOVEMENTSTATE_H_
#define	_CDOUBLEJUMPINGPLAYERMOVEMENTSTATE_H_

#include "../CPlayerMovementState.h"

class CDoubleJumpingPlayerMovementState
	: public CPlayerMovementState
{
public:
	CDoubleJumpingPlayerMovementState();

	virtual ~CDoubleJumpingPlayerMovementState() override;

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

	//Make the player jump
	void DoJump(CPlayer& player);

	const char*   mk_pszAnim_DanielleJumping = "DoubleJumping";
	const char*   mk_pszPhys_DanielleJumping = "Danielle_DoubleJumping";
};

#endif
