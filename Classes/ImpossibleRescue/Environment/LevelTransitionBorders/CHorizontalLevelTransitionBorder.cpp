//Name of class:	CHorizontalLevelTransitionBorder
//Main author:		Toyan Green
//Summary:			This class is responsible for horizontal level transition border
//					in the game.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjPlatform

#ifndef _CHORIZONTALLEVELTRANSITIONBORDER_H_
#include "CHorizontalLevelTransitionBorder.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CHorizontalLevelTransitionBorder, "TexturePacker/Sprites/CollisionBorders/HorizontalBorder/HorizontalBorder.plist", "HorizontalBorder", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CHorizontalLevelTransitionBorder );

void CHorizontalLevelTransitionBorder::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CHorizontalLevelTransitionBorder);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CHorizontalLevelTransitionBorder::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CHorizontalLevelTransitionBorder::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
