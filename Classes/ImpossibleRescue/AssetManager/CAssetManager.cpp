#include "CAssetManager.h"
#include "base/ccMacros.h"
#include "ImpossibleRescue/Audio/CSoundEffect.h"

CAssetManager::CAssetManager( std::function<IAudioSystem*()> fnpGetAudioEngine )
	: m_fnpGetAudioEngine( fnpGetAudioEngine )
{
}

CAssetManager::~CAssetManager( )
{
}

// Initialise the asset manager
void CAssetManager::VInitialise( )
{
	LoadSoundEffects( );
}

// Get a sound effect object pointer a given sound effect type
ISoundEffect* CAssetManager::VGetSoundEffect( ESoundFX esfxSoundEffect )
{
	// Throw an assert if a sound effect is not in the map. Sound effects are added to the map when preloaded.
	CCASSERT(m_pmapSoundEffects->at(esfxSoundEffect), "Sound effect has not been preloaded");

	return new CSoundEffect( m_fnpGetAudioEngine, esfxSoundEffect );
}

// Preload all sound effects
void CAssetManager::LoadSoundEffects( )
{
	// If the map has already been created we should not be creating it again.
	CCASSERT(m_pmapSoundEffects, "Sound effects have already been loaded");

	m_pmapSoundEffects = new std::map<const ESoundFX, const char*>();

	// This code loops through all of the enum values between "Unknown" and
	// "Last" and preloads the sound effect for that value
	for (int i = static_cast<int>(ESoundFX::Unknown) + 1; i != static_cast<int>(ESoundFX::Last); ++i)
	{
		PreloadSoundEffect(static_cast<ESoundFX>(i));
	}
}

CActionOnRelease CAssetManager::PreloadSoundEffect( ESoundFX esfxSoundEffect )
{
	// Get sound effect file path from map using enum
	const char* sSoundFXFilePath = GetSoundEffectFilePath(esfxSoundEffect);

	// Preload the sound effect file path using the audio system
	m_fnpGetAudioEngine()->VPreloadEffect(sSoundFXFilePath);

	// Add the sound effect to the map
	m_pmapSoundEffects->insert({ esfxSoundEffect, sSoundFXFilePath });

	return CActionOnRelease([&]() -> void
	{
		m_fnpGetAudioEngine()->VUnloadEffect(sSoundFXFilePath);
	});
}