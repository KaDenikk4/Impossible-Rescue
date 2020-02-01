//Name of class:	CWalkingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player walking
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#ifndef	_CWALKINGPLAYERMOVEMENTSTATE_H_
#define	_CWALKINGPLAYERMOVEMENTSTATE_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "../CPlayerMovementState.h"

class CWalkingPlayerMovementState
	: public CPlayerMovementState
{
public:
	CWalkingPlayerMovementState();
	
	virtual ~CWalkingPlayerMovementState( ) override;
	
	// Initialise the movement state.
	virtual void VInitialise() override;

	//State beginning transition. Called once when player movement state is set to this state.
	virtual void VEnter(CPlayer& player) override;

	//state exit
	virtual void VExit(CPlayer& player) override;

	//Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VUpdate( CPlayer& player ) override;

	//Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VHandleInput( CPlayer& player, TGCController< EPlayerActions >& input ) override;

protected:

	virtual const char* VGetAnimationName() const override;
	virtual const char* VGetPhysicsShapeName() const override;

private:

	void CleanupSoundEffects();

	ISoundEffect* m_psfxWalking;
	const char*   mk_pszAnim_DanielleWalking        = "Walking";
	const char*   mk_pszPhys_DanielleJumpingWalking = "Danielle_Walking";
};

#endif