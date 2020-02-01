// Name of class:	CTitleScreen
// Summary:			Class responsible for displaying the splash/title screen.
//					Skipping it, should lead the player to the main menu.
// Functions:		onEnter, VOnCreate, VOnUpdate, VOnDestroy

#ifndef _CTITLE_SCREEN_
#define _CTITLE_SCREEN_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Player/EPlayerCutsceneActions.h"
#include "GamerCamp/GameController/GCController.h"
#include "ImpossibleRescue/Audio/ISoundEffect.h"

class CTimerHelper;

class CTitleScreen : public IGCGameLayer
{
public:
	CTitleScreen();
	~CTitleScreen();


	// CCNode interface...
	virtual void onEnter() override;
	// CCNode interface...

	// IGCGameLayer interface
	virtual	void VOnCreate( void ) override;
	virtual void VOnUpdate( f32 fTimeStep ) override;
	virtual	void VOnDestroy( void ) override;
	// IGCGameLayer interface

private:
	Label*			m_pcPressXToContinueLabel;
	Sprite*			m_pcTitleScreenBackground;
	Sprite*			m_pcSplashScreen;
	FadeIn*			m_pcTitleScreenFadeIn;
	FadeIn*			m_pcSplashScreenFadeIn;
	FadeOut*		m_pcSplashScreenFadeOut;
	CTimerHelper*	m_pcTimerForBlinkingOn;
	CTimerHelper*	m_pcTimerForBlinkingOff;
	bool			m_bSplashScreenFaded;

	std::unique_ptr< TGCActionToKeyMap< EPlayerCutsceneActions > > m_pcControllerCutsceneActionsToButtonMap;
};

#endif