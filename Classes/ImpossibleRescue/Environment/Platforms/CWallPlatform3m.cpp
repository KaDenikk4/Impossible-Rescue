//Name of class:	CWallPlatform3m
//Main author:		Toyan Green
//Summary:			This class is responsible for 3 metre wall platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALLPLATFORM3M_H_
#include "CWallPlatform3m.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

//IN_CPP_CREATION_PARAMS_DECLARE(CWallPlatform3m, "TexturePacker/Sprites/Platforms/WallPlatform3m/WallPlatform3m.plist", "WallPlatform3mIdle", b2_staticBody, true);

// implement the factory method to enable this to be created via CGCFactory_ObjSpritePhysics 
GCFACTORY_IMPLEMENT_CREATEABLECLASS(CWallPlatform3m);

CWallPlatform3m::CWallPlatform3m( )
	: CGCObjSpritePhysics(GetGCTypeIDOf(CWallPlatform3m))
{
}

void CWallPlatform3m::VHandleFactoryParams( const CGCFactoryCreationParams& rCreationParams,
	cocos2d::Vec2 v2InitialPosition )
{
	CGCObjSpritePhysics::VHandleFactoryParams(rCreationParams, v2InitialPosition);
	
	//Get editor parameters

	
}

// This will be called exactly once for each CGCObject derived class instance 
// registered with CGCObjectManager as soon as the TGB level file has stopped 
// loading- it is an "explicit constructor". (Note from GCFramework)
void CWallPlatform3m::VOnResourceAcquire(void)
{
	//IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CWallPlatform3m);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CWallPlatform3m::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWallPlatform3m::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
