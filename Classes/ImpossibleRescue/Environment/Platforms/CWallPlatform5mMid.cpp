//Name of class:	CWallPlatform5mMid
//Summary:			This class is responsible for 5 metre wall platforms.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CWALLPLATFORM5M_H_
#include "CWallPlatform5mMid.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CWallPlatform5mMid );

void CWallPlatform5mMid::VOnResourceAcquire(void)
{
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CWallPlatform5mMid::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWallPlatform5mMid::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
