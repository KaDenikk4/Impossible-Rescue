#include "CEventMediator.h"

CEventMediator::~CEventMediator( )
{
}

CActionOnRelease CEventMediator::VSubscribeToGameWasPausedEvents( ITReceiveEvents<CGamePausedEvent>& gpeEventHandler)
{
	return m_GamePausedNotificationChannel.AddSubscriber(gpeEventHandler);
}

void CEventMediator::VPublishGameWasPausedEvent( const CGamePausedEvent& gpeEvent )
{
	m_GamePausedNotificationChannel.PublishEvent(gpeEvent);
}

CActionOnRelease CEventMediator::VSubscribeToGameWasResumedEvents( ITReceiveEvents<CGameResumedEvent>& gpeEventHandler )
{
	return m_GameResumedNotificationChannel.AddSubscriber(gpeEventHandler);
}

void CEventMediator::VPublishGameWasResumedEvent( const CGameResumedEvent& gpeEvent )
{
	m_GameResumedNotificationChannel.PublishEvent(gpeEvent);
}

CActionOnRelease CEventMediator::VSubscribeToStationHackedEvents( ITReceiveEvents<CStationHackedEvent>& sheEventHandler )
{
	return m_StationHackedNotificationChannel.AddSubscriber(sheEventHandler);
}

void CEventMediator::VPublishStationHackedEvent( const CStationHackedEvent& sheEvent )
{
	m_StationHackedNotificationChannel.PublishEvent(sheEvent);
}

CActionOnRelease CEventMediator::VSubscribeToLevelTransitionEvents(	ITReceiveEvents<CLevelTransitionEvent>& lteEventHandler )
{
	return m_LevelTransitionNotificationChannel.AddSubscriber( lteEventHandler );
}

void CEventMediator::VPublishLevelTransitionEvent( const CLevelTransitionEvent& lteEvent )
{
	m_LevelTransitionNotificationChannel.PublishEvent(lteEvent);
}

CActionOnRelease CEventMediator::VSubscribeToPlayerHasDiedEvents( ITReceiveEvents<CPlayerHasDiedEvent>& phdEventHandler )
{
	return m_PlayerHasDiedNotificationChannel.AddSubscriber(phdEventHandler);
}

void CEventMediator::VPublishPlayerHasDiedEvent( const CPlayerHasDiedEvent& phdEvent )
{
	m_PlayerHasDiedNotificationChannel.PublishEvent(phdEvent);
}

CActionOnRelease CEventMediator::VSubscribeToPlayBackgroundMusicEvents(	ITReceiveEvents<CPlayBackgroundMusicEvent>& pbmEventHandler )
{
	return m_PlayBackgroundMusicNotificationChannel.AddSubscriber(pbmEventHandler);
}

void CEventMediator::VPublishPlayBackgroundMusicEvent( const CPlayBackgroundMusicEvent& pbmEvent )
{
	m_PlayBackgroundMusicNotificationChannel.PublishEvent(pbmEvent);
}
