#ifndef _GCOBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif


class CCeiling
	: public CGCObjSpritePhysics
{
public:
	CCeiling()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CCeiling ) )
	{
		
	}

	GCFACTORY_DECLARE_CREATABLECLASS( CCeiling );

	virtual void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;
};

