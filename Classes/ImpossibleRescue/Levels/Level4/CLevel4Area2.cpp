//Name of class:	CLevel4Area2
//Summary:			This class is creating the level 4 area 2
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, VOnUpdate,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit

#include "CLevel4Area2.h"

#include "CLevel4Area1.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Levels/Level1/CLevel1Area1.h"
#include "../../Gameplay/CLevelTimer.h"
#include "ImpossibleRescue/Levels/CMenuScene.h"
#include "ImpossibleRescue/Levels/CEndScreen.h"

CLevel4Area2::CLevel4Area2()
	: CBaseLevel(GetGCTypeIDOf(CLevel4Area2))
	, m_pcLevelTimer( nullptr )
	, m_pcTimerBackground(nullptr)
{
}

CLevel4Area2::~CLevel4Area2()
{
	m_pcLevelTimer->RemoveTimer( this );
	m_pcLevelTimer = nullptr;
	
	if (m_pcTimerBackground)
	{
		delete(m_pcTimerBackground);
		m_pcTimerBackground = nullptr;
	}
	
}

//Getter function for path of level file from OGMO
const char* CLevel4Area2::VGetLevelFilePath()
{
	return "OgmoEditor/Act1/Level4/Level4Area2.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel4Area2::VGetBackgroundFilePath()
{
	// ToDo change this
	return "TexturePacker/Backgrounds/Act1/Level4Area2/Level4Area2.plist";
}

void CLevel4Area2::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();
	m_pcLevelTimer = new CLevelTimer();
	
	m_pcTimerBackground = cocos2d::Sprite::create("Loose/Timer_box.png");
	m_pcTimerBackground->setPosition(cocos2d::Vec2(1015.0f, 1000.0f));
	this->addChild(m_pcTimerBackground, 1);
	m_pcTimerBackground->setVisible(true);

	
	float fTimerTime = AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->GetLevelRemainingTimeFromPreviousArea();
	//ToDo: Get remaining time from the previous area on the THIRD parameter.
	m_pcLevelTimer->AddTimerLabel( this, 50.0f, 20.0f, Vec2( 960.0f, 1000.0f ) );
	m_pcLevelTimer->SetTimer( fTimerTime );
}

void CLevel4Area2::VOnUpdate( f32 fTimeStep )
{
	CBaseLevel::VOnUpdate( fTimeStep );
	
	//ToDo: Refactor this.
	if( !GetIsPaused( ) )
	{
		m_pcTimerBackground->setVisible(true);
		// Show the timer if the game is not paused
		m_pcLevelTimer->SetVisibility(true);
		
		m_pcLevelTimer->Update( fTimeStep );
		if( m_pcLevelTimer->GetDidTimeRunOut() )
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

void CLevel4Area2::VTransitionToNextScreen()
{
	CCASSERT(false, "There is no next area.");
}

void CLevel4Area2::VTransitionToPreviousScreen()
{
	// ToDo save player positional data / velocity / movement state
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );

	//Save the remaining time between areas.
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetLevelTimerRemainingTime( m_pcLevelTimer->GetTimeRemaining() );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel4Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel4Area2::VTransitionToNextLevel( )
{
	// ToDo refactor end game resets
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( false );

	//Resetting the timer to 30 seconds when the level is finished
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetLevelTimerRemainingTime(30.0f);

	//Go to end screen after this level is finished.
	ReplaceScene( TGCGameLayerSceneCreator< CEndScreen >::CreateScene() );
	//ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel4Area2::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetLevelTimerRemainingTime( 30.0f );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel4Area1 >::CreateScene());
}

void CLevel4Area2::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel1Area1 >::CreateScene());
}

void CLevel4Area2::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the previous area.
void CLevel4Area2::VOnVerticalTransitionBorderHit( )
{
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::PreviousArea));
}
