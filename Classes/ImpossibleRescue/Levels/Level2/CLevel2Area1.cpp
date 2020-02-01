//Name of class:	CLevel2Area1
//Summary:			This class is creating the level 2 area 1
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit,	VOnCreate, ShadowAnimation

#include "CLevel2Area1.h"
#include "CLevel2Area2.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Levels/Level1/CLevel1Area1.h"

static EPlayerActions s_aePlayerActions[] = { EPlayerActions::Hack };
static cocos2d::Controller::Key s_aeTutorialKeys[] = { cocos2d::Controller::Key::BUTTON_Y };

CLevel2Area1::CLevel2Area1()
	: CBaseLevel(GetGCTypeIDOf( CLevel2Area1 ))
	, m_bTriangleButtonWasPressed	( false )
	, m_pcFirstTutorialTickerText	( nullptr )
	, m_pcShadowTextbox				( nullptr )
	, m_pcTalkingShadowTExtbox		( nullptr )
	, m_bShouldPlaySound			( false )
	, m_bIsCalledOnceForFirst		( false )
	, m_bImageSwap					( false )
	, m_pShadowTimer				( nullptr )
{
	m_pcControllerTutorialActionsToButtonMap = std::unique_ptr<TGCActionToKeyMap<EPlayerActions>>(TCreateActionToKeyMap(s_aePlayerActions, s_aeTutorialKeys));
	m_pShadowTimer = new CTimerHelper(0.2f);
}

CLevel2Area1::~CLevel2Area1()
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

void CLevel2Area1::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();

	AppDelegate::GetEventMediator()->VPublishPlayBackgroundMusicEvent(CPlayBackgroundMusicEvent(ESoundFX::Act1MiddleMusic));

	//Check if player is going between areas, if so do not play fade from black action.
	if( !AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetIsTransitioningBetweenAreas() )
	{
		RunFadeFromBlackAction();
	}

	//Level label gets displayed at the start of the level, it's available via base level.
	GetLevelLabel()->setString( "Level 2" );
}

//Getter function for path of level file from OGMO
const char* CLevel2Area1::VGetLevelFilePath()
{
	return "OgmoEditor/Act1/Level2/Level2Area1.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel2Area1::VGetBackgroundFilePath()
{
	// ToDo change this
	return "TexturePacker/Backgrounds/Act1/Level2Area1/Level2Area1.plist";
}

//Function responsible for transition between screens, moving to Level 2 Area 2.
void CLevel2Area1::VTransitionToNextScreen()
{
	// ToDo save player positional data / velocity / movement state
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel2Area2 >::CreateScene());
	SetLevelTransitionDisabled();
	m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
}

void CLevel2Area1::VTransitionToPreviousScreen()
{
	// There is no previous area
	CCASSERT(false, "There is no previous screen to transition to.");
}

void CLevel2Area1::VTransitionToNextLevel( )
{
}

void CLevel2Area1::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel2Area1 >::CreateScene());
}

void CLevel2Area1::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel2Area1::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the next area.
void CLevel2Area1::VOnVerticalTransitionBorderHit( )
{
	m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::NextArea));
}

void CLevel2Area1::VOnCreate()
{
	CBaseLevel::VOnCreate();

	AfterFadeFromBlackIsComplete();

	//creating ticker text 
	m_pcFirstTutorialTickerText = new TickerText(m_crFirstTutorialText, 24);
	//creating dialog box 
	m_pcShadowTextbox = cocos2d::Sprite::create("Loose/Dialog-box.png");
	m_pcShadowTextbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));
	m_pcTalkingShadowTExtbox = cocos2d::Sprite::create("Loose/Dialog-box_v2.png");
	m_pcTalkingShadowTExtbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));
	//m_pcTalkingShadowTExtbox->setOpacity(200);
	m_pcTalkingShadowTExtbox->setVisible(false);
	

	this->addChild(m_pcShadowTextbox, 1);
	this->addChild(m_pcTalkingShadowTExtbox, 1);

	//setting ticker text
	m_pcFirstTutorialTickerText->SetTextAreaSize(670.0f, 120.0f);
	m_pcFirstTutorialTickerText->SetTextPosition(220.0f, 909.0f);
	this->addChild(m_pcFirstTutorialTickerText->getText(), 1);
}

void CLevel2Area1::VOnUpdate(f32 fTimeStep)
{
	CBaseLevel::VOnUpdate(fTimeStep);

	AfterFadeFromBlackIsComplete();
	ShadowAnimation(GetIsPaused(), fTimeStep); //playing shadow animation

	if (!GetIsPaused())
	{
		//checking the sound effects 
		m_bShouldPlaySound = true;
		if (m_bTriangleButtonWasPressed == false)
		{
			m_pcFirstTutorialTickerText->TextAnimation(fTimeStep);
			//SOUND
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

		//checking which button should be pressed during the tutorial
		TGCController<EPlayerActions> cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerTutorialActionsToButtonMap));
		if (cController.IsActive())
		{
			if (cController.ButtonHasJustBeenPressed(EPlayerActions::Hack) && m_pcFirstTutorialTickerText->GetTextEnd() && !m_bTriangleButtonWasPressed)
			{
				m_bTriangleButtonWasPressed = true;
				m_pcFirstTutorialTickerText->getText()->setOpacity(0);
				m_pcShadowTextbox->setVisible(false);
				m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
			}
		}
		//tutorial visibility check
		m_pcFirstTutorialTickerText->getText()->setVisible(true);
		if (m_bTriangleButtonWasPressed == false)
			m_pcShadowTextbox->setVisible(true);
		else
		{
			m_pcShadowTextbox->setVisible(false);
			m_pcTalkingShadowTExtbox->setVisible(false);
		}
	}
	else
		//checking a visibility and sound effects here
	{
		m_bShouldPlaySound = false;
		if (!m_pcFirstTutorialTickerText->GetTextEnd())
		{
			m_bIsCalledOnceForFirst = false;
		}
		m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
		m_pcFirstTutorialTickerText->getText()->setVisible(false);
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(false);
	}
}

void CLevel2Area1::ShadowAnimation(bool pIsPAused, float timeStep)
{
	if (!pIsPAused && !m_pcFirstTutorialTickerText->GetTextEnd() && !m_bTriangleButtonWasPressed)
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
	else
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(false);
	}
	//extra check on tutorial visibility
	if (!pIsPAused && m_pcFirstTutorialTickerText->GetTextEnd())
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(true);
	}
}
