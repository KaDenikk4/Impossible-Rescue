////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
//#include "ImpossibleRescue/UI/CButton.h"
#include "2d/CCMenuItem.h"
#include "../Player/EPlayerActions.h"
#include "GamerCamp/GameController/GCController.h"
#include <ImpossibleRescue/UI/EPlayerMenuActions.h>

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

class CButton;
//class MenuItemImage;
//////////////////////////////////////////////////////////////////////////
// class deriving from CCLayer that creates our main menu scene
//////////////////////////////////////////////////////////////////////////
class CMenuLayer 
: public cocos2d::CCLayer
{
public:
	CMenuLayer();
	~CMenuLayer();
    // cocos2d-x classes all have a static create() function
	// This macro implements the default behaviour of create()
	// i.e. news an instance, calls init, and calls autorelease 
    CREATE_FUNC( CMenuLayer );

    // Explicit constructor - called from the CREATE_FUNC() macro
	// n.b. this must back-chain calls to the base class versions of init()
	// or the behaviour of your code will be 'unexpected'
    virtual bool init();  

    // callback passed to the CCMenu system to be called when
	// the Game Start button is pushed
    void CB_OnGameNewGameButton( Ref* pSender);
	void CB_OnGameExitButton(Ref* pSender);
	void CB_OnGameOptionsButton(Ref* pSender);
	void CB_OnReturnButton(Ref* pSender);
	void CB_OnControlsButton(Ref* pSender);
	void CB_OnAudioButton(Ref* pSender);

	void update(float delta);

    // The cocos2d convention is to have the root layer of a scene
	// be able to create and return a CCScene* (set to autorelease)
	// which has an instance of itself as a child
    static cocos2d::Scene* scene();

private:

	CButton*				 m_apcButtonArray[2][2];
	Vec2					 m_vCurrentButtonIndex;
	Vec2					 m_vPreviousButtonIndex;

	const int				 m_ciButtonArraySize = 1;

	bool					 m_bOptionsSelected;

		
	//new way buttons done
	CButton*				 m_pcNewGameButton;
	CButton*				 m_pcLoadGameButton;
	CButton*				 m_pcOptionsButton;
	CButton*				 m_pcExitButton;

	CButton*				 m_pcReturnButton;
	
	//old way buttons done

	std::unique_ptr< TGCActionToKeyMap< EPlayerMenuActions > > m_pcControllerMenuActionsToButtonMap;

	Sprite*					 m_pcControls;

	ISoundEffect*			 m_psfxButtonSelect;
	ISoundEffect*			 m_psfxButtonPress;
};

#endif // __MENUSCENE_H__
