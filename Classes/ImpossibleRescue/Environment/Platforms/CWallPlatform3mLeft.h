//Name of class:	CWallPlatform3mLeft
//Summary:			This class is responsible for 3 metre wall platforms, attached on left side.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VHandleFactoryParams, VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CWALLPLATFORM3M_H_
#define _CWALLPLATFORM3M_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

#include "CMovingPlatform.h"

 class CWallPlatform3mLeft
	: public CGCObjSpritePhysics
{
public:
	CWallPlatform3mLeft();
	GCFACTORY_DECLARE_CREATABLECLASS( CWallPlatform3mLeft );

	// params are buffered and then resources acquired on VOnResourceAcquire (Note from GCFramework)
	virtual void VHandleFactoryParams( const CGCFactoryCreationParams& rCreationParams,	cocos2d::Vec2 v2InitialPosition ) override;

	// This will be called exactly once for each CGCObject derived class instance 
	// registered with CGCObjectManager as soon as the TGB level file has stopped 
	// loading- it is an "explicit constructor". (Note from GCFramework)
 	virtual void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
};

#endif
