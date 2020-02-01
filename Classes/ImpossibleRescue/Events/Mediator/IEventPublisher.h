//Name of class:	IEventPublisher
//Main author:		Toyan Green
//Summary:			This class is an interface for publishing to the event system
//					in the game.
//Functions:		VPublishGameWasPausedEvent

#ifndef	_IEVENTPUBLISHER_H_
#define	_IEVENTPUBLISHER_H_

#ifndef	_CGAMEPAUSEDEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CGamePausedEvent.h"
#endif

#ifndef	_CSTATIONHACKEDEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"
#endif

#ifndef	_CLEVELTRANSITIONEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CLevelTransitionEvent.h"
#endif

#ifndef	_CPLAYERHASDIEDEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CPlayerHasDiedEvent.h"
#endif

#ifndef _CPLAYBACKGROUNDMUSICEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CPlayBackgroundMusicEvent.h"
#endif


class IEventPublisher
{
public:
	virtual ~IEventPublisher( ) = default;
	virtual void VPublishGameWasPausedEvent(const CGamePausedEvent& gpeEvent) = 0;
	virtual void VPublishGameWasResumedEvent(const CGameResumedEvent& gpeEvent) = 0;
	virtual void VPublishStationHackedEvent(const CStationHackedEvent& sheEvent) = 0;
	virtual void VPublishLevelTransitionEvent(const CLevelTransitionEvent& lteEvent) = 0;
	virtual void VPublishPlayerHasDiedEvent(const CPlayerHasDiedEvent& phdEvent) = 0;
	virtual void VPublishPlayBackgroundMusicEvent(const CPlayBackgroundMusicEvent& pbmEvent) = 0;
};

#endif