#include "CFloor.h"


#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CFloor, "TexturePacker/Sprites/Floors/Floors.plist", "Floor", b2_staticBody, true );

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CFloor );

void CFloor::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CFloor );
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CFloor::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CFloor::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
