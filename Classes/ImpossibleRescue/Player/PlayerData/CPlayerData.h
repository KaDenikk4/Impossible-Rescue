//Name of class:	CPlayerData
//Main author:		Toyan Green
//Summary:			This class is responsible for storing the player state data
//					in the game.
//Functions:		Initialise, GetPlayerHealth, InitialisePlayerHealth
//					DestroyPlayerHealth

#ifndef	_CPLAYERDATA_H_
#define	_CPLAYERDATA_H_

#include "ImpossibleRescue/Player/Health/CPlayerHealth.h"
#include "LevelTransitionData/CPlayerLevelTransitionData.h"

class CPlayerData
{
public:
	CPlayerData() = default;
	~CPlayerData();

	// Initialise the player data (Called at the start of the game)
	void Initialise();

	// Accessor for player player health
	CPlayerHealth* GetPlayerHealth() const;
	CPlayerLevelTransitionData* GetPlayerLevelTransitionData() const;

private:
	
	// Initialise the available player health
	void InitialisePlayerHealth();
	// Destroy the available player health
	void DestroyPlayerHealth();

	// Initialise the available player transition data
	void InitialisePlayerLevelTransitionData();
	// Destroy the available player transition data
	void DestroyPlayerLevelTransitionData();
	
	CPlayerHealth* m_pcPlayerHealth; // Player health
	
	CPlayerLevelTransitionData* m_pcPlayerLevelTransitionData; // Player transition data for moving between level areas
};

#endif