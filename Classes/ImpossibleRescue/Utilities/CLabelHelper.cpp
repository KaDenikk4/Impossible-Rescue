//Name of class:	CLabelHelper
//Summary:			Helper class for creating functional labels
//Functions:		AddLabelAtPosition, RemoveLabel, ShowLabel, DisplayLabelForSeconds, SetLabelMessage
//					Update


#include "CLabelHelper.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"



CLabelHelper::CLabelHelper()
	: m_pcLabel ( nullptr )
{
}


CLabelHelper::~CLabelHelper()
{
	
}


// ToDo: create overloaded constructor with this function params
// ToDo: const & for string
void CLabelHelper::AddLabelAtPosition(	IGCGameLayer* pcCurrentLayer, std::string cMsgToDisplay, std::string cFontName,
										float fFontSize, const cocos2d::Vec2& rv2Position, bool bIsVisible )
{
	m_pcLabel = cocos2d::Label::create( cMsgToDisplay, cFontName, fFontSize );
	m_pcLabel->setPosition( rv2Position );
	pcCurrentLayer->addChild( m_pcLabel );
	m_pcLabel->setVisible( bIsVisible );
}

void CLabelHelper::RemoveLabel( IGCGameLayer* pcCurrentLayer )
{
	pcCurrentLayer->removeChild( m_pcLabel );
	m_pcLabel = nullptr;
}

void CLabelHelper::ShowLabel( bool bIsVisible )
{
	m_pcLabel->setVisible( bIsVisible );
}

void CLabelHelper::DisplayLabelForSeconds( float fSeconds, float fTimestep )
{
	if( fSeconds > 0.0f )
	{
		m_pcLabel->setVisible( true );
		fSeconds -= fTimestep;
	}
	else
	{
		m_pcLabel->setVisible( false );
	}
}

void CLabelHelper::SetLabelMessage( std::string strMessage )
{
	m_pcLabel->setString( strMessage );
}
