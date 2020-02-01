#ifndef _CHORIZONTALLEVELTRANSITIONBORDER_H_
#define _CHORIZONTALLEVELTRANSITIONBORDER_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CHorizontalLevelTransitionBorder
	: public CGCObjSpritePhysics
{
public:
	CHorizontalLevelTransitionBorder( void )
		: CGCObjSpritePhysics( GetGCTypeIDOf( CHorizontalLevelTransitionBorder ) )
	{
	}

	GCFACTORY_DECLARE_CREATABLECLASS( CHorizontalLevelTransitionBorder );
	
	virtual void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

#endif
