#include "CHazardCables2m.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CHazardCables2m, "TexturePacker/Sprites/HorizontalHazards/HorizontalHazards.plist", "HorizontalHazard2m", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CHazardCables2m );

CHazardCables2m::CHazardCables2m()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CHazardCables2m ) )
{

}

CHazardCables2m::~CHazardCables2m()
{

}

void CHazardCables2m::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CHazardCables2m );
	CGCObjSpritePhysics::VOnResourceAcquire();
	m_dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(m_dicPList, mk_pszAnim_HazardCablesActive)));
}

// Check if there is valid editor data
bool CHazardCables2m::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CHazardCables2m::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}

