#ifndef _CVERTICALHAZARD_H_
#define _CVERTICALHAZARD_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#include "ImpossibleRescue/Audio/ISoundEffect.h"

class CVerticalHazard
: public CGCObjSpritePhysics
, ITReceiveEvents< CStationHackedEvent >
{
public:

	GCFACTORY_DECLARE_CREATABLECLASS(CVerticalHazard);
	CVerticalHazard();
	~CVerticalHazard();

	void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement) override;
	virtual void VSetEditorData(const tinyxml2::XMLElement* rxmlElement) override;

	virtual void VOnReset() override;
	virtual void VOnEventReceived( CStationHackedEvent eventArgs ) override;

	bool GetIsHazardEnabled() const;
	
private:

	void EnableHazard();
	void DisableHazard();
	
	cocos2d::ValueMap m_dicPList;
	bool              m_bIsActive;
	CActionOnRelease  m_aorHackedEventHandler;
	const char*       m_psHackingID;
	const char*       mk_pszAnim_VerticalHazardActive   = "VerticalHazardActive";
	const char*       mk_pszAnim_VerticalHazardInactive = "VerticalHazardInactive";
	const char*       mk_pszAnim_VerticalHazardDisabled = "VerticalHazardDisabled";
	ISoundEffect*     m_psfxHazardActiveSound;
};

#endif