// Name of class:	CCinematicScene
// Summary:			Class responsible for displaying the cinematic sequences
//					before level 1, divided by ticker text that can be skipped.
// Functions:		onEnter, VOnCreate, VOnUpdate, VOnDestroy

#include "CCinematicScene.h"
#include "ImpossibleRescue/Levels/Level1/CLevel1Area1.h"
#include "ImpossibleRescue/UI/TickerText.h"

static EPlayerCutsceneActions s_aePlayerCutsceneActions[] = { EPlayerCutsceneActions::SkipCutscene };
static cocos2d::Controller::Key s_aeCutsceneKeys[] = { cocos2d::Controller::Key::BUTTON_A };


CCinematicScene::CCinematicScene()
	: IGCGameLayer(GetGCTypeIDOf (CCinematicScene))
	, m_pcFadeInDanielleBackground	( nullptr )
	, m_pcTickerTextPanel				( nullptr )
	, m_bPanelFadingOut					( false )
	, m_psfxTickerTextSound				( nullptr )
	, m_pcSkipButton					( nullptr )
	, m_pcDanielleBackgroundImage		( nullptr )
	, m_pcMarsBackgroundSprite			( nullptr )
	, m_pcMarsBackgroundFadeToAction	( nullptr )
{
	m_pcControllerCutsceneActionsToButtonMap = std::unique_ptr<TGCActionToKeyMap<EPlayerCutsceneActions>>
												( TCreateActionToKeyMap( s_aePlayerCutsceneActions, s_aeCutsceneKeys ));

	m_psfxTickerTextSound = AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::TickerText );
	
	this->scheduleUpdate();
}

CCinematicScene::~CCinematicScene()
{
	
}

void CCinematicScene::onEnter()
{
	IGCGameLayer::onEnter();
	
}

//This function is responsible for setting up the scene.
void CCinematicScene::VOnCreate( void )
{
	IGCGameLayer::VOnCreate();

	//Caching values as given in GCFramework
	const Size  k_sVisibleSize		= Director::getInstance()->getVisibleSize();
	const Point k_pOrigin			= Director::getInstance()->getVisibleOrigin();

	//All actions need to have retain() called, since they'd get autoreleased before they were used.
	m_pcFadeInDanielleBackground = new FadeIn();
	m_pcFadeInDanielleBackground	= FadeIn::create( 3.0f );
	m_pcFadeInDanielleBackground->retain();

	m_pcMarsBackgroundFadeToAction = new FadeTo();
	m_pcMarsBackgroundFadeToAction = FadeTo::create( 3.0f, 50 );
	m_pcMarsBackgroundFadeToAction->retain();
	
	m_eCurrentCutsceneStage = ECutsceneStages::FirstPanel;

	m_pcTickerTextPanel = new TickerText( m_rcTextFirstPanel, 60.0f, 0.02f );
	m_pcTickerTextPanel->SetTextPosition( 50.0f, 40.0f );
	m_pcTickerTextPanel->getText()->setTextColor( Color4B::WHITE );
	m_pcTickerTextPanel->SetTextAreaSize(1800.0f, 1000.0f);

	//Adding an integer as a second parameter in this function sets the "order layer"
	//The higher the number, the more "on top" the layer is.
	this->addChild( m_pcTickerTextPanel->getText(), 2 );

	m_psfxTickerTextSound->VPlay( true );

	m_pcSkipButton = new Sprite();
	m_pcSkipButton = Sprite::create( "loose/SkipButton.png" );
	m_pcSkipButton->setPosition( 1670.0f, 100.0f );
	this->addChild( m_pcSkipButton, 2 );

	m_pcDanielleBackgroundImage = new Sprite();
	m_pcDanielleBackgroundImage = Sprite::create( "loose/Danielle_Cutscene.png" );
	m_pcDanielleBackgroundImage->setPosition( 960.0f, 540.0f );
	this->addChild( m_pcDanielleBackgroundImage, 1 );

	m_pcDanielleBackgroundImage->setOpacity( 0 );

	m_pcMarsBackgroundSprite = new Sprite();
	m_pcMarsBackgroundSprite = Sprite::create( "loose/Planet-Mars_Cutscene.png" );
	m_pcMarsBackgroundSprite->setPosition( 960.0f, 540.0f );
	this->addChild( m_pcMarsBackgroundSprite, 1 );
	m_pcMarsBackgroundSprite->setOpacity( 0 );
	

	//Run the first action when the scene is created.
	m_pcMarsBackgroundSprite->runAction( m_pcMarsBackgroundFadeToAction );
	
}

