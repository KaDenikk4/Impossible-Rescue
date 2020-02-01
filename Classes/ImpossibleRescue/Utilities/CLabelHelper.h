//Name of class:	CLabelHelper
//Summary:			Helper class for creating functional labels
//Functions:		AddLabelAtPosition, RemoveLabel, ShowLabel, DisplayLabelForSeconds, SetLabelMessage
//					Update

#ifndef CLABEL_HELPER
#define	CLABEL_HELPER

#include "2d/CCLabel.h"

class IGCGameLayer;

class CLabelHelper
{
public:
	CLabelHelper();
	~CLabelHelper();

	void AddLabelAtPosition( IGCGameLayer* pcCurrentLayer, std::string cMsgToDisplay, std::string cFontName, 
							 float fFontSize, const cocos2d::Vec2& rv2Position, bool bIsVisible);
	
	void RemoveLabel( IGCGameLayer* pcCurrentLayer );

	void ShowLabel( bool bIsVisible );
	
	void DisplayLabelForSeconds( float fSeconds, float fTimestep );

	void SetLabelMessage( std::string strMessage );

	void Update( float fTimeStep );
	
private:
	cocos2d::Label* m_pcLabel;
};

#endif // CLABEL_HELPER