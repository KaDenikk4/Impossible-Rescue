//Name of class:	ELevelTransitionType
//Main author:		Toyan Green
//Summary:			This class is an enumeration for level transition types
//					in the game.

#ifndef	_ELEVELTRANSITIONTYPE_H_
#define	_ELEVELTRANSITIONTYPE_H_

enum class ELevelTransitionType
{
	Unknown = 0,
	PreviousArea = 1,
	NextArea = 2,
	NextLevel = 3,
	NewGame = 4,
};

#endif