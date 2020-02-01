// Name of class:	CCinematicScene
// Summary:			Class responsible for displaying the cinematic sequences
//					before level 1, divided by ticker text that can be skipped.
// Functions:		onEnter, VOnCreate, VOnUpdate, VOnDestroy

#ifndef _CCINEMATIC_SCENE_
#define _CCINEMATIC_SCENE_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Player/EPlayerCutsceneActions.h"
#include "GamerCamp/GameController/GCController.h"
#include "ImpossibleRescue/Audio/ISoundEffect.h"

class TickerText;

USING_NS_CC;

enum class ECutsceneStages;

class CCinematicScene
	: public IGCGameLayer
{
public:
	CCinematicScene();
	~CCinematicScene();

	// CCNode interface...
	virtual void onEnter() override;
	// CCNode interface...

	// IGCGameLayer interface
	virtual	void VOnCreate( void ) override;
	virtual void VOnUpdate( f32 fTimeStep ) override;
	virtual	void VOnDestroy( void ) override;
	// IGCGameLayer interface
	
private:
	FadeIn*			m_pcFadeInDanielleBackground;

	TickerText*		m_pcTickerTextPanel;

	bool m_bPanelFadingOut;

	ISoundEffect* m_psfxTickerTextSound;
		
	//NOTE: Values below are constants and therefore, strings cannot be added together on new lines.
	//		Forgive the inconvenience. To see the text wrapped go to Tools->Options->Text Editor->All Languages->General
	//		Enable Word wrap in settings box.
	const std::string& m_rcTextFirstPanel = "By 2180, the three main factions were the Terran Federation of Continents, The Solar Alliance and the Imperial Empire of Mars.\n\nIn 2199, with aggression and force, the Imperial Empire of Mars have attacked the headquarters of the Terran Federation of Continents. The President escaped death, however his daughter was captured and taken back to Mars; now being held prisoner in their hidden Martian security installation.\n\nIn a desperate plea, the Vice-President of Earth secretly hires freelance mercenary 'Danielle', a former top-tier covert operative of the Terran Federation of Continents.";
	const std::string& m_rcTextSecondPanel	= "The mission was simple, infiltrate the Imperial base and extract the President's Daughter. SHADOW's scanners detected the girl's biometrics deep beneath an abandoned research station. They were hiding in plain sight, but no one can hide from me. . .";
	
	std::unique_ptr< TGCActionToKeyMap< EPlayerCutsceneActions > > m_pcControllerCutsceneActionsToButtonMap;

	ECutsceneStages m_eCurrentCutsceneStage;

	Sprite* m_pcSkipButton;
	Sprite* m_pcDanielleBackgroundImage;
	Sprite* m_pcMarsBackgroundSprite;
	
	FadeTo* m_pcMarsBackgroundFadeToAction;
	
};

//Cutscene stages enum exists to easily expand on the new sequences
enum class ECutsceneStages
{
	FirstPanel = 0,
	SecondPanel,
};

#endif //_CCINEMATIC_SCENE_
