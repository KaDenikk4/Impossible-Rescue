//Name of class:	CContainerAsset
//Summary:			This class is responsible for containers asset in the game.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#include "CContainersAsset.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"


CContainersAsset::CContainersAsset()
	:CGCObjSpritePhysics()
{
}


CContainersAsset::~CContainersAsset()
{
}

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CContainersAsset, "TexturePacker/Sprites/Containers/Containers.plist", "Containers", b2_staticBody, true );

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CContainersAsset );

void CContainersAsset::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CContainersAsset );
	CGCObjSpritePhysics::VOnResourceAcquire();
}

// Check if there is valid editor data
bool CContainersAsset::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CContainersAsset::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
