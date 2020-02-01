#include "CLeftWall.h"


#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CLeftWall, "TexturePacker/Sprites/Walls/WallLeft/WallLeft.plist", "LeftWall", b2_staticBody, true );

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CLeftWall );

void CLeftWall::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CLeftWall );
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CLeftWall::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CLeftWall::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
