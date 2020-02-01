#ifndef _CVERTICALLEVELTRANSITIONBORDER_H_
#define _CVERTICALLEVELTRANSITIONBORDER_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CVerticalLevelTransitionBorder
	: public CGCObjSpritePhysics
{
public:
	CVerticalLevelTransitionBorder( void )
		: CGCObjSpritePhysics( GetGCTypeIDOf( CVerticalLevelTransitionBorder ) )
	{
	}

	GCFACTORY_DECLARE_CREATABLECLASS( CVerticalLevelTransitionBorder );
	
	virtual void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

#endif
