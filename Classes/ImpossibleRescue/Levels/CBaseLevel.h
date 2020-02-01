//Name of class:	CBaseLevel
//Summary:			This base class for all levels created with OGMO. It contains pause menu, handling
//					collisions and fading functionality that each level can utilise.
//
//Functions:		HandleCollisions, onEnter, VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, VOnUpdate,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit, BeginContact, EndContact, PreSolve, PostSolve,
//					SetLevelTransitionEnabled, SetLevelTransitionDisabled, VOnEventReceived,
//					HandleResets, RequestLevelReset, CheckLevelResetRequested, HandleLevelResetRequest,
//					RequestActReset, CheckActResetRequested, HandleActResetRequest,
//					CB_OnPauseButton, CB_OnReturnButton, CB_OnExitButton, CB_OnOptionsButton,
//					UpdateMenu, setHealthUI, VUpdateLevel, GetIsPaused,	GetFadeToBlackAction,
//					GetFadeFromBlackAction,	SetFadeActionWasPlayed,	GetWasFadeActionPlayed,
//					GetBackgroundForFading,	RunFadeFromBlackAction,	RunFadeToBlackAction,
//					AfterFadeFromBlackIsComplete, AfterFadeToBlackIsComplete, ResetFadeActions,
//					GetLevelLabel, SetPause
			


#ifndef _CBASELEVEL_H_
#define _CBASELEVEL_H_

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Player/CPlayer.h"
#include "../Player/Equipment/Shooting/SecondaryShooting/CPlayerSecondaryProjectileGroup.h"
#include "ImpossibleRescue/Enemies/Turret/CTurretProjectileGroup.h"
#include "ImpossibleRescue/Player/Equipment/Shooting/PrimaryShooting/CPlayerPrimaryProjectileGroup.h"
#include "ImpossibleRescue/Events/Mediator/IEventMediator.h"
#include "GamerCamp/GameController/GCController.h"
#include <ImpossibleRescue/UI/EPlayerMenuActions.h>
#include "ImpossibleRescue/UI/CButton.h"

#ifndef _GCLEVELLOADER_OGMO_H_
#include "GamerCamp/GCCocosInterface/LevelLoader/GCLevelLoader_Ogmo.h"
#endif

#ifndef	_ITRECEIVEEVENTS_H_
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#endif

#ifndef	_CLEVELTRANSITIONEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CLevelTransitionEvent.h"
#endif

#ifndef	_CLEVELTRANSITIONEVENT_H_
#include "ImpossibleRescue/Events/EventTypes/CLevelTraCPlayerHasDiedEventnsitionEvent.h"
#endif

