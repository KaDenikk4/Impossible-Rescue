//Name of class:	CExperimentalAudioSystem
//Main author:		Toyan Green
//Summary:			This class is the audio system
//					in the game.
//Functions:		Initialise, PauseAllAudio, ResumeAllAudio,
//					PlaySoundEffect, PreloadSoundEffect,
//					GetSoundEffect

#ifndef	_CEXPERIMENTALAUDIOSYSTEM_H_
#define	_CEXPERIMENTALAUDIOSYSTEM_H_

#ifndef	_IAUDIOSYSTEM_H_
#include "IAudioSystem.h"
#endif

#include "AudioEngine.h"

#ifndef __COCOS2D_H__
#include "cocos2d.h"
#endif

#include <map>

USING_NS_CC;

class CExperimentalAudioSystem : public IAudioSystem
{
public:
	// This audio system implementation can only be created with a pointer to experimental::AudioEngine
	CExperimentalAudioSystem( ) = delete;
	CExperimentalAudioSystem( experimental::AudioEngine* pcAudioEngine );
	
	virtual ~CExperimentalAudioSystem( ) override;

	// Initialise the asset manager
	virtual void VInitialise( ) override;
	// Pause all audio in the game
	virtual void VPauseAllAudio( ) override;
	// Resume all audio in the game
	virtual void VResumeAllAudio( ) override;
	// Play a given sound effect
	virtual unsigned int VPlaySoundEffect( ESoundFX esfxSoundEffect, bool bLoop = false ) override;
	// Play a given sound effect (with volume option)
	virtual unsigned int VPlaySoundEffect( ESoundFX esfxSoundEffect, float fVolume = 1.0f, bool bLoop = false ) override;
	// Pause a given sound effect
	virtual void VPauseEffect( unsigned int iSoundId) override;
	// Resume a given sound effect
	virtual void VResumeEffect( unsigned int iSoundId) override;
	// Stop a given sound effect
	virtual void VStopEffect( unsigned int iSoundId) override;
	// Preload a sound effect using the file path
	virtual void VPreloadEffect( const char* sSoundFXFilePath) override;
	// Unload a sound effect using the file path
	virtual void VUnloadEffect( const char* sSoundFXFilePath) override;
	
private:

	experimental::AudioEngine* m_pcAudioEngine;
};

#endif
