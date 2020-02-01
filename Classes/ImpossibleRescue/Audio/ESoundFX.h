//Name of class:	ESoundEffect
//Main author:		Toyan Green
//Summary:			This class is an enumeration for sound effects
//					in the game.

#ifndef	_ESOUNDEFFECT_H_
#define	_ESOUNDEFFECT_H_

enum class ESoundFX
{
	Unknown = 0,
	MenuButtonSelected = 1,
	MenuButtonPressed = 2,
	WeaponSwitch = 3,
	MainMenuMusic = 4,
	TickerText = 5,
	EnemyShoot = 6,
	EnemyDisabled = 7,
	HackingInProgress = 8,
	MovingPlatform = 9,
	PlayerJumping = 10,
	PlayerHit = 11,
	Footsteps = 12,
	PauseMenuMusic = 13,
	EnemyEnabled = 14,
	PlayerCrouch = 15,
	PlayerLand = 16,
	PlayerStandsUp = 17,
	Hazard = 18,
	PlayerShoot = 19,
	ProjectileHitOtherObject = 20,
	DoorOpen = 21,
	PlayerIdle = 22,
	Act1StartMusic = 23,
	Act1MiddleMusic = 24,
	Act1TimerMusic = 25,
	CutsceneMusic = 26,
	
	//Used to detect the end of the enum list
	Last,
	
};

#endif

