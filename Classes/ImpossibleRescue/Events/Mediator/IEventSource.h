//Name of class:	IEventSource
//Main author:		Toyan Green
//Summary:			This class is an interface for subscribing to the event system
//					in the game.
//Functions:		VSubscribeToGameWasPausedEvent

#ifndef	_IEVENTSOURCE_H_
#define	_IEVENTSOURCE_H_

#ifndef	_ITRECEIVEEVENTS_H_
#include "ITReceiveEvents.h"
#endif

#ifndef	_CGAMEPAUSEDEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CGamePausedEvent.h"
#endif

#ifndef	_CGAMERESUMEDEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CGameResumedEvent.h"
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

#ifndef	_CACTIONONRELEASE_H_
#include "CActionOnRelease.h"
#endif

class IEventSource
{
public:
	virtual ~IEventSource( ) = default;
	virtual CActionOnRelease VSubscribeToGameWasPausedEvents( ITReceiveEvents<CGamePausedEvent>& gpeEventHandler) = 0;
	virtual CActionOnRelease VSubscribeToGameWasResumedEvents( ITReceiveEvents<CGameResumedEvent>& gpeEventHandler) = 0;
	virtual CActionOnRelease VSubscribeToStationHackedEvents( ITReceiveEvents<CStationHackedEvent>& sheEventHandler) = 0;
	virtual CActionOnRelease VSubscribeToLevelTransitionEvents( ITReceiveEvents<CLevelTransitionEvent>& lteEventHandler) = 0;
	virtual CActionOnRelease VSubscribeToPlayerHasDiedEvents( ITReceiveEvents<CPlayerHasDiedEvent>& phdEventHandler) = 0;
	virtual CActionOnRelease VSubscribeToPlayBackgroundMusicEvents( ITReceiveEvents<CPlayBackgroundMusicEvent>& pbmEventHandler) = 0;
};

#endif