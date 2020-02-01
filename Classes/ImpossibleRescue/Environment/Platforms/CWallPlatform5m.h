//Name of class:	CWallPlatform5m
//Main author:		Toyan Green
//Summary:			This class is responsible for 5 metre wall platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALLPLATFORM5M_H_
#define _CWALLPLATFORM5M_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CWallPlatform5m
	: public CGCObjSpritePhysics
{
public:
	CWallPlatform5m(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CWallPlatform5m))
	{
	}

	virtual void VOnResourceAcquire(void) override;
};

#endif
