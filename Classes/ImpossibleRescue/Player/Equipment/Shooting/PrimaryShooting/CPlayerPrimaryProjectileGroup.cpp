//Name of class:	CPlayerPrimaryProjectileGroup
//Main author:		Toyan Green
//Summary:			This class is responsible for the player primary projectile group
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
#include "CPlayerPrimaryProjectile.h"
#include "CPlayerPrimaryProjectileGroup.h"

using namespace cocos2d;

// N.B. we want reset to put the projectiles on the dead list
CPlayerPrimaryProjectileGroup::CPlayerPrimaryProjectileGroup()
{
	SetResetBehaviour(CGCObjectGroup::EResetDead);
}

// virtual
CPlayerPrimaryProjectileGroup::~CPlayerPrimaryProjectileGroup()
{}

// only handle projectiles
//virtual 
bool CPlayerPrimaryProjectileGroup::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CPlayerPrimaryProjectile) == idQueryType);
}

// must return the typeid of the CGCObjectGroup derived class
//virtual 
GCTypeID CPlayerPrimaryProjectileGroup::VGetTypeId()
{
	return GetGCTypeIDOf(CPlayerPrimaryProjectileGroup);
}

void CPlayerPrimaryProjectileGroup::CreateProjectiles()
{
	// n.b. these register themselves with this class on creation via CGCObject & CGCObjectManager
	for (u32 uLoop = 0; uLoop < k_uNumProjectiles; ++uLoop)
	{
		new CPlayerPrimaryProjectile();
	}
}

struct SArrayOfProjectiles
{
	u32 uCount;
	CPlayerPrimaryProjectile* apProjectiles[CGCObjectGroup::EMaxGCObjects];
};
//////////////////////////////////////////////////////////////////////////
void CPlayerPrimaryProjectileGroup::DestroyProjectiles()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder([&](CGCObject* pObject)
	{
		GCASSERT(GetGCTypeIDOf(CPlayerPrimaryProjectile) == pObject->GetGCTypeID(), "wrong type!");
		delete pObject;
	});
}

void CPlayerPrimaryProjectileGroup::SpawnProjectile(const cocos2d::Vec2& v2Position, const cocos2d::Vec2& v2Velocity, f32 fMaxLifeTime, f32 fRotation)
{
	// check we have a projectile to spawn...
	if (GetCountDead())
	{
		// this case is safe because we know what type this group manages
		CPlayerPrimaryProjectile* pProjectile = static_cast<CPlayerPrimaryProjectile*>(GetDeadObject());

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
void CPlayerPrimaryProjectileGroup::VOnGroupResourceAcquire()
{
	CreateProjectiles();
	CGCObjectGroup::VOnGroupResourceAcquire();
}

//virtual 
void CPlayerPrimaryProjectileGroup::VOnGroupResourceRelease()
{
	// need to do this first as it resets the state of internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyProjectiles();
}