//Name of class:	CLevel1Area2
//Summary:			This class is creating the level 1 area 2
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, 
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit,	VOnCreate, VOnUpdate, ShadowAnimation

#ifndef	_CLEVEL1AREA2_H_
#define	_CLEVEL1AREA2_H_

#ifndef _CBASELEVEL_H_
#include "ImpossibleRescue/Levels/CBaseLevel.h"
#endif
#include "ImpossibleRescue/UI/TickerText.h"


class CLevel1Area2
	: public CBaseLevel
{
public:
	CLevel1Area2();
	~CLevel1Area2();
	
	const char* VGetLevelFilePath( ) override;
	const char* VGetBackgroundFilePath( ) override;

	virtual void VOnResourceAcquire() override;
	virtual void VTransitionToNextScreen() override;
	virtual void VTransitionToPreviousScreen( ) override;
	virtual void VTransitionToNextLevel( ) override;
	virtual void VRestartLevel() override;
	virtual void VRestartAct() override;
	virtual void VOnHorizontalTransitionBorderHit( ) override;
	virtual void VOnVerticalTransitionBorderHit( ) override;

	virtual void VOnCreate() override;
	virtual void VOnUpdate( f32 fTimeStep ) override;

	void ShadowAnimation(bool pIsPAused, float timeStep);

private:
	bool						m_bWasInitialised;

	bool						m_bXButtonWasPressed;
	bool						m_bCircleWasPressed;

	TickerText*					m_pcFirstTutorialTickerText;
	TickerText*					m_pcSecondTutorialTickerText;
	const std::string&			m_crFirstTutorialText	= "Here's a crazy idea, press x to jump onto platforms.";
	const std::string&			m_crSecondTutorialText	= "You can also press circle to crouch through tight spaces.";
	cocos2d::Sprite*			m_pcShadowTextbox;
	cocos2d::Sprite*			m_pcTalkingShadowTExtbox;
	bool						m_bImageSwap;

	CTimerHelper*				m_pShadowTimer;

	bool						m_bShouldPlaySound;
	bool						m_bIsCalledOnceForFirst;
	bool						m_bIsCalledOnceForSecond;

	std::unique_ptr< TGCActionToKeyMap< EPlayerActions > > m_pcControllerTutorialActionsToButtonMap;

};

#endif
