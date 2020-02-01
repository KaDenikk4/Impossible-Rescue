#////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CMenuScene.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "ImpossibleRescue/UI/CButton.h"
#include "AppDelegate.h"
#include "Level4/CLevel4Area1.h"
#include "Level4/CLevel4Area2.h"
#include "Level1/CLevel1Area1.h"
#include "Level2/CLevel2Area1.h"
#include "Level3/CLevel3Area1.h"
#include "ImpossibleRescue/UI/TickerText.h"
#include <iostream>
#include <string>
#include "ImpossibleRescue/Cinematic/CCinematicScene.h"
#include "CEndScreen.h"


USING_NS_CC;


//array of the actions
static EPlayerMenuActions s_aePlayerMenuActions[] = { EPlayerMenuActions::Menu_MoveDown, EPlayerMenuActions::Menu_MoveUp, EPlayerMenuActions::Menu_MoveRight, EPlayerMenuActions::Menu_MoveLeft,
	EPlayerMenuActions::Menu_ButtonPressed, EPlayerMenuActions::Menu_MoveXAxis, EPlayerMenuActions::Menu_MoveYAxis
};

//making keys map array
static cocos2d::Controller::Key s_aeMenuKeys[] = {
cocos2d::Controller::Key::BUTTON_DPAD_DOWN, cocos2d::Controller::Key::BUTTON_DPAD_UP, cocos2d::Controller::Key::BUTTON_DPAD_RIGHT, cocos2d::Controller::Key::BUTTON_DPAD_LEFT, cocos2d::Controller::Key::BUTTON_A,
	cocos2d::Controller::Key::JOYSTICK_LEFT_X, cocos2d::Controller::Key::JOYSTICK_LEFT_Y,
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
Scene* CMenuLayer::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    CMenuLayer *layer = CMenuLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


CMenuLayer::CMenuLayer()
	: m_vCurrentButtonIndex(0, 0)
	, m_vPreviousButtonIndex(0, 0)
	, m_psfxButtonSelect( nullptr )
	, m_psfxButtonPress( nullptr )
	, m_bOptionsSelected(false)
	, m_pcControls(nullptr)
{

	m_pcControllerMenuActionsToButtonMap = std::unique_ptr< TGCActionToKeyMap< EPlayerMenuActions > >(TCreateActionToKeyMap(s_aePlayerMenuActions, s_aeMenuKeys));
	this->scheduleUpdate();

}

//TODO: add a declaration of the used buttons at the constructor

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
bool CMenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize	= Director::getInstance()->getVisibleSize();
    Vec2 origin			= Director::getInstance()->getVisibleOrigin();

	///////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////
	//background creation
	Sprite* pBackground = Sprite::create("Loose/Menu_background_IDEA_V1.png");
	pBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(pBackground, 1);
	///////////////////////////////////////////////////////////////////////
	//Controls picture
	//TODO: add the controls picture from the texture packer
	
	////////////////////////////////////////////////////////////////////////
	//creating controls picture
	m_pcControls = Sprite::create("Loose/Controls_v3.png");
	m_pcControls->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_pcControls, 1);
	m_pcControls->setVisible(false);
	//implementing the new buttons
	///////////////////////////////////////////////////////////////////////
    //creating start button 
	
	m_pcNewGameButton = new CButton(origin.x + (visibleSize.width * 0.5f), origin.y - 50 + (visibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/New_Game_Pressed_IDEA_v1.png",
											"Loose/New_Game_Button_IDEA_v1.png",
												  CC_CALLBACK_1(CMenuLayer::CB_OnGameNewGameButton, this)));
	Menu* pMenu = Menu::create(m_pcNewGameButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);	
	///////////////////////////////////////////////////////////////////////
	//creating options  button	
	m_pcOptionsButton = new CButton(origin.x - 285 + (visibleSize.width * 0.5f), (origin.y - 320 + (visibleSize.height * 0.5f)),
		cocos2d::MenuItemImage::create("Loose/Controls_Pressed_IDEA_v1.png",
											"Loose/Controls_Button_IDEA_v1.png",
													CC_CALLBACK_1(CMenuLayer::CB_OnGameOptionsButton, this)));
	pMenu = Menu::create(m_pcOptionsButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);	
	///////////////////////////////////////////////////////////////////////
    //creating exit the game button

	m_pcExitButton = new CButton(origin.x + 285 + (visibleSize.width * 0.5f), origin.y - 320 + (visibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/Exit_Pressed_IDEA_v1.png",
											"Loose/Exit_Button_IDEA_v1.png",
													CC_CALLBACK_1(CMenuLayer::CB_OnGameExitButton, this)));
	pMenu = Menu::create(m_pcExitButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	///////////////////////////////////////////////////////////////////////
	//creating return button

	m_pcReturnButton = new CButton(origin.x + 670 + (visibleSize.width * 0.5f), origin.y - 400 + (visibleSize.height * 0.5f),
		cocos2d::MenuItemImage::create("Loose/Back_button_Pressed.png",
			"Loose/Back_button.png",
			CC_CALLBACK_1(CMenuLayer::CB_OnReturnButton, this)));
	pMenu = Menu::create(m_pcReturnButton->getItem(), NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	m_pcReturnButton->setVisibility(false);	
	////////////////////////////////////////////////////////////////////////
	//populating the array of the buttons
		m_apcButtonArray[0][0] = m_pcNewGameButton;
		m_apcButtonArray[0][1] = m_pcLoadGameButton;
		m_apcButtonArray[1][0] = m_pcOptionsButton;
		m_apcButtonArray[1][1] = m_pcExitButton;
	////////////////////////////////////////////////////////////////////////
	
	// populate sound effects
		m_psfxButtonSelect = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::MenuButtonSelected);
		m_psfxButtonPress = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::MenuButtonPressed);

	// Play menu music
		AppDelegate::GetEventMediator()->VPublishPlayBackgroundMusicEvent(CPlayBackgroundMusicEvent( ESoundFX::MainMenuMusic));
	
	//scheduler test
		//cocos2d::Director::getInstance()->getScheduler()->schedule(CMenuLayer::updateTextAnim, this, 0.2f, false);

		//this->schedule->schedule(, CMenuLayer::updateTextAnim, 0.2, false );

		return true;
}


