
#ifndef _BUTTON_
#define _BUTTON_
#include "2d/CCMenuItem.h"

class CButton
{
private:
	//creating the button from cocos 2dx
	cocos2d::MenuItemImage*		 mItem;
	
	//boolean will help us recognize, when button is selected for controller	
	bool						 mButtonIsHighlighted;
	cocos2d::Color3B			 color;
public:
	CButton(float x, float y, cocos2d::MenuItemImage* item  );
	~CButton();

	void						 ButtonHighlighted();
	void						 ButtonNotHighlighted();
	void						 ButtonPressed();
	bool						 getIsHighlighted();
	void						 setIsHighlighted(bool highlited);
	void						 setVisibility(bool visibility);
	cocos2d::MenuItemImage*		getItem();
};


#endif // _BUTTON_
