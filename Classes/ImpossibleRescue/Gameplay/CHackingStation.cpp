// Name of class:	CHackingStation
// Summary:			Class responsible for creating a hacking station player can interact with.
//					Once it's hacked, it can relate that information to doors and other objects.
//					
// Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData,  SetProgressBar, InitialiseProgressBar,
//					VOnReset, VOnUpdate, VOnResourceRelease, VOnCollisionEnter,	VOnCollisionExit,
//					SetHackingID, SetStationIsHacked, SetStationIsBeingHacked, SetStationTimer,
//					GetIsStationActive, GetIsStationHacked, AddHackingLabels, DisplayLabelForSeconds,
//					RemoveLabels, GetLabelsOffset, Hack
//					
// ToDo:			Refactor class to use enum for states rather than multiple bools and functions

#include "CHackingStation.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Player/CPlayer.h"
#include "ImpossibleRescue/Utilities/CLabelHelper.h"
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"
#include "AppDelegate.h"


USING_NS_CC;

static const char* k_pszXmlAttr_HackingId = "HackingID";
static const char* k_pszXmlAttr_HackingTimer = "HackingTimer";

CHackingStation::CHackingStation()
	: CGCObjSpritePhysics		( GetGCTypeIDOf( CHackingStation ) )
	, m_v2StartingPos			( 0.0f, 0.0f )
	, m_v2SpritePos				( 0.0f, 0.0f )
	, m_pcHackingBackgroundBar	( nullptr )
	, m_pcHackingInProgressBar	( nullptr )
	, m_bIsStationActive		( false )
	, m_bIsStationHacked		( false )
	, m_bHackingInProgress		( false )
	, m_bWasLabelDisplayed		( false )
	, m_fTimeToHackStation		( 0.0f )
	, m_fPlayerHackingTime		( 0.0f )
	, m_fLabelDisplayTime		( 0.0f )
	, m_eCurrentProgress		( HSS_NotHacked )
	, m_eCurrentProgressOld		( HSS_NotHacked )
	, m_pcPlayer ( nullptr )
	, m_psfxHacking(nullptr)
{
	m_psfxHacking = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::HackingInProgress);
	m_psfxHackingCompleted = AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::MenuButtonSelected );
}


CHackingStation::~CHackingStation()
{
	m_psfxHacking->VStop();
	if( m_psfxHacking )
	{
		delete m_psfxHacking;
		m_psfxHacking = nullptr;
	}

	if (m_psfxHackingCompleted)
	{
		delete m_psfxHackingCompleted;
		m_psfxHackingCompleted = nullptr;
	}
}


//Helper macro for acquiring assets and attaching box2d base fixture
IN_CPP_CREATION_PARAMS_DECLARE(CHackingStation, "TexturePacker/Sprites/HackingStation/HackingStation.plist", "HackingStation", b2_staticBody, true);

//Helper macro allowing to use OGMO to place hacking stations in levels
GCFACTORY_IMPLEMENT_CREATEABLECLASS( CHackingStation );

//Summary:		Virtual function to be called exactly once for each CGCObject derived class instance
//				registered with CGCObjectManager as soon as the TGB level file has stopped
//				loading- it is an "explicit constructor". (Note from GCFramework)
//			
void CHackingStation::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CHackingStation);

	CGCObjSpritePhysics::VOnResourceAcquire();

	this->SetSpritePosition(m_v2StartingPos);

	InitialiseProgressBar();
		

	m_psfxHacking = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::HackingInProgress);

	// Animation loop
	m_dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(m_dicPList, mk_pszAnim_HackingStationNotHacked)));
}

// Check if there is valid editor data
bool CHackingStation::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	if (nullptr == rxmlElement)
	{
		return false;
	}

	const tinyxml2::XMLAttribute* pHackingId = rxmlElement->FindAttribute(k_pszXmlAttr_HackingId);
	const tinyxml2::XMLAttribute* pHackingTimer = rxmlElement->FindAttribute(k_pszXmlAttr_HackingTimer);

	return((nullptr != pHackingId
		&& nullptr != pHackingTimer));
}

void CHackingStation::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	m_psHackingID = rxmlElement->Attribute( k_pszXmlAttr_HackingId );
	SetStationTimer( rxmlElement->FloatAttribute(k_pszXmlAttr_HackingTimer) );
}

