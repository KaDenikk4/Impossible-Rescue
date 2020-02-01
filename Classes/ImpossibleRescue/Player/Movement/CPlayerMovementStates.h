//Name of class:	CPlayerMovementStates
//Main author:		Toyan Green
//Summary:			This class is responsible for storing player movement states that the player can use
//					in the game.

#ifndef	_CPLAYEMOVEMENTSTATES_H_
#define	_CPLAYEMOVEMENTSTATES_H_

#include "CPlayerMovementState.h"
#include "Crouching/CCrouchingPlayerMovementState.h"
#include "Walking/CWalkingPlayerMovementState.h"
#include "Jumping/CJumpingPlayerMovementState.h"
#include "JumpingCrouch/CJumpingCrouchPlayerMovementState.h"
#include "JumpingWalk/CJumpingWalkPlayerMovementState.h"
#include "IdleCrouching/CIdleCrouchingPlayerMovementState.h"
#include "IdleStanding/CIdleStandingPlayerMovementState.h"

class CPlayerMovementStates
{
	
public:
	CPlayerMovementStates();
	~CPlayerMovementStates();
	
	void Initialise( );

	CPlayerMovementState* GetCurrentPlayerMovementState() const;
	void SetCurrentPlayerMovementState(CPlayerMovementState* pNewPlayerMovementState);
	
	CCrouchingPlayerMovementState* GetCrouchingPlayerMovementState() const;
	CWalkingPlayerMovementState* GetWalkingPlayerMovementState() const;
	CJumpingPlayerMovementState* GetJumpingPlayerMovementState() const;
	CJumpingCrouchPlayerMovementState* GetJumpingCrouchPlayerMovementState() const;
	CJumpingWalkPlayerMovementState* GetJumpingWalkPlayerMovementState() const;
	CIdleStandingPlayerMovementState* GetIdleStandingPlayerMovementState( ) const;
	CIdleCrouchingPlayerMovementState* GetIdleCrouchingPlayerMovementState( ) const;

private:

	CPlayerMovementState* m_pcCurrentPlayerMovementState;
	
	CCrouchingPlayerMovementState* m_pcCrouchingPlayerMovementState;
	CWalkingPlayerMovementState* m_pcWalkingPlayerMovementState;
	CJumpingPlayerMovementState* m_pcJumpingPlayerMovementState;
	CJumpingCrouchPlayerMovementState* m_pcJumpingCrouchPlayerMovementState;
	CJumpingWalkPlayerMovementState* m_pcJumpingWalkPlayerMovementState;
	CIdleStandingPlayerMovementState* m_pcIdleStandingPlayerMovementState;
	CIdleCrouchingPlayerMovementState* m_pcIdleCrouchingPlayerMovementState;
};

inline CPlayerMovementStates::CPlayerMovementStates()
{
	m_pcCrouchingPlayerMovementState = new CCrouchingPlayerMovementState();
	m_pcWalkingPlayerMovementState = new CWalkingPlayerMovementState();
	m_pcJumpingPlayerMovementState = new CJumpingPlayerMovementState();
	m_pcJumpingCrouchPlayerMovementState = new CJumpingCrouchPlayerMovementState();
	m_pcJumpingWalkPlayerMovementState = new CJumpingWalkPlayerMovementState();
	m_pcIdleStandingPlayerMovementState = new CIdleStandingPlayerMovementState();
	m_pcIdleCrouchingPlayerMovementState = new CIdleCrouchingPlayerMovementState();
}

inline CPlayerMovementStates::~CPlayerMovementStates()
{
	if (m_pcCrouchingPlayerMovementState)
	{
		delete m_pcCrouchingPlayerMovementState;
		m_pcCrouchingPlayerMovementState = nullptr;
	}

	if (m_pcWalkingPlayerMovementState)
	{
		delete m_pcWalkingPlayerMovementState;
		m_pcWalkingPlayerMovementState = nullptr;
	}

	if (m_pcJumpingPlayerMovementState)
	{
		delete m_pcJumpingPlayerMovementState;
		m_pcJumpingPlayerMovementState = nullptr;
	}

	if (m_pcJumpingCrouchPlayerMovementState)
	{
		delete m_pcJumpingCrouchPlayerMovementState;
		m_pcJumpingCrouchPlayerMovementState = nullptr;
	}

	if (m_pcJumpingWalkPlayerMovementState)
	{
		delete m_pcJumpingWalkPlayerMovementState;
		m_pcJumpingWalkPlayerMovementState = nullptr;
	}

	if (m_pcIdleStandingPlayerMovementState)
	{
		delete m_pcIdleStandingPlayerMovementState;
		m_pcIdleStandingPlayerMovementState = nullptr;
	}

	if (m_pcIdleCrouchingPlayerMovementState)
	{
		delete m_pcIdleCrouchingPlayerMovementState;
		m_pcIdleCrouchingPlayerMovementState = nullptr;
	}
}

inline void CPlayerMovementStates::Initialise()
{
	SetCurrentPlayerMovementState(nullptr);

	m_pcCrouchingPlayerMovementState->VInitialise();
	m_pcWalkingPlayerMovementState->VInitialise();
	m_pcJumpingPlayerMovementState->VInitialise();
	m_pcJumpingCrouchPlayerMovementState->VInitialise();
	m_pcJumpingWalkPlayerMovementState->VInitialise();
	m_pcIdleStandingPlayerMovementState->VInitialise();
	m_pcIdleCrouchingPlayerMovementState->VInitialise();
}

inline CPlayerMovementState* CPlayerMovementStates::GetCurrentPlayerMovementState() const
{
	return m_pcCurrentPlayerMovementState;
}

inline void CPlayerMovementStates::SetCurrentPlayerMovementState(CPlayerMovementState* pNewPlayerMovementState)
{
	m_pcCurrentPlayerMovementState = pNewPlayerMovementState;
}

inline CCrouchingPlayerMovementState* CPlayerMovementStates::GetCrouchingPlayerMovementState() const
{
	return m_pcCrouchingPlayerMovementState;
}

inline CWalkingPlayerMovementState* CPlayerMovementStates::GetWalkingPlayerMovementState() const
{
	return m_pcWalkingPlayerMovementState;
}

inline CJumpingPlayerMovementState* CPlayerMovementStates::GetJumpingPlayerMovementState() const
{
	return m_pcJumpingPlayerMovementState;
}

inline CJumpingCrouchPlayerMovementState* CPlayerMovementStates::GetJumpingCrouchPlayerMovementState() const
{
	return m_pcJumpingCrouchPlayerMovementState;
}

inline CJumpingWalkPlayerMovementState* CPlayerMovementStates::GetJumpingWalkPlayerMovementState() const
{
	return m_pcJumpingWalkPlayerMovementState;
}

inline CIdleStandingPlayerMovementState* CPlayerMovementStates::GetIdleStandingPlayerMovementState() const
{
	return m_pcIdleStandingPlayerMovementState;
}

inline CIdleCrouchingPlayerMovementState* CPlayerMovementStates::GetIdleCrouchingPlayerMovementState() const
{
	return m_pcIdleCrouchingPlayerMovementState;
}

#endif