void CCinematicScene::VOnUpdate( f32 fTimeStep )
{
	IGCGameLayer::VOnUpdate( fTimeStep );
	TGCController< EPlayerCutsceneActions > cController = TGetActionMappedController( CGCControllerManager::eControllerOne, (*m_pcControllerCutsceneActionsToButtonMap) );

	//Switch case to allow updating each panel with ticker text and fading background.
	switch (m_eCurrentCutsceneStage)
	{
	case ECutsceneStages::FirstPanel:

		//Run ticker text
		m_pcTickerTextPanel->TextAnimation(fTimeStep);

		//Make sure that the text sound gets stopped when it finishes typing.
		if(m_pcTickerTextPanel->GetTextEnd() )
		{
			m_pcTickerTextPanel->GetTypingSound()->VStop();
			m_psfxTickerTextSound->VStop();
		}

		//Skipping functionality, stops fading, sets the desired opacity, completes the ticker text and stops the ticking sound.
		if( cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) && !m_pcTickerTextPanel->GetTextEnd() )
		{
			//ToDo: Complete TickerText here
			m_pcTickerTextPanel->SetIsSkipped(true);
			m_pcTickerTextPanel->GetTypingSound()->VStop();
			stopAction( m_pcMarsBackgroundFadeToAction );
			m_pcMarsBackgroundSprite->setOpacity( 50 );
			m_psfxTickerTextSound->VStop();
		}
		//Skipping to the next panel resets the ticker text and sets its new content and area to show it next to picture of Danielle.
		//Hiding the first sprite.
		else if(cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) && m_pcTickerTextPanel->GetTextEnd())
		{
			m_pcTickerTextPanel->SetText( m_rcTextSecondPanel );
			m_pcTickerTextPanel->Reset();
			m_psfxTickerTextSound->VPlay( true );
			m_pcDanielleBackgroundImage->runAction( m_pcFadeInDanielleBackground );
			m_pcTickerTextPanel->SetTextPosition( 800.0f, 40.0f );
			m_pcTickerTextPanel->SetTextAreaSize( 1000.0f, 1000.0f );
			m_pcMarsBackgroundSprite->setOpacity( 0 );
			m_eCurrentCutsceneStage = ECutsceneStages::SecondPanel;
		}
		
		break;

	case ECutsceneStages::SecondPanel:
		//Run ticker text
		m_pcTickerTextPanel->TextAnimation( fTimeStep );

		//Make sure that the text sound gets stopped when it finishes typing.
		if( m_pcTickerTextPanel->GetTextEnd() )
		{
			m_pcTickerTextPanel->GetTypingSound()->VStop();
			m_psfxTickerTextSound->VStop();
		}
		
		if( cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) && !m_pcTickerTextPanel->GetTextEnd() )
		{
			//Complete TickerText here
			m_pcTickerTextPanel->SetIsSkipped( true );
			m_pcTickerTextPanel->GetTypingSound()->VStop();
			m_psfxTickerTextSound->VStop();
		}
		else if( cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) && m_pcTickerTextPanel->GetTextEnd() )
		{
			//If action is left running it would crash - cocos2d asserts no actions are left running between scenes.
			if( !m_pcFadeInDanielleBackground->isDone() )
			{
				stopAction( m_pcFadeInDanielleBackground );
			}
			//Skipping would move player to the first level.
			Director::getInstance()->replaceScene( TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene() );
		}
		
		break;
	}
}

//This function is responsible for the clean up of the scene
void CCinematicScene::VOnDestroy( void )
{
	IGCGameLayer::VOnDestroy();

	if( m_psfxTickerTextSound )
	{
		delete m_psfxTickerTextSound;
		m_psfxTickerTextSound = nullptr;
	}
	
	if( m_pcFadeInDanielleBackground )
	{
		delete m_pcFadeInDanielleBackground;
		m_pcFadeInDanielleBackground = nullptr;
	}

	if( m_pcTickerTextPanel )
	{
		delete m_pcTickerTextPanel;
		m_pcTickerTextPanel = nullptr;
	}

	if ( m_pcSkipButton )
	{
		//removeChild function deletes the pointer, trying to use keyword delete throws 0xDDDDDDD error
		removeChild( m_pcSkipButton );
		m_pcSkipButton = nullptr;
	}

	if( m_pcMarsBackgroundSprite )
	{
		//removeChild function deletes the pointer, trying to use keyword delete throws 0xDDDDDDD error
		removeChild( m_pcMarsBackgroundSprite );
		m_pcMarsBackgroundSprite = nullptr;
	}

	if (m_pcMarsBackgroundFadeToAction)
	{
		m_pcMarsBackgroundFadeToAction->release(  );
		m_pcMarsBackgroundFadeToAction = nullptr;
	}
	
}
