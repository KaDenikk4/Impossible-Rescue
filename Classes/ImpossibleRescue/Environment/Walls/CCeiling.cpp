#include "CCeiling.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CCeiling, "TexturePacker/Sprites/Ceiling/Ceiling.plist", "Ceiling", b2_staticBody, true );

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CCeiling );

void CCeiling ::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CCeiling );
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CCeiling::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CCeiling::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
