#include "TickerText.h"
#include "AppDelegate.h"

//creating a constructor for the ticker text
TickerText::TickerText(const std::string& p_text, const float p_textSize)
	:  m_iCurrentLetter(0)
	, m_pTimer(nullptr)
	, m_bTextFinished(false)
	, m_bIsSkipped(false)
	, m_pText(nullptr)
	, m_psfxTypingSound(nullptr)
{
	//setting up a text here
	m_pText = cocos2d::ui::Text::create(p_text, "fonts/ethnocentric_rg.ttf", p_textSize);
	m_pText->setOpacity(0);
	m_pTimer = new CTimerHelper(0.001f); // setting timer
	m_pText->setAnchorPoint(cocos2d::Vec2(0, 0));
	//sound effect
	m_psfxTypingSound = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::TickerText);
}
//another constructor
TickerText::TickerText(const std::string& p_text, const float p_textSize, const float p_textSpeed)
	: m_iCurrentLetter(0)
	, m_pTimer(nullptr)
	, m_bTextFinished(false)
	, m_bIsSkipped(false)
	, m_pText(nullptr)
	, m_psfxTypingSound(nullptr)
{
	//setting up a text here
	m_pText = cocos2d::ui::Text::create(p_text, "fonts/deadman.ttf", p_textSize);
	m_pText->setOpacity(0);
	m_pTimer = new CTimerHelper(p_textSpeed); //setting timer
	m_pText->setAnchorPoint(cocos2d::Vec2(0, 0));
	//setting sound effect
	m_psfxTypingSound = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::TickerText);
}


TickerText::~TickerText() 
{
	if(m_pText)
	{
		m_pText->removeFromParentAndCleanup( true );
		m_pText = nullptr;
	}

	if(m_pTimer)
	{
		delete(m_pTimer);
		m_pTimer = nullptr;
	}

	if(m_psfxTypingSound)
	{
		delete(m_psfxTypingSound);
		m_psfxTypingSound = nullptr;
	}
}

void TickerText::TextAnimation(float timeStep)
{
	auto m_pAnimatedText = static_cast<cocos2d::Sprite*>(m_pText->getLetter(m_iCurrentLetter));

	//running timer
	m_pTimer->RunTimer(timeStep);
	if (m_pTimer->GetTimerCompleted())
	{
		if (!m_bIsSkipped)
		{
			//setting letter opacity after timer finish
			if (m_pAnimatedText)
			{
				m_pAnimatedText->setOpacity(255);
			}
			m_iCurrentLetter++;
			m_pTimer->ResetTimer();
		}
		else
		{
			m_pText->setOpacity(255);
			m_bTextFinished = true;
		}
	}
	//checking end of the string
	if(m_iCurrentLetter>=m_pText->getStringLength())
	{
		m_bTextFinished = true;
	}

}

//skipping text
void TickerText::SkipTextAnimation()
{
	for (int i = 0; i++; i >= m_pText->getStringLength())
	{
		auto m_pAnimated = static_cast<cocos2d::Sprite*>(m_pText->getLetter(i));
		if (m_pAnimated)
			m_pAnimated->setOpacity(255);
	}
}

//setting string
void TickerText::SetText(const std::string& pSetText)
{
	m_pText->setString(pSetText);
	Reset();
}
//setting positions
void TickerText::SetTextPosition(float x, float y)
{
	m_pText->setPosition(cocos2d::Vec2(x, y));
}
//setting area size
void TickerText::SetTextAreaSize(float x, float y)
{
	m_pText->setTextAreaSize(cocos2d::Size(x, y));
}
//checking if text is finished
bool TickerText::GetTextEnd()
{
	return m_bTextFinished;
}
//checking if text is skipped
bool TickerText::GetIsSkipped()
{
	return m_bIsSkipped;
}
//setting text to be skipped
void TickerText::SetIsSkipped(bool pIsSkipped)
{
	m_bIsSkipped = pIsSkipped;
}
//reseting the text
void TickerText::Reset()
{
	m_iCurrentLetter = 0;
	m_pText->setOpacity(0);
	m_bIsSkipped = false;
	m_bTextFinished = false;
}
//setting font
void TickerText::SetTextSize(float p_textSize)
{
	m_pText->setFontSize(p_textSize);
}
//checking typing sound
ISoundEffect* TickerText::GetTypingSound()
{
	return m_psfxTypingSound;
}
//returning cocos2d text function
cocos2d::ui::Text* TickerText::getText()
{
	return m_pText;
}
