//Name of class:	CWallPlatform5m
//Main author:		Toyan Green
//Summary:			This class is responsible for 5 metre wall platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALLPLATFORM5M_H_
#include "CWallPlatform5m.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CWallPlatform5m, "TexturePacker/Sprites/Platforms/WallPlatform5m/WallPlatform5m.plist", "WallPlatform5mIdle", b2_staticBody, true);
void CWallPlatform5m::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CWallPlatform5m);
	CGCObjSpritePhysics::VOnResourceAcquire();
}
