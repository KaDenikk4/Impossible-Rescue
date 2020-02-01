//Name of class:	CPlayerEquipmentState
//Main author:		Toyan Green
//Summary:			This class is the base class for all player equipment states
//					in the game.
//Functions:		VInitialise, VEnter, VUpdate, VHandleInput

#ifndef	_CPLAYEREQUIPMENTSTATE_H_
#define	_CPLAYEREQUIPMENTSTATE_H_

#include "../EPlayerActions.h"
#include "../CPlayer.h"
#include "GamerCamp/GameController/GCController.h"

class CPlayer;

class CPlayerEquipmentState
{
public:
	virtual ~CPlayerEquipmentState() { }

	// Initialise the equipment state.
	virtual void VInitialise() { };
	
	//State beginning transition. Called once when player equipment state is set to this state.
	virtual void VEnter(CPlayer& player) { };
	
	//Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerEquipmentState* VUpdate(CPlayer& player) { return nullptr; }
	
	//Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerEquipmentState* VHandleInput(CPlayer& player, TGCController<EPlayerActions>& input) { return nullptr; }

	cocos2d::Vec2 GetPlayerProjectileOffset() const
	{
		return mk_v2ProjectileOffset;
	}

	float GetPlayerBulletSpeed() const
	{
		return mk_fPlayerBulletSpeed;
	}

private:
	// (player width / 2) + (projectile width / 2) = 66
	const cocos2d::Vec2 mk_v2ProjectileOffset = cocos2d::Vec2(116.0f, 26.0f);
	const float mk_fPlayerBulletSpeed = 90.0f;
};

#endif