#include "CPlayerData.h"

CPlayerData::~CPlayerData( )
{
	DestroyPlayerHealth();
}

// Initialise the player data (Called at the start of the game)
void CPlayerData::Initialise( )
{
	InitialisePlayerHealth();
	InitialisePlayerLevelTransitionData();
}

// Accessor for player player health
CPlayerHealth* CPlayerData::GetPlayerHealth( ) const
{
	return m_pcPlayerHealth;
}

CPlayerLevelTransitionData* CPlayerData::GetPlayerLevelTransitionData( ) const
{
	return m_pcPlayerLevelTransitionData;
}

// Initialise the available player health
void CPlayerData::InitialisePlayerHealth( )
{
	// For now just creating a new player health object.
	// When game saves are implemented, should load data from disk
	m_pcPlayerHealth = new CPlayerHealth();
	m_pcPlayerHealth->Initialise();
}

// Destroy the available player health
void CPlayerData::DestroyPlayerHealth( )
{
	if( m_pcPlayerHealth )
	{
		delete m_pcPlayerHealth;
		m_pcPlayerHealth = nullptr;
	}
}

void CPlayerData::InitialisePlayerLevelTransitionData( )
{
	m_pcPlayerLevelTransitionData = new CPlayerLevelTransitionData();
	m_pcPlayerLevelTransitionData->Initialise();
}

void CPlayerData::DestroyPlayerLevelTransitionData( )
{
	if (m_pcPlayerLevelTransitionData)
	{
		delete m_pcPlayerLevelTransitionData;
		m_pcPlayerLevelTransitionData = nullptr;
	}
}
