//Name of class:	CStandardPlatform5m
//Main author:		Toyan Green
//Summary:			This class is responsible for 5 metre standard platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CSTANDARDPLATFORM5M_H_
#include "CStandardPlatform5m.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CStandardPlatform5m, "TexturePacker/Sprites/Platforms/StandardPlatform5m/StandardPlatform5m.plist", "StandardPlatform5mIdle", b2_staticBody, true);
void CStandardPlatform5m::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CStandardPlatform5m);
	CGCObjSpritePhysics::VOnResourceAcquire();
}
