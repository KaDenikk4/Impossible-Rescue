//Name of class:	CLevel3Area1
//Summary:			This class is creating the level 3 area 1
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit,	VOnCreate, ShadowAnimation

#include "CLevel3Area1.h"
#include "CLevel3Area2.h"
#include "AppDelegate.h"



static EPlayerActions s_aePlayerActions[] = { EPlayerActions::Shoot };
static cocos2d::Controller::Key s_aeTutorialKeys[] = { cocos2d::Controller::Key::BUTTON_X };


CLevel3Area1::CLevel3Area1()
	: CBaseLevel(GetGCTypeIDOf( CLevel3Area1 ))
	, m_bSquareWasPressed(false)
	, m_pcFirstTutorialTickerText(nullptr)
	, m_pcShadowTextbox(nullptr)
	, m_bShouldPlaySound(false)
	, m_bIsCalledOnceForFirst(false)
	, m_pcTalkingShadowTExtbox(nullptr)
	, m_bImageSwap(false)
	, m_pShadowTimer(nullptr)
{
	m_pcControllerTutorialActionsToButtonMap = std::unique_ptr<TGCActionToKeyMap<EPlayerActions>>(TCreateActionToKeyMap(s_aePlayerActions, s_aeTutorialKeys));
	m_pShadowTimer = new CTimerHelper(0.2f);
}

CLevel3Area1::~CLevel3Area1()
{
	if (m_pcFirstTutorialTickerText)
	{
		delete(m_pcFirstTutorialTickerText);
		m_pcFirstTutorialTickerText = nullptr;
	}
	
	if (m_pcShadowTextbox)
	{
		delete(m_pcShadowTextbox);
		m_pcShadowTextbox = nullptr;
	}
		if (m_pcFirstTutorialTickerText)
	{
		delete(m_pcFirstTutorialTickerText);
		m_pcFirstTutorialTickerText = nullptr;
	}
		if (m_pShadowTimer)
		{
			delete(m_pShadowTimer);
			m_pShadowTimer = nullptr;
		}
}

void CLevel3Area1::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();
	if( !AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetIsTransitioningBetweenAreas() )
	{
		RunFadeFromBlackAction();
	}

	GetLevelLabel()->setString( "Level 3" );
}

//Getter function for path of level file from OGMO
const char* CLevel3Area1::VGetLevelFilePath()
{
	return "OgmoEditor/Act1/Level3/Level3Area1.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel3Area1::VGetBackgroundFilePath()
{
	// ToDo change this
	return "TexturePacker/Backgrounds/Act1/Level3Area1/Level3Area1.plist";
}

//Function responsible for transition between screens, moving to Level 3 Area 2.
void CLevel3Area1::VTransitionToNextScreen()
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area2 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel3Area1::VTransitionToPreviousScreen()
{
	// There is no previous area
	CCASSERT(false, "There is no previous screen to transition to.");
}

void CLevel3Area1::VTransitionToNextLevel( )
{
}

void CLevel3Area1::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	m_pcFirstTutorialTickerText->SetIsSkipped( true ); //reseting the tutorial
	m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area1 >::CreateScene());
}

void CLevel3Area1::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area1 >::CreateScene());
}

void CLevel3Area1::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the next area. Complete tutorial text to avoid SFX bug with multiple tickertext sounds
void CLevel3Area1::VOnVerticalTransitionBorderHit( )
{
	m_pcFirstTutorialTickerText->SetIsSkipped( true );
	m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::NextArea));
}

