//Name of class:	CPlayerPrimaryProjectile
//Main author:		Toyan Green
//Summary:			This class is responsible for player primary ammo projectiles
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VHandleCollision
//Based on:			GCObjProjectilePlayer

#ifndef _CPLAYERPRIMARYPROJECTILE_H_
#define _CPLAYERPRIMARYPROJECTILE_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

class CPlayerPrimaryProjectile
	: public CGCObjSpritePhysics
{

private:
	cocos2d::Vec2	m_v2VelocityDesired;	// velocity of the projectile
	f32				m_fRemainingLifetime;	// remaining lifetime

public:
	CPlayerPrimaryProjectile();

	// we need a virtual destructor since delete will be called on pointers of 
	// this class to delete derived types.
	virtual ~CPlayerPrimaryProjectile()
	{}

	// accessors for data members
	void SetVelocity(const cocos2d::Vec2& v2Velocity);
	void SetLifeTime(f32 fLifeTime);

	// overridden virtuals from the game object interface

	//Virtual function to be called exactly once for each CGCObject derived class instance
	//registered with CGCObjectManager as soon as the TGB level file has stopped
	//loading- it is an "explicit constructor". (Note from GCFramework)
	virtual void VOnResourceAcquire() override;

	// OnReset is called for each CGCObject derived class when CGCObjectManager is 
	// reset. (Note from GCFramework)
	virtual void VOnReset() override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnUpdate(f32 fTimeStep) override;

	// overridden virtuals from the game object interface

	//Handle collisions with CGCObjSpritePhysics (called every frame)
	void VHandleCollision(CGCObjSpritePhysics& collidingSpriteObj) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;
};

#endif