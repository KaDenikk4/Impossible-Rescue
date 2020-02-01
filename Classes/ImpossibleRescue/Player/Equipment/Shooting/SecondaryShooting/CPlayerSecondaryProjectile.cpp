//Name of class:	CPlayerSecondaryProjectile
//Main author:		Toyan Green
//Summary:			This class is responsible for player secondary ammo projectiles
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VHandleCollision
//Based on:			GCObjProjectilePlayer

#include "CPlayerSecondaryProjectile.h"
#include <memory.h>
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "ImpossibleRescue/Enemies/Turret/CTurret.h"
#include "ImpossibleRescue/Environment/Door/CDoor.h"

USING_NS_CC;

// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// this type - need this to construct our base type
CPlayerSecondaryProjectile::CPlayerSecondaryProjectile( )
	: CGCObjSpritePhysics( GetGCTypeIDOf( CPlayerSecondaryProjectile ) )
	, m_bShouldKillProjectile ( false )
	, m_iCollisionHitCount( 0 )
{
	m_iCollisionHitCount = 0;
}

CPlayerSecondaryProjectile::~CPlayerSecondaryProjectile()
{
	if(m_psfxHitOtherSFX )
	{
		delete m_psfxHitOtherSFX;
		m_psfxHitOtherSFX = nullptr;
	}	
}

void CPlayerSecondaryProjectile::SetVelocity(const cocos2d::Vec2& v2Velocity)
{
	m_v2VelocityDesired = v2Velocity;
	m_iCollisionHitCount = 0;
}

void CPlayerSecondaryProjectile::SetLifeTime(f32 fLifeTime)
{
	m_fRemainingLifetime = fLifeTime;
}

IN_CPP_CREATION_PARAMS_DECLARE( CPlayerSecondaryProjectile, "TexturePacker/Sprites/StunWeaponProjectile/StunWeaponProjectile.plist", "Stun_Weapon_Projectile", b2_dynamicBody, true);
//Virtual function to be called exactly once for each CGCObject derived class instance
//registered with CGCObjectManager as soon as the TGB level file has stopped
//loading- it is an "explicit constructor". (Note from GCFramework)
void CPlayerSecondaryProjectile::VOnResourceAcquire( )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CPlayerSecondaryProjectile );
	CGCObjSpritePhysics::VOnResourceAcquire ( );

	m_psfxHitOtherSFX = AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::ProjectileHitOtherObject );
	m_iCollisionHitCount = 0;
}


// OnReset is called for each CGCObject derived class when CGCObjectManager is 
// reset. (Note from GCFramework)
void CPlayerSecondaryProjectile::VOnReset( )
{
	CGCObjSpritePhysics::VOnReset ( );

	m_bShouldKillProjectile = false;
	m_iCollisionHitCount	= 0;
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CPlayerSecondaryProjectile::VOnUpdate( f32 fTimeStep )
{
	// changes to desired velocity
	Vec2 v2DesiredVelocityDelta = ( m_v2VelocityDesired - GetVelocity ( ) );

	// 1) f = m * a -> a = f/m
	// 2) v = a * t -> a = v/t
	// so f/m = v/t -> f = (v/t) * m
	Vec2 v2RequiredForce = GetPhysicsBody ( )->GetMass ( ) * ( ( 1.0f / fTimeStep ) * v2DesiredVelocityDelta );
	ApplyForceToCenter( v2RequiredForce );

	// handle lifetime
	m_fRemainingLifetime -= fTimeStep;
	if( (m_fRemainingLifetime < 0.0f || m_bShouldKillProjectile) && m_iCollisionHitCount > 0)
	{
		m_bShouldKillProjectile = false;
		CGCObjectManager::ObjectKill( this );
		m_iCollisionHitCount = 0;
	}
}

void CPlayerSecondaryProjectile::VOnCollisionEnter( GCTypeID typeOfObj )
{
	if (GetGCTypeIDOf(CPlayerPrimaryProjectile) == typeOfObj
		|| GetGCTypeIDOf(CPlayerSecondaryProjectile) == typeOfObj
		|| GetGCTypeIDOf(CDoor) == typeOfObj
		|| GetGCTypeIDOf(CHackingStation) == typeOfObj
		|| GetGCTypeIDOf(CPlayer) == typeOfObj)
	{
		return;
	}

	m_iCollisionHitCount += 1;

	//This check needs to be done as CGCObjectManager::ObjectKill( this ), line 87 is not executed on the same frame, causing second call here
	if(m_iCollisionHitCount == 1)
	{
		m_psfxHitOtherSFX->VPlay();
		m_bShouldKillProjectile = true;
	}
}

// Check if there is valid editor data
bool CPlayerSecondaryProjectile::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CPlayerSecondaryProjectile::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
