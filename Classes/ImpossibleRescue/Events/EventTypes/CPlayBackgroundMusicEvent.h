//Name of class:	CPlayBackgroundMusicEvent
//Main author:		Toyan Green
//Summary:			This class is used to broadcast a message that background music should be played
//					in the game.
//
//Functions:		GetBackgroundMusicType					

#ifndef	_CPLAYBACKGROUNDMUSICEVENT_H_
#define	_CPLAYBACKGROUNDMUSICEVENT_H_

#include "ImpossibleRescue/Audio/ESoundFX.h"

class CPlayBackgroundMusicEvent
{
public:

	CPlayBackgroundMusicEvent() = delete;
	CPlayBackgroundMusicEvent(ESoundFX eSoundFX);
	~CPlayBackgroundMusicEvent();
	ESoundFX GetBackgroundMusicType() const;

private:
	ESoundFX m_eSoundFX;
};

inline CPlayBackgroundMusicEvent::CPlayBackgroundMusicEvent(ESoundFX eSoundFX)
	: m_eSoundFX(eSoundFX)
{
}

inline CPlayBackgroundMusicEvent::~CPlayBackgroundMusicEvent()
{
}

inline ESoundFX CPlayBackgroundMusicEvent::GetBackgroundMusicType() const
{
	return m_eSoundFX;
}

#endif

