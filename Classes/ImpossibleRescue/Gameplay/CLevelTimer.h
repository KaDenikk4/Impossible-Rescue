// Name of class:	CLevelTimer
// Summary:			Class responsible for creating level timer with the function to add the label
//					to the scene.
// Functions:		AddTimerLabel, ResetTimer, Update, GetDidTimeRunOut, RemoveTimer, SetTimer,
//					GetTimeRemaining, SetVisibility


#ifndef LEVELTIMER_H
#define LEVELTIMER_H

#include "math/Vec2.h"
#include "../../GamerCamp/GCObject/GCObject.h"
#include "2d/CCLabel.h"
#include "ImpossibleRescue/Utilities/CTimerHelper.h"


class IGCGameLayer;

class CLevelTimer
{
public:
	CLevelTimer();
	CLevelTimer( float fTimerAmount );
	~CLevelTimer();

	//Function for adding the timer Label
	void AddTimerLabel		( IGCGameLayer* pcCurrentLayer, float fFontSize, float fTimerValue, const cocos2d::Vec2& rcPosition );
	
	//Function for reset of the timer with the value of choice
	void ResetTimer			( float fMaxValue );
	
	//Base update function for timer countdown
	void Update				( float fTimeStep );
	
	//Getter of bool to check if timer finished
	bool GetDidTimeRunOut();

	//Function for removal of the timer Label
	void RemoveTimer		( IGCGameLayer* pcCurrentLayer );

	void	SetTimer( float fTimeValue );
	float	GetTimeRemaining();

	// Set the visibility of the timer
	void SetVisibility( bool bVisibility ) const;

private:
	std::string				m_cStringToDisplay;
	std::string				m_cStringToDisplayDecimals;
	cocos2d::Label*			m_pcTimerText;
	cocos2d::Label*			m_pcTimerColonSign;
	cocos2d::Label*			m_pcTimerTextDecimals;
	CTimerHelper*			m_pcTextFlashTimer;
	float					m_fTimerAmount;
	float					m_fWholeNumber;
	float					m_fDecimalNumber;
	float					m_fColonSignOffset;
	float					m_fDecimalNumberOffset;
	int						m_iTimeHolder;
	float					m_fScaleHolder;
	bool					m_bDidTimeRunOut;
	bool					m_bScalingSwap;
	bool					m_bWasScaled;
	cocos2d::Color4B		m_cYellowColour;
	cocos2d::Color4B		m_cOrangeColour;
	cocos2d::Color4B		m_cRedColour;
};

#endif
