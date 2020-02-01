//Name of class:	CTurretProjectile
//Main author:		Toyan Green
//Summary:			This class is responsible for stationary enemy turret projectiles
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnCollisionEnter
//Based on:			GCObjProjectilePlayer

#ifndef _CTURRETPROJECTILE_H_
#define _CTURRETPROJECTILE_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

class CTurretProjectile
	: public CGCObjSpritePhysics
{

private:
	cocos2d::Vec2	m_v2VelocityDesired;	// velocity of the projectile
	f32				m_fRemainingLifetime;	// remaining lifetime
	bool			m_bShouldKillProjectile;

public:
	CTurretProjectile();

	// we need a virtual destructor since delete will be called on pointers of 
	// this class to delete derived types.
	virtual ~CTurretProjectile()
	{}

	// accessors for data members
	void SetVelocity(const cocos2d::Vec2& v2Velocity);
	void SetLifeTime(f32 fLifeTime);

	//Virtual function to be called exactly once for each CGCObject derived class instance
	//registered with CGCObjectManager as soon as the TGB level file has stopped
	//loading- it is an "explicit constructor". (Note from GCFramework)
	virtual void VOnResourceAcquire() override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;

	// OnReset is called for each CGCObject derived class when CGCObjectManager is 
	// reset. (Note from GCFramework)
	virtual void VOnReset() override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnUpdate(f32 fTimeStep) override;

	// overridden virtuals from the game object interface

	//Handle collisions with own b2Fixture and other b2Fixture (called once when collision first occurs) 
	virtual void VOnCollisionEnter(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture) override;
};

#endif