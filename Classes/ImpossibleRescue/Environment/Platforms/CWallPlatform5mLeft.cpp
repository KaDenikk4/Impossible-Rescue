//Name of class:	CWallPlatform5mLeft
//Main author:		Toyan Green
//Summary:			This class is responsible for 5 metre wall platforms
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALLPLATFORM5M_H_
#include "CWallPlatform5mLeft.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CWallPlatform5mLeft );

void CWallPlatform5mLeft::VOnResourceAcquire(void)
{
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CWallPlatform5mLeft::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWallPlatform5mLeft::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