//Summary:	Called for each CGCObject derived class when CGCObjectManager is reset
//			(Note from GCFramework)
//			
void CHackingStation::VOnReset(void)
{
	CGCObjSpritePhysics::VOnReset();

	SetFlippedX( false );
	SetFlippedY( false );
	m_bHackingInProgress = false;
	m_bIsStationActive = false;
	m_bIsStationHacked = false;
	m_bWasLabelDisplayed = false;
	
	m_fLabelDisplayTime = 0.0f;

	//If the station was previously hacked, it will be stored in the player level transition data and is going to be set accordingly
	//when the level is loaded.
	if (AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->CheckHackingIDHasBeenObtained(m_psHackingID))
	{
		m_fPlayerHackingTime = m_fTimeToHackStation;

		m_eCurrentProgress = HSS_HackingCompleted;
		m_eCurrentProgressOld = HSS_HackingCompleted;
		RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(m_dicPList, mk_pszAnimHackingCompleted)));
	}
	else
	{
		m_fPlayerHackingTime = 0.0f;
		m_eCurrentProgress = HSS_NotHacked;
		m_eCurrentProgressOld = HSS_NotHacked;
	}
		
	if (GetPhysicsBody())
	{
		m_v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetLinearVelocity	( b2Vec2( 0.0f, 0.0f ) );
		GetPhysicsBody()->SetTransform		( IGCGameLayer::B2dPixelsToWorld( b2Vec2( m_v2SpritePos.x, m_v2SpritePos.y ) ), 0.0f );
		GetPhysicsBody()->SetFixedRotation	( true );
	}

	
}


//Summary:		Called for each CGCObject derived class when CGCObjectManager is 
//				updated in t2dSCeneGraph onProcessTick() (Note from GCFramework)
//Parameters:	fTimeStep - float indicating timestep in main gameloop
//	
void CHackingStation::VOnUpdate(f32 fTimeStep)
{
	//if the station is not yet hacked and player is standing at the station, allow for hacking it.
	if(!m_bIsStationHacked && m_pcPlayer && m_bIsStationActive )
	{
		m_pcPlayer->HackTheStation( *this );
	}

	//Switch case for different states of the hacking station
	switch( m_eCurrentProgress )
	{
		case HSS_NotHacked:
			{
				if (m_eCurrentProgress != m_eCurrentProgressOld)
				{
					m_pcHackingBackgroundBar->setVisible(false);
					m_pcHackingInProgressBar->setVisible(false);

					m_psfxHacking->VStop();
					
					// ToDo change to not hacking animation
					m_eCurrentProgressOld = m_eCurrentProgress;
				}
			}
			break;
		case HSS_Hacking:
			{
				if (m_eCurrentProgress != m_eCurrentProgressOld)
				{
					m_pcHackingBackgroundBar->setVisible(true);
					m_pcHackingInProgressBar->setVisible(true);

					m_psfxHacking->VPlay(true);
					
					m_eCurrentProgressOld = m_eCurrentProgress;
				}
				//Player hacking time is added until it's higher than the default value on the station
				if( m_fTimeToHackStation > m_fPlayerHackingTime )
				{
					m_fPlayerHackingTime += fTimeStep;
				}

				//When the player hacked for long enough - set station to be hacked
				if( m_fTimeToHackStation <= m_fPlayerHackingTime )
				{
					Hack( );
					RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnimHackingCompleted ) ) );
					m_eCurrentProgress = HSS_HackingCompleted;
				}
			}
			break;

		case HSS_HackingCompleted:
			{
				m_bIsStationActive = false;

				if (m_eCurrentProgress != m_eCurrentProgressOld)
				{
					m_pcHackingBackgroundBar->setVisible(false);
					m_pcHackingInProgressBar->setVisible(false);

					m_psfxHacking->VStop();
					
					m_eCurrentProgressOld = m_eCurrentProgress;
				}
			}
			break;
	}
	
	// Update the hacking progress bar
	SetProgressBar();
}


//Summary:		Called immediately before the managing object group releases its own assets
//				(Note from GCFramework)
//
void CHackingStation::VOnResourceRelease(void)
{
	CGCObjSpritePhysics::VOnResourceRelease();
}

void CHackingStation::VOnCollisionEnter( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture )
{
	//If self fixture is not the hacking station then we should return
	if (FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID())
	{
		return;
	}

	CGCObjSpritePhysics* pSprPhysColliding = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture);

	// If the object that collided with the hacking station was the player, set the station to active, and take a pointer to the player
	
	if (!m_bIsStationHacked && pSprPhysColliding && GetGCTypeIDOf(CPlayer) == pSprPhysColliding->GetGCTypeID( ) )
	{
		CCLOG("Hacking station active.");
		m_bIsStationActive = true;
		m_pcPlayer = dynamic_cast<CPlayer*>(pSprPhysColliding);
	}		
}