void CMenuLayer::update(float delta)
{
	//controller
	TGCController< EPlayerMenuActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerMenuActionsToButtonMap));

	//checking if controller is active and options are not selected
	if (cController.IsActive() && !m_bOptionsSelected) //main menu itself
	{
		//movement through the menu
		if(cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_MoveDown) || cController.GetCurrentAxisValueRaw(EPlayerMenuActions::Menu_MoveYAxis) < -0.5f)
		{
			if(m_vCurrentButtonIndex.x != m_ciButtonArraySize)
			{
				//sound
				m_psfxButtonSelect->VPlay();
				//saving buttons positions
				m_vPreviousButtonIndex.x = m_vCurrentButtonIndex.x;
				m_vPreviousButtonIndex.y = m_vCurrentButtonIndex.y;
				m_vCurrentButtonIndex.x++;
			}
		}
		else if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_MoveUp) || cController.GetCurrentAxisValueRaw(EPlayerMenuActions::Menu_MoveYAxis) > 0.5f)
		{
			if (m_vCurrentButtonIndex.x != 0)
			{
				m_psfxButtonSelect->VPlay();
							
				if(m_vCurrentButtonIndex.y == 1 && m_vCurrentButtonIndex.x == 1)
				{
					m_vPreviousButtonIndex.x = m_vCurrentButtonIndex.x;
					m_vPreviousButtonIndex.y = m_vCurrentButtonIndex.y;
					m_vCurrentButtonIndex.x--;
					m_vCurrentButtonIndex.y--;
				}
				else
				{
					m_vPreviousButtonIndex.x = m_vCurrentButtonIndex.x;
				m_vPreviousButtonIndex.y = m_vCurrentButtonIndex.y;
				m_vCurrentButtonIndex.x--;
				}
			}
		}
		else if ( (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_MoveLeft) ||  cController.GetCurrentAxisValueRaw(EPlayerMenuActions::Menu_MoveXAxis) < -0.5f) && m_vCurrentButtonIndex.x == 1)
		{
			if (m_vCurrentButtonIndex.y != 0)
			{
				m_psfxButtonSelect->VPlay();
				m_vPreviousButtonIndex.x = m_vCurrentButtonIndex.x;
				m_vPreviousButtonIndex.y = m_vCurrentButtonIndex.y;
				m_vCurrentButtonIndex.y--;
			}
		}
		else if ((cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_MoveRight) || cController.GetCurrentAxisValueRaw(EPlayerMenuActions::Menu_MoveXAxis) > 0.5f) && m_vCurrentButtonIndex.x == 1)
		{
			if (m_vCurrentButtonIndex.y != m_ciButtonArraySize)
			{
				m_psfxButtonSelect->VPlay();
				m_vPreviousButtonIndex.x = m_vCurrentButtonIndex.x; 
				m_vPreviousButtonIndex.y = m_vCurrentButtonIndex.y;
				m_vCurrentButtonIndex.y++;
			}
		}
		//highlighting needed button
		m_apcButtonArray[static_cast<int>(m_vPreviousButtonIndex.x)][static_cast<int>(m_vPreviousButtonIndex.y)]->ButtonNotHighlighted();
		m_apcButtonArray[static_cast<int>(m_vCurrentButtonIndex.x)][static_cast<int>(m_vCurrentButtonIndex.y)]->ButtonHighlighted();
		//pressing highlighted button
		if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_ButtonPressed))
		{
			m_apcButtonArray[static_cast<int>(m_vCurrentButtonIndex.x)][static_cast<int>(m_vCurrentButtonIndex.y)]->ButtonPressed();
		}
	}
	else if (cController.IsActive() && m_bOptionsSelected) // options button is clicked
	{
		m_pcReturnButton->ButtonHighlighted();
		if (cController.ButtonHasJustBeenPressed(EPlayerMenuActions::Menu_ButtonPressed))
		{
			m_pcReturnButton->ButtonPressed();
			m_bOptionsSelected = false;
		}
	}
	
}


