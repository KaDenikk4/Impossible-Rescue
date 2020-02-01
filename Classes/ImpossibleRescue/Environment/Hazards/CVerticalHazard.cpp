#include "CVerticalHazard.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "AppDelegate.h"

USING_NS_CC;

IN_CPP_CREATION_PARAMS_DECLARE(CVerticalHazard, "TexturePacker/Sprites/VerticalHazards/VerticalHazards.plist", "VerticalHazard", b2_staticBody, true);

GCFACTORY_IMPLEMENT_CREATEABLECLASS(CVerticalHazard);

static const char* k_pszXmlAttr_HackingId = "HackingID";

CVerticalHazard::CVerticalHazard()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CVerticalHazard))
	, m_bIsActive(true)
	, m_aorHackedEventHandler(nullptr)
{
	m_aorHackedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToStationHackedEvents(*this);
	m_psfxHazardActiveSound = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::Hazard);
}

CVerticalHazard::~CVerticalHazard()
{
	if (m_psfxHazardActiveSound)
	{
		delete m_psfxHazardActiveSound;
		m_psfxHazardActiveSound = nullptr;
	}
	m_aorHackedEventHandler.Release();
}

void CVerticalHazard::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CVerticalHazard);
	CGCObjSpritePhysics::VOnResourceAcquire();
	m_dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
}

// Check if there is valid editor data
bool CVerticalHazard::VIsValidEditorData(const tinyxml2::XMLElement* rxmlElement)
{
	if (nullptr == rxmlElement)
	{
		return false;
	}

	const tinyxml2::XMLAttribute* pHackingId = rxmlElement->FindAttribute(k_pszXmlAttr_HackingId);

	return((nullptr != pHackingId));
}

void CVerticalHazard::VSetEditorData(const tinyxml2::XMLElement* rxmlElement)
{
	m_psHackingID = rxmlElement->Attribute(k_pszXmlAttr_HackingId);
}

void CVerticalHazard::VOnReset( )
{
	CGCObjSpritePhysics::VOnReset();

	// Check if the player transition data contains the hacking ID for this hazard
	// If the ID is found set the hazard to be disabled, otherwise set it to be enabled
	if (AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->CheckHackingIDHasBeenObtained(m_psHackingID))
	{
		// Start disabled		
		m_bIsActive = false;
		m_psfxHazardActiveSound->VStop();
		cocos2d::Animation* pAnimation = GCCocosHelpers::CreateAnimation(m_dicPList, mk_pszAnim_VerticalHazardDisabled);
		// Set the frames per second time the animation should run at
		pAnimation->setDelayPerUnit(AppDelegate::gks_fTimeStep);

		RunAction(GCCocosHelpers::CreateAnimationActionOnce(pAnimation));
	}
	else
	{
		EnableHazard( );
	}
}

void CVerticalHazard::VOnEventReceived( CStationHackedEvent eventArgs )
{
	if (strcmp("", eventArgs.GetHackID()) == 0)
	{
		return;
	}

	// If the hazard receives a station hacked event with an Id that matches its own hacking ID, set the hazard to disabled
	if (strcmp(m_psHackingID, eventArgs.GetHackID()) == 0)
	{
		DisableHazard();
	}
}

bool CVerticalHazard::GetIsHazardEnabled( ) const
{
	return m_bIsActive;
}

void CVerticalHazard::EnableHazard()
{
	m_bIsActive = true;
	m_psfxHazardActiveSound->VPlay(0.5f, true );
	cocos2d::Animation* pAnimation = GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_VerticalHazardActive );
	// Set the frames per second time the animation should run at
	pAnimation->setDelayPerUnit(AppDelegate::gks_fTimeStep);
	// Run the animation
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(pAnimation));
}

void CVerticalHazard::DisableHazard()
{
	m_bIsActive = false;
	m_psfxHazardActiveSound->VStop();
	cocos2d::Animation* pAnimation = GCCocosHelpers::CreateAnimation(m_dicPList, mk_pszAnim_VerticalHazardInactive);
	// Set the frames per second time the animation should run at
	pAnimation->setDelayPerUnit(AppDelegate::gks_fTimeStep);
	// Run the animation
	RunAction(GCCocosHelpers::CreateAnimationActionOnce(pAnimation));
}