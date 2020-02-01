//Name of class:	IHackable
//Main author:		Toyan Green
//Summary:			This class is an interface for hackable entities
//					in the game.
//Functions:		VHack

#ifndef	_IHACKABLE_H_
#define	_IHACKABLE_H_

class IHackable
{
public:

	virtual ~IHackable( ) = default;
	//Called from parent CHackingStation Hack method when it is successfully hacked.
	virtual void VHack() = 0;
	
};

#endif