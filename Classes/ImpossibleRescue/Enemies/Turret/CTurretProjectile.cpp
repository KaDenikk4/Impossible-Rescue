//Name of class:	CTurretProjectile
//Main author:		Toyan Green
//Summary:			This class is responsible for stationary enemy turret projectiles
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnCollisionEnter
//Based on:			GCObjProjectilePlayer

#include "CTurretProjectile.h"
#include <memory.h>
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GameSpecific/Invaders/GCObjInvader.h"
#include "CTurret.h"

USING_NS_CC;

// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// this type - need this to construct our base type
CTurretProjectile::CTurretProjectile()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CTurretProjectile))
	, m_bShouldKillProjectile(false)
{
}

void CTurretProjectile::SetVelocity(const cocos2d::Vec2& v2Velocity)
{
	m_v2VelocityDesired = v2Velocity;
}

void CTurretProjectile::SetLifeTime(f32 fLifeTime)
{
	m_fRemainingLifetime = fLifeTime;
}

IN_CPP_CREATION_PARAMS_DECLARE(CTurretProjectile, "TexturePacker/Sprites/TurretProjectile/TurretProjectile.plist", "Turret_Projectile", b2_dynamicBody,	true);
//Virtual function to be called exactly once for each CGCObject derived class instance
//registered with CGCObjectManager as soon as the TGB level file has stopped
//loading- it is an "explicit constructor". (Note from GCFramework)
void CTurretProjectile::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CTurretProjectile);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CTurretProjectile::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CTurretProjectile::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}


// OnReset is called for each CGCObject derived class when CGCObjectManager is 
// reset. (Note from GCFramework)
void CTurretProjectile::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();
	
	m_bShouldKillProjectile = false;
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CTurretProjectile::VOnUpdate(f32 fTimeStep)
{
	// changes to desired velocity
	Vec2 v2DesiredVelocityDelta = (m_v2VelocityDesired - GetVelocity());

	// 1) f = m * a -> a = f/m
	// 2) v = a * t -> a = v/t
	// so f/m = v/t -> f = (v/t) * m
	Vec2 v2RequiredForce = GetPhysicsBody()->GetMass() * ((1.0f / fTimeStep) * v2DesiredVelocityDelta);
	ApplyForceToCenter(v2RequiredForce);

	//Sprite rotation needs to be flipped for the physics body
	SetPhysicsTransform(Vec2(GetPhysicsTransform().p.x, GetPhysicsTransform().p.y), -GetSpriteRotation());
	// handle lifetime
	m_fRemainingLifetime -= fTimeStep;
	if (m_fRemainingLifetime < 0.0f || m_bShouldKillProjectile)
	{
		m_bShouldKillProjectile = false;
		CGCObjectManager::ObjectKill(this);
	}
}

//Handle collisions with own b2Fixture and other b2Fixture (called once when collision first occurs)
void CTurretProjectile::VOnCollisionEnter(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture)
{
	//If self fixture is not the player then we should return
	if (FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID())
	{
		return;
	}
	bool bIsFixtureATurretProjectile = FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture )
	                                   && GetGCTypeIDOf( CTurretProjectile ) == FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture )->GetGCTypeID( );
	bool bIsFixtureATurret = FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture )
	                         && GetGCTypeIDOf( CTurret ) == FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture )->GetGCTypeID( );

	//There is a chance that we collide with a fixture that doesn't have a shape in the shapecache so we should check if it belongs to a SpritePhysicsObject first
	 const std::string* pstrCheckMe = FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture) ? cocos2d::GB2ShapeCache::getFixtureIdText(&b2fCollidingFixture) : nullptr;
	 bool               bHeadspaceSensorNameMatches = (pstrCheckMe && 0 == pstrCheckMe->compare("player_headspace"));
	 bool               bIsASensor = b2fCollidingFixture.IsSensor();
	
	 bool bIsFixturePlayerHeadSpaceSensor = pstrCheckMe
	                                        && bHeadspaceSensorNameMatches
	                                        && bIsASensor
	                                        && FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture );
	
	if (bIsFixtureATurretProjectile || bIsFixtureATurret || bIsFixturePlayerHeadSpaceSensor)
	{
		return;
	}
	
	m_bShouldKillProjectile = true;
}
