//Name of class:	CPlayerEquipmentStates
//Main author:		Toyan Green
//Summary:			This class is responsible for storing player equipment states that the player can use
//					in the game.

#ifndef	_CPLAYEREQUIPMENTSTATES_H_
#define	_CPLAYEREQUIPMENTSTATES_H_

#include "../Equipment/Shooting/PrimaryShooting/CPlayerPrimaryProjectileGroup.h"
#include "../Equipment/Shooting/PrimaryShooting/CPrimaryShootingPlayerEquipmentState.h"
#include "../Equipment/Shooting/SecondaryShooting/CPlayerSecondaryProjectileGroup.h"
#include "../Equipment/Shooting/SecondaryShooting/CSecondaryShootingPlayerEquipmentState.h"

class CPlayerEquipmentState;
class CPlayerPrimaryProjectileGroup;
class CPlayerSecondaryProjectileGroup;
class CPrimaryShootingPlayerEquipmentState;
class CSecondaryShootingPlayerEquipmentState;

class CPlayerEquipmentStates
{
	
public:
	CPlayerEquipmentStates() = delete;
	CPlayerEquipmentStates(std::function< CPlayerPrimaryProjectileGroup*() > fnpGetPrimaryProjectileGroup, std::function< CPlayerSecondaryProjectileGroup*() > fnpGetSecondaryProjectileGroup);
	~CPlayerEquipmentStates();
	void Initialise( );

	CPlayerEquipmentState* GetCurrentPlayerEquipmentState() const;
	void SetCurrentPlayerEquipmentState(CPlayerEquipmentState* pNewPlayerEquipmentState);

	// No need for 2 ammo types with cut scope so ammo type is disabled
	// CPrimaryShootingPlayerEquipmentState* GetPrimaryShootingPlayerEquipmentState() const;
	CSecondaryShootingPlayerEquipmentState* GetSecondaryShootingPlayerEquipmentState() const;

private:

	CPlayerEquipmentState* m_pcCurrentPlayerEquipmentState;
	
	CPrimaryShootingPlayerEquipmentState* m_pcPrimaryShootingPlayerEquipmentState;
	CSecondaryShootingPlayerEquipmentState* m_pcSecondaryShootingPlayerEquipmentState;
};

#endif