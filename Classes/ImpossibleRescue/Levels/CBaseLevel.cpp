//Name of class:	CBaseLevel
//Summary:			This base class for all levels created with OGMO. It contains pause menu, handling
//					collisions and fading functionality that each level can utilise.
//
//Functions:		HandleCollisions, onEnter, VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, VOnUpdate,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit, BeginContact, EndContact, PreSolve, PostSolve,
//					SetLevelTransitionEnabled, SetLevelTransitionDisabled, VOnEventReceived,
//					HandleResets, RequestLevelReset, CheckLevelResetRequested, HandleLevelResetRequest,
//					RequestActReset, CheckActResetRequested, HandleActResetRequest,
//					CB_OnPauseButton, CB_OnReturnButton, CB_OnExitButton, CB_OnOptionsButton,
//					UpdateMenu, setHealthUI, VUpdateLevel, GetIsPaused,	GetFadeToBlackAction,
//					GetFadeFromBlackAction,	SetFadeActionWasPlayed,	GetWasFadeActionPlayed,
//					GetBackgroundForFading,	RunFadeFromBlackAction,	RunFadeToBlackAction,
//					AfterFadeFromBlackIsComplete, AfterFadeToBlackIsComplete, ResetFadeActions,
//					GetLevelLabel, SetPause

#include "ImpossibleRescue/Levels/CBaseLevel.h"
#include <algorithm>
#include <stdlib.h>
#include "ImpossibleRescue/Levels/CMenuScene.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Environment/LevelTransitionBorders/CHorizontalLevelTransitionBorder.h"
#include "ImpossibleRescue/Environment/LevelTransitionBorders/CVerticalLevelTransitionBorder.h"
#include "ImpossibleRescue/Player/Movement/CPlayerMovementStates.h"

USING_NS_CC;

static EPlayerMenuActions s_aePlayerMenuActions[] = { EPlayerMenuActions::Menu_MoveDown, EPlayerMenuActions::Menu_MoveUp, 
	EPlayerMenuActions::Menu_ButtonPressed, EPlayerMenuActions::Menu_MoveYAxis, EPlayerMenuActions::Menu_SelectOptions
};

//making keys map array
static cocos2d::Controller::Key s_aeMenuKeys[] = {
cocos2d::Controller::Key::BUTTON_DPAD_DOWN, cocos2d::Controller::Key::BUTTON_DPAD_UP, cocos2d::Controller::Key::BUTTON_A,
	 cocos2d::Controller::Key::JOYSTICK_LEFT_Y, cocos2d::Controller::Key::BUTTON_OPTIONS
};

// this just demos how simple it is to turn on/off logging on a define....
#define ENABLE_COLLISION_TEST_LOGGING

#if defined (ENABLE_COLLISION_TEST_LOGGING)

#define COLLISIONTESTLOG( str )		CCLOG( str )

#else

#define COLLISIONTESTLOG( str )		/*nothing*/

#endif

