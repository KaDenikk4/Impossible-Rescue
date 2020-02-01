//Name of class:	CLevel1Area1
//Summary:			This class is creating the level 1 area 1
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit, VOnVerticalTransitionBorderHit,
//					VOnCreate, ShadowAnimation

#ifndef	_CLEVEL1AREA1_H_
#define	_CLEVEL1AREA1_H_

#ifndef _CBASELEVEL_H_
#include "ImpossibleRescue/Levels/CBaseLevel.h"
#endif
#include "ImpossibleRescue/UI/TickerText.h"


class CLevel1Area1
	: public CBaseLevel
{
public:
	CLevel1Area1();
	~CLevel1Area1();

	virtual void VOnResourceAcquire() override;
	virtual void VOnUpdate( f32 fTimeStep ) override;
	
	virtual const char* VGetLevelFilePath( ) override;
	virtual const char* VGetBackgroundFilePath( ) override;
	
	virtual void VTransitionToNextScreen() override;
	virtual void VTransitionToPreviousScreen( ) override;
	virtual void VTransitionToNextLevel() override;
	virtual void VRestartLevel() override;
	virtual void VRestartAct() override;
	virtual void VOnHorizontalTransitionBorderHit( ) override;	
	virtual void VOnVerticalTransitionBorderHit( ) override;

	virtual void VOnCreate() override;
	
	void ShadowAnimation(bool pIsPAused, float timeStep);


private:
	
	TickerText*					 m_pcFirstTutorialTickerText;
	//setting up ticker text string here
	const std::string&			 m_crTutorialText = "Hi, I am SHADOW your personal advisor. Use the left analog stick or left and right on the D-pad to move.";
	cocos2d::Sprite*			 m_pcShadowTextbox;
	cocos2d::Sprite*			 m_pcTalkingShadowTExtbox;
	bool						 m_bShouldPlaySound;
	bool						 m_bIsCalledOnce;

	bool						 m_bImageSwap;

	CTimerHelper*				 m_pShadowTimer;

};

#endif
