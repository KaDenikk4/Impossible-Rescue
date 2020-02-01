#ifndef CRIGHT_WALL
#define CRIGHT_WALL


#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CRightWall
	: public CGCObjSpritePhysics
{
public:
	CRightWall()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CRightWall ) )
	{
		
	}
	
	GCFACTORY_DECLARE_CREATABLECLASS( CRightWall );

	virtual void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;	
};

#endif