//Name of class:	CTurretProjectileGroup
//Main author:		Toyan Green
//Summary:			This class is responsible for stationary enemy turret projectile group
//					in the game.
//Functions:		VHandlesThisTypeId, VGetTypeId, VOnGroupResourceAcquire, VOnGroupResourceAcquire,
//					CreateProjectiles, DestroyProjectiles, SpawnProjectile
//Based on:			GCObjGroupProjectilePlayer

#ifndef	_CTURRETPROJECTILEGROUP_H_
#define	_CTURRETPROJECTILEGROUP_H_

#ifndef MATH_VEC2_H
#include "cocos2d/cocos/math/Vec2.h"
#endif

#ifndef BOX2D_H
#include "Box2d/Box2D.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif

class CPlayerPrimaryProjectile;

class CTurretProjectileGroup
	: public CGCObjectGroup
{
public:
	// number of projectiles
	static const u32 k_uNumProjectiles = 16;

	CTurretProjectileGroup();
	virtual ~CTurretProjectileGroup()  override;

	// called from CGCGameLayerSpaceInvaders::VOnCreate
	void				CreateProjectiles();
	void				DestroyProjectiles();

	void				SpawnProjectile(const cocos2d::Vec2& v2Position, const cocos2d::Vec2& v2Velocity, f32 fMaxLifeTime, f32 fRotation);

	// overrides for CGCObjectGroup public interface

		// handles GCObjInvader
	virtual bool		VHandlesThisTypeId(GCTypeID idQueryType) override;

	// must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId() override;

	virtual void		VOnGroupResourceAcquire() override;
	virtual void		VOnGroupResourceRelease() override;
};

#endif