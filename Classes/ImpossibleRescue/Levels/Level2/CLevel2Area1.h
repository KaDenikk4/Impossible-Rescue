//Name of class:	CLevel2Area1
//Summary:			This class is creating the level 2 area 1
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit,	VOnCreate, ShadowAnimation

#ifndef	_CLEVEL2AREA1_H_
#define	_CLEVEL2AREA1_H_

#ifndef _CBASELEVEL_H_
#include "ImpossibleRescue/Levels/CBaseLevel.h"
#endif
#include "ImpossibleRescue/UI/TickerText.h"


class CLevel2Area1
	: public CBaseLevel
{
public:
	
	CLevel2Area1();
	~CLevel2Area1();

	virtual void VOnResourceAcquire() override;
	virtual void VOnUpdate( f32 fTimeStep ) override;

	const char* VGetLevelFilePath() override;
	const char* VGetBackgroundFilePath() override;

	virtual void VTransitionToNextScreen() override;
	virtual void VTransitionToPreviousScreen() override;
	virtual void VTransitionToNextLevel() override;
	virtual void VRestartLevel() override;
	virtual void VRestartAct() override;
	virtual void VOnHorizontalTransitionBorderHit( ) override;
	virtual void VOnVerticalTransitionBorderHit( ) override;

	virtual void VOnCreate() override;

	void ShadowAnimation(bool pIsPAused, float timeStep);

private:
	bool					m_bTriangleButtonWasPressed;
	
	TickerText*				m_pcFirstTutorialTickerText;

	const std::string&		m_crFirstTutorialText = "Hold triangle to hack that terminal. It should shut down the laser and clear a path.";
	cocos2d::Sprite*		m_pcShadowTextbox;
	cocos2d::Sprite*		m_pcTalkingShadowTExtbox;
	
	bool					m_bShouldPlaySound;
	bool					m_bIsCalledOnceForFirst;

	std::unique_ptr< TGCActionToKeyMap< EPlayerActions > > m_pcControllerTutorialActionsToButtonMap;

	bool					m_bImageSwap;

	CTimerHelper*			m_pShadowTimer;

};

#endif
