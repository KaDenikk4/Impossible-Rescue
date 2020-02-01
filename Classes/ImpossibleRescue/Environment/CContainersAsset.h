//Name of class:	CContainerAsset
//Summary:			This class is responsible for containers asset in the game.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CCONTAINERSASSET_H_
#define	_CCONTAINERSASSET_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

class CContainersAsset : CGCObjSpritePhysics
{
public:

	GCFACTORY_DECLARE_CREATABLECLASS( CContainersAsset );
	CContainersAsset();
	~CContainersAsset();
	
	void VOnResourceAcquire( void ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;
};
#endif //_CCONTAINERSASSET_H_
