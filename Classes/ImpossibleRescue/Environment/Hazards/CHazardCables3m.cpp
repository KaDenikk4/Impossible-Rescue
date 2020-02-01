#include "CHazardCables3m.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE( CHazardCables3m, "TexturePacker/Sprites/HorizontalHazards/HorizontalHazards.plist", "HorizontalHazard3m", b2_staticBody, true );

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CHazardCables3m );

CHazardCables3m::CHazardCables3m()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CHazardCables3m ) )
{

}

CHazardCables3m::~CHazardCables3m()
{

}

void CHazardCables3m::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CHazardCables3m );
	CGCObjSpritePhysics::VOnResourceAcquire();
	m_dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(m_dicPList, mk_pszAnim_HazardCablesActive)));
}

// Check if there is valid editor data
bool CHazardCables3m::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CHazardCables3m::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}

