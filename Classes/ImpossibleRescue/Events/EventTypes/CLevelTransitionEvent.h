//Name of class:	CLevelTransitionEvent
//Main author:		Toyan Green
//Summary:			This class is used to broadcast a message that the a different level scene should be loaded
//					in the game.

#ifndef	_CLEVELTRANSITIONEVENT_H_
#define	_CLEVELTRANSITIONEVENT_H_

#ifndef	_ELEVELTRANSITIONTYPE_H_
#include "ImpossibleRescue/Levels/ELevelTransitionType.h"
#endif

class CLevelTransitionEvent
{
public:

	CLevelTransitionEvent() = delete;
	
	CLevelTransitionEvent(ELevelTransitionType levelTransitionType)
	{
		m_eLevelTransitionType = levelTransitionType;
	}

	ELevelTransitionType GetTransitionType() const;

private:
	ELevelTransitionType m_eLevelTransitionType;
};

inline ELevelTransitionType CLevelTransitionEvent::GetTransitionType() const
{
	return m_eLevelTransitionType;
}

#endif