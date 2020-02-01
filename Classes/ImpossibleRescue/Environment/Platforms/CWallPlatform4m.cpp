//Name of class:	CWallPlatform4m
//Main author:		Toyan Green
//Summary:			This class is responsible for 4 metre wall platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALLPLATFORM4M_H_
#include "CWallPlatform4m.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CWallPlatform4m, "TexturePacker/Sprites/Platforms/WallPlatform4m/WallPlatform4m.plist", "WallPlatform4mIdle", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CWallPlatform4m );

void CWallPlatform4m::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CWallPlatform4m);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CWallPlatform4m::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWallPlatform4m::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
