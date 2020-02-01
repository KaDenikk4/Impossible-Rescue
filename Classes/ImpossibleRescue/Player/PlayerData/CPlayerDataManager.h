//Name of class:	CPlayerDataManager
//Main author:		Toyan Green
//Summary:			This class is responsible for managing the player data and states
//					in the game.
//Functions:		Initialise, GetPlayerData, GetPlayerMovementStates, GetPlayerEquipmentStates
//					, SetProjectileGroups, InitialisePlayerData, DestroyPlayerData, InitialisePlayerMovementStates
//					, DestroyPlayerMovementStates, InitialisePlayerEquipmentStates, DestroyPlayerEquipmentStates

#ifndef	_CPLAYERDATAMANAGER_H_
#define	_CPLAYERDATAMANAGER_H_

#include "CPlayerData.h"
#include "ImpossibleRescue/Player/Equipment/Shooting/PrimaryShooting/CPlayerPrimaryProjectileGroup.h"
#include "ImpossibleRescue/Player/Equipment/Shooting/SecondaryShooting/CPlayerSecondaryProjectileGroup.h"

class CPlayerMovementStates;
class CPlayerEquipmentStates;

class CPlayerDataManager
{
public:

	CPlayerDataManager( ) = default;
	~CPlayerDataManager();
	
	// Initialise the player data manager
	void Initialise( );
	// Accessor for the current player data
	CPlayerData* GetPlayerData( ) const;
	// Accessor for the available player movement states
	CPlayerMovementStates* GetPlayerMovementStates() const;
	// Accessor for the available player equipment states
	CPlayerEquipmentStates* GetPlayerEquipmentStates() const;
	// Set the player projectile groups used for shooting mechanic (Must be called in each scene)
	void SetProjectileGroups(CPlayerPrimaryProjectileGroup* pcPrimaryProjectileGroup, CPlayerSecondaryProjectileGroup* pcSecondaryProjectileGroup);
	
private:
	
	// Initialise the available player data
	void InitialisePlayerData();
	// Destroy the available player data
	void DestroyPlayerData();
	// Initialise the available player movement states
	void InitialisePlayerMovementStates();
	// Destroy the available player movement states
	void DestroyPlayerMovementStates();
	// Initialise the available player equipment states
	void InitialisePlayerEquipmentStates();
	// Destroy the available player equipment states
	void DestroyPlayerEquipmentStates();


	// Player data
	CPlayerData*                     m_pcPlayerData;
	// Primary ammo object pool
	CPlayerPrimaryProjectileGroup*   m_pcPlayerPrimaryProjectileGroup;
	// Secondary ammo object pool
	CPlayerSecondaryProjectileGroup* m_pcPlayerSecondaryProjectileGroup;
	// Available player equipment states (Primary / Secondary shooting)
	CPlayerEquipmentStates* m_pcPlayerEquipmentStates;
	// Available player movement states (Walking, Jumping, etc.)
	CPlayerMovementStates*  m_pcPlayerMovementStates;
};

#endif