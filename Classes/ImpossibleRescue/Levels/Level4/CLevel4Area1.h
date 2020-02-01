//Name of class:	CLevel4Area1
//Summary:			This class is creating the level 4 area 1
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VOnResourceAcquire, VOnUpdate,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit

#ifndef	_CLEVEL4AREA1_H_
#define	_CLEVEL4AREA1_H_

#ifndef _CBASELEVEL_H_
#include "ImpossibleRescue/Levels/CBaseLevel.h"
#endif

class CLevelTimer;

class CLevel4Area1
	: public CBaseLevel
{
public:
	
	CLevel4Area1();
	~CLevel4Area1();

	const char* VGetLevelFilePath() override;
	const char* VGetBackgroundFilePath() override;

	virtual void VOnResourceAcquire() override;
	virtual void VOnUpdate( f32 fTimeStep ) override;
	
	virtual void VTransitionToNextScreen() override;
	virtual void VTransitionToPreviousScreen() override;
	virtual void VTransitionToNextLevel() override;
	virtual void VRestartLevel() override;
	virtual void VRestartAct() override;
	virtual void VOnHorizontalTransitionBorderHit( ) override;
	virtual void VOnVerticalTransitionBorderHit( ) override;

private:
	CLevelTimer* m_pcLevelTimer;
	cocos2d::Sprite* m_pcTimerBackground;
};

#endif
