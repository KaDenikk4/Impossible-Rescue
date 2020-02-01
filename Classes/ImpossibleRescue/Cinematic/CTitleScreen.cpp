// Name of class:	CTitleScreen
// Summary:			Class responsible for displaying the splash/title screen.
//					Skipping it, should lead the player to the main menu.
// Functions:		onEnter, VOnCreate, VOnUpdate, VOnDestroy

#include "CTitleScreen.h"
#include "ImpossibleRescue/Levels/CMenuScene.h"
#include "ImpossibleRescue/Utilities/CTimerHelper.h"


static EPlayerCutsceneActions s_aePlayerCutsceneActions[] = { EPlayerCutsceneActions::SkipCutscene };
static cocos2d::Controller::Key s_aeCutsceneKeys[] = { cocos2d::Controller::Key::BUTTON_A };

CTitleScreen::CTitleScreen()
	: IGCGameLayer( GetGCTypeIDOf( CTitleScreen ) )
	, m_pcPressXToContinueLabel	( nullptr )
	, m_pcTitleScreenBackground	( nullptr )
	, m_pcSplashScreen			( nullptr )
	, m_pcTitleScreenFadeIn		( nullptr )
	, m_pcSplashScreenFadeIn	( nullptr )
	, m_pcSplashScreenFadeOut	( nullptr )
	, m_pcTimerForBlinkingOn	( nullptr )
	, m_pcTimerForBlinkingOff	( nullptr )
	, m_bSplashScreenFaded		( false )

{
	m_pcControllerCutsceneActionsToButtonMap = std::unique_ptr<TGCActionToKeyMap<EPlayerCutsceneActions>>
		( TCreateActionToKeyMap( s_aePlayerCutsceneActions, s_aeCutsceneKeys ) );
}


CTitleScreen::~CTitleScreen()
{
}

//This function adds all the label and sprites to the scene
//and prepares them to run FadeIn and FadeOut actions.
void CTitleScreen::onEnter()
{
	IGCGameLayer::onEnter();

	m_pcPressXToContinueLabel = new Label();
	m_pcPressXToContinueLabel = Label::createWithTTF( "Press X to continue", "fonts/ethnocentric_rg.ttf", 60 );
	m_pcPressXToContinueLabel->enableOutline( Color4B::BLACK, 3 );
	m_pcPressXToContinueLabel->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
	m_pcPressXToContinueLabel->setPosition( 960.0f, 540.0f );

	//Adding an integer as a second parameter in this function sets the "order layer"
	//The higher the number, the more "on top" the layer is.
	this->addChild( m_pcPressXToContinueLabel, 2 );

	//Using cocos2d::Sprite instead of CGCObjSprite allows adding sprites to the layer
	//without having to generate a .plist file.
	m_pcTitleScreenBackground = new Sprite();
	m_pcTitleScreenBackground = Sprite::create( "loose/Planet-Mars_Cutscene.png" );
	m_pcTitleScreenBackground->setPosition( 960.0f, 540.0f );
	this->addChild( m_pcTitleScreenBackground, 1 );

	m_pcSplashScreen = new Sprite();
	m_pcSplashScreen = Sprite::create( "loose/Splash_Screen.png" );
	m_pcSplashScreen->setPosition( 960.0f, 540.0f );
	this->addChild( m_pcSplashScreen, 1 );

	//All actions need to have retain() called, since they'd get autoreleased before they were used.
	m_pcTitleScreenFadeIn = new FadeIn();
	m_pcTitleScreenFadeIn = FadeIn::create( 5.0f );
	m_pcTitleScreenFadeIn->retain();

	m_pcSplashScreenFadeIn = new FadeIn();
	m_pcSplashScreenFadeIn = FadeIn::create( 3.0f );
	m_pcSplashScreenFadeIn->retain();

	m_pcSplashScreenFadeOut = new FadeOut();
	m_pcSplashScreenFadeOut = FadeOut::create( 3.0f );
	m_pcSplashScreenFadeOut->retain();

	//Preparing timers for blinking of the "Press X to continue" label
	m_pcTimerForBlinkingOn = new CTimerHelper(0.5f);
	m_pcTimerForBlinkingOff = new CTimerHelper( 0.5f );
	
	//Setting opacity of the screen elements to 0 to allow fade in and out actions
	m_pcTitleScreenBackground->setOpacity( 0 );
	m_pcPressXToContinueLabel->setOpacity( 0 );

	m_pcSplashScreen->setOpacity( 0 );

	//Running the first action as soon as the scene gets created.
	m_pcSplashScreen->runAction( m_pcSplashScreenFadeIn );	
}

void CTitleScreen::VOnCreate( void )
{
	IGCGameLayer::VOnCreate();
	
}

void CTitleScreen::VOnUpdate( f32 fTimeStep )
{
	IGCGameLayer::VOnUpdate( fTimeStep );

	//Caching a reference to the mapped controller.
	TGCController< EPlayerCutsceneActions > cController = TGetActionMappedController( CGCControllerManager::eControllerOne, (*m_pcControllerCutsceneActionsToButtonMap) );

	//Pressing the SkipCutscene button should put player straight to the menu.
	if( cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) )
	{
		ReplaceScene( CMenuLayer::scene() );
	}

	//After splash screen faded in, start fade out and show the title screen background
	if( m_pcSplashScreenFadeIn->isDone() && !m_bSplashScreenFaded )
	{
		m_pcSplashScreen->runAction( m_pcSplashScreenFadeOut );
		m_pcTitleScreenBackground->runAction( m_pcTitleScreenFadeIn );
		m_bSplashScreenFaded = true;
	}

	//When the title screen background is fully faded in, display "Press X to continue" message blinking
	if( m_pcTitleScreenFadeIn->isDone() )
	{
		if( !m_pcTimerForBlinkingOn->GetTimerCompleted() )
		{
			m_pcTimerForBlinkingOn->RunTimer( fTimeStep );
			m_pcTimerForBlinkingOff->ResetTimer();
			m_pcPressXToContinueLabel->setOpacity( 255 );
		}

		else if( m_pcTimerForBlinkingOn->GetTimerCompleted() )
		{
			m_pcTimerForBlinkingOff->RunTimer( fTimeStep );
			m_pcPressXToContinueLabel->setOpacity( 0 );

			if( m_pcTimerForBlinkingOff->GetTimerCompleted() )
			{
				m_pcTimerForBlinkingOn->ResetTimer();
			}
		}
	}	
}

//This function is responsible for the clean up of the scene.
void CTitleScreen::VOnDestroy( void )
{
	IGCGameLayer::VOnDestroy();

	if(m_pcPressXToContinueLabel)
	{
		//removeChild function deletes the pointer, trying to use keyword delete throws 0xDDDDDDD error
		removeChild( m_pcPressXToContinueLabel );
		m_pcPressXToContinueLabel = nullptr;
	}

	if (m_pcTitleScreenBackground)
	{
		//removeChild function deletes the pointer, trying to use keyword delete throws 0xDDDDDDD error
		removeChild( m_pcTitleScreenBackground );
		m_pcTitleScreenBackground = nullptr;
	}

	if(m_pcTitleScreenFadeIn)
	{
		m_pcTitleScreenFadeIn->release(  );
		m_pcTitleScreenFadeIn = nullptr;
	}
	if( m_pcSplashScreenFadeIn )
	{
		m_pcSplashScreenFadeIn->release(  );
		m_pcSplashScreenFadeIn = nullptr;
	}
	if( m_pcSplashScreenFadeOut )
	{
		m_pcSplashScreenFadeOut->release(  );
		m_pcSplashScreenFadeOut = nullptr;
	}
}

