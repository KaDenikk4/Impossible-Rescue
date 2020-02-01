#include "CDoor.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Player/CPlayer.h"
#include "AppDelegate.h"


USING_NS_CC;


static const char* k_pszXmlAttr_HackingId = "HackingID";

CDoor::CDoor()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CDoor))
	, m_v2StartingPos(0.0f, 0.0f)
	, m_bIsActive(false)
	, m_aorHackedEventHandler( nullptr )
{
	m_aorHackedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToStationHackedEvents(*this);
	m_psfxDoorOpenSound = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::DoorOpen);

}


CDoor::~CDoor()
{
	if(m_psfxDoorOpenSound)
	{
		delete m_psfxDoorOpenSound;
		m_psfxDoorOpenSound = nullptr;
	}
	m_aorHackedEventHandler.Release();
}

IN_CPP_CREATION_PARAMS_DECLARE(CDoor, "TexturePacker/Sprites/Door/Door.plist", "Door", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CDoor );

void CDoor::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CDoor);

	CGCObjSpritePhysics::VOnResourceAcquire();

	this->SetSpritePosition(m_v2StartingPos);

	// Animation loop
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, m_pszAnim_DoorClosed)));
}

// Check if there is valid editor data
bool CDoor::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	if (nullptr == rxmlElement)
	{
		return false;
	}

	const tinyxml2::XMLAttribute* pHackingId = rxmlElement->FindAttribute(k_pszXmlAttr_HackingId);

	return((nullptr != pHackingId));
}

void CDoor::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// Set the hacking Id for this door from the editor data
	m_psHackingID = rxmlElement->Attribute(k_pszXmlAttr_HackingId);
}


void CDoor::VOnReset(void)
{
	CGCObjSpritePhysics::VOnReset();

	if (GetPhysicsBody())
	{
		Vec2 v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody()->SetFixedRotation(true);
	}
	
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);

	// Check if the player transition data contains the hacking ID for this door
	// If the ID is found set the door to open, otherwise set it to closed
	if( AppDelegate::GetPlayerDataManager(  )->GetPlayerData(  )->GetPlayerLevelTransitionData(  )->CheckHackingIDHasBeenObtained( m_psHackingID ) )
	{
		m_bIsActive = true;
		RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, m_pszAnim_DoorOpen)));
	}
	else
	{
		RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, m_pszAnim_DoorClosed)));
	}
}

void CDoor::VOnUpdate(f32 fTimeStep)
{
	//logic here
}

void CDoor::VOnResourceRelease(void)
{
	CGCObjSpritePhysics::VOnResourceRelease();
}

bool CDoor::GetIsActive()
{
	return m_bIsActive;
}

void CDoor::VOnCollisionEnter(GCTypeID typeOfObj)
{
	if (GetGCTypeIDOf(CPlayer) == typeOfObj)
	{
		if(m_bIsActive)
		{
			// Raise event to transition to next level
			AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::NextLevel));
		}		
	}
}

void CDoor::VOnCollisionExit(GCTypeID typeOfObj)
{
	if (GetGCTypeIDOf(CPlayer) == typeOfObj)
	{
		if(!m_bIsActive)
		CCLOG("Door inactive.");
	}
}

//Called from parent CHackingStation when it is successfully hacked.
void CDoor::VHack( )
{
	m_bIsActive = true;
}

void CDoor::VOnEventReceived( CStationHackedEvent eventArgs )
{
	if (strcmp("", eventArgs.GetHackID()) == 0)
	{
		return;
	}

	// If the door receives a station hacked event with an Id that matches its own hacking ID, set the door to open
	if (strcmp(m_psHackingID, eventArgs.GetHackID()) == 0)
	{
		m_psfxDoorOpenSound->VPlay();
		m_bIsActive = true;
		ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
		RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, m_pszAnim_DoorOpen)));
	}
}

