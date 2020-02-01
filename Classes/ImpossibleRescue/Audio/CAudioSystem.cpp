#include "CAudioSystem.h"
#include "SimpleAudioEngine.h"
#include "ImpossibleRescue/AssetManager/CAssetManager.h"

// This audio system implementation can only be created with a pointer to CocosDenshion::SimpleAudioEngine
CAudioSystem::CAudioSystem( CocosDenshion::SimpleAudioEngine* pcAudioEngine )
	: m_pcAudioEngine(pcAudioEngine)
{
}

CAudioSystem::~CAudioSystem( )
{
	CocosDenshion::SimpleAudioEngine::end();
}

// Initialise the asset manager
void CAudioSystem::VInitialise( )
{
}

// Pause all audio in the game
void CAudioSystem::VPauseAllAudio( )
{
	m_pcAudioEngine->pauseAllEffects();
	// ToDo pause music when background music is added
}

// Resume all audio in the game
void CAudioSystem::VResumeAllAudio( )
{
	m_pcAudioEngine->resumeAllEffects();
	// ToDo resume music when background music is added
}

// Play a given sound effect
unsigned int CAudioSystem::VPlaySoundEffect( ESoundFX esfxSoundEffect, bool bLoop )
{
	// Get sound effect file path from map using enum
	const char* sSoundFXFilePath = IAssetManager::GetSoundEffectFilePath( esfxSoundEffect );

	return m_pcAudioEngine->playEffect( sSoundFXFilePath, bLoop );
}

// Pause a given sound effect
void CAudioSystem::VPauseEffect( unsigned int iSoundId )
{
	m_pcAudioEngine->pauseEffect( iSoundId );
}

// Resume a given sound effect
void CAudioSystem::VResumeEffect( unsigned int iSoundId)
{
	m_pcAudioEngine->resumeEffect(iSoundId);
}

// Stop a given sound effect
void CAudioSystem::VStopEffect( unsigned int iSoundId)
{
	m_pcAudioEngine->stopEffect(iSoundId);
}

// Preload a sound effect using the file path
void CAudioSystem::VPreloadEffect( const char* sSoundFXFilePath)
{
	m_pcAudioEngine->preloadEffect(sSoundFXFilePath);
}

// Unload a sound effect using the file path
void CAudioSystem::VUnloadEffect( const char* sSoundFXFilePath)
{
	m_pcAudioEngine->unloadEffect(sSoundFXFilePath);
}
