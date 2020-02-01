//Name of class:	CAudioSystem
//Main author:		Toyan Green
//Summary:			This class is the audio system
//					in the game.
//Functions:		Initialise, PauseAllAudio, ResumeAllAudio,
//					PlaySoundEffect, PreloadSoundEffect,
//					GetSoundEffect, VPauseEffect, VResumeEffect,
//					VStopEffect

#ifndef	_CAUDIOSYSTEM_H_
#define	_CAUDIOSYSTEM_H_

#ifndef	_IAUDIOSYSTEM_H_
#include "IAudioSystem.h"
#endif

#include "SimpleAudioEngine.h"
#include <map>


class CAudioSystem : public IAudioSystem
{
public:
	// This audio system implementation can only be created with a pointer to CocosDenshion::SimpleAudioEngine
	CAudioSystem( ) = delete;
	CAudioSystem( CocosDenshion::SimpleAudioEngine* pcAudioEngine );

	virtual ~CAudioSystem( ) override;

	// Initialise the asset manager
	virtual void VInitialise( ) override;
	// Pause all audio in the game
	virtual void VPauseAllAudio( ) override;
	// Resume all audio in the game
	virtual void VResumeAllAudio( ) override;
	// Play a given sound effect
	virtual unsigned int VPlaySoundEffect( ESoundFX esfxSoundEffect, bool bLoop = false ) override;
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

	// Audio engine pointer
	CocosDenshion::SimpleAudioEngine* m_pcAudioEngine;
};

#endif
