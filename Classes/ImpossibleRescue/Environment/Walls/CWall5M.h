#ifndef _CWALL5M_H_
#define _CWALL5M_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CWall5M
	: public CGCObjSpritePhysics
{
public:
	CWall5M( void )
		: CGCObjSpritePhysics( GetGCTypeIDOf( CWall5M ) )
	{
	}

	GCFACTORY_DECLARE_CREATABLECLASS( CWall5M );
	
	virtual void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

#endif
