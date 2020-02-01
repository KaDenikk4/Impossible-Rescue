#include "CSoundEffect.h"

// This sound effect implementation can only be created with a function to access an audio system
// and the enum value for that sound effect
CSoundEffect::CSoundEffect( std::function<IAudioSystem*()> fnpGetAudioSystem, ESoundFX esfxSoundEffect)
	: m_fnpGetAudioSystem( fnpGetAudioSystem )
	, m_esfxSoundEffect( esfxSoundEffect )
{
}

CSoundEffect::~CSoundEffect( )
{
}

// Play the sound effect
void CSoundEffect::VPlay( bool isLooping )
{
	m_iSoundId = m_fnpGetAudioSystem()->VPlaySoundEffect(m_esfxSoundEffect, isLooping);
}

// Play the sound effect (with volume option)
void CSoundEffect::VPlay( float fVolume, bool isLooping )
{
	m_iSoundId = m_fnpGetAudioSystem()->VPlaySoundEffect(m_esfxSoundEffect, fVolume, isLooping);
}

// Pause the sound effect
void CSoundEffect::VPause( )
{
	m_fnpGetAudioSystem()->VPauseEffect( m_iSoundId );
}

// Resume playing the sound effect
void CSoundEffect::VResume( )
{
	m_fnpGetAudioSystem()->VResumeEffect( m_iSoundId );
}

// Stop playing the sound effect
void CSoundEffect::VStop( )
{
	m_fnpGetAudioSystem()->VStopEffect( m_iSoundId );
}

// Get Sound effect type
const ESoundFX& CSoundEffect::VGetType( ) const
{
	return m_esfxSoundEffect;
}
