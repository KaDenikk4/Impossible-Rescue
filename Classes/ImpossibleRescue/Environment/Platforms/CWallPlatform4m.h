//Name of class:	CWallPlatform4m
//Main author:		Toyan Green
//Summary:			This class is responsible for 4 metre wall platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALLPLATFORM4M_H_
#define _CWALLPLATFORM4M_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CWallPlatform4m
	: public CGCObjSpritePhysics
{
public:
	CWallPlatform4m(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CWallPlatform4m))
	{
	}

	GCFACTORY_DECLARE_CREATABLECLASS( CWallPlatform4m );

	virtual void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;
};

#endif
