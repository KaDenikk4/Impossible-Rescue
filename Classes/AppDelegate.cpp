#include "AppDelegate.h"
#include <vector>
#include <string>

#include "AppMacros.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCObject/GCObjGroupDefault.h"
#include "ImpossibleRescue/Levels/CMenuScene.h"
#include "ImpossibleRescue/Audio/CAudioSystem.h"
#include "ImpossibleRescue/AssetManager/CAssetManager.h"
#include "ImpossibleRescue/Events/Mediator/CEventMediator.h"
#include "ImpossibleRescue/Audio/CExperimentalAudioSystem.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "ImpossibleRescue/Cinematic/CTitleScreen.h"


USING_NS_CC;
using namespace std;

// GamerCamp Edit
// static 
CGCKeyboardManager*		AppDelegate::sm_pcKeyboardManager	= NULL;
CGCControllerManager*	AppDelegate::sm_pcControllerManager = NULL;
// GamerCamp Edit

// The Mob Edit
// static
IEventMediator*	AppDelegate::sm_pcEventMediator = nullptr;
CPlayerDataManager*	AppDelegate::sm_pcPlayerDataManager = nullptr;
IAudioSystem*	AppDelegate::sm_pcAudioSystem = nullptr;
IAssetManager*	AppDelegate::sm_pcAssetManager = nullptr;
const float AppDelegate::gks_fTimeStep = 1.0f / 60.0f;
// The Mob Edit

AppDelegate::AppDelegate()
: m_aorPausedHandler( nullptr )
, m_aorResumedHandler( nullptr )
, m_aorBackgroundMusicEventHandler( nullptr )
, m_psfxBackgroundMusic (nullptr)
{
}

AppDelegate::~AppDelegate() 
{
// GamerCamp Edit
	// clean up win32 input 
	delete sm_pcKeyboardManager;
	sm_pcKeyboardManager = nullptr;

	delete sm_pcControllerManager;
	sm_pcControllerManager = nullptr;
// GamerCamp Edit

// GamerCamp Edit

	CleanupBackgroundMusic( );
	
	m_aorPausedHandler.Release();
	m_aorResumedHandler.Release();
	m_aorBackgroundMusicEventHandler.Release();
	
	if(sm_pcPlayerDataManager)
	{
		delete sm_pcPlayerDataManager;
		sm_pcPlayerDataManager = nullptr;
	}

	if( sm_pcAssetManager )
	{
		delete sm_pcAssetManager;
		sm_pcAssetManager = nullptr;
	}

	if (sm_pcAudioSystem)
	{
		delete sm_pcAudioSystem;
		sm_pcAudioSystem = nullptr;
	}

	if (sm_pcEventMediator)
	{
		delete sm_pcEventMediator;
		sm_pcEventMediator = nullptr;
	}
// GamerCamp Edit
}


bool AppDelegate::applicationDidFinishLaunching() 
{
   // initialize director
	auto pDirector = Director::getInstance();
	auto glview = pDirector->getOpenGLView();
	
	if( !glview ) 
	{
		glview = GLViewImpl::createWithFullScreen("Impossible Rescue");
		//ToDo: Uncomment to toggle fullscreen
		//glview = GLViewImpl::createWithRect( "Impossible Rescue", cocos2d::Rect( 0, 0, 1920, 1080 ), 1.0f, false );
		pDirector->setOpenGLView(glview);
	}

	pDirector->setOpenGLView(glview);

    // Set the design resolution
	glview->setDesignResolutionSize( designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER );

	Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;

	//////////////////////////////////////////////////////////////////////////
	// GamerCamp Edit - add windows
	#if defined WIN32
		   searchPath.push_back( WindowsResource.directory );

		   pDirector->setContentScaleFactor( MIN( WindowsResource.size.height/designResolutionSize.height, WindowsResource.size.width/designResolutionSize.width ) );
	#else
	// GamerCamp Edit - add windows
	//////////////////////////////////////////////////////////////////////////

		// In this demo, we select resource according to the frame's height.
		// If the resource size is different from design resolution size, you need to set contentScaleFactor.
		// We use the ratio of resource's height to the height of design resolution,
		// this can make sure that the resource's height could fit for the height of design resolution.

		// if the frame's height is larger than the height of medium resource size, select large resource.
		if (frameSize.height > mediumResource.size.height)
		{
			searchPath.push_back(largeResource.directory);

			pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
		}
		// if the frame's height is larger than the height of small resource size, select medium resource.
		else if (frameSize.height > smallResource.size.height)
		{
			searchPath.push_back(mediumResource.directory);
        
			pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
		}
		// if the frame's height is smaller than the height of medium resource size, select small resource.
		else
		{
			searchPath.push_back(smallResource.directory);

			pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
		}

	//////////////////////////////////////////////////////////////////////////
	// GamerCamp Edit - add windows
	#endif //#if defined WIN32
	// GamerCamp Edit - add windows
	//////////////////////////////////////////////////////////////////////////
    
    // set searching path
    CCFileUtils::getInstance()->setSearchPaths( searchPath );
	
    // turn on display FPS
    // ToDo Use this to turn on/off display stats
    // pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(gks_fTimeStep);

	//////////////////////////////////////////////////////////////////////////
	// GamerCamp Edit

 		// create & init input
		sm_pcKeyboardManager	= new CGCKeyboardManager();

		sm_pcControllerManager	= new CGCControllerManager();
		InitialiseControllerManager();

		//The Mob Edit
		sm_pcEventMediator = new CEventMediator();

		m_aorPausedHandler = AppDelegate::GetEventMediator( )->VSubscribeToGameWasPausedEvents( *this );
		m_aorResumedHandler = AppDelegate::GetEventMediator( )->VSubscribeToGameWasResumedEvents( *this );
		m_aorBackgroundMusicEventHandler = AppDelegate::GetEventMediator( )->VSubscribeToPlayBackgroundMusicEvents( *this );
	
		sm_pcAudioSystem = new CExperimentalAudioSystem(new experimental::AudioEngine());
		InitialiseAudioSystem();

		sm_pcAssetManager = new CAssetManager([&]() -> IAudioSystem* { return sm_pcAudioSystem; });
		InitialiseAssetManager();

		sm_pcPlayerDataManager = new CPlayerDataManager();
		InitialisePlayerDataManager();
	
		//The Mob Edit

		// create the initial GameScene
		Scene* pScene = CMenuLayer::scene();
		


	// GamerCamp Edit
	//////////////////////////////////////////////////////////////////////////

	// run
    pDirector->runWithScene( pScene );

	Director::getInstance()->replaceScene( TGCGameLayerSceneCreator< CTitleScreen >::CreateScene() );
	
    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}


// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::VOnEventReceived( CGamePausedEvent eventArgs )
{
	// Pause all game audio
	GetAudioSystem()->VPauseAllAudio();
}

void AppDelegate::VOnEventReceived( CGameResumedEvent eventArgs )
{
	// Resume all game audio
	GetAudioSystem()->VResumeAllAudio();
}

void AppDelegate::VOnEventReceived( CPlayBackgroundMusicEvent eventArgs)
{
	CleanupBackgroundMusic();

	m_psfxBackgroundMusic = AppDelegate::GetAssetManager()->VGetSoundEffect(eventArgs.GetBackgroundMusicType( ));
	m_psfxBackgroundMusic->VPlay(true);
}

void AppDelegate::CleanupBackgroundMusic()
{
	if (m_psfxBackgroundMusic)
	{
		m_psfxBackgroundMusic->VStop();
		delete m_psfxBackgroundMusic;
		m_psfxBackgroundMusic = nullptr;
	}
}
