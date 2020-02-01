//Name of class:	CEndScreen
//Summary:			This is class for creating end screen displayed after completing Level 4 Area 2.
//Functions:		onEnter, VOnCreate, VOnUpdate, VOnDestroy

#ifndef CEND_SCREEN
#define CEND_SCREEN

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Player/EPlayerCutsceneActions.h"
#include "GamerCamp/GameController/GCController.h"

class TickerText;

class CEndScreen :
	public IGCGameLayer
{
public:
	CEndScreen();
	~CEndScreen();


	// CCNode interface...
	virtual void onEnter() override;
	// CCNode interface...

	//////////////////////////////////////////////////////////////////////////
	// IGCGameLayer interface

	virtual	void VOnCreate( void );
	virtual void VOnUpdate( f32 fTimeStep );
	virtual	void VOnDestroy( void );

private:
	TickerText* m_pcTickerText;
	const std::string& m_krstrEndPanelText = "To be continued. . .";

	std::unique_ptr< TGCActionToKeyMap< EPlayerCutsceneActions > > m_pcControllerCutsceneActionsToButtonMap;
	
};

#endif // CEND_SCREEN