void CLevel3Area1::VOnCreate()
{
	CBaseLevel::VOnCreate();
	AfterFadeFromBlackIsComplete();

	//creating ticker text
	m_pcFirstTutorialTickerText = new TickerText(m_crFirstTutorialText, 21);
	//creating dialogbox
	m_pcShadowTextbox = cocos2d::Sprite::create("Loose/Dialog-box.png");
	m_pcShadowTextbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));
	m_pcTalkingShadowTExtbox = cocos2d::Sprite::create("Loose/Dialog-box_v2.png");
	m_pcTalkingShadowTExtbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));
	//m_pcTalkingShadowTExtbox->setOpacity(200);

	this->addChild(m_pcShadowTextbox, 1);
	this->addChild(m_pcTalkingShadowTExtbox, 1);
	//setting ticker text
	m_pcFirstTutorialTickerText->SetTextAreaSize(670.0f, 120.0f);
	m_pcFirstTutorialTickerText->SetTextPosition(220.0f, 909.0f);
	this->addChild(m_pcFirstTutorialTickerText->getText(), 1);
}

void CLevel3Area1::VOnUpdate(f32 fTimeStep)
{
	CBaseLevel::VOnUpdate(fTimeStep);

	
	AfterFadeFromBlackIsComplete();
	
	ShadowAnimation(GetIsPaused(), fTimeStep); //playing shadow animation

	//checking the tutorial sound here sound 
	m_bShouldPlaySound = true;
	if (!GetIsPaused())
	{
		if (m_bSquareWasPressed == false)
		{			
			m_pcFirstTutorialTickerText->TextAnimation(fTimeStep);
			
			if (!m_pcFirstTutorialTickerText->GetTextEnd() && m_bShouldPlaySound && !m_bIsCalledOnceForFirst)
			{
				m_pcFirstTutorialTickerText->GetTypingSound()->VPlay(true);
				m_bIsCalledOnceForFirst = true;
			}
			if (m_pcFirstTutorialTickerText->GetTextEnd())
			{
				m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
			}
		}

		//checking which button should be  pressed at the tutorial
		TGCController<EPlayerActions> cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerTutorialActionsToButtonMap));
		if (cController.IsActive())
		{
			if (cController.ButtonHasJustBeenPressed(EPlayerActions::Shoot) && m_pcFirstTutorialTickerText->GetTextEnd() && m_bSquareWasPressed == false)
			{
				m_bSquareWasPressed = true;
				m_pcFirstTutorialTickerText->getText()->setOpacity(0);
				m_pcShadowTextbox->setVisible(false);
				m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
			}
		}
		//checking visibility and sound here
		m_pcFirstTutorialTickerText->getText()->setVisible(true);
		if (!m_bSquareWasPressed)
			m_pcShadowTextbox->setVisible(true);
		else
		{
			m_pcShadowTextbox->setVisible(false);
			m_pcTalkingShadowTExtbox->setVisible(false);
		}
	}
	else
	{
		m_bShouldPlaySound = false;
		if (!m_pcFirstTutorialTickerText->GetTextEnd())
		{
			m_bIsCalledOnceForFirst = false;
		}
		m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
		
		m_pcFirstTutorialTickerText->getText()->setVisible(false);
		m_pcShadowTextbox->setVisible(false);
	}
}

void CLevel3Area1::ShadowAnimation(bool pIsPAused, float timeStep)
{
	if (!pIsPAused && !m_pcFirstTutorialTickerText->GetTextEnd() && !m_bSquareWasPressed)
	{
		//timer
		m_pShadowTimer->RunTimer(timeStep);
		if (m_pShadowTimer->GetTimerCompleted())
		{
			//swapping images
			if (m_bImageSwap)
			{
				m_pcShadowTextbox->setVisible(false);
				m_pcTalkingShadowTExtbox->setVisible(true);
			}
			else
			{
				m_pcShadowTextbox->setVisible(true);
				m_pcTalkingShadowTExtbox->setVisible(false);
			}
			m_bImageSwap = !m_bImageSwap;
			m_pShadowTimer->ResetTimer();
		}
	}
	//extra check on the visibility of the tutorial
	else
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(false);
	}
	if (!pIsPAused && m_pcFirstTutorialTickerText->GetTextEnd())
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(true);
	}
}
