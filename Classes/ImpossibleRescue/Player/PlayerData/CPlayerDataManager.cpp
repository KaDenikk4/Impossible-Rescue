#include "CPlayerDataManager.h"
#include "ImpossibleRescue/Player/Movement/CPlayerMovementStates.h"
#include "ImpossibleRescue/Player/Equipment/CPlayerEquipmentStates.h"

CPlayerDataManager::~CPlayerDataManager( )
{
	DestroyPlayerData();
	DestroyPlayerMovementStates();
	DestroyPlayerEquipmentStates();
}

// Initialise the player data manager
void CPlayerDataManager::Initialise( )
{
	InitialisePlayerData();
	InitialisePlayerMovementStates();
	InitialisePlayerEquipmentStates();
}

// Accessor for the current player data
CPlayerData* CPlayerDataManager::GetPlayerData( ) const
{
	return m_pcPlayerData;
}

// Accessor for the available player movement states
CPlayerMovementStates* CPlayerDataManager::GetPlayerMovementStates( ) const
{
	return m_pcPlayerMovementStates;
}

// Accessor for the available player equipment states
CPlayerEquipmentStates* CPlayerDataManager::GetPlayerEquipmentStates( ) const
{
	return m_pcPlayerEquipmentStates;
}

// Set the player projectile groups used for shooting mechanic (Must be called in each scene)
void CPlayerDataManager::SetProjectileGroups( CPlayerPrimaryProjectileGroup* pcPrimaryProjectileGroup,
	CPlayerSecondaryProjectileGroup* pcSecondaryProjectileGroup )
{
	m_pcPlayerPrimaryProjectileGroup   = pcPrimaryProjectileGroup;
	m_pcPlayerSecondaryProjectileGroup = pcSecondaryProjectileGroup;
}

// Destroy the available player data
void CPlayerDataManager::InitialisePlayerData( )
{
	// Clean up existing player data if there is any
	//DestroyPlayerData();
	
	// For now just creating a new player state object.
	// When game saves are implemented, should load data from disk
	m_pcPlayerData = new CPlayerData();
	m_pcPlayerData->Initialise();
}

// Destroy the available player data
void CPlayerDataManager::DestroyPlayerData( )
{
	if(m_pcPlayerData)
	{
		delete m_pcPlayerData;
		m_pcPlayerData = nullptr;
	}
}

// Initialise the available player movement states
void CPlayerDataManager::InitialisePlayerMovementStates( )
{
	// Clean up existing states if there are any
	DestroyPlayerMovementStates();

	m_pcPlayerMovementStates = new CPlayerMovementStates();
	m_pcPlayerMovementStates->Initialise();
}

// Destroy the available player movement states
void CPlayerDataManager::DestroyPlayerMovementStates( )
{
	if (m_pcPlayerMovementStates)
	{
		delete m_pcPlayerMovementStates;
		m_pcPlayerMovementStates = nullptr;
	}
}

// Initialise the available player equipment states
void CPlayerDataManager::InitialisePlayerEquipmentStates( )
{
	// Clean up existing states if there are any
	DestroyPlayerEquipmentStates();
	
	// Initialise the equipment states, with a mechanism to get the projectile groups when they are needed
	m_pcPlayerEquipmentStates = new CPlayerEquipmentStates([&]() -> CPlayerPrimaryProjectileGroup* { return m_pcPlayerPrimaryProjectileGroup; }
	, [&]() -> CPlayerSecondaryProjectileGroup* { return m_pcPlayerSecondaryProjectileGroup; });
	m_pcPlayerEquipmentStates->Initialise();
}

// Destroy the available player equipment states
void CPlayerDataManager::DestroyPlayerEquipmentStates( )
{
	if (m_pcPlayerEquipmentStates)
	{
		delete m_pcPlayerEquipmentStates;
		m_pcPlayerEquipmentStates = nullptr;
	}
}