void CHackingStation::VOnCollisionExit( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture )
{
	//If self fixture is not the hacking station then we should return
	if (FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID())
	{
		return;
	}

	CGCObjSpritePhysics* pSprPhysColliding = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture);

	//If player is not at the hacking station - set it to inactive (not hackable)
	if (!m_bIsStationHacked && pSprPhysColliding && GetGCTypeIDOf(CPlayer) == pSprPhysColliding->GetGCTypeID() )
	{
		CCLOG("Hacking station inactive.");
		m_bIsStationActive = false;
		SetStationIsBeingHacked( false );
		m_pcPlayer = nullptr;
	}
}

void CHackingStation::SetHackingID( const char* psHackingID )
{
	m_psHackingID = psHackingID;
}

//Summary:		Setter function for hacking in progress
//
void CHackingStation::SetStationIsBeingHacked( bool bPlayerIsHacking )
{

	//RunAction is used for playing correct animations.
	if (bPlayerIsHacking && m_fPlayerHackingTime <= m_fTimeToHackStation)
	{
		RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnimHackingInProgress ) ) );
		m_eCurrentProgress = HSS_Hacking;
	}
	else if (!bPlayerIsHacking && m_eCurrentProgress != HSS_HackingCompleted )
	{
		RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_HackingStationNotHacked ) ) );
		m_eCurrentProgress = HSS_NotHacked;
	}

	m_bHackingInProgress = bPlayerIsHacking;
}


//Summary:		Setter function for the time required for how long hacking station takes to be hacked.
//
void CHackingStation::SetStationTimer( float fStationMaxTimer )
{
	m_fTimeToHackStation = fStationMaxTimer;
}


//Summary:		Getter function for checking if station is active
//
bool CHackingStation::GetIsStationActive()
{
	return m_bIsStationActive;
}


//Summary:		Getter function for checking if station is hacked
//
bool CHackingStation::GetIsStationHacked()
{
	return m_bIsStationHacked;
}

//Summary:		Getter function for label offset
//
cocos2d::Vec2 CHackingStation::GetLabelsOffset()
{
	return m_kv2LabelOffset;
}

//Called when the station is successfully hacked
void CHackingStation::Hack( )
{
	m_psfxHackingCompleted->VPlay();
	AppDelegate::GetEventMediator()->VPublishStationHackedEvent(CStationHackedEvent(m_psHackingID));
}

void CHackingStation::InitialiseProgressBar()
{
	// Setup progress bar background
	if (m_pcHackingBackgroundBar)
	{
		m_pcHackingBackgroundBar->removeFromParentAndCleanup(true);
		m_pcHackingBackgroundBar = nullptr;
	}

	m_pcHackingBackgroundBar = ui::LoadingBar::create("Loose/ProgressBarBackground.png");
	m_pcHackingBackgroundBar->setPercent(100);
	m_pcHackingBackgroundBar->setVisible(false);
	
	
	IGCGameLayer::ActiveInstance()->addChild(m_pcHackingBackgroundBar);

	// Setup progress bar
	if (m_pcHackingInProgressBar)
	{
		m_pcHackingInProgressBar->removeFromParentAndCleanup(true);
		m_pcHackingInProgressBar = nullptr;
	}

	m_pcHackingInProgressBar = ui::LoadingBar::create("Loose/ProgressBarRed.png");
	m_pcHackingInProgressBar->setVisible(false);

	IGCGameLayer::ActiveInstance()->addChild(m_pcHackingInProgressBar);
	
	SetProgressBar();
}

void CHackingStation::SetProgressBar() const
{
	m_pcHackingBackgroundBar->setPosition(GetSpritePosition() + m_kv2LabelOffset);
	m_pcHackingInProgressBar->setPosition(GetSpritePosition() + m_kv2LabelOffset);

	const float fPercentageComplete = ( m_fPlayerHackingTime / m_fTimeToHackStation ) * 100;

	// Change the colour of the hacking station progress bar at set thresholds
	
	if(fPercentageComplete <= 25.0f)
	{
		m_pcHackingInProgressBar->loadTexture("Loose/ProgressBarRed.png");
	}
	else if( fPercentageComplete <= 50.0f )
	{
		m_pcHackingInProgressBar->loadTexture("Loose/ProgressBarOrange.png");
	}
	else if (fPercentageComplete <= 75.0f)
	{
		m_pcHackingInProgressBar->loadTexture("Loose/ProgressBarYellow.png");
	}
	else
	{
		m_pcHackingInProgressBar->loadTexture("Loose/ProgressBarGreen.png");
	}
	
	m_pcHackingInProgressBar->setPercent(fPercentageComplete);
}
