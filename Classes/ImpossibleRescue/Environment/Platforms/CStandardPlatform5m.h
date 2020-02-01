//Name of class:	CStandardPlatform5m
//Main author:		Toyan Green
//Summary:			This class is responsible for 5 metre standard platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CSTANDARDPLATFORM5M_H_
#define _CSTANDARDPLATFORM5M_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CStandardPlatform5m
	: public CGCObjSpritePhysics
{
public:
	CStandardPlatform5m(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CStandardPlatform5m))
	{
	}

	virtual void VOnResourceAcquire(void) override;
};

#endif
