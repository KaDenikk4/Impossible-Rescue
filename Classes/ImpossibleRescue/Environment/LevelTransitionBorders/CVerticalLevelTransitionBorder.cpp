//Name of class:	CVerticalLevelTransitionBorder
//Main author:		Toyan Green
//Summary:			This class is responsible for vertical level transition border
//					in the game.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjPlatform

#ifndef _CVERTICALLEVELTRANSITIONBORDER_H_
#include "CVerticalLevelTransitionBorder.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CVerticalLevelTransitionBorder, "TexturePacker/Sprites/CollisionBorders/VerticalBorder/VerticalBorder.plist", "VerticalBorder", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CVerticalLevelTransitionBorder );

void CVerticalLevelTransitionBorder::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CVerticalLevelTransitionBorder);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CVerticalLevelTransitionBorder::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CVerticalLevelTransitionBorder::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
