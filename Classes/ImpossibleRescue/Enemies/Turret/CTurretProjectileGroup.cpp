//Name of class:	CTurretProjectileGroup
//Main author:		Toyan Green
//Summary:			This class is responsible for stationary enemy turret projectile group
//					in the game.
//Functions:		VHandlesThisTypeId, VGetTypeId, VOnGroupResourceAcquire, VOnGroupResourceAcquire,
//					CreateProjectiles, DestroyProjectiles, SpawnProjectile
//Based on:			GCObjGroupProjectilePlayer

#include <string.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "CTurretProjectileGroup.h"
#include "CTurretProjectile.h"

using namespace cocos2d;

// N.B. we want reset to put the projectiles on the dead list
CTurretProjectileGroup::CTurretProjectileGroup()
{
	SetResetBehaviour(CGCObjectGroup::EResetDead);
}

// virtual
CTurretProjectileGroup::~CTurretProjectileGroup()
{}

// only handle projectiles
//virtual 
bool CTurretProjectileGroup::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CTurretProjectile) == idQueryType);
}

// must return the typeid of the CGCObjectGroup derived class
//virtual 
GCTypeID CTurretProjectileGroup::VGetTypeId()
{
	return GetGCTypeIDOf(CTurretProjectileGroup);
}

void CTurretProjectileGroup::CreateProjectiles()
{
	// n.b. these register themselves with this class on creation via CGCObject & CGCObjectManager
	for (u32 uLoop = 0; uLoop < k_uNumProjectiles; ++uLoop)
	{
		new CTurretProjectile();
	}
}

struct SArrayOfProjectiles
{
	u32 uCount;
	CTurretProjectile* apProjectiles[CGCObjectGroup::EMaxGCObjects];
};
//////////////////////////////////////////////////////////////////////////
void CTurretProjectileGroup::DestroyProjectiles()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder([&](CGCObject* pObject)
	{
		GCASSERT(GetGCTypeIDOf(CTurretProjectile) == pObject->GetGCTypeID(), "wrong type!");
		delete pObject;
	});
}

void CTurretProjectileGroup::SpawnProjectile(const cocos2d::Vec2& v2Position, const cocos2d::Vec2& v2Velocity, f32 fMaxLifeTime, f32 fRotation)
{
	// check we have a projectile to spawn...
	if (GetCountDead())
	{
		// this case is safe because we know what type this group manages
		CTurretProjectile* pProjectile = static_cast<CTurretProjectile*>(GetDeadObject());

		// set up the projectile
		pProjectile->SetSpriteRotation(fRotation);
		pProjectile->SetSpritePosition(v2Position);
		pProjectile->SetVelocity(v2Velocity);
		pProjectile->SetLifeTime(fMaxLifeTime);

		// resurrect it to fire	it
		VOnObjectResurrect(pProjectile);
	}
}

// called from CGCObjectManager::Initialise
//virtual 
void CTurretProjectileGroup::VOnGroupResourceAcquire()
{
	CreateProjectiles();
	CGCObjectGroup::VOnGroupResourceAcquire();
}

//virtual 
void CTurretProjectileGroup::VOnGroupResourceRelease()
{
	// need to do this first as it resets the state of internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyProjectiles();
}