class CBaseLevel
	: public IGCGameLayer
	, public b2ContactListener
	, public ITReceiveEvents<CLevelTransitionEvent>
	, public ITReceiveEvents<CPlayerHasDiedEvent>
{
private:

	//Player primary projectiles
	CPlayerPrimaryProjectileGroup*		 m_pcPlayerPrimaryProjectileGroup;
	//Player secondary projectiles
	CPlayerSecondaryProjectileGroup*	 m_pcPlayerSecondaryProjectileGroup;
	//Turret projectiles
	CTurretProjectileGroup*				 m_pcTurretProjectileGroup;

	// Level loader
	CGCLevelLoader_Ogmo				m_cLevelLoader;

	// Background
	CGCObjSprite*					m_pcSprBackGround;

	// Pause Menu Background
	Sprite*							m_pcSprPauseMenuBackGround;

	ELevelTransitionType			m_eLevelTransitionType;
	bool							m_LevelTransitionEnabled;
	
	bool							m_bPaused;
	bool							m_bOptionsSelected;

	CActionOnRelease				m_pLevelTransitionEventHandler;
	CActionOnRelease				m_pPlayerHasDiedEventHandler;

	//pause menu variables declaration
	CButton*		 m_apcButtonArray[4];
	int				 m_vCurrentButtonIndex;
	int				 m_vPreviousButtonIndex;

	const int		 m_ciButtonArraySize = 2;

	bool			 m_bPlayerDamaged;

	std::unique_ptr< TGCActionToKeyMap< EPlayerMenuActions > > m_pcControllerMenuActionsToButtonMap;

	Sprite*			 m_pcControls;

	//health ui
	Sprite*			 m_pcHealthUIFull;
	Sprite*			 m_pcHealthUIDamaged;

	bool			 m_bHealthUIFullVisibility;
	bool			 m_bHealthUIDamagedVisibility;

	//buttons
	CButton*		 m_pcResumeButton;
	CButton*		 m_pcOptionsButton;
	CButton*		 m_pcExitButton;
	CButton*		 m_pcReturnButton;

	bool			 m_bLevelResetWasRequested;
	bool			 m_bActResetWasRequested;
	bool			 m_bWasFadePlayed;

	ISoundEffect*	 m_psfxButtonPress;
	ISoundEffect*	 m_psfxButtonSelect;
	ISoundEffect*	 m_psfxPauseMenuMusic;

	FadeIn*			 m_pcLayerFadeIn;
	FadeOut*		 m_pcLayerFadeOut;

	Sprite*			 m_pcBlackPanelForFading;

	const float		 m_kfFadeFromBlackTime	= 1.0f;
	const float		 m_kfFadeToBlackTime		= 1.0f;

	Label*			 m_pcLevelLabel;

	bool			 m_bControlsMenuDisplayed;

public:
	CBaseLevel(GCTypeID idDerivedType);
	~CBaseLevel(void);

	// called from VOnUpdate
	void HandleCollisions(void);

	// CCNode interface...
	virtual void onEnter() override;
	// CCNode interface...

	virtual const char* VGetLevelFilePath() = 0;
	virtual const char* VGetBackgroundFilePath( ) = 0;

	// IGCGameLayer interface
	virtual	void VOnCreate(void) override;
	virtual void VOnUpdate(f32 fTimeStep) override;
	virtual	void VOnDestroy(void) override;
	// IGCGameLayer interface

	// Transition to previous screen method
	virtual void VTransitionToPreviousScreen() = 0;
	// Transition to next screen method
	virtual void VTransitionToNextScreen() = 0;
	// Transition to next level method
	virtual void VTransitionToNextLevel() = 0;
	// Restart the current level
	virtual void VRestartLevel();
	// Restart the act
	virtual void VRestartAct();

	// Behaviour called when horizontal transition collision border hit
	virtual void VOnHorizontalTransitionBorderHit( ) = 0;
	// Behaviour called when vertical transition collision border hit
	virtual void VOnVerticalTransitionBorderHit( ) = 0;
	
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are
	virtual void BeginContact(b2Contact* pB2Contact) override;
	virtual void EndContact(b2Contact* pB2Contact) override;
	virtual void PreSolve(b2Contact* pB2Contact, const b2Manifold* pOldManifold) override;
	virtual void PostSolve(b2Contact* pB2Contact, const b2ContactImpulse* pImpulse) override;
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are

	void			 SetLevelTransitionEnabled();
	void			 SetLevelTransitionDisabled();
	

	virtual void	 VOnEventReceived( CLevelTransitionEvent eventArgs ) override;
	virtual void	 VOnEventReceived( CPlayerHasDiedEvent eventArgs ) override;

	//Must be called LAST in update function
	void			 HandleResets();
	
	void			 RequestLevelReset();
	bool			 CheckLevelResetRequested() const;
	void			 HandleLevelResetRequest();
	
	void			 RequestActReset();
	bool			 CheckActResetRequested() const;
	void			 HandleActResetRequest();

	void			 CB_OnPauseButton(Ref* pSender);
	void			 CB_OnReturnButton(Ref* pSender);
	void			 CB_OnExitButton(Ref* pSender);
	void			 CB_OnOptionsButton(Ref* pSender);
	void			 UpdateMenu();

	void			 setHealthUI();

	virtual void	 VUpdateLevel(f32 fTimeStep);

	bool			 GetIsPaused() const;

	FadeIn*			 GetFadeToBlackAction();
	FadeOut*		 GetFadeFromBlackAction();
	
	void			 SetFadeActionWasPlayed(bool bWasPlayed);
	bool			 GetWasFadeActionPlayed();

	Sprite*			 GetBackgroundForFading();

	void			 RunFadeFromBlackAction();
	void			 RunFadeToBlackAction();
	void			 AfterFadeFromBlackIsComplete();
	void			 AfterFadeToBlackIsComplete();
	void			 ResetFadeActions();
	
	Label*			 GetLevelLabel();
	
protected:
	void			 SetPause( bool bIsPaused );
};

#endif // __CGCGameLayerPlatformer_SCENE_H__
