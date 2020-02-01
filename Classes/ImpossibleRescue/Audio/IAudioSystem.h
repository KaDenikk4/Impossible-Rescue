//Name of class:	IAudioSystem
//Main author:		Toyan Green
//Summary:			This class is an interface for a the audio system
//					in the game.
//Functions:		Initialise, PauseAllAudio, ResumeAllAudio,
//					PlaySoundEffect, PreloadSoundEffect,
//					GetSoundEffect

#ifndef	_IAUDIOSYSTEM_H_
#define	_IAUDIOSYSTEM_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ISoundEffect.h"
#endif

#ifndef	_ESOUNDEFFECT_H_
#include "ESoundFX.h"
#endif

#ifndef	_CACTIONONRELEASE_H_
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#endif

class IAudioSystem
{
public:
	virtual ~IAudioSystem( ) = default;
	virtual void VInitialise() = 0;
	virtual void VPauseAllAudio() = 0;
	virtual void VResumeAllAudio() = 0;
	virtual unsigned int VPlaySoundEffect( ESoundFX esfxSoundEffect, bool bLoop = false ) = 0;
	virtual unsigned int VPlaySoundEffect(ESoundFX esfxSoundEffect, float fVolume = 1.0f, bool bLoop = false) = 0;
	virtual void VPauseEffect( unsigned int iSoundId) = 0;
	virtual void VResumeEffect( unsigned int iSoundId) = 0;
	virtual void VStopEffect( unsigned int iSoundId) = 0;
	virtual void VPreloadEffect( const char* sSoundFXFilePath) = 0;
	virtual void VUnloadEffect( const char* sSoundFXFilePath) = 0;
};

#endif



