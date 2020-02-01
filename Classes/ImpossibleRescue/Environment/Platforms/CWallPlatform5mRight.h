//Name of class:	CWallPlatform5mRight
//Summary:			This class is responsible for 5 metre wall platforms,  attached on right side.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CWALLPLATFORM5M_H_
#define _CWALLPLATFORM5M_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CWallPlatform5mRight
	: public CGCObjSpritePhysics
{
public:
	CWallPlatform5mRight(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf( CWallPlatform5mRight ))
	{
	}

	GCFACTORY_DECLARE_CREATABLECLASS( CWallPlatform5mRight );

	virtual void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

#endif
