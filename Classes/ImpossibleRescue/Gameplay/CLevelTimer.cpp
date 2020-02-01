// Name of class:	CLevelTimer
// Summary:			Class responsible for creating level timer with the function to add the label
//					to the scene.
// Functions:		AddTimerLabel, ResetTimer, Update, GetDidTimeRunOut, RemoveTimer, SetTimer,
//					GetTimeRemaining, SetVisibility

#include "CLevelTimer.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include <stdlib.h>
#include <math.h>

CLevelTimer::CLevelTimer()
	: m_cStringToDisplay		( "" )
	, m_cStringToDisplayDecimals( "" )
	, m_pcTimerText				( nullptr )
	, m_pcTimerColonSign		( nullptr )
	, m_pcTimerTextDecimals		( nullptr )
	, m_fTimerAmount			( 0.0f )
	, m_fWholeNumber			( 0.0f )
	, m_fDecimalNumber			( 0.0f )
	, m_fColonSignOffset		( 0.0f )
	, m_fDecimalNumberOffset	( 0.0f )
	, m_bDidTimeRunOut			( false )
	, m_cYellowColour			( 192, 192, 0, 255 )
	, m_cOrangeColour			( 192, 128, 0, 255 )
	, m_cRedColour				( 255, 0, 0, 255 )
	, m_pcTextFlashTimer		(nullptr)
	, m_bScalingSwap			(false)
	, m_bWasScaled				(false)
{
	m_pcTextFlashTimer = new CTimerHelper(0.5f);
}

CLevelTimer::CLevelTimer( float fTimerAmount )
	: m_pcTimerText				( nullptr )
	, m_fTimerAmount			( fTimerAmount )
	, m_bDidTimeRunOut			( false )
	, m_cStringToDisplay		( "" )
	, m_cStringToDisplayDecimals( "" )
	, m_pcTimerColonSign		( nullptr )
	, m_pcTimerTextDecimals		( nullptr )
	, m_fWholeNumber			( 0.0f )
	, m_fDecimalNumber			( 0.0f )
	, m_fColonSignOffset		( 0.0f )
	, m_fDecimalNumberOffset	( 0.0f )
	, m_cYellowColour			( 192, 192, 0, 255 )
	, m_cOrangeColour			( 192, 128, 0, 255 )
	, m_cRedColour				( 255, 0, 0, 255 )
	, m_pcTextFlashTimer		( nullptr )
	, m_bScalingSwap			( false )
	, m_bWasScaled				( false )
{
	m_pcTextFlashTimer = new CTimerHelper(0.5f);
}

CLevelTimer::~CLevelTimer()
{
	if(m_pcTextFlashTimer)
	{
		delete(m_pcTextFlashTimer);
		m_pcTextFlashTimer = nullptr;
	}
	
}


//Summary:		Adds the timer label and sets the timer expiry time.
//
//Parameters:	pcCurrentLayer	- pointer to current scene's layer, required for
//								  adding the labels
//				fFontsize		- sets the size of the font on the label
//				fTimerValue		- sets the timer expiry time
//				rcPosition		- sets the position of the labels
//
void CLevelTimer::AddTimerLabel( IGCGameLayer* pcCurrentLayer, float fFontSize, float fTimerValue, const cocos2d::Vec2& rcPosition )
{
	// ToDo look into using sprintf to do text formatting
	
	m_fTimerAmount				= fTimerValue;
	m_fColonSignOffset			= fFontSize + 10.0f;
	m_fDecimalNumberOffset		= fFontSize * 2 + 15.0f;

	//Setting up strings to display only 2 symbols on reset instead of "accurate" float (x.xxxxxx)
	m_fWholeNumber				= floor( m_fTimerAmount );
	m_cStringToDisplay			= std::to_string( m_fWholeNumber );
	m_cStringToDisplay.resize( 2 );
	
	m_fDecimalNumber			= m_fTimerAmount - m_fWholeNumber;
	m_cStringToDisplayDecimals	= "0" + std::to_string( m_fDecimalNumber * 100 );
	m_cStringToDisplayDecimals.resize( 2 );
	
	//Setting up separate labels so the numbers don't jitter on the screen.
	//Setting it as one string causes the timer value to move around due to non-uniform size of the font used.
	m_pcTimerText = new cocos2d::Label();
	m_pcTimerText = cocos2d::Label::createWithTTF( "", "fonts/ethnocentric_rg.ttf", fFontSize );
	m_pcTimerText->setString( m_cStringToDisplay );
	m_pcTimerText->setPosition( rcPosition );
	pcCurrentLayer->addChild( m_pcTimerText, 1 );

	m_pcTimerColonSign = new cocos2d::Label();
	m_pcTimerColonSign = cocos2d::Label::createWithTTF( ":", "fonts/ethnocentric_rg.ttf", fFontSize );
	m_pcTimerColonSign->setPosition( rcPosition.x + m_fColonSignOffset, rcPosition.y );
	pcCurrentLayer->addChild( m_pcTimerColonSign, 1 );
	
	m_pcTimerTextDecimals = new cocos2d::Label();
	m_pcTimerTextDecimals = cocos2d::Label::createWithTTF( m_cStringToDisplayDecimals, "fonts/ethnocentric_rg.ttf", fFontSize );
	m_pcTimerTextDecimals->setPosition( rcPosition.x + m_fDecimalNumberOffset, rcPosition.y );
	pcCurrentLayer->addChild( m_pcTimerTextDecimals, 1 );

	m_pcTimerText->setTextColor( m_cYellowColour );
	m_pcTimerColonSign->setTextColor( m_cYellowColour );
	m_pcTimerTextDecimals->setTextColor( m_cYellowColour );

	m_fScaleHolder = m_pcTimerText->getScaleX();
}