// Constructor
CBaseLevel::CBaseLevel( GCTypeID idDerivedType )
	: IGCGameLayer							( idDerivedType )
	, m_pcPlayerPrimaryProjectileGroup		( nullptr )
	, m_pcPlayerSecondaryProjectileGroup	( nullptr )
	, m_pcTurretProjectileGroup				( nullptr )
	, m_bPaused								( false )
	, m_LevelTransitionEnabled				( false )
	, m_pcSprBackGround						( nullptr )
	, m_pcSprPauseMenuBackGround			( nullptr )
	, m_eLevelTransitionType				( ELevelTransitionType::Unknown )
	, m_pLevelTransitionEventHandler		( nullptr )
	, m_pPlayerHasDiedEventHandler			( nullptr )
	, m_vCurrentButtonIndex					( 0 )
	, m_vPreviousButtonIndex				( 0 )
	, m_bPlayerDamaged						( false )
	, m_pcControls							( nullptr )
	, m_pcHealthUIFull						( nullptr )
	, m_pcHealthUIDamaged					( nullptr )
	, m_bLevelResetWasRequested				( false )
	, m_bActResetWasRequested				( false )
	, m_psfxButtonPress						( nullptr )
	, m_psfxButtonSelect					( nullptr )
	, m_psfxPauseMenuMusic					( nullptr )
	, m_bHealthUIFullVisibility				( false )
	, m_bHealthUIDamagedVisibility			( false )
	, m_bWasFadePlayed						( false )
	, m_pcLayerFadeIn						( nullptr )
	, m_pcLayerFadeOut						( nullptr )
	, m_bOptionsSelected					( false )
	, m_bControlsMenuDisplayed				( false )
{
	m_pcControllerMenuActionsToButtonMap = std::unique_ptr< TGCActionToKeyMap< EPlayerMenuActions > >(TCreateActionToKeyMap(s_aePlayerMenuActions, s_aeMenuKeys));
	this->scheduleUpdate();
	
	// Subscribe to level transition events
	m_pLevelTransitionEventHandler = AppDelegate::GetEventMediator()->VSubscribeToLevelTransitionEvents(*this);
	// Subscribe to player has died events
	m_pPlayerHasDiedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToPlayerHasDiedEvents(*this);

	//setting sound effects for buttons
	m_psfxButtonPress = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::MenuButtonPressed);
	m_psfxButtonSelect = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::MenuButtonSelected);
	m_psfxPauseMenuMusic = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PauseMenuMusic);
}
//TODO: add a declaration of the used buttons at the constructor

// Destructor
CBaseLevel::~CBaseLevel( )
{
	m_psfxButtonSelect->VStop();
	if (m_psfxButtonSelect)
	{
		delete m_psfxButtonSelect;
		m_psfxButtonSelect = nullptr;
	}

	m_psfxButtonPress->VStop();
	if (m_psfxButtonPress)
	{
		delete m_psfxButtonPress;
		m_psfxButtonPress = nullptr;
	}
	
	m_psfxPauseMenuMusic->VStop();
	if (m_psfxPauseMenuMusic)
	{
		delete m_psfxPauseMenuMusic;
		m_psfxPauseMenuMusic = nullptr;
	}
	m_pLevelTransitionEventHandler.Release();
	m_pPlayerHasDiedEventHandler.Release();

	if (m_pcLayerFadeIn)
	{
		delete m_pcLayerFadeIn;
		m_pcLayerFadeIn = nullptr;
	}

	if (m_pcLayerFadeOut)
	{
		delete m_pcLayerFadeOut;
		m_pcLayerFadeOut = nullptr;
	}
}


//////////////////////////////////////////////////////////////////////////
// in order to guarantee the actions this layer expects we need to 
// initialise the keyboard action map every time onEnter is called - this
// fixes the case where an IGCGameLayer with a different mapping was
// pushed over this one on Director's scene stack
//////////////////////////////////////////////////////////////////////////
void CBaseLevel::onEnter( )
{
	// load the physics shapes from the plist created with PhysicsEditor
	B2dLoadShapesFromPlist( "PhysicsEditor/GameShapes.plist" );

	IGCGameLayer::onEnter( );
}


