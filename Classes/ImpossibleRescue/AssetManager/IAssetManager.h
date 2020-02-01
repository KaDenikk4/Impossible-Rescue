//Name of class:	IAssetManager
//Main author:		Toyan Green
//Summary:			This class is an interface for the asset manager
//					in the game.
//Functions:		Initialise, GetSoundEffect, GetSoundEffectFilePath

#ifndef	_IASSETMANAGER_H_
#define	_IASSETMANAGER_H_

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#ifndef	_ESOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ESoundFX.h"
#endif

class IAssetManager
{
public:
	virtual ~IAssetManager() = default;

	// Initialise the asset manager
	virtual void VInitialise() = 0;

	// Get a sound effect object pointer a given sound effect type
	virtual ISoundEffect* VGetSoundEffect(ESoundFX esfxSoundEffect) = 0;

	// Get the file path for a given sound effect type
	static const char* GetSoundEffectFilePath(ESoundFX esfxSoundEffect);
};

inline const char* IAssetManager::GetSoundEffectFilePath(ESoundFX esfxSoundEffect)
{
	switch (esfxSoundEffect)
	{
	case ESoundFX::MenuButtonSelected:
		return "SoundEffects/Buttons/Button_Select.mp3";
		break;
	case ESoundFX::MenuButtonPressed:
		return "SoundEffects/Buttons/Button_Press.mp3";
		break;
	case ESoundFX::WeaponSwitch:
		return "SoundEffects/Danielle/Danielle_Switch_Weapons.mp3";
		break;
	case ESoundFX::MainMenuMusic:
		return "SoundEffects/Music/Bens_Themes/Menu_Theme.mp3";
		break;
	case ESoundFX::EnemyShoot:
		return "SoundEffects/WeaponsAndShooting/Weapon_01_Shooting.mp3";
		break;
	case ESoundFX::EnemyDisabled:
		return "SoundEffects/Enemy_01/Enemy_01_Stunned.mp3";
		break;
	case ESoundFX::HackingInProgress:
		return "SoundEffects/Danielle/Hacking_Sound.mp3";
		break;
	case ESoundFX::MovingPlatform:
		return "SoundEffects/EnvironmentAndHazards/Moving_Platforms.mp3";
		break;
	case ESoundFX::PlayerJumping:
		return "SoundEffects/Danielle/Danielle_Jumping.mp3";
		break;
	case ESoundFX::PlayerHit:
		return "SoundEffects/Danielle/Danielle_Hit.mp3";
		break;
	case ESoundFX::Footsteps:
		return "SoundEffects/Danielle/Danielle_Footstep.mp3";
		break;
	case ESoundFX::PauseMenuMusic:
		return "SoundEffects/Music/Bens_Themes/Pause_Menu_Theme.mp3";
		break;
	case ESoundFX::EnemyEnabled:
		return "SoundEffects/Enemy_01/Enemy_01_Power_Up.mp3";
		break;
	case ESoundFX::PlayerCrouch:
		return "SoundEffects/Danielle/Danielle_Crouch.mp3";
		break;
	case ESoundFX::PlayerLand:
		return "SoundEffects/Danielle/Danielle_Lands.mp3";
		break;
	case ESoundFX::PlayerStandsUp:
		return "SoundEffects/Danielle/Danielle_Stand_Up.mp3";
		break;
	case ESoundFX::Hazard:
		return "SoundEffects/EnvironmentAndHazards/Vertical_Hazard.mp3";
		break;
	case ESoundFX::PlayerShoot:
		return "SoundEffects/Danielle/Danielle_Shooting.mp3";
		break;
	case ESoundFX::ProjectileHitOtherObject:
		return "SoundEffects/EnvironmentAndHazards/Hit_Other.mp3";
		break;
	case ESoundFX::DoorOpen:
		return "SoundEffects/EnvironmentAndHazards/Door_Open.mp3";
		break;
	case ESoundFX::PlayerIdle:
		return "SoundEffects/Danielle/Danielle_Idle_Breathing.mp3";
		break;
	case ESoundFX::Act1StartMusic:
		return "SoundEffects/Music/Bens_Themes/Level_1_Theme.mp3";
		break;
	case ESoundFX::Act1MiddleMusic:
		return "SoundEffects/Music/Bens_Themes/Level_2_3_Theme.mp3";
		break;
	case ESoundFX::Act1TimerMusic:
		return "SoundEffects/Music/Bens_Themes/Level_4_Theme.mp3";
		break;
	case ESoundFX::TickerText:
		return "SoundEffects/Buttons/Ticker_Text.mp3";
		break;
	case ESoundFX::CutsceneMusic:
		//ToDo replace this with correct music for the cutscenes
		return "SoundEffects/Buttons/Ticker_Text.mp3";
		break;
	default:
		;
	}

	return nullptr;
}

#endif