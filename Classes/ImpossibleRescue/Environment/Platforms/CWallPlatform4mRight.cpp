//Name of class:	CWallPlatform4mRight
//Summary:			This class is responsible for 4 metre wall platforms, attached on right side.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CWALLPLATFORM4M_H_
#include "CWallPlatform4mRight.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CWallPlatform4mRight );

void CWallPlatform4mRight::VOnResourceAcquire(void)
{
	CGCObjSpritePhysics::VOnResourceAcquire();
	SetFlippedX( true );
}

// Check if there is valid editor data
bool CWallPlatform4mRight::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWallPlatform4mRight::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
