#ifndef _CDOOR_H_
#define _CDOOR_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "ImpossibleRescue/Gameplay/IHackable.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Audio/ISoundEffect.h"

class CDoor
	: public CGCObjSpritePhysics
	, public IHackable
	, ITReceiveEvents< CStationHackedEvent >
{
public:
	CDoor();
	virtual ~CDoor();

	GCFACTORY_DECLARE_CREATABLECLASS( CDoor );
	
	// This will be called exactly once for each CGCObject derived class instance 
	// registered with CGCObjectManager as soon as the TGB level file has stopped 
	// loading- it is an "explicit constructor".
	virtual void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	// Set entity variables using editor data
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;

	// OnReset is called for each CGCObject derived class when CGCObjectManager is 
	// reset
	virtual void VOnReset(void) override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick()
	virtual void VOnUpdate(f32 fTimeStep) override;

	// called immediately before the managing object group releases its own assets
	virtual void VOnResourceRelease(void) override;

	bool GetIsActive();
	void VOnCollisionEnter(GCTypeID typeOfObj) override;
	void VOnCollisionExit(GCTypeID typeOfObj) override;

	//Called from parent CHackingStation when it is successfully hacked.
	virtual void VHack() override;

	virtual void VOnEventReceived( CStationHackedEvent eventArgs ) override;
private:
	cocos2d::Vec2		m_v2StartingPos;
	bool				m_bIsActive;

	CActionOnRelease	m_aorHackedEventHandler;
	const char*			m_psHackingID;

	const char* m_pszAnim_DoorOpen = "DoorOpen";
	const char* m_pszAnim_DoorClosed = "DoorClosed";

	ISoundEffect* m_psfxDoorOpenSound;
};

#endif //#ifndef _CDOOR_H_