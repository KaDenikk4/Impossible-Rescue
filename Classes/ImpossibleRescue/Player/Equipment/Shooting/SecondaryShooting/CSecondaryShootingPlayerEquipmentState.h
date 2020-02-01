//Name of class:	CSecondaryShootingPlayerEquipmentState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player's secondary weapon type
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#ifndef	_CSECONDARYSHOOTINGPLAYEREQUIPMENTSTATE_H_
#define	_CSECONDARYSHOOTINGPLAYEREQUIPMENTSTATE_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "../../CPlayerEquipmentState.h"
#include "CPlayerSecondaryProjectileGroup.h"

class CPlayerSecondaryProjectileGroup;

class CSecondaryShootingPlayerEquipmentState
	: public CPlayerEquipmentState
{
public:
	CSecondaryShootingPlayerEquipmentState() = delete;
	
	CSecondaryShootingPlayerEquipmentState(std::function<CPlayerSecondaryProjectileGroup*()> pProjectileManager);

	virtual ~CSecondaryShootingPlayerEquipmentState() override;

	// Initialise the equipment state.
	virtual void VInitialise() override;
	
	//State beginning transition. Called once when player equipment state is set to this state.
	virtual void VEnter(CPlayer& player) override;

	//Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerEquipmentState* VUpdate(CPlayer& player) override;

	//Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerEquipmentState* VHandleInput(CPlayer& player, TGCController< EPlayerActions >& input) override;

private :
	std::function<CPlayerSecondaryProjectileGroup*()> m_fnpGetProjectileGroup;
	ISoundEffect* m_psfxPlayerShoot;
};

#endif