//Summary:		Resets the timer with a value of choice
//Parameters:	fMaxValue - value that timer takes as new expiry time
//
void CLevelTimer::ResetTimer( float fMaxValue )
{
	m_fTimerAmount = fMaxValue;
	m_bDidTimeRunOut = false;
}


//Summary:		Base update function. It sets the string for the timer
//				to be rounded to 2 decimal points.
//Parameters:	fTimeStep - float indicating timestep in main gameloop
//
void CLevelTimer::Update( float fTimeStep )
{
	m_cStringToDisplay.resize( 2 );
	m_cStringToDisplayDecimals.resize( 2 );
	
	if (m_fTimerAmount > 0.0f)
	{
		m_fTimerAmount -= fTimeStep;
		//This line rounds float to 2 decimal points, reference with link in the PDF portfolio (Tomasz)
		m_cStringToDisplay = std::to_string(roundf(m_fTimerAmount * 100) / 100);

		m_fWholeNumber = floor( m_fTimerAmount );
		
		m_cStringToDisplay = std::to_string( m_fWholeNumber );
		m_fDecimalNumber = m_fTimerAmount - m_fWholeNumber;
		m_cStringToDisplayDecimals = std::to_string( m_fDecimalNumber * 100 );
		m_cStringToDisplayDecimals.resize( 2 );
		//Resizing the string based on the number displayed to show only 2 decimal points
		//Note: comma is a symbol.

		if(m_fDecimalNumber < 0.1 )
		{
			m_cStringToDisplayDecimals = "0" + std::to_string( m_fDecimalNumber*100 );
			m_cStringToDisplayDecimals.resize( 2 );
		}
		
		if( m_fTimerAmount >= 20.0f )
		{
			m_cStringToDisplay.resize( 2 );
			m_pcTimerText->setTextColor( m_cYellowColour );
			m_pcTimerColonSign->setTextColor( m_cYellowColour );
			m_pcTimerTextDecimals->setTextColor( m_cYellowColour );
		}
		if ( m_fTimerAmount >= 10.0f && m_fTimerAmount < 20.0f)
		{
			m_cStringToDisplay.resize( 2 );
			m_pcTimerText->setTextColor( m_cOrangeColour );
			m_pcTimerColonSign->setTextColor( m_cOrangeColour );
			m_pcTimerTextDecimals->setTextColor( m_cOrangeColour );
		}
		if( m_fTimerAmount < 10.0f )
		{
			m_cStringToDisplay = "0" + std::to_string( m_fWholeNumber );
			m_cStringToDisplay.resize( 2 );
			
			m_pcTimerText->setTextColor( m_cRedColour );
			m_pcTimerColonSign->setTextColor( m_cRedColour );
			m_pcTimerTextDecimals->setTextColor( m_cRedColour );
			//adding the flashing here
			//m_iTimeHolder = roundf(m_fTimerAmount);
			//setting scaling of the text here to making blinking effect
			
			//timer
			m_pcTextFlashTimer->RunTimer(fTimeStep);
			if (m_pcTextFlashTimer->GetTimerCompleted())
			{
				//scaling text up
				if (m_bScalingSwap /*&& m_iTimeHolder % 2 == 0 && !m_bWasScaled*/)
				{
					m_pcTimerText->setScale(1.2, 1.2);
					m_pcTimerColonSign->setScale(1.2, 1.2);
					m_pcTimerTextDecimals->setScale(1.2, 1.2);
					m_bWasScaled = true;
				}
				//scaling text down
				else
				{
					m_pcTimerText->setScale(m_fScaleHolder, m_fScaleHolder);
					m_pcTimerColonSign->setScale(m_fScaleHolder, m_fScaleHolder);
					m_pcTimerTextDecimals->setScale(m_fScaleHolder, m_fScaleHolder);
					m_bWasScaled = false;
				}
				m_bScalingSwap = !m_bScalingSwap;
				m_pcTextFlashTimer->ResetTimer(); //reset timer
			}

		}

		m_pcTimerTextDecimals->setString( m_cStringToDisplayDecimals );
		m_pcTimerText->setString( m_cStringToDisplay );
		
	}
	else
	{
		//ToDo: Display - "You failed your mission!"
		m_bDidTimeRunOut = true;
		m_pcTimerText->setString( "0.00" );
	}
	
}


//Summary:		Getter for a bool to check if timer ran out.
//
bool CLevelTimer::GetDidTimeRunOut()
{
	return m_bDidTimeRunOut;
}


//Summary:		Function responsible for cleaning up timer label.
//Parameters:	pcCurrentLayer* - pointer to current scene's layer, required for
//								  removal of labels
//								  
void CLevelTimer::RemoveTimer( IGCGameLayer* pcCurrentLayer )
{
	pcCurrentLayer->removeChild( m_pcTimerTextDecimals, true );
	m_pcTimerTextDecimals = nullptr;

	pcCurrentLayer->removeChild( m_pcTimerColonSign, true );
	m_pcTimerColonSign = nullptr;
	
	pcCurrentLayer->removeChild( m_pcTimerText, true );
	m_pcTimerText = nullptr;
}

void CLevelTimer::SetTimer( float fTimeValue )
{
	m_fTimerAmount = fTimeValue;
}

float CLevelTimer::GetTimeRemaining()
{
	return m_fTimerAmount;
}

void CLevelTimer::SetVisibility( bool bVisibility ) const
{
	m_pcTimerText->setVisible(bVisibility);
	m_pcTimerColonSign->setVisible(bVisibility);
	m_pcTimerTextDecimals->setVisible(bVisibility);
}
