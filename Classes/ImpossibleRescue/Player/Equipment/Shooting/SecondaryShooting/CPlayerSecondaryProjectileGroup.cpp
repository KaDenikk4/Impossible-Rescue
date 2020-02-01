//Name of class:	CPlayerSecondaryProjectile
//Main author:		Toyan Green
//Summary:			This class is responsible for the player secondary projectile group
//					in the game.
//Functions:		VHandlesThisTypeId, VGetTypeId, VOnGroupResourceAcquire, VOnGroupResourceAcquire,
//					CreateProjectiles, DestroyProjectiles, SpawnProjectile
//Based on:			GCObjGroupProjectilePlayer

#include <string.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/Core/GCTypes.h"+
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "CPlayerSecondaryProjectile.h"
#include "CPlayerSecondaryProjectileGroup.h"

using namespace cocos2d;

// N.B. we want reset to put the projectiles on the dead list
CPlayerSecondaryProjectileGroup::CPlayerSecondaryProjectileGroup()
{
	SetResetBehaviour(CGCObjectGroup::EResetDead);
}

// virtual
CPlayerSecondaryProjectileGroup::~CPlayerSecondaryProjectileGroup()
{}

// only handle projectiles
//virtual 
bool CPlayerSecondaryProjectileGroup::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CPlayerSecondaryProjectile) == idQueryType);
}

// must return the typeid of the CGCObjectGroup derived class
//virtual 
GCTypeID CPlayerSecondaryProjectileGroup::VGetTypeId()
{
	return GetGCTypeIDOf(CPlayerSecondaryProjectileGroup);
}

void CPlayerSecondaryProjectileGroup::CreateProjectiles()
{
	// n.b. these register themselves with this class on creation via CGCObject & CGCObjectManager
	for (u32 uLoop = 0; uLoop < k_uNumProjectiles; ++uLoop)
	{
		new CPlayerSecondaryProjectile();
	}
}

struct SArrayOfProjectiles
{
	u32 uCount;
	CPlayerSecondaryProjectile* apProjectiles[CGCObjectGroup::EMaxGCObjects];
};
//////////////////////////////////////////////////////////////////////////
void CPlayerSecondaryProjectileGroup::DestroyProjectiles()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder([&](CGCObject* pObject)
	{
		GCASSERT(GetGCTypeIDOf(CPlayerSecondaryProjectile) == pObject->GetGCTypeID(), "wrong type!");
		delete pObject;
	});
}

void CPlayerSecondaryProjectileGroup::SpawnProjectile(const cocos2d::Vec2& v2Position, const cocos2d::Vec2& v2Velocity, f32 fMaxLifeTime, f32 fRotation)
{
	// check we have a projectile to spawn...
	if (GetCountDead())
	{
		// this case is safe because we know what type this group manages
		CPlayerSecondaryProjectile* pProjectile = static_cast<CPlayerSecondaryProjectile*>(GetDeadObject());

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
void CPlayerSecondaryProjectileGroup::VOnGroupResourceAcquire()
{
	CreateProjectiles();
	CGCObjectGroup::VOnGroupResourceAcquire();
}

//virtual 
void CPlayerSecondaryProjectileGroup::VOnGroupResourceRelease()
{
	// need to do this first as it resets the state of internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyProjectiles();
}