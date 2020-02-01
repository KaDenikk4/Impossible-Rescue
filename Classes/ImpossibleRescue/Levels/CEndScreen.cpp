//Name of class:	CEndScreen
//Summary:			This is class for creating end screen displayed after completing Level 4 Area 2.
//Functions:		onEnter, VOnCreate, VOnUpdate, VOnDestroy


#include "CEndScreen.h"
#include "CMenuScene.h"
#include "../UI/TickerText.h"
#include "ImpossibleRescue/Player/EPlayerCutsceneActions.h"

static EPlayerCutsceneActions s_aePlayerCutsceneActions[] = { EPlayerCutsceneActions::SkipCutscene };
static cocos2d::Controller::Key s_aeCutsceneKeys[] = { cocos2d::Controller::Key::BUTTON_A };

CEndScreen::CEndScreen()
	: IGCGameLayer( GetGCTypeIDOf( CEndScreen ) )
	, m_pcTickerText( nullptr )
{
	m_pcControllerCutsceneActionsToButtonMap = std::unique_ptr<TGCActionToKeyMap<EPlayerCutsceneActions>>
		( TCreateActionToKeyMap( s_aePlayerCutsceneActions, s_aeCutsceneKeys ) );
}

CEndScreen::~CEndScreen()
{
}

void CEndScreen::onEnter()
{
	IGCGameLayer::onEnter();
}

void CEndScreen::VOnCreate( void )
{
	IGCGameLayer::VOnCreate();

	//Cache screen size and origin values
	const cocos2d::Size  k_sVisibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	const cocos2d::Point k_pOrigin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//Add ticker text for "To be continued..."
	m_pcTickerText = new TickerText( m_krstrEndPanelText, 50.0f, 0.02f );
	m_pcTickerText->getText()->setTextHorizontalAlignment( TextHAlignment::CENTER );
	m_pcTickerText->getText()->setTextVerticalAlignment( TextVAlignment::CENTER );
	m_pcTickerText->getText()->setAnchorPoint( cocos2d::Vec2::ANCHOR_MIDDLE );
	m_pcTickerText->SetTextPosition(k_sVisibleSize.width/2, k_sVisibleSize.height/2);
	m_pcTickerText->getText()->setTextColor( Color4B::GREEN );
	this->addChild( m_pcTickerText->getText(), 1 );
}

void CEndScreen::VOnUpdate( f32 fTimeStep )
{
	IGCGameLayer::VOnUpdate( fTimeStep );

	//Cache a reference to the mapped controller
	TGCController< EPlayerCutsceneActions > cController = TGetActionMappedController( CGCControllerManager::eControllerOne, (*m_pcControllerCutsceneActionsToButtonMap) );

	m_pcTickerText->TextAnimation( fTimeStep );

	//Allow to skip the ticker text on button press
	if( cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) && !m_pcTickerText->GetTextEnd())
	{
		m_pcTickerText->SetIsSkipped( true );
	}
	//Allow to go to menu on button press after ticker text was completed.
	if( cController.ButtonHasJustBeenPressed( EPlayerCutsceneActions::SkipCutscene ) && m_pcTickerText->GetTextEnd() )
	{
		ReplaceScene( CMenuLayer::scene() );
	}

}

void CEndScreen::VOnDestroy( void )
{
	IGCGameLayer::VOnDestroy();
	

}
