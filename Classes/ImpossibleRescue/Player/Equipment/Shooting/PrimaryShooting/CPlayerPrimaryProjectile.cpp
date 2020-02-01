//Name of class:	CPlayerPrimaryProjectile
//Main author:		Toyan Green
//Summary:			This class is responsible for player primary ammo projectiles
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VHandleCollision
//Based on:			GCObjProjectilePlayer

#include "CPlayerPrimaryProjectile.h"
#include <memory.h>
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "ImpossibleRescue/Environment/Door/CDoor.h"

USING_NS_CC;

// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// this type - need this to construct our base type
CPlayerPrimaryProjectile::CPlayerPrimaryProjectile( )
	: CGCObjSpritePhysics( GetGCTypeIDOf( CPlayerPrimaryProjectile ) )
{
}

void CPlayerPrimaryProjectile::SetVelocity(const cocos2d::Vec2& v2Velocity)
{
	m_v2VelocityDesired = v2Velocity;
}

void CPlayerPrimaryProjectile::SetLifeTime(f32 fLifeTime)
{
	m_fRemainingLifetime = fLifeTime;
}

IN_CPP_CREATION_PARAMS_DECLARE( CPlayerPrimaryProjectile, "TexturePacker/Sprites/Egg/Egg.plist", "egg", b2_dynamicBody, true);
//Virtual function to be called exactly once for each CGCObject derived class instance
//registered with CGCObjectManager as soon as the TGB level file has stopped
//loading- it is an "explicit constructor". (Note from GCFramework)
void CPlayerPrimaryProjectile::VOnResourceAcquire( )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CPlayerPrimaryProjectile );
	CGCObjSpritePhysics::VOnResourceAcquire ( );
}


// OnReset is called for each CGCObject derived class when CGCObjectManager is 
// reset. (Note from GCFramework)
void CPlayerPrimaryProjectile::VOnReset( )
{
	CGCObjSpritePhysics::VOnReset ( );
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CPlayerPrimaryProjectile::VOnUpdate( f32 fTimeStep )
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
	if( m_fRemainingLifetime < 0.0f )
	{
		CGCObjectManager::ObjectKill( this );
	}
}

//Handle collisions with CGCObjSpritePhysics (called every frame)
void CPlayerPrimaryProjectile::VHandleCollision( CGCObjSpritePhysics& collidingSpriteObj )
{
	if (GetGCTypeIDOf(CPlayerPrimaryProjectile) == collidingSpriteObj.GetGCTypeID()
		|| GetGCTypeIDOf(CPlayerSecondaryProjectile) == collidingSpriteObj.GetGCTypeID()
		|| GetGCTypeIDOf(CDoor) == collidingSpriteObj.GetGCTypeID()
		|| GetGCTypeIDOf(CHackingStation) == collidingSpriteObj.GetGCTypeID()
		|| GetGCTypeIDOf(CPlayer) == collidingSpriteObj.GetGCTypeID())
	{
		return;
	}

	CGCObjectManager::ObjectKill(this);
}

// Check if there is valid editor data
bool CPlayerPrimaryProjectile::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CPlayerPrimaryProjectile::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
