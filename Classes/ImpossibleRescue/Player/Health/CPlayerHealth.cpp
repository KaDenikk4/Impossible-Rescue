#include "CPlayerHealth.h"
#include <algorithm>
#include "AppDelegate.h"

CPlayerHealth::CPlayerHealth( )
: m_MaxHealthPoints( 0 )
, m_CurrentHealthPoints( 0 )
, m_MaxLives( 0 )
, m_CurrentLives( 0 )
, m_aorLevelTransitionEventHandler( nullptr )
{
	m_aorLevelTransitionEventHandler = AppDelegate::GetEventMediator()->VSubscribeToLevelTransitionEvents(*this);
}

CPlayerHealth::~CPlayerHealth( )
{
	m_aorLevelTransitionEventHandler.Release();
}

// Initialise the player health
void CPlayerHealth::Initialise( )
{
	InitialiseHealthPoints();
	InitialiseLives();
}

// Accessor for the current player health points
int CPlayerHealth::GetCurrentHealthPoints( ) const
{
	return m_CurrentHealthPoints;
}

// Accessor for the max player health points
int CPlayerHealth::GetMaxHealthPoints( ) const
{
	return m_MaxHealthPoints;
}

// Add to current player health points
void CPlayerHealth::ReplenishHealthPoints( int iNumHealthPoints )
{
	//Set current health points to whichever is lesser, the maximum amount of health points or current health points after adding the additional health points
	m_CurrentHealthPoints = std::min(m_CurrentHealthPoints + iNumHealthPoints, m_MaxHealthPoints);
}

// Deduct from current player health points
void CPlayerHealth::DepleteHealthPoints( int iNumHealthPoints )
{
	//Set current health points to whichever is greater, 0 or current health points after subtracting health points
	m_CurrentHealthPoints = std::max(m_CurrentHealthPoints - iNumHealthPoints, 0);

	if( m_CurrentHealthPoints == 0 )
	{
		
		// Player has died
		DepleteALife();
		// Restart the level
	}
}

// Accessor for the current player lives
int CPlayerHealth::GetCurrentLives( ) const
{
	return m_CurrentLives;
}

// Accessor for the max player lives
int CPlayerHealth::GetMaxLives( ) const
{
	return m_MaxLives;
}

// Add a life to current player lives
void CPlayerHealth::ReplenishALife( )
{
	//Set current lives to whichever is lesser, the maximum amount of lives or current lives after adding a life
	m_CurrentLives = std::min(m_CurrentLives + 1, m_MaxLives);
}

// Remove a life from current player lives
void CPlayerHealth::DepleteALife( )
{
	//Set current lives to whichever is greater, 0 or current lives after subtracting a life
	m_CurrentLives = std::max(m_CurrentLives - 1, 0);


	// Player has died and should restart the level
	AppDelegate::GetEventMediator()->VPublishPlayerHasDiedEvent(CPlayerHasDiedEvent(m_CurrentLives));

	// Reset player health because new level is starting
	InitialiseHealthPoints();

	if(m_CurrentLives == 0)
	{
		//The act is restarting to reset the lives
		InitialiseLives();
	}	
}

// Initialise the player health points
void CPlayerHealth::InitialiseHealthPoints( )
{
	// For now just setting the player health points variables.
	// When game saves are implemented, should load data from disk.

	m_MaxHealthPoints = 1;
	m_CurrentHealthPoints = m_MaxHealthPoints;
}

void CPlayerHealth::VOnEventReceived( CLevelTransitionEvent eventArgs )
{
	if( ELevelTransitionType::NewGame ==  eventArgs.GetTransitionType(  ) )
	{
		Initialise();
	}
}

// Initialise the player lives
void CPlayerHealth::InitialiseLives( )
{
	// For now just setting the player lives variables.
	// When game saves are implemented, should load data from disk.
	
	m_MaxLives = 3;
	m_CurrentLives = m_MaxLives;
}
