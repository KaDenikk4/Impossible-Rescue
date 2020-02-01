//Name of class:	CLevel3Area2
//Summary:			This class is creating the level 3 area 2
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit

#include "CLevel3Area2.h"

#include "CLevel3Area1.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Levels/Level4/CLevel4Area1.h"


CLevel3Area2::CLevel3Area2()
	: CBaseLevel(GetGCTypeIDOf( CLevel3Area2 ))
{
}

CLevel3Area2::~CLevel3Area2()
{
}

void CLevel3Area2::VOnResourceAcquire()
{
	CBaseLevel::VOnResourceAcquire();
}

void CLevel3Area2::VOnUpdate( f32 fTimeStep )
{
	CBaseLevel::VOnUpdate( fTimeStep );
}

//Getter function for path of level file from OGMO
const char* CLevel3Area2::VGetLevelFilePath()
{
	return "OgmoEditor/Act1/Level3/Level3Area2.oel";
}

//Background gets added in base level, this override specifies which background to use
const char* CLevel3Area2::VGetBackgroundFilePath()
{
	// ToDo change this
	return "TexturePacker/Backgrounds/Act1/Level3Area2/Level3Area2.plist";
}

void CLevel3Area2::VTransitionToNextScreen()
{
	CCASSERT(false, "There is no next area.");
}


//Function responsible for transition between screens, moving to Level 3 Area 1.
void CLevel3Area2::VTransitionToPreviousScreen()
{
	// ToDo save player positional data / velocity / movement state
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( true );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

//Function responsible for transition between levels moving to Level 4 Area 1.
void CLevel3Area2::VTransitionToNextLevel( )
{
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetIsTransitioningBetweenAreas( false );
	ReplaceScene(TGCGameLayerSceneCreator< CLevel4Area1 >::CreateScene());
	SetLevelTransitionDisabled();
}

void CLevel3Area2::VRestartLevel( )
{
	CBaseLevel::VRestartLevel();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area1 >::CreateScene());
}

void CLevel3Area2::VRestartAct( )
{
	CBaseLevel::VRestartAct();
	ReplaceScene(TGCGameLayerSceneCreator< CLevel3Area1 >::CreateScene());
}

void CLevel3Area2::VOnHorizontalTransitionBorderHit( )
{
	CCASSERT(false, "There is no horizontal transition to hit.");
}

//On hitting the vertical border, transition to the previous area.
void CLevel3Area2::VOnVerticalTransitionBorderHit( )
{
	AppDelegate::GetEventMediator()->VPublishLevelTransitionEvent(CLevelTransitionEvent(ELevelTransitionType::PreviousArea));
}