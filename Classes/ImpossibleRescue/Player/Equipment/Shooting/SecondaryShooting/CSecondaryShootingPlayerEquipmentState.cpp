//Name of class:	CSecondaryShootingPlayerEquipmentState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player's secondary weapon type
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CSecondaryShootingPlayerEquipmentState.h"
#include "../../CPlayerEquipmentStates.h"
#include "AppDelegate.h"

CSecondaryShootingPlayerEquipmentState::CSecondaryShootingPlayerEquipmentState(std::function<CPlayerSecondaryProjectileGroup*()> fnpGetProjectileGroup)
: m_fnpGetProjectileGroup(fnpGetProjectileGroup)
	, m_psfxPlayerShoot(nullptr)
{
}

CSecondaryShootingPlayerEquipmentState::~CSecondaryShootingPlayerEquipmentState( )
{
	
	if (m_psfxPlayerShoot)
	{
		delete m_psfxPlayerShoot;
		m_psfxPlayerShoot = nullptr;
	}
}

void CSecondaryShootingPlayerEquipmentState::VInitialise( )
{
	m_psfxPlayerShoot = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerShoot);
}

//State beginning transition. Called once when player equipment state is set to this state.
void CSecondaryShootingPlayerEquipmentState::VEnter( CPlayer& player )
{
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerEquipmentState* CSecondaryShootingPlayerEquipmentState::VUpdate( CPlayer& player )
{
	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerEquipmentState* CSecondaryShootingPlayerEquipmentState::VHandleInput( CPlayer& player,
	TGCController<EPlayerActions>& input )
{
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Shoot))
	{
		m_psfxPlayerShoot->VPlay();
		if (player.IsFlippedX())
		{
			m_fnpGetProjectileGroup()->SpawnProjectile(
				Vec2(player.GetSpritePosition().x - GetPlayerProjectileOffset().x, player.GetSpritePosition().y + GetPlayerProjectileOffset().y )
				, Vec2(-GetPlayerBulletSpeed(), 0.0f)
				, 3.0f
				, CC_DEGREES_TO_RADIANS( 180.0f ));
		}
		else
		{
			m_fnpGetProjectileGroup()->SpawnProjectile(player.GetSpritePosition() + GetPlayerProjectileOffset()
				, Vec2(GetPlayerBulletSpeed(), 0.0f)
				, 3.0f
				, 0);
		}
	}

	// No need for 2 ammo types with cut scope so ammo type is disabled
	// if (input.ButtonHasJustBeenPressed(EPlayerActions::SwitchWeapon))
	// {
	// 	return AppDelegate::GetPlayerDataManager()->GetPlayerEquipmentStates()->GetPrimaryShootingPlayerEquipmentState();
	// }

	return nullptr;
}
