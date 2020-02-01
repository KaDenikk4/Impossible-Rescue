#include "CExperimentalAudioSystem.h"
#include "ImpossibleRescue/AssetManager/CAssetManager.h"

// This audio system implementation can only be created with a pointer to experimental::AudioEngine
CExperimentalAudioSystem::CExperimentalAudioSystem( experimental::AudioEngine* pcAudioEngine )
	: m_pcAudioEngine(pcAudioEngine)
{
}

CExperimentalAudioSystem::~CExperimentalAudioSystem( )
{
	//ToDo: During clean up the audio system is getting deleted twice, search and destroy (the bug).
	//m_pcAudioEngine->end();
}

// Initialise the asset manager
void CExperimentalAudioSystem::VInitialise( )
{
}

// Pause all audio in the game
void CExperimentalAudioSystem::VPauseAllAudio( )
{
	m_pcAudioEngine->pauseAll();
}

// Resume all audio in the game
void CExperimentalAudioSystem::VResumeAllAudio( )
{
	m_pcAudioEngine->resumeAll();
}

// Play a given sound effect
unsigned int CExperimentalAudioSystem::VPlaySoundEffect( ESoundFX esfxSoundEffect, bool bLoop )
{
	// Get sound effect file path from map using enum
	const char* sSoundFXFilePath = IAssetManager::GetSoundEffectFilePath( esfxSoundEffect );

	return m_pcAudioEngine->play2d( sSoundFXFilePath, bLoop );
}

// Play a given sound effect (with volume option)
unsigned CExperimentalAudioSystem::VPlaySoundEffect( ESoundFX esfxSoundEffect, float fVolume, bool bLoop )
{
	// Get sound effect file path from map using enum
	const char* sSoundFXFilePath = IAssetManager::GetSoundEffectFilePath(esfxSoundEffect);

	return m_pcAudioEngine->play2d(sSoundFXFilePath, bLoop, fVolume);
}

// Pause a given sound effect
void CExperimentalAudioSystem::VPauseEffect( unsigned int iSoundId )
{
	m_pcAudioEngine->pause( iSoundId );
}

// Resume a given sound effect
void CExperimentalAudioSystem::VResumeEffect( unsigned int iSoundId)
{
	m_pcAudioEngine->resume(iSoundId);
}

// Stop a given sound effect
void CExperimentalAudioSystem::VStopEffect( unsigned int iSoundId)
{
	m_pcAudioEngine->stop(iSoundId);
}

// Preload a sound effect using the file path
void CExperimentalAudioSystem::VPreloadEffect( const char* sSoundFXFilePath)
{
	m_pcAudioEngine->preload(sSoundFXFilePath);
}

// Unload a sound effect using the file path
void CExperimentalAudioSystem::VUnloadEffect( const char* sSoundFXFilePath)
{
	m_pcAudioEngine->uncache(sSoundFXFilePath);
}
