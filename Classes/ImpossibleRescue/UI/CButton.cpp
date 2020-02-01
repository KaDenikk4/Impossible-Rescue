#include "CButton.h"
//#include "../../cocos2d/cocos/2d/CCMenuItem.h"


CButton::CButton(float x, float y, cocos2d::MenuItemImage* item) // setting up the button here
	: mButtonIsHighlighted(false)
	, color(0, 0, 0)
{
	mItem = item;
	mItem->setPosition(x, y); // setting button's position
}

CButton::~CButton()
{

}

//this functions makes button blinking to show that the button is selected
void CButton::ButtonHighlighted()
{
	CCLOG("button is highlighting");
	mItem->selected();
}
//unselect the button
void CButton::ButtonNotHighlighted()
{
	mItem->unselected();
}

void CButton::ButtonPressed()
{
	mItem->activate(); //activate the button if the certain button was clicked on the controller
}
//check if button is highlighted
bool CButton::getIsHighlighted()
{
	return mButtonIsHighlighted;
}
//highlighting the button
void CButton::setIsHighlighted(bool highlited)
{
	mButtonIsHighlighted = highlited;
}
//set visibility of the button
void CButton::setVisibility(bool visibility)
{
	mItem->setVisible(visibility);
}
//get cocos2d button
cocos2d::MenuItemImage* CButton::getItem()
{
	return mItem;
}

