#include "CRightWall.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CRightWall, "TexturePacker/Sprites/Walls/WallRight/WallRight.plist", "RightWall", b2_staticBody, true );

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CRightWall );

void CRightWall::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CRightWall );
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CRightWall::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CRightWall::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
