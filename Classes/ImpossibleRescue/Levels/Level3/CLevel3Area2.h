//Name of class:	CLevel3Area2
//Summary:			This class is creating the level 3 area 2
//Functions:		VOnResourceAcquire, VOnUpdate, VGetLevelFilePath, VGetBackgroundFilePath,
//					VTransitionToNextScreen, VTransitionToPreviousScreen, VTransitionToNextLevel,
//					VRestartLevel, VRestartAct,	VOnHorizontalTransitionBorderHit,
//					VOnVerticalTransitionBorderHit

#ifndef	_CLEVEL3AREA2_H_
#define	_CLEVEL3AREA2_H_

#ifndef _CBASELEVEL_H_
#include "ImpossibleRescue/Levels/CBaseLevel.h"
#endif


class CLevel3Area2
	: public CBaseLevel
{
public:
	CLevel3Area2();
	~CLevel3Area2();

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
};

#endif
