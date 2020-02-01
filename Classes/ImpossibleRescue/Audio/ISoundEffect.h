//Name of class:	ISoundEffect
//Main author:		Toyan Green
//Summary:			This class is an interface for a sound effect
//					in the game.
//Functions:		VPlay, VPause, VResume, VStop

#ifndef	_ISOUNDEFFECT_H_
#define	_ISOUNDEFFECT_H_
#include "ESoundFX.h"

class ISoundEffect
{
public:
	virtual ~ISoundEffect( ) = default;
	// Play the sound effect
	virtual void VPlay(bool isLooping = false) = 0;
	// Play the sound effect (with volume option)
	virtual void VPlay(float fVolume, bool isLooping = false) = 0;
	// Pause the sound effect
	virtual void VPause() = 0;
	// Resume playing the sound effect
	virtual void VResume() = 0;
	// Stop playing the sound effect
	virtual void VStop() = 0;
	// Get Sound effect type
	virtual const ESoundFX& VGetType() const = 0;
};

#endif
