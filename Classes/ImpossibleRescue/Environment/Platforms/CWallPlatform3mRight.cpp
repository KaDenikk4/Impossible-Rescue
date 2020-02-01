//Name of class:	CWallPlatform3mRight
//Summary:			This class is responsible for 3 metre wall platforms, attached on right side.
//					Using GCFactory macros the objects can be placed in OGMO Editor, and created in the scene via this code.
//Functions:		VHandleFactoryParams, VOnResourceAcquire, VIsValidEditorData, VSetEditorData
//Based on:			CGCObjSpritePhysics

#ifndef _CWALLPLATFORM3M_H_
#include "CWallPlatform3mRight.h"
#endif

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

USING_NS_CC;

// implement the factory method to enable this to be created via CGCFactory_ObjSpritePhysics 
GCFACTORY_IMPLEMENT_CREATEABLECLASS( CWallPlatform3mRight );

CWallPlatform3mRight::CWallPlatform3mRight( )
	: CGCObjSpritePhysics(GetGCTypeIDOf( CWallPlatform3mRight ))
{
	
}

void CWallPlatform3mRight::VHandleFactoryParams( const CGCFactoryCreationParams& rCreationParams,
	cocos2d::Vec2 v2InitialPosition )
{
	//Gets editor parameters
	CGCObjSpritePhysics::VHandleFactoryParams(rCreationParams, v2InitialPosition);
}

// This will be called exactly once for each CGCObject derived class instance 
// registered with CGCObjectManager as soon as the TGB level file has stopped 
// loading- it is an "explicit constructor". (Note from GCFramework)
void CWallPlatform3mRight::VOnResourceAcquire(void)
{
	CGCObjSpritePhysics::VOnResourceAcquire();
	SetFlippedX( true );
}

// Check if there is valid editor data
bool CWallPlatform3mRight::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CWallPlatform3mRight::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}
