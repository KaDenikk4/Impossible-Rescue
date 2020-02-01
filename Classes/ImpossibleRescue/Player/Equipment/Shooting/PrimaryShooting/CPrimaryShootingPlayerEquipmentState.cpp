//Name of class:	CPrimaryShootingPlayerEquipmentState
//Main author:		Toyan Green
//Summary:			This class is responsible for the player's primary weapon type
//					in the game.
//Functions:		VEnter, VUpdate, VHandleInput

#include "CPrimaryShootingPlayerEquipmentState.h"
#include "../../CPlayerEquipmentStates.h"
#include "AppDelegate.h"

CPrimaryShootingPlayerEquipmentState::CPrimaryShootingPlayerEquipmentState(std::function<CPlayerPrimaryProjectileGroup*()> fnpGetProjectileGroup)
: m_fnpGetProjectileGroup(fnpGetProjectileGroup)
, m_psfxWeaponSwitch( nullptr )
{
}

CPrimaryShootingPlayerEquipmentState::~CPrimaryShootingPlayerEquipmentState( )
{
	if(m_psfxWeaponSwitch)
	{
		delete m_psfxWeaponSwitch;
		m_psfxWeaponSwitch = nullptr;
	}
}

void CPrimaryShootingPlayerEquipmentState::VInitialise( )
{
	m_psfxWeaponSwitch = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::WeaponSwitch);
}

//State beginning transition. Called once when player equipment state is set to this state.
void CPrimaryShootingPlayerEquipmentState::VEnter( CPlayer& player )
{
	m_psfxWeaponSwitch->VPlay();
}

//Update loop. Called from CPlayer VOnUpdate.
CPlayerEquipmentState* CPrimaryShootingPlayerEquipmentState::VUpdate( CPlayer& player )
{
	return nullptr;
}

//Handle player input. Called from CPlayer VOnUpdate.
CPlayerEquipmentState* CPrimaryShootingPlayerEquipmentState::VHandleInput( CPlayer& player,
	TGCController<EPlayerActions>& input )
{
	if (input.ButtonHasJustBeenPressed(EPlayerActions::Shoot))
	{
		if (player.IsFlippedX())
		{
			m_fnpGetProjectileGroup()->SpawnProjectile(
				Vec2(player.GetSpritePosition().x - GetPlayerProjectileOffset().x, player.GetSpritePosition().y + GetPlayerProjectileOffset().y)
				, Vec2(-GetPlayerBulletSpeed(), 0.0f)
				, 3.0f
				, CC_DEGREES_TO_RADIANS(180.0f));
		}
		else
		{
			m_fnpGetProjectileGroup()->SpawnProjectile(player.GetSpritePosition() + GetPlayerProjectileOffset()
				, Vec2(GetPlayerBulletSpeed(), 0.0f)
				, 3.0f
				, 0);
		}
	}

	if( input.ButtonHasJustBeenPressed( EPlayerActions::SwitchWeapon ) )
	{
		return AppDelegate::GetPlayerDataManager()->GetPlayerEquipmentStates()->GetSecondaryShootingPlayerEquipmentState();
	}

	return nullptr;
}
