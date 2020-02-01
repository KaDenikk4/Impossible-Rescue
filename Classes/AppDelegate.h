#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#ifndef _GCKEYBOARDMANAGER_H_
	#include "GamerCamp/Win32Input/GCKeyboardManager.h"
#endif

#ifndef _GCINPUTCONTROLLER_H_
	#include "GamerCamp/GameController/GCControllerManager.h"
#endif

#ifndef _GCKEYBOARDMANAGER_H_
	#include "GamerCamp/Win32Input/GCKeyboardManager.h"
#endif

#ifndef __cocos2d_libs__CCKeyboardEvent__
	#include "base/CCEventKeyboard.h"
#endif

#include "ImpossibleRescue/Player/PlayerData/CPlayerDataManager.h"
#include "ImpossibleRescue/Audio/IAudioSystem.h"
#include "ImpossibleRescue/AssetManager/IAssetManager.h"
#include "ImpossibleRescue/Events/Mediator/IEventMediator.h"
#include "ImpossibleRescue/Events/EventTypes/CPlayBackgroundMusicEvent.h"

// GamerCamp Edit - fwd declare
class CGCObjGroupDefault;

// The Mob Edit - fwd declare
class CPlayerDataManager;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate
: private cocos2d::Application
, ITReceiveEvents<CGamePausedEvent>
, ITReceiveEvents<CGameResumedEvent>
, ITReceiveEvents<CPlayBackgroundMusicEvent>
{
// GamerCamp Edit
private:
	static CGCKeyboardManager*		sm_pcKeyboardManager;	// handles keyboard input
	static CGCControllerManager*	sm_pcControllerManager;
// GamerCamp Edit

// The Mob Edit
	static IEventMediator*		sm_pcEventMediator;
	CActionOnRelease			m_aorPausedHandler;
	CActionOnRelease			m_aorResumedHandler;
	CActionOnRelease			m_aorBackgroundMusicEventHandler;
	ISoundEffect*				m_psfxBackgroundMusic;

	static void					InitialisePlayerDataManager();
	static CPlayerDataManager*	sm_pcPlayerDataManager;
		
	static void					InitialiseAudioSystem();
	static IAudioSystem*		sm_pcAudioSystem;
	IAudioSystem*				GetAudioSystem() const;

	static void					InitialiseAssetManager();
	static IAssetManager*		sm_pcAssetManager;

	void CleanupBackgroundMusic();
// The Mob Edit
	
public:
    AppDelegate();
	virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

// GamerCamp Edit
	// accessors for m_pcInputManager

		// initialise actions - see CGCKeyboardManager::Initialise() for details of arguments
		static void						InitialiseKeyboardManager( u32 uNumActions, cocos2d::EventKeyboard::KeyCode pauActionsAsKeycodes[] );
		static CGCKeyboardManager*		GetKeyboardManager();

		static void						InitialiseControllerManager();
		static CGCControllerManager*	GetControllerManager();

	// accessors for m_pcInputManager
// GamerCamp Edit

// The Mob Edit
		// accessor for sm_pcEventMediator
		static IEventMediator*		GetEventMediator();
		// accessor for sm_pcEventMediator

		// accessor for sm_pcPlayerDataManager
		static CPlayerDataManager*		GetPlayerDataManager();
		// accessor for sm_pcPlayerDataManager

		// accessor for sm_pcAssetManager
		static IAssetManager*		GetAssetManager();

		virtual void VOnEventReceived( CGamePausedEvent eventArgs ) override;
		virtual void VOnEventReceived( CGameResumedEvent eventArgs ) override;
		virtual void VOnEventReceived( CPlayBackgroundMusicEvent eventArgs ) override;
		// accessor for sm_pcAssetManager
		static const float gks_fTimeStep;
// The Mob Edit
};

// GamerCamp Edit

	// initialise actions - see CGCKeyboardManager::Initialise() for details of arguments
	// static
	inline void AppDelegate::InitialiseKeyboardManager( u32 uNumActions, cocos2d::EventKeyboard::KeyCode pauActionsAsKeycodes[] )
	{
		sm_pcKeyboardManager->Initialise( uNumActions, pauActionsAsKeycodes );
		sm_pcKeyboardManager->Reset();
	}
	

	// accessor for keyboard manager
	// static
	inline CGCKeyboardManager* AppDelegate::GetKeyboardManager()
	{
		return sm_pcKeyboardManager;
	}

	// initialise actions - see CGCKeyboardManager::Initialise() for details of arguments
	// static
	inline void AppDelegate::InitialiseControllerManager()
	{
		sm_pcControllerManager->Initialise();
	}


	// accessor for keyboard manager
	// static
	inline CGCControllerManager* AppDelegate::GetControllerManager()
	{
		return sm_pcControllerManager;
	}

// GamerCamp Edit

// The Mob Edit

	// accessor for the event mediator
	// static
	inline IEventMediator* AppDelegate::GetEventMediator()
	{
		return sm_pcEventMediator;
	}

	// static
	inline void AppDelegate::InitialisePlayerDataManager()
	{
		sm_pcPlayerDataManager->Initialise();
	}

	// accessor for player data manager
	// static
	inline CPlayerDataManager* AppDelegate::GetPlayerDataManager()
	{
		return sm_pcPlayerDataManager;
	}

	// static
	inline void AppDelegate::InitialiseAudioSystem()
	{
		sm_pcAudioSystem->VInitialise();
	}


	inline IAudioSystem* AppDelegate::GetAudioSystem() const
	{
		return sm_pcAudioSystem;
	}

	// static
	inline void AppDelegate::InitialiseAssetManager()
	{
		sm_pcAssetManager->VInitialise();
	}

	// accessor for asset manager
	// static
	inline IAssetManager* AppDelegate::GetAssetManager()
	{
		return sm_pcAssetManager;
	}

	// The Mob Edit

#endif // _APP_DELEGATE_H_

