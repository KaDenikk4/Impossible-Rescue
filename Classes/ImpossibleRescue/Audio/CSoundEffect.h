//Name of class:	CSoundEffect
//Main author:		Toyan Green
//Summary:			This class is a sound effect
//					in the game.
//Functions:		VPlay, VPause, VResume, VStop

#ifndef	_CSOUNDEFFECT_H_
#define	_CSOUNDEFFECT_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ISoundEffect.h"
#endif

#include <functional>
#include "IAudioSystem.h"

class CSoundEffect : public ISoundEffect
{
public:
	
	// This sound effect implementation can only be created with a function to access an audio system
	// and the enum value for that sound effect
	CSoundEffect() = delete;
	CSoundEffect(std::function< IAudioSystem*() > fnpGetAudioSystem, ESoundFX esfxSoundEffect);
	
	virtual ~CSoundEffect( ) override;
	// Play the sound effect
	void VPlay( bool isLooping = false ) override;
	// Play the sound effect (with volume option)
	void VPlay(float fVolume, bool isLooping = false) override;
	// Pause the sound effect
	void VPause( ) override;
	// Resume playing the sound effect
	void VResume( ) override;
	// Stop playing the sound effect
	void VStop( ) override;
	// Get Sound effect type
	const ESoundFX& VGetType() const override;

private:

	// Function to access an audio system
	std::function< IAudioSystem*() > m_fnpGetAudioSystem;
	// Sound effect ID
	unsigned int m_iSoundId;
	// Sound effect enum value
	ESoundFX m_esfxSoundEffect;
};

#endif