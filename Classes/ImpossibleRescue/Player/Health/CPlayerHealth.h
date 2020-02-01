//Name of class:	CPlayerHealth
//Main author:		Toyan Green
//Summary:			This class is responsible for the player health system
//					in the game.
//Functions:		Initialise, GetCurrentHealthPoints, GetMaxHealthPoints
//					, ReplenishHealthPoints, DepleteHealthPoints
//					, GetCurrentLives, GetMaxLives, ReplenishALife,
//					, DepleteALife, InitialiseHealthPoints, InitialiseLives

#ifndef	_CPLAYERHEALTH_H_
#define	_CPLAYERHEALTH_H_
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Events/EventTypes/CLevelTransitionEvent.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"

class CPlayerHealth : ITReceiveEvents<CLevelTransitionEvent>
{
public:
	CPlayerHealth();
	~CPlayerHealth();

	// Initialise the player health
	void Initialise( );

	// Accessor for the current player health points
	int GetCurrentHealthPoints() const;
	// Accessor for the max player health points
	int GetMaxHealthPoints() const;
	// Add to current player health points
	void ReplenishHealthPoints(int iNumHealthPoints);
	// Deduct from current player health points
	void DepleteHealthPoints(int iNumHealthPoints);

	// Accessor for the current player lives
	int GetCurrentLives() const;
	// Accessor for the max player lives
	int GetMaxLives() const;
	// Add a life to current player lives
	void ReplenishALife();
	// Remove a life from current player lives
	void DepleteALife();

	// Initialise the player health points
	void InitialiseHealthPoints();

	virtual void VOnEventReceived(CLevelTransitionEvent eventArgs) override;
	
private:


	// Initialise the player lives
	void InitialiseLives();

private:
	int m_MaxHealthPoints; // Maximum number of health points the player can have
	int m_CurrentHealthPoints; // Current number of health points the player has
	int m_MaxLives; // Maximum number of lives the player can have
	int m_CurrentLives; // Current number of lives the player has

	CActionOnRelease m_aorLevelTransitionEventHandler;
};

#endif