//Name of class:	CJumpingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player jumping
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput, DoJump

#ifndef	_CJUMPINGPLAYERMOVEMENTSTATE_H_
#define	_CJUMPINGPLAYERMOVEMENTSTATE_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "../CPlayerMovementState.h"

class CJumpingPlayerMovementState
	: public CPlayerMovementState
{
public:
	CJumpingPlayerMovementState();
	
	virtual ~CJumpingPlayerMovementState() override;

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
	virtual bool VGetIsAnimationLooping( ) override;
	
private:

	//Make the player jump
	void DoJump(CPlayer& player);

	void CleanupSoundEffects();

	ISoundEffect* m_psfxJumping;
	ISoundEffect* m_psfxCrouching;
	const char*   mk_pszAnim_DanielleJumping = "Jumping";
	const char*   mk_pszPhys_DanielleJumping = "Danielle_Jumping";
};

#endif