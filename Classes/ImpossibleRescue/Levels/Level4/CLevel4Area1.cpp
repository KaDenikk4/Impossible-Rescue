//Name of class:	CLevel4Area1
//Summary:			This class is creating the level 4 area 1
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, VOnUpdate,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit

#include "CLevel4Area1.h"
#include "CLevel4Area2.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Levels/Level1/CLevel1Area1.h"
#include "../../Gameplay/CLevelTimer.h"

CLevel4Area1::CLevel4Area1()
	: CBaseLevel(GetGCTypeIDOf(CLevel4Area1))
	, m_pcLevelTimer(nullptr)
	, m_pcTimerBackground(nullptr)
{
}

CLevel4Area1::~CLevel4Area1()
{
	m_pcLevelTimer->RemoveTimer( this );
	m_pcLevelTimer = nullptr;

	if(m_pcTimerBackground)
	{
		delete(m_pcTimerBackground);
		m_pcTimerBackground = nullptr;
	}
}

//Getter function for path of level file from OGMO
const char* CLevel4Area1::VGetLevelFilePath()
{
	return "OgmoEditor/Act1/Level4/Level4Area1.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel4Area1::VGetBackgroundFilePath()
{
	// ToDo change this
	return "TexturePacker/Backgrounds/Act1/Level4Area1/Level4Area1.plist";
}

void CLevel4Area1::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();
	m_pcLevelTimer = new CLevelTimer();

	m_pcTimerBackground = cocos2d::Sprite::create("Loose/Timer_box.png");
	m_pcTimerBackground->setPosition(cocos2d::Vec2(1015.0f, 1000.0f));
	this->addChild(m_pcTimerBackground, 1);
	m_pcTimerBackground->setVisible(true);
	

	//Adding the level timer to the scene, this line is setting the timer to what is remaining if player goes between areas
	float fTimerTime = AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetLevelRemainingTimeFromPreviousArea();
	if (fTimerTime <= 0)
	{
		m_pcLevelTimer->AddTimerLabel( this, 50.0f, 30.0f, Vec2( 960.0f, 1000.0f ) );
	} 
	else
	{
		m_pcLevelTimer->AddTimerLabel( this, 50.0f, fTimerTime, Vec2( 960.0f, 1000.0f ) );
	}
	
	AppDelegate::GetEventMediator()->VPublishPlayBackgroundMusicEvent(ESoundFX::Act1TimerMusic);
	
	if( !AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetIsTransitioningBetweenAreas() )
	{
		RunFadeFromBlackAction();
	}

	GetLevelLabel()->setString( "Level 4" );
}

void CLevel4Area1::VOnUpdate( f32 fTimeStep )
{
	CBaseLevel::VOnUpdate( fTimeStep );

	AfterFadeFromBlackIsComplete();
	
	//ToDo: Refactor this.
	if( !GetIsPaused(  ) )
	{
		m_pcTimerBackground->setVisible(true);
		
		// Show the timer if the game is not paused
		m_pcLevelTimer->SetVisibility(true);

		m_pcLevelTimer->Update( fTimeStep );
		if (m_pcLevelTimer->GetDidTimeRunOut())
		{
			AppDelegate::GetEventMediator()->VPublishPlayerHasDiedEvent( CPlayerHasDiedEvent( 0 ) );
		}
	
	}
	else
	{
		m_pcTimerBackground->setVisible(false);
		// Hide the timer if the game is paused
		m_pcLevelTimer->SetVisibility(false);
		

	}
}

//Function responsible for transition between screens, moving to Level 4 Area 2.
 void CLevel4Area1::VTransitionToNextScreen()
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );

	//Save the remaining time on the timer when going to the next area.
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetLevelTimerRemainingTime( m_pcLevelTimer->GetTimeRemaining() );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel4Area2 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel4Area1::VTransitionToPreviousScreen()
{
	// There is no previous area
	CCASSERT(false, "There is no previous screen to transition to.");
}

void CLevel4Area1::VTransitionToNextLevel( )
{
}

void CLevel4Area1::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();

	//Resetting the timer to 30 seconds when the level is restarted
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetLevelTimerRemainingTime( 30.0f );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel4Area1 >::CreateScene());
}

void CLevel4Area1::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel4Area1::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the next area.
void CLevel4Area1::VOnVerticalTransitionBorderHit( )
{
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::NextArea));
}