CMenuLayer::~CMenuLayer()
{
	if(m_psfxButtonSelect)
	{
		delete m_psfxButtonSelect;
		m_psfxButtonSelect = nullptr;		
	}

	if (m_psfxButtonPress)
	{
		delete m_psfxButtonPress;
		m_psfxButtonPress = nullptr;
	}

	//delting the new button created manualy, not been taken from the cocos
	if (m_pcNewGameButton)
	{
		delete m_pcNewGameButton;
		m_pcNewGameButton = nullptr;
	}
	if (m_pcOptionsButton)
	{
		delete m_pcOptionsButton;
		m_pcOptionsButton = nullptr;
	}
	if (m_pcExitButton)
	{
		delete m_pcExitButton;
		m_pcExitButton = nullptr;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CMenuLayer::CB_OnGameNewGameButton( Ref* pSender )
{
	m_psfxButtonPress->VPlay();//sound
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(ELevelTransitionType::NewGame);
	AppDelegate::GetEventMediator()->VPublishPlayBackgroundMusicEvent(CPlayBackgroundMusicEvent(ESoundFX::Act1StartMusic));
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( false );
	Director::getInstance()->replaceScene(TGCGameLayerSceneCreator< CCinematicScene >::CreateScene() ); // replacing the scene on the callback function
}

void CMenuLayer::CB_OnGameExitButton( Ref* pSender )
{
	m_psfxButtonPress->VPlay(); // sound
	Director::getInstance()->end(); //end of the game
}

void CMenuLayer::CB_OnGameOptionsButton(Ref* pSender)
{
	//selecting options
	m_bOptionsSelected = true;
	m_psfxButtonPress->VPlay(); //sound
	
	//setting visibility of the buttons
	m_pcNewGameButton->setVisibility(false);
	m_pcOptionsButton->setVisibility(false);
	m_pcExitButton->setVisibility(false);
	m_pcReturnButton->setVisibility(true);
	m_pcControls->setVisible(true);
}


void CMenuLayer::CB_OnReturnButton(Ref* pSender)
{
	//returning back to menu from options screen
	// ToDo Play a different sound when transitioning back
	 m_psfxButtonPress->VPlay(); //sound
	m_bOptionsSelected = false;

	//setting visibility of the buttons
	m_pcNewGameButton->setVisibility(true);
	m_pcOptionsButton->setVisibility(true);
	m_pcExitButton->setVisibility(true);

	m_pcReturnButton->setVisibility(false);
	m_pcControls->setVisible(false);
	
}

void CMenuLayer::CB_OnControlsButton(Ref* pSender)
{
	m_psfxButtonPress->VPlay(); //sound
}

void CMenuLayer::CB_OnAudioButton(Ref* pSender)
{
	m_psfxButtonPress->VPlay(); //sound
}
