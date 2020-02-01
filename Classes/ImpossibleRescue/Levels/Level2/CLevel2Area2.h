//Name of class:	CLevel2Area2
//Summary:			This class is creating the level 2 area 2
//Functions:		VGetLevelFilePath, VGetBackgroundFilePath, VTransitionToNextScreen,
//					VTransitionToPreviousScreen, VTransitionToNextLevel, VRestartLevel, 
//					VRestartAct, VOnHorizontalTransitionBorderHit, VOnVerticalTransitionBorderHit,
//					VOnUpdate

#ifndef	_CLEVEL2AREA2_H_
#define	_CLEVEL2AREA2_H_

#ifndef _CBASELEVEL_H_
#include "ImpossibleRescue/Levels/CBaseLevel.h"
#endif



class CLevel2Area2
	: public CBaseLevel
{
public:
	CLevel2Area2();
	~CLevel2Area2();

	const char* VGetLevelFilePath() override;
	const char* VGetBackgroundFilePath() override;

	virtual void VTransitionToNextScreen() override;
	virtual void VTransitionToPreviousScreen() override;
	virtual void VTransitionToNextLevel() override;
	virtual void VRestartLevel() override;
	virtual void VRestartAct() override;
	virtual void VOnHorizontalTransitionBorderHit( ) override;
	virtual void VOnVerticalTransitionBorderHit( ) override;

	virtual void VOnUpdate(f32 fTimeStep) override;
	
private:
	bool m_bWasInitialised;
};

#endif
