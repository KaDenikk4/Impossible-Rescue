#ifndef _GCOBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

class CLeftWall
	: public CGCObjSpritePhysics
{
public:
	CLeftWall()
		: CGCObjSpritePhysics( GetGCTypeIDOf( CLeftWall ) )
	{

	}

	GCFACTORY_DECLARE_CREATABLECLASS( CLeftWall );
	
	virtual void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

