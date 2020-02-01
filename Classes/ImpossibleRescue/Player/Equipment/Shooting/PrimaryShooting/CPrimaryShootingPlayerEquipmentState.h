//Name of class:	CPrimaryShootingPlayerEquipmentState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player's primary weapon type
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#ifndef	_CPRIMARYSHOOTINGPLAYEREQUIPMENTSTATE_H_
#define	_CPRIMARYSHOOTINGPLAYEREQUIPMENTSTATE_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "../../CPlayerEquipmentState.h"

class CPrimaryShootingPlayerEquipmentState
	: public CPlayerEquipmentState
{
public:
	CPrimaryShootingPlayerEquipmentState() = delete;
	
	CPrimaryShootingPlayerEquipmentState(std::function<CPlayerPrimaryProjectileGroup*()> fnpGetProjectileGroup);

	virtual ~CPrimaryShootingPlayerEquipmentState() override;

	// Initialise the equipment state.
	virtual void VInitialise( ) override;
	
	//State beginning transition. Called once when player equipment state is set to this state.
	virtual void VEnter(CPlayer& player) override;

	//Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerEquipmentState* VUpdate(CPlayer& player) override;

	//Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerEquipmentState* VHandleInput(CPlayer& player, TGCController< EPlayerActions >& input) override;

private :
	std::function<CPlayerPrimaryProjectileGroup*()> m_fnpGetProjectileGroup;
	ISoundEffect* m_psfxWeaponSwitch;
};

#endif