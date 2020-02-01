//Name of class:	CIdleStandingPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player idling whilst standing
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#ifndef	_CIDLESTANDINGPLAYERMOVEMENTSTATE_H_
#define	_CIDLESTANDINGPLAYERMOVEMENTSTATE_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "../CPlayerMovementState.h"

class CIdleStandingPlayerMovementState
	: public CPlayerMovementState
{
public:
	CIdleStandingPlayerMovementState();
	
	virtual ~CIdleStandingPlayerMovementState( ) override;

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

	ISoundEffect* m_psfxIdleStanding;
	const char*   mk_pszAnim_DanielleIdleStanding = "IdleStanding";
	const char*   mk_pszPhys_DanielleIdleStanding = "Danielle_Idle_Standing";
};

#endif