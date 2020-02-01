#ifndef _TICKERTEXT_
#define _TICKERTEXT_


#include "cocos2d.h"
#include "ui/UIText.h"
#include <iostream>
#include <string>
#include "ImpossibleRescue/Utilities/CTimerHelper.h"
#include "ImpossibleRescue/Audio/ISoundEffect.h"

class TickerText
{
public:
	TickerText(const std::string& p_text, const float p_textSize);
	TickerText(const std::string& p_text, const float p_textSize, const float p_textSpeed);
	~TickerText();

	void							TextAnimation(float timeStep );
	void							SkipTextAnimation();
	cocos2d::ui::Text*				getText();
	void							SetText(const std::string& pSetText);
	void							SetTextPosition(float x, float y);
	void							SetTextAreaSize(float x, float y);
//	void							SetColorOfText(int p_r, int p_g)
	bool							GetTextEnd();

	bool							GetIsSkipped();
	void							SetIsSkipped(bool pIsSkipped);
	void							Reset();
	void							SetTextSize(float p_textSize);
	ISoundEffect*					GetTypingSound();
	
private:
	int								m_iCurrentLetter;
	
	cocos2d::ui::Text*				m_pText;

	CTimerHelper*					m_pTimer;
	bool							m_bTextFinished;

	bool							m_bIsSkipped;

	ISoundEffect*					m_psfxTypingSound;
};


#endif //_TICKERTEXT_

