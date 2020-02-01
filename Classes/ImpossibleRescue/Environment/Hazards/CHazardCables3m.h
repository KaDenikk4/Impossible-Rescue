#ifndef _CHAZARDCABLES3M_H_
#define _CHAZARDCABLES3M_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CHazardCables3m : public CGCObjSpritePhysics
{
public:

	GCFACTORY_DECLARE_CREATABLECLASS( CHazardCables3m );
	CHazardCables3m();
	~CHazardCables3m();

	void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;

private:

	cocos2d::ValueMap			m_dicPList;
	const char*					mk_pszAnim_HazardCablesActive = "HorizontalHazard3mActive";
};

#endif