// on create
//virtual
void CBaseLevel::VOnCreate( )
{
	// create the default object group
	IGCGameLayer::VOnCreate( );

	// cache some useful values 
	const Size  k_sVisibleSize = Director::getInstance( )->getVisibleSize( );
	const Point k_pOrigin      = Director::getInstance( )->getVisibleOrigin( );

	///////////////////////////////////////////////////////////////////////////
	// custom object groups
	//
	// N.B. Cannot do this in CGCObjectGroup internally on construction, 
	// because ObjectGroupRegister calls a virtual function 
	// in the CGCObjectManager interface to check the 
	// types of objects that the group handles
	///////////////////////////////////////////////////////////////////////////

	// create and register the object group for the player primary projectile objects
	m_pcPlayerPrimaryProjectileGroup = new CPlayerPrimaryProjectileGroup( );
	CGCObjectManager::ObjectGroupRegister( m_pcPlayerPrimaryProjectileGroup );

	// create and register the object group for the player secondary projectile objects
	m_pcPlayerSecondaryProjectileGroup = new CPlayerSecondaryProjectileGroup( );
	CGCObjectManager::ObjectGroupRegister( m_pcPlayerSecondaryProjectileGroup );

	AppDelegate::GetPlayerDataManager( )->SetProjectileGroups( m_pcPlayerPrimaryProjectileGroup, m_pcPlayerSecondaryProjectileGroup );

	// create and register the object group for the turret projectile objects
	m_pcTurretProjectileGroup = new CTurretProjectileGroup( );
	CGCObjectManager::ObjectGroupRegister( m_pcTurretProjectileGroup );

	// set "self" as contact listener
	B2dGetWorld( )->SetContactListener( this );

	// PTM_RATIO
	//TODO: need to delete this if unused
	f32 PTM_RATIO = IGCGAMELAYER_B2D_PIXELS_PER_METER;

	b2Vec2 b2v2ScreenCentre_Pixels( ( k_pOrigin.x + ( k_sVisibleSize.width * 0.5f ) ),
	                                ( k_pOrigin.y + ( k_sVisibleSize.height * 0.5f ) ) );
	Vec2 v2ScreenCentre_Pixels( 100.0f, 1000.0f );

	// Load level file and create objects using the factory
	m_cLevelLoader.LoadLevelFile(FileUtils::getInstance()->fullPathForFilename(std::string( VGetLevelFilePath() )).c_str());
	m_cLevelLoader.CreateObjects(CGCFactory_ObjSpritePhysics::GetFactory());

	// Set level background
	m_pcSprBackGround = new CGCObjSprite();
	m_pcSprBackGround->CreateSprite( VGetBackgroundFilePath() );
	m_pcSprBackGround->SetResetPosition(Vec2(k_sVisibleSize.width / 2, k_sVisibleSize.height / 2));
	m_pcSprBackGround->SetParent(IGCGameLayer::ActiveInstance());

	// Set pause menu background
	m_pcSprPauseMenuBackGround = Sprite::create("Loose/Pause_Background_v1.png");
	m_pcSprPauseMenuBackGround->setPosition(Vec2(k_sVisibleSize.width / 2, k_sVisibleSize.height / 2));
	this->addChild(m_pcSprPauseMenuBackGround, 1);
	m_pcSprPauseMenuBackGround->setVisible(false);

	///////////////////////////////////////////////////////////////////////////////////
	///
	///
	//TODO: sprite for the controls + plus volume regulations

	m_pcControls = Sprite::create("Loose/Controls_v3.png");
	m_pcControls->setPosition(Vec2(k_sVisibleSize.width / 2, k_sVisibleSize.height / 2));
	this->addChild(m_pcControls, 1);
	m_pcControls->setVisible(false);
	//new buttons implementation here
	//
	//creating exit button
	
	m_pcExitButton = new CButton(k_pOrigin.x + (k_sVisibleSize.width * 0.5f), k_pOrigin.y - 350 + (k_sVisibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/Main-Menu_Pause_Pressed_IDEA_v1.png",
			"Loose/Main-Menu_Pause_IDEA_v1.png",
			CC_CALLBACK_1(CBaseLevel::CB_OnExitButton, this)));
	Menu* pMenu = Menu::create(m_pcExitButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	m_pcExitButton->setVisibility(false);

	//creating resume button

	m_pcResumeButton = new CButton(k_pOrigin.x + (k_sVisibleSize.width * 0.5f), k_pOrigin.y + 50 + (k_sVisibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/Resume_Paused_Pressed_IDEA_v1.png",
			"Loose/Resume_Paused_IDEA_v1.png",
			CC_CALLBACK_1(CBaseLevel::CB_OnPauseButton, this)));
	pMenu = Menu::create(m_pcResumeButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	m_pcResumeButton->setVisibility(false);

	//creating options button
	
	m_pcOptionsButton = new CButton(k_pOrigin.x + (k_sVisibleSize.width * 0.5f), k_pOrigin.y - 150 + (k_sVisibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/Controls_Paused_Pressed_IDEA_v1.png",
			"Loose/Controls_Paused_IDEA_v1.png",
			CC_CALLBACK_1(CBaseLevel::CB_OnOptionsButton, this)));
	pMenu = Menu::create(m_pcOptionsButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	m_pcOptionsButton->setVisibility(false);

	//creating return button

	m_pcReturnButton = new CButton(k_pOrigin.x + 670 + (k_sVisibleSize.width * 0.5f), k_pOrigin.y - 400 + (k_sVisibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/Back_button_Pressed.png",
			"Loose/Back_button.png",
			CC_CALLBACK_1(CBaseLevel::CB_OnReturnButton, this)));
	pMenu = Menu::create(m_pcReturnButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	m_pcReturnButton->setVisibility(false);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//populating the array of the buttons
	m_apcButtonArray[0] = m_pcResumeButton;
	m_apcButtonArray[1] = m_pcOptionsButton;
	m_apcButtonArray[2] = m_pcExitButton;

	m_pcLayerFadeIn = FadeIn::create( m_kfFadeToBlackTime );
	m_pcLayerFadeOut = FadeOut::create( m_kfFadeFromBlackTime );

	m_pcLayerFadeIn->retain();
	m_pcLayerFadeOut->retain();

	//Setup black background
	m_pcBlackPanelForFading = new Sprite();
	m_pcBlackPanelForFading = Sprite::create( "Loose/BlackBackground.png" );
	m_pcBlackPanelForFading->setPosition( Vec2(k_sVisibleSize.width / 2, k_sVisibleSize.height / 2) );
	m_pcBlackPanelForFading->setOpacity( 0 );
	this->addChild( m_pcBlackPanelForFading, 1 );

	//Setup level label
	m_pcLevelLabel = new Label();
	m_pcLevelLabel = Label::createWithTTF( "Level 1", "fonts/ethnocentric_rg.ttf", 50.0f );
	m_pcLevelLabel->setPosition( Vec2( k_sVisibleSize.width / 2, k_sVisibleSize.height / 2 ) );
	m_pcLevelLabel->enableOutline( Color4B::BLACK, 3 );
	m_pcLevelLabel->setAlignment( TextHAlignment::CENTER );
	m_pcLevelLabel->setOpacity( 0 );
	this->addChild( m_pcLevelLabel, 1 );
}

void CBaseLevel::SetLevelTransitionEnabled( )
{
	m_LevelTransitionEnabled = true;
}

void CBaseLevel::SetLevelTransitionDisabled( )
{
	m_LevelTransitionEnabled = false;
}

void CBaseLevel::VOnEventReceived( CLevelTransitionEvent eventArgs )
{
	m_eLevelTransitionType = eventArgs.GetTransitionType();
	SetLevelTransitionEnabled();
}

void CBaseLevel::VOnEventReceived( CPlayerHasDiedEvent eventArgs )
{
	// ToDo Show death message
	if( eventArgs.GetLivesRemaining(  ) != 0 )
	{
		RequestLevelReset();
	}
	else
	{
		//Can be act reset if we'd like to change it.
		RequestLevelReset();
	}
}

void CBaseLevel::HandleResets( )
{
	if (CheckLevelResetRequested())
	{
		HandleLevelResetRequest();
	}
	else if(CheckActResetRequested())
	{
		HandleActResetRequest();
	}
}

void CBaseLevel::RequestLevelReset( )
{
	m_bLevelResetWasRequested = true;
}

bool CBaseLevel::CheckLevelResetRequested( ) const
{
	return m_bLevelResetWasRequested;
}

void CBaseLevel::HandleLevelResetRequest( )
{
	m_bLevelResetWasRequested = false;
	VRestartLevel();
}

void CBaseLevel::RequestActReset( )
{
	m_bActResetWasRequested = true;
}

bool CBaseLevel::CheckActResetRequested( ) const
{
	return m_bActResetWasRequested;
}

void CBaseLevel::HandleActResetRequest( )
{
	m_bActResetWasRequested = false;
	VRestartAct();
}

void CBaseLevel::CB_OnPauseButton(Ref* pSender)
{
	if( GetFadeFromBlackAction()->isDone() || AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetIsTransitioningBetweenAreas() )
	{
				
	//implementing the pause menu here

		if( GetIsPaused() )
		{

			m_psfxButtonPress->VPlay();//sound
			// Stop the pause menu music
			m_psfxPauseMenuMusic->VStop();

			// This event will resume all in game audio
			AppDelegate::GetEventMediator()->VPublishGameWasResumedEvent( CGameResumedEvent() );

			//set visibility of the buttons
			m_pcExitButton->setVisibility( false );
			m_pcResumeButton->setVisibility( false );
			m_pcOptionsButton->setVisibility( false );
						
			m_pcReturnButton->setVisibility( false );
			m_pcControls->setVisible( false );
			m_pcSprPauseMenuBackGround->setVisible( false );
		}
		else if( !GetIsPaused() )
		{

			m_psfxButtonPress->VPlay();//sound
			m_pcExitButton->setVisibility( true );
			m_pcResumeButton->setVisibility( true );
			m_pcOptionsButton->setVisibility( true );

			//m_psfxButtonPress->VPlay(); //sound
			m_bOptionsSelected = false;
			
			// This event will pause all in game audio
			AppDelegate::GetEventMediator()->VPublishGameWasPausedEvent( CGamePausedEvent() );

			// Show the pause menu background
			m_pcSprPauseMenuBackGround->setVisible( true );

			// Play the pause menu music
			m_psfxPauseMenuMusic->VPlay( true );
		}
		
		m_bPaused = !m_bPaused;
		
	}
}

void CBaseLevel::CB_OnReturnButton(Ref* pSender)
{
	m_psfxButtonPress->VPlay(); //sound
	m_bOptionsSelected = false;

	//setting visibility of the buttons
	m_pcResumeButton->setVisibility(true);
	m_pcOptionsButton->setVisibility(true);
	m_pcExitButton->setVisibility(true);
	m_pcReturnButton->setVisibility(false);
	m_pcControls->setVisible(false);
	m_bControlsMenuDisplayed = false;
}

void CBaseLevel::CB_OnExitButton(Ref* pSender)
{
	
	Director::getInstance()->resume(); // making sure that game is resumed
	
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::NextLevel));
	ReplaceScene(CMenuLayer::scene());
}

void CBaseLevel::CB_OnOptionsButton(Ref* pSender)
{
	//open options - set visibility of the buttons
	m_psfxButtonPress->VPlay(); //sound
	m_bOptionsSelected = true;
	m_pcResumeButton->setVisibility(false);
	m_pcOptionsButton->setVisibility(false);
	m_pcExitButton->setVisibility(false);
	m_pcReturnButton->setVisibility(true);
	m_pcControls->setVisible(true);
	m_bControlsMenuDisplayed = true;
}

// on update
//virtual 
void CBaseLevel::VOnUpdate( f32 fTimeStep )
{
	if (!GetIsPaused( ))
	{
		VUpdateLevel(fTimeStep);
	}
	
	UpdateMenu();

	HandleResets();
}

void CBaseLevel::VUpdateLevel(f32 fTimeStep)
{
	IGCGameLayer::VOnUpdate(fTimeStep);
	
	HandleCollisions();// this shows how to iterate and respond to the box2d collision info
	//if(AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerHealth()->GetCurrentHealthPoints() == 1)
	//{
	//	m_pcHealthUIDamaged->setVisible(true);
	//	m_pcHealthUIFull->setVisible(false);
	//}
	
	//flag for changing the level

	
	if (m_LevelTransitionEnabled)
	{
		switch (m_eLevelTransitionType)
		{
		case ELevelTransitionType::PreviousArea:
			VTransitionToPreviousScreen();
			break;

		case ELevelTransitionType::NextArea:
			VTransitionToNextScreen();
			break;
			
		case ELevelTransitionType::NextLevel:
			VTransitionToNextLevel();
			break;
		default:
			CCASSERT(false, "Invalid transition type");
		}
	}
}

bool CBaseLevel::GetIsPaused( ) const
{
	return m_bPaused;
}

cocos2d::FadeIn* CBaseLevel::GetFadeToBlackAction()
{
	return m_pcLayerFadeIn;
}

cocos2d::FadeOut* CBaseLevel::GetFadeFromBlackAction()
{
	return m_pcLayerFadeOut;
}

void CBaseLevel::SetFadeActionWasPlayed( bool bWasPlayed )
{
	m_bWasFadePlayed = bWasPlayed;
}

bool CBaseLevel::GetWasFadeActionPlayed()
{
	return m_bWasFadePlayed;
}

cocos2d::Sprite* CBaseLevel::GetBackgroundForFading()
{
	return m_pcBlackPanelForFading;
}

void CBaseLevel::RunFadeFromBlackAction()
{
	if( !m_bWasFadePlayed )
	{
		m_pcBlackPanelForFading->setOpacity( 255 );
		m_pcLevelLabel->setOpacity( 255 );
		m_pcBlackPanelForFading->runAction( m_pcLayerFadeOut );
	}
}

void CBaseLevel::RunFadeToBlackAction()
{
	m_pcBlackPanelForFading->runAction( m_pcLayerFadeIn );
}

//This function should unpause the game
void CBaseLevel::AfterFadeFromBlackIsComplete()
{
	if( GetFadeFromBlackAction()->isDone() && !GetWasFadeActionPlayed() )
	{
		SetPause( false );
		m_pcLevelLabel->setOpacity( 0 );
		SetFadeActionWasPlayed( true );
	}
}

void CBaseLevel::AfterFadeToBlackIsComplete()
{
	if(GetFadeToBlackAction()->isDone() && !GetWasFadeActionPlayed() )
	{
		SetPause( false );
		SetFadeActionWasPlayed( true );
	}
}

void CBaseLevel::ResetFadeActions()
{
	m_pcBlackPanelForFading->setOpacity( 0 );
	m_bWasFadePlayed = false;
}

cocos2d::Label* CBaseLevel::GetLevelLabel()
{
	return m_pcLevelLabel;
}

void CBaseLevel::SetPause( bool bIsPaused )
{
	m_bPaused = bIsPaused;
}

void CBaseLevel::UpdateMenu()
{
	//controller 
	TGCController< EPlayerMenuActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerMenuActionsToButtonMap));

	//checking controller
	if (cController.IsActive())
	{
		//if options are not selected at the same moment
		if( GetIsPaused( ) && !m_bOptionsSelected )
		{
			//our movement in the array - saving buttons positions
			if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_MoveDown))
			{				
				m_psfxButtonSelect->VPlay();
				m_vPreviousButtonIndex = m_vCurrentButtonIndex;
				m_vCurrentButtonIndex++;
				if (m_vCurrentButtonIndex >= 3)
				{
						m_vCurrentButtonIndex = 0;
				}				
			}
			else if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_MoveUp))
			{
				if (m_vCurrentButtonIndex != 0)
				{
					m_psfxButtonSelect->VPlay();
					m_vPreviousButtonIndex = m_vCurrentButtonIndex;
					m_vCurrentButtonIndex--;					
				}
			}
			//setting which button will be highlighted in the array of the buttons
			m_apcButtonArray[m_vPreviousButtonIndex]->ButtonNotHighlighted();
			m_apcButtonArray[m_vCurrentButtonIndex]->ButtonHighlighted();
			
			//press the button which have selected
			if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_ButtonPressed))
			{
				m_apcButtonArray[static_cast<int>(m_vCurrentButtonIndex)]->ButtonPressed();
			}
		}
		//special movement for options menu -> just one button is selected straight away here
		else if (cController.IsActive() && m_bOptionsSelected && GetIsPaused()) // options button is clicked
		{
			m_pcReturnButton->ButtonHighlighted();
			if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_ButtonPressed))
			{
				m_pcReturnButton->ButtonPressed();
				m_bOptionsSelected = false;
			}
		}
		//calling pause menu
		if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_SelectOptions))
		{
			CB_OnPauseButton(this);
		}
		
	}
}


// on destroy
// virtual
void CBaseLevel::VOnDestroy( )
{
	///////////////////////////////////////////////////////////////////////////
	// clean up anything we allocated in opposite order to creation
	///////////////////////////////////////////////////////////////////////////
	
	// delete and unregister the object group for the player primary projectile objects
	CGCObjectManager::ObjectGroupUnRegister( m_pcPlayerPrimaryProjectileGroup );
	delete m_pcPlayerPrimaryProjectileGroup;
	m_pcPlayerPrimaryProjectileGroup = nullptr;

	// delete and unregister the object group for the player secondary projectile objects
	CGCObjectManager::ObjectGroupUnRegister( m_pcPlayerSecondaryProjectileGroup );
	delete m_pcPlayerSecondaryProjectileGroup;
	m_pcPlayerSecondaryProjectileGroup = nullptr;

	// delete and unregister the object group for the turret projectile objects
	CGCObjectManager::ObjectGroupUnRegister( m_pcTurretProjectileGroup );
	delete m_pcTurretProjectileGroup;
	m_pcTurretProjectileGroup = nullptr;

	// clean up the level
	m_cLevelLoader.DestroyObjects();

	if(m_pcHealthUIFull)
	{
		removeChild(m_pcHealthUIFull);
		m_pcHealthUIFull = nullptr;
	}


	if (m_pcHealthUIDamaged)
	{
		removeChild(m_pcHealthUIDamaged);
		m_pcHealthUIDamaged = nullptr;
	}

	if ( m_pcBlackPanelForFading )
	{
		removeChild(m_pcBlackPanelForFading, true);
		m_pcBlackPanelForFading = nullptr;
	}
	if(m_pcResumeButton)
	{
		delete(m_pcResumeButton);
		m_pcResumeButton = nullptr;
	}
	if(m_pcOptionsButton)
	{
		delete(m_pcOptionsButton);
		m_pcOptionsButton = nullptr;
	}
	if(m_pcExitButton)
	{
		delete(m_pcExitButton);
		m_pcExitButton = nullptr;
	}
	if(m_pcReturnButton)
	{
		delete(m_pcReturnButton);
		m_pcReturnButton = nullptr;
		
	}

	if(m_pcLevelLabel)
	{
		removeChild( m_pcLevelLabel, true );
		m_pcLevelLabel = nullptr;
	}
	
	IGCGameLayer::VOnDestroy( );
}

void CBaseLevel::VRestartLevel( )
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( false );
	AppDelegate::GetPlayerDataManager(  )->GetPlayerMovementStates(  )->SetCurrentPlayerMovementState(nullptr);
}

void CBaseLevel::VRestartAct( )
{
	AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates()->SetCurrentPlayerMovementState(nullptr);
}

// begin contact
// insert any logic that relies on detecting the first frame where a 
// contact exists
//virtual 
void CBaseLevel::BeginContact( b2Contact* pB2Contact )
{
	const b2Fixture* pFixtureA = pB2Contact->GetFixtureA( );
	const b2Fixture* pFixtureB = pB2Contact->GetFixtureB( );

	const b2Body* pBodyA = pFixtureA->GetBody( );
	const b2Body* pBodyB = pFixtureB->GetBody( );

	CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*)pBodyA->GetUserData( );
	CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*)pBodyB->GetUserData( );

	//Check collision between fixtures
	if( pGcSprPhysA )
	{
		pGcSprPhysA->VOnCollisionEnter( *pFixtureA, *pFixtureB );
	}
	if( pGcSprPhysB )
	{
		pGcSprPhysB->VOnCollisionEnter( *pFixtureB, *pFixtureA );
	}

	if( !pGcSprPhysA )
	{
		return;
	}
	if( !pGcSprPhysB )
	{
		return;
	}

	if (pB2Contact->IsEnabled())
	{
		if (pGcSprPhysA->GetGCTypeID() != pGcSprPhysB->GetGCTypeID())
		{
			pGcSprPhysA->VOnCollisionEnter(pGcSprPhysB->GetGCTypeID());
			pGcSprPhysB->VOnCollisionEnter(pGcSprPhysA->GetGCTypeID());
		}

		if ( pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CPlayer) && pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CHorizontalLevelTransitionBorder)
			|| pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CHorizontalLevelTransitionBorder) && pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CPlayer) )
		{
			// If the player hit a horizontal transition border, call the virtual method that is mandatorily overriden in each level to execute the correct behaviour
			VOnHorizontalTransitionBorderHit();
		}

		if (pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CPlayer) && pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CVerticalLevelTransitionBorder)
			|| pGcSprPhysA->GetGCTypeID() == GetGCTypeIDOf(CVerticalLevelTransitionBorder) && pGcSprPhysB->GetGCTypeID() == GetGCTypeIDOf(CPlayer))
		{
			// If the player hit a vertical transition border, call the virtual method that is mandatorily overriden in each level to execute the correct behaviour
			VOnVerticalTransitionBorderHit();
		}
	}
}


// end contact
// insert any logic that relies on detecting the last frame where a 
// contact exists
//virtual 
void CBaseLevel::EndContact( b2Contact* pB2Contact )
{
	const b2Fixture* pFixtureA = pB2Contact->GetFixtureA( );
	const b2Fixture* pFixtureB = pB2Contact->GetFixtureB( );

	const b2Body* pBodyA = pFixtureA->GetBody( );
	const b2Body* pBodyB = pFixtureB->GetBody( );

	CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*)pBodyA->GetUserData( );
	CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*)pBodyB->GetUserData( );

	if (pGcSprPhysA)
	{
		pGcSprPhysA->VOnCollisionExit(*pFixtureA, *pFixtureB);
	}
	if (pGcSprPhysB)
	{
		pGcSprPhysB->VOnCollisionExit(*pFixtureB, *pFixtureA);
	}
	
	if( !pGcSprPhysA )
	{
		return;
	}
	if( !pGcSprPhysB )
	{
		return;
	}

	if( pB2Contact->IsEnabled( )
	    && ( pGcSprPhysA->GetGCTypeID( ) != pGcSprPhysB->GetGCTypeID( ) ) )
	{
		pGcSprPhysA->VOnCollisionExit( pGcSprPhysB->GetGCTypeID( ) );
		pGcSprPhysB->VOnCollisionExit( pGcSprPhysA->GetGCTypeID( ) );
	}
}


// pre solve
// insert any logic that needs to be done before a contact is resolved
//virtual 
void CBaseLevel::PreSolve( b2Contact* pB2Contact, const b2Manifold* pOldManifold )
{
	const b2Fixture* pFixtureA = pB2Contact->GetFixtureA( );
	const b2Fixture* pFixtureB = pB2Contact->GetFixtureB( );

	const b2Body* pBodyA = pFixtureA->GetBody( );
	const b2Body* pBodyB = pFixtureB->GetBody( );

	CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*)pBodyA->GetUserData( );
	// if( this is not a GC object )
	if( pGcSprPhysA == nullptr )
	{
		return;
	}

	CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*)pBodyB->GetUserData( );
	// if( this is not a GC object )
	if( pGcSprPhysB == nullptr )
	{
		return;
	}
}


// post solve
// insert any logic that needs to be done after a contact is resolved
// e.g. check the types and double the impulse
//virtual 
void CBaseLevel::PostSolve( b2Contact* pB2Contact, const b2ContactImpulse* pImpulse )
{
}

// this function can only look at the collisions that happened (and which 
// have potentially been resolved) in the previous physics step
// 
// N.B. it is totally possible to get a callback after collisions have been 
// detected, but before they're resolved so you can choose to ignore them - 
// e.g. for gameplay reasons like jumping up through a platform
// 
void CBaseLevel::HandleCollisions( )
{
	// check for collisions
	b2Body* pBodyToDestroy = nullptr;
	for( const b2Contact* pB2Contact = IGCGameLayer::ActiveInstance( )->B2dGetWorld( )->GetContactList( );
	     nullptr != pB2Contact;
	     pB2Contact = pB2Contact->GetNext( ) )
	{
		const b2Fixture* pFixtureA = CGCObjSpritePhysics::FromB2DContactGetFixture_A( pB2Contact );
		const b2Fixture* pFixtureB = CGCObjSpritePhysics::FromB2DContactGetFixture_B( pB2Contact );

		CGCObjSpritePhysics* pGcSprPhysA = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(pFixtureA);
		CGCObjSpritePhysics* pGcSprPhysB = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(pFixtureB);
		
		if (pGcSprPhysA)
		{
			pGcSprPhysA->VHandleCollision(*pFixtureA, *pFixtureB);
		}
		if (pGcSprPhysB)
		{
			pGcSprPhysB->VHandleCollision(*pFixtureB, *pFixtureA);
		}
		
		// return if either physics body has null user data		
		if( !pGcSprPhysA || !pGcSprPhysB)
		{
			return;
		}

		pGcSprPhysA->VHandleCollision( *pGcSprPhysB );
		pGcSprPhysB->VHandleCollision( *pGcSprPhysA );
	}
}
