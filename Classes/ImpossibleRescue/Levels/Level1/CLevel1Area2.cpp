//Name of class:	CLevel1Area2
//Summary:			This class is creating the level 1 area 2
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, 
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit,	VOnCreate, VOnUpdate, ShadowAnimation

#include "CLevel1Area2.h"

#include "CLevel1Area1.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Levels/Level2/CLevel2Area1.h"


static EPlayerActions s_aePlayerActions[] = { EPlayerActions::Jump, EPlayerActions::Crouch };
static cocos2d::Controller::Key s_aeTutorialKeys[] = { cocos2d::Controller::Key::BUTTON_A, cocos2d::Controller::Key::BUTTON_B };

CLevel1Area2::CLevel1Area2( )
	: CBaseLevel( GetGCTypeIDOf(CLevel1Area2) )
	, m_bWasInitialised				( false )
	, m_bXButtonWasPressed			( false )
	, m_bCircleWasPressed			( false )
	, m_pcFirstTutorialTickerText	( nullptr )
	, m_pcSecondTutorialTickerText	( nullptr )
	, m_pcShadowTextbox				( nullptr )
	, m_pcTalkingShadowTExtbox		( nullptr )
	, m_bImageSwap					( false )
	, m_pShadowTimer				( nullptr )
	, m_bShouldPlaySound			( false )
	, m_bIsCalledOnceForFirst		( false )
	, m_bIsCalledOnceForSecond		( false )
{
	m_pcControllerTutorialActionsToButtonMap = std::unique_ptr<TGCActionToKeyMap<EPlayerActions>>(TCreateActionToKeyMap(s_aePlayerActions, s_aeTutorialKeys));
	m_pShadowTimer = new CTimerHelper(0.2f);
}

CLevel1Area2::~CLevel1Area2( )
{
	if(m_pcFirstTutorialTickerText)
	{
		delete(m_pcFirstTutorialTickerText);
		m_pcFirstTutorialTickerText = nullptr;
	}
	if(m_pcSecondTutorialTickerText)
	{
		delete(m_pcSecondTutorialTickerText);
		m_pcSecondTutorialTickerText = nullptr;
	}
	if(m_pcShadowTextbox)
	{
		delete(m_pcShadowTextbox);
		m_pcShadowTextbox = nullptr;
	}
	if (m_pShadowTimer)
	{
		delete(m_pShadowTimer);
		m_pShadowTimer = nullptr;
	}
}

//Getter function for path of level file from OGMO
const char* CLevel1Area2::VGetLevelFilePath( )
{
	return "OgmoEditor/Act1/Level1/Level1Area2.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel1Area2::VGetBackgroundFilePath( )
{
	return "TexturePacker/Backgrounds/Act1/Level1Area2/Level1Area2.plist";
}

void CLevel1Area2::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();	
}

void CLevel1Area2::VTransitionToNextScreen()
{
	CCASSERT(false, "There is no next area.");
}

//Function responsible for transition between screens, moving to Level 1 Area 1.
void CLevel1Area2::VTransitionToPreviousScreen( )
{
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

//Function responsible for transition between levels moving to Level 2 Area 1.
void CLevel1Area2::VTransitionToNextLevel( )
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( false );
	ReplaceScene( TGCGameLayerSceneCreator< CLevel2Area1 >::CreateScene() );
	SetLevelTransitionDisabled();
}

void CLevel1Area2::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel1Area2::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel1Area2::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the previous area.
void CLevel1Area2::VOnVerticalTransitionBorderHit( )
{
	//Completing the ticker text to prevent sfx bug which caused ticker text sound overlap between levels.	
	m_pcFirstTutorialTickerText->SetIsSkipped( true );
	m_pcSecondTutorialTickerText->SetIsSkipped( true );
	m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
	m_pcSecondTutorialTickerText->GetTypingSound()->VStop();
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::PreviousArea));
}

void CLevel1Area2::VOnCreate()
{
	CBaseLevel::VOnCreate();

	//creating ticker text in here
	m_pcFirstTutorialTickerText = new TickerText(m_crFirstTutorialText, 24);

	//setting the dialog box here
	m_pcShadowTextbox = cocos2d::Sprite::create("Loose/Dialog-box.png");
	m_pcShadowTextbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));

	m_pcTalkingShadowTExtbox = cocos2d::Sprite::create("Loose/Dialog-box_v2.png");
	m_pcTalkingShadowTExtbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));

	this->addChild(m_pcShadowTextbox, 1);
	this->addChild(m_pcTalkingShadowTExtbox, 1);
	m_pcFirstTutorialTickerText->SetTextAreaSize(670.0f, 120.0f);
	m_pcFirstTutorialTickerText->SetTextPosition(220.0f, 909.0f);
	this->addChild(m_pcFirstTutorialTickerText->getText(), 1);

	//creating second ticker text in here
	m_pcSecondTutorialTickerText = new TickerText(m_crSecondTutorialText, 24);

	m_pcSecondTutorialTickerText->SetTextAreaSize(670.0f, 120.0f);
	m_pcSecondTutorialTickerText->SetTextPosition(220.0f, 909.0f);
	this->addChild(m_pcSecondTutorialTickerText->getText(), 1);
}

