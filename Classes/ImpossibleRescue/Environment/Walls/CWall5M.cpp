//Name of class:	CWall5m
//Main author:		Toyan Green
//Summary:			This class is responsible for 5 metre walls
//					in the game.
//Functions:		VOnResourceAcquire
//Based on:			CGCObjPlatform

#ifndef _CWALL5M_H_
#include "CWall5M.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CWall5M, "TexturePacker/Sprites/Walls/Wall5m/Wall5m.plist", "Wall5mIdle", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CWall5M );

void CWall5M::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CWall5M);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CWall5M::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWall5M::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
