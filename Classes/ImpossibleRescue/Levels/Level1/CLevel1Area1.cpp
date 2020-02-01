//Name of class:	CLevel1Area1
//Summary:			This class is creating the level 1 area 1
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit, VOnVerticalTransitionBorderHit,
//					VOnCreate, ShadowAnimation

#include "CLevel1Area1.h"
#include "CLevel1Area2.h"
#include "AppDelegate.h"

CLevel1Area1::CLevel1Area1( )
	: CBaseLevel( GetGCTypeIDOf(CLevel1Area1) )
	, m_pcFirstTutorialTickerText	( nullptr )
	, m_pcShadowTextbox				( nullptr )
	, m_pcTalkingShadowTExtbox		( nullptr )
	, m_bShouldPlaySound			( false )
	, m_bIsCalledOnce				( false )
	, m_bImageSwap					( false )
	, m_pShadowTimer				( nullptr )
{
	m_pShadowTimer = new CTimerHelper(0.2f);
}

CLevel1Area1::~CLevel1Area1( )
{
	if(m_pcShadowTextbox)
	{
		delete(m_pcShadowTextbox);
		m_pcShadowTextbox = nullptr;
	}

	if(m_pcTalkingShadowTExtbox)
	{
		delete(m_pcTalkingShadowTExtbox);
		m_pcTalkingShadowTExtbox = nullptr;
	}
	if(m_pcFirstTutorialTickerText)
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

void CLevel1Area1::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();

	//Check if player is going between areas, if so do not play fade from black action.
	if (!AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetIsTransitioningBetweenAreas())
	{
		RunFadeFromBlackAction();
	}

	//Level label gets displayed at the start of the level, it's available via base level.
	GetLevelLabel()->setString( "Level 1" );
}

//Getter function for path of level file from OGMO
const char* CLevel1Area1::VGetLevelFilePath( )
{
	return "OgmoEditor/Act1/Level1/Level1Area1.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel1Area1::VGetBackgroundFilePath( )
{
	return "TexturePacker/Backgrounds/Act1/Level1Area1/Level1Area1.plist";
}

//Function responsible for transition between screens, moving to Level 1 Area 2.
void CLevel1Area1::VTransitionToNextScreen()
{
	// ToDo: Save player positional data / velocity / movement state
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );
	SetFadeActionWasPlayed( false );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area2 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel1Area1::VTransitionToPreviousScreen( )
{
	// There is no previous area
	CCASSERT(false, "There is no previous screen to transition to.");
}

void CLevel1Area1::VTransitionToNextLevel( )
{
}

void CLevel1Area1::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel1Area1::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel1Area1::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the next area.
void CLevel1Area1::VOnVerticalTransitionBorderHit( )
{
	m_pcFirstTutorialTickerText->SetIsSkipped( true );
	m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::NextArea));
}

void CLevel1Area1::VOnCreate()
{
	CBaseLevel::VOnCreate();

	//creating ticker text here
	m_pcFirstTutorialTickerText = new TickerText(m_crTutorialText, 24);

	//setting sprites for the dialog boxes
	m_pcShadowTextbox = cocos2d::Sprite::create("Loose/Dialog-box.png");
	m_pcShadowTextbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));
	
	m_pcTalkingShadowTExtbox = cocos2d::Sprite::create("Loose/Dialog-box_v2.png");
	m_pcTalkingShadowTExtbox->setPosition(cocos2d::Vec2(470.0f, 970.0f));
	//m_pcTalkingShadowTExtbox->setOpacity(200);

	this->addChild(m_pcShadowTextbox, 1);
	this->addChild(m_pcTalkingShadowTExtbox, 1);
	//setting ticker text here
	m_pcFirstTutorialTickerText->SetTextAreaSize(670.0f,120.0f);
	m_pcFirstTutorialTickerText->SetTextPosition(220.0f, 909.0f);
	this->addChild(m_pcFirstTutorialTickerText->getText(), 1);
	
}

void CLevel1Area1::VOnUpdate(f32 fTimeStep)
{
	m_pcFirstTutorialTickerText->TextAnimation(fTimeStep);

	CBaseLevel::VOnUpdate(fTimeStep);
	ShadowAnimation(GetIsPaused(), fTimeStep);

	AfterFadeFromBlackIsComplete();
	
	if (!GetIsPaused())
	{
		//sound check here -> it is checking when shadow should play sound and when shouldn't
		m_bShouldPlaySound = true;
		m_pcFirstTutorialTickerText->TextAnimation(fTimeStep);
		if(!m_pcFirstTutorialTickerText->GetTextEnd() && m_bShouldPlaySound && !m_bIsCalledOnce)
		{
			m_pcFirstTutorialTickerText->GetTypingSound()->VPlay(true);
			m_bIsCalledOnce = true;
		}
		if(m_pcFirstTutorialTickerText->GetTextEnd())
		{
			m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
		}
		//visibility of the text on the screen
		m_pcFirstTutorialTickerText->getText()->setVisible(true);
		m_pcShadowTextbox->setVisible(true);
	}
	else
	{
		m_bShouldPlaySound = false;
		if(!m_pcFirstTutorialTickerText->GetTextEnd())
		{
			m_bIsCalledOnce = false;
		}
		m_pcFirstTutorialTickerText->GetTypingSound()->VStop();
		//visibility of the text on the screen
		m_pcShadowTextbox->setVisible(false);
		m_pcFirstTutorialTickerText->getText()->setVisible(false);
	}
}

void CLevel1Area1::ShadowAnimation(bool pIsPAused, float timeStep)
{
	//checking if we still need to play shadow animations
	if(!pIsPAused && !m_pcFirstTutorialTickerText->GetTextEnd())
	{
		//run timer
		m_pShadowTimer->RunTimer(timeStep);
		if(m_pShadowTimer->GetTimerCompleted())
		{
			//swapping images here
			if(m_bImageSwap)
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
		//setting visibility of the text on the screen
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(false);
	}
	if(!pIsPAused && m_pcFirstTutorialTickerText->GetTextEnd())
	{
		m_pcShadowTextbox->setVisible(false);
		m_pcTalkingShadowTExtbox->setVisible(true);
	}
}