void CLevel1Area2::VOnUpdate( f32 fTimeStep )
{
	CBaseLevel::VOnUpdate( fTimeStep );
	if(!m_bCircleWasPressed) // checking the shadow animation here
	{
		ShadowAnimation(GetIsPaused(), fTimeStep);
	}
	//checking the pause state
	if (!GetIsPaused())
	{
		m_bShouldPlaySound = true; //checking if sound should definitely play here
		if (!m_bXButtonWasPressed)
		{			
			m_pcFirstTutorialTickerText->TextAnimation(fTimeStep); //playing shadow talking animation
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
		
		if (m_bXButtonWasPressed && !m_bCircleWasPressed) //checking the state
		{
			m_pcSecondTutorialTickerText->TextAnimation(fTimeStep); //playing second shadow animation

			if (!m_pcSecondTutorialTickerText->GetTextEnd() && m_bShouldPlaySound && !m_bIsCalledOnceForSecond) //sound check
			{
				m_pcSecondTutorialTickerText->GetTypingSound()->VPlay(true);
				m_bIsCalledOnceForSecond = true;
			}
			if (m_pcSecondTutorialTickerText->GetTextEnd())
			{
				m_pcSecondTutorialTickerText->GetTypingSound()->VStop();
			}
		}

		if (!m_bWasInitialised)
		{
			AppDelegate::GetEventMediator()->VPublishStationHackedEvent(CStationHackedEvent("L2A1"));
			m_bWasInitialised = true;
		}

		//this part checks if player press needed button in the tutorial process
		TGCController<EPlayerActions> cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerTutorialActionsToButtonMap));
		if (cController.IsActive())
		{
			if (cController.ButtonHasJustBeenPressed(EPlayerActions::Jump) && m_pcFirstTutorialTickerText->GetTextEnd() && m_bXButtonWasPressed == false && m_bCircleWasPressed == false)
			{
				//sets tutorial done if player jump
				m_bXButtonWasPressed = true;
				m_pcFirstTutorialTickerText->getText()->setOpacity(0);
				m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
			}
			if (cController.ButtonHasJustBeenPressed(EPlayerActions::Crouch) && m_pcSecondTutorialTickerText->GetTextEnd() && m_bXButtonWasPressed == true && m_bCircleWasPressed == false)
			{
				//sets tutorial done if player crouch
				m_bCircleWasPressed = true;

				m_pcSecondTutorialTickerText->getText()->setOpacity(0);
				m_pcShadowTextbox->setVisible(false);
				m_pcSecondTutorialTickerText->GetTypingSound()->VStop();
			}
		}

		//doublecheck on visibility of the tutorial
		m_pcFirstTutorialTickerText->getText()->setVisible(true);
		if (m_bXButtonWasPressed == false || m_bCircleWasPressed == false)
		{
			m_pcShadowTextbox->setVisible(true);
			m_pcSecondTutorialTickerText->getText()->setVisible(true);
		}
		else if(m_bXButtonWasPressed && m_bCircleWasPressed)
		{
			m_pcShadowTextbox->setVisible(false);
			m_pcTalkingShadowTExtbox->setVisible(false);
			m_pcSecondTutorialTickerText->getText()->setVisible(false);
		}
	}
	else
	{ // checking the visibility of the tutorial
		m_bShouldPlaySound = false;
		if (!m_pcFirstTutorialTickerText->GetTextEnd())
		{
			m_bIsCalledOnceForFirst = false;
		}
		if (!m_pcSecondTutorialTickerText->GetTextEnd())
		{
			m_bIsCalledOnceForSecond = false;
		}		
		m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
		m_pcSecondTutorialTickerText->GetTypingSound()->VStop();
		
		m_pcFirstTutorialTickerText->getText()->setVisible(false);
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(false);
		m_pcSecondTutorialTickerText->getText()->setVisible(false);
	}
}

//playing shadow talking animation in here
void CLevel1Area2::ShadowAnimation(bool pIsPAused, float timeStep)
{
	if (!pIsPAused && !m_pcFirstTutorialTickerText->GetTextEnd() && !m_bXButtonWasPressed && !m_bCircleWasPressed)
	{
		//running timer here
		m_pShadowTimer->RunTimer(timeStep);
		if (m_pShadowTimer->GetTimerCompleted())
		{ //swaping images here
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
	else if (!pIsPAused && m_pcFirstTutorialTickerText->GetTextEnd() && !m_pcSecondTutorialTickerText->GetTextEnd() && m_bXButtonWasPressed && !m_bCircleWasPressed)
	{
		//timer
		m_pShadowTimer->RunTimer(timeStep);
		if (m_pShadowTimer->GetTimerCompleted())
		{
			//image swap
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
	//extra check of the tutorial visibility 
	if(m_bCircleWasPressed || pIsPAused )
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(false);
	}

	if (!pIsPAused && m_pcFirstTutorialTickerText->GetTextEnd() && !m_bXButtonWasPressed && !m_bCircleWasPressed)
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(true);
	}
	if (!pIsPAused && m_pcSecondTutorialTickerText->GetTextEnd() && m_bXButtonWasPressed && !m_bCircleWasPressed)
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(true);
	}
}

