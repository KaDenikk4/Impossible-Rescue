//Name of class:	CPlayerEquipmentStates
//Main author:		Toyan Green
//Summary:			This class is responsible for storing player equipment states that the player can use
//					in the game.

#include "CPlayerEquipmentStates.h"

CPlayerEquipmentStates::CPlayerEquipmentStates( std::function<CPlayerPrimaryProjectileGroup*()> fnpGetPrimaryProjectileGroup,
	std::function<CPlayerSecondaryProjectileGroup*()> fnpGetSecondaryProjectileGroup)
{
	m_pcPrimaryShootingPlayerEquipmentState = new CPrimaryShootingPlayerEquipmentState(fnpGetPrimaryProjectileGroup);
	m_pcSecondaryShootingPlayerEquipmentState = new CSecondaryShootingPlayerEquipmentState(fnpGetSecondaryProjectileGroup);
}

CPlayerEquipmentStates::~CPlayerEquipmentStates( )
{
	if(m_pcPrimaryShootingPlayerEquipmentState)
	{
		delete m_pcPrimaryShootingPlayerEquipmentState;
		m_pcPrimaryShootingPlayerEquipmentState = nullptr;
	}

	if (m_pcSecondaryShootingPlayerEquipmentState)
	{
		delete m_pcSecondaryShootingPlayerEquipmentState;
		m_pcSecondaryShootingPlayerEquipmentState = nullptr;
	}
}

void CPlayerEquipmentStates::Initialise( )
{
	SetCurrentPlayerEquipmentState(nullptr);
	
	m_pcPrimaryShootingPlayerEquipmentState->VInitialise();
	m_pcSecondaryShootingPlayerEquipmentState->VInitialise();
}

CPlayerEquipmentState* CPlayerEquipmentStates::GetCurrentPlayerEquipmentState( ) const
{
	return m_pcCurrentPlayerEquipmentState;
}

void CPlayerEquipmentStates::SetCurrentPlayerEquipmentState( CPlayerEquipmentState* pNewPlayerEquipmentState )
{
	m_pcCurrentPlayerEquipmentState = pNewPlayerEquipmentState;
}

// No need for 2 ammo types with cut scope so ammo type is disabled
// CPrimaryShootingPlayerEquipmentState* CPlayerEquipmentStates::GetPrimaryShootingPlayerEquipmentState( ) const
// {
// 	return m_pcPrimaryShootingPlayerEquipmentState;
// }

CSecondaryShootingPlayerEquipmentState* CPlayerEquipmentStates::GetSecondaryShootingPlayerEquipmentState( ) const
{
	return m_pcSecondaryShootingPlayerEquipmentState;
}
