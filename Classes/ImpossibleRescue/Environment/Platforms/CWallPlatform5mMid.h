//Name of class:	CWallPlatform5mMid
//Summary:			This class is responsible for 5 metre wall platforms.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CWALLPLATFORM5M_H_
#define _CWALLPLATFORM5M_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

class CWallPlatform5mMid
	: public CGCObjSpritePhysics
{
public:
	CWallPlatform5mMid(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf( CWallPlatform5mMid ))
	{
	}
	GCFACTORY_DECLARE_CREATABLECLASS( CWallPlatform5mMid );

	virtual void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

#endif
