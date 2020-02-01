//Name of class:	CLevel2Area2
//Summary:			This class is creating the level 2 area 2
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VTransitionToNextScreen,
//					VTransitionToPreviousScreen, VTransitionToNextLevel, VRestartLevel, 
//					VRestartAct, VOnHorizontalTransitionBorderHit, VOnVerticalTransitionBorderHit,
//					VOnUpdate

#include "CLevel2Area2.h"
#include "CLevel2Area1.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Levels/Level3/CLevel3Area1.h"
#include "ImpossibleRescue/Player/Movement/CPlayerMovementStates.h"


CLevel2Area2::CLevel2Area2()
	: CBaseLevel(GetGCTypeIDOf( CLevel2Area2 ))
	, m_bWasInitialised(false)
{
}

CLevel2Area2::~CLevel2Area2()
{
}

//Getter function for path of level file from OGMO
const char* CLevel2Area2::VGetLevelFilePath()
{
	return "OgmoEditor/Act1/Level2/Level2Area2.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel2Area2::VGetBackgroundFilePath()
{
	// ToDo change this
	return "TexturePacker/Backgrounds/Act1/Level2Area2/Level2Area2.plist";
}

void CLevel2Area2::VTransitionToNextScreen()
{
	CCASSERT(false, "There is no next area.");
}

//Function responsible for transition between screens, moving to Level 2 Area 1.
void CLevel2Area2::VTransitionToPreviousScreen()
{
	// ToDo save player positional data / velocity / movement state
	ReplaceScene(TGCGameLayerSceneCreator< CLevel2Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

//Function responsible for transition between levels moving to Level 3 Area 1.
void CLevel2Area2::VTransitionToNextLevel( )
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( false );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel2Area2::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel2Area1 >::CreateScene());
}

void CLevel2Area2::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel2Area1 >::CreateScene());
}

void CLevel2Area2::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the previous area.
void CLevel2Area2::VOnVerticalTransitionBorderHit( )
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::PreviousArea));
}

void CLevel2Area2::VOnUpdate( f32 fTimeStep )
{
	CBaseLevel::VOnUpdate(fTimeStep);

	if (!m_bWasInitialised)
	{
		AppDelegate::GetEventMediator()->VPublishStationHackedEvent(CStationHackedEvent("L3A1"));
		m_bWasInitialised = true;
	}
}
