//Name of class:	CEventMediator
//Main author:		Toyan Green
//Summary:			This class is an the event system
//					in the game.
//Functions:		

#ifndef	_CEVENTMEDIATOR_H_
#define	_CEVENTMEDIATOR_H_

#ifndef _IEVENTMEDIATOR_H_
#include "IEventMediator.h"
#endif

#ifndef	_TNOTIFICATIONCHANNEL_H_
#include "TNotificationChannel.h"
#endif

class CEventMediator : public IEventMediator
{
public:

	~CEventMediator() override;

	virtual CActionOnRelease VSubscribeToGameWasPausedEvents( ITReceiveEvents<CGamePausedEvent>& gpeEventHandler ) override;
	virtual void VPublishGameWasPausedEvent( const CGamePausedEvent& gpeEvent ) override;

	virtual CActionOnRelease VSubscribeToGameWasResumedEvents( ITReceiveEvents<CGameResumedEvent>& gpeEventHandler) override;
	virtual void VPublishGameWasResumedEvent( const CGameResumedEvent& gpeEvent ) override;

	virtual CActionOnRelease VSubscribeToStationHackedEvents(ITReceiveEvents<CStationHackedEvent>& sheEventHandler) override;
	virtual void VPublishStationHackedEvent(const CStationHackedEvent& sheEvent) override;

	virtual CActionOnRelease VSubscribeToLevelTransitionEvents( ITReceiveEvents<CLevelTransitionEvent>& lteEventHandler ) override;
	virtual void VPublishLevelTransitionEvent( const CLevelTransitionEvent& lteEvent ) override;

	virtual CActionOnRelease VSubscribeToPlayerHasDiedEvents( ITReceiveEvents<CPlayerHasDiedEvent>& phdEventHandler ) override;
	virtual void VPublishPlayerHasDiedEvent( const CPlayerHasDiedEvent& phdEvent ) override;

	virtual CActionOnRelease VSubscribeToPlayBackgroundMusicEvents(	ITReceiveEvents<CPlayBackgroundMusicEvent>& pbmEventHandler ) override;
	virtual void VPublishPlayBackgroundMusicEvent( const CPlayBackgroundMusicEvent& pbmEvent ) override;
	
private:
	TNotificationChannel<CGamePausedEvent> m_GamePausedNotificationChannel;
	TNotificationChannel<CGameResumedEvent> m_GameResumedNotificationChannel;
	TNotificationChannel<CStationHackedEvent> m_StationHackedNotificationChannel;
	TNotificationChannel<CLevelTransitionEvent> m_LevelTransitionNotificationChannel;
	TNotificationChannel<CPlayerHasDiedEvent> m_PlayerHasDiedNotificationChannel;
	TNotificationChannel<CPlayBackgroundMusicEvent> m_PlayBackgroundMusicNotificationChannel;
};

#endif