//Name of class:	IAssetManager
//Main author:		Toyan Green
//Summary:			This class is the asset manager
//					in the game.
//Functions:		VInitialise, VGetSoundEffect,
//					LoadSoundEffects, PreloadSoundEffect 

#ifndef	_CASSETMANAGER_H_
#define	_CASSETMANAGER_H_

#ifndef	_IASSETMANAGER_H_
#include "IAssetManager.h"
#endif

#include <map>
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#include "ImpossibleRescue/Audio/IAudioSystem.h"

namespace CocosDenshion {
	class SimpleAudioEngine;
}

class CAssetManager : public IAssetManager
{
public:

	// This asset manager implementation can only be created with a function to access an audio system
	CAssetManager() = delete;
	CAssetManager(std::function< IAudioSystem*() > fnpGetAudioEngine);
	
	virtual ~CAssetManager() override;

	// Initialise the asset manager
	void VInitialise( ) override;

	// Get a sound effect object pointer a given sound effect type
	ISoundEffect* VGetSoundEffect( ESoundFX esfxSoundEffect ) override;

private:

	// Preload all sound effects
	void LoadSoundEffects();

	// Preload a sound effect
	CActionOnRelease PreloadSoundEffect(ESoundFX esfxSoundEffect);

	// Function to access an audio system
	std::function< IAudioSystem*() > m_fnpGetAudioEngine;

	// Map of sound effects and their respective file path
	std::map< const ESoundFX, const char* >* m_pmapSoundEffects;
};

#endif