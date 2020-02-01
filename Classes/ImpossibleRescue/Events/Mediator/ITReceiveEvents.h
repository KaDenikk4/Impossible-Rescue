//Name of class:	ITReceiveEvents
//Main author:		Toyan Green
//Summary:			This an interface to a template class for objects that will receive events
//					in the game.
//Functions:		VOnEventReceived

#ifndef	_ITRECEIVEEVENTS_H_
#define	_ITRECEIVEEVENTS_H_

template < typename TEventType >
class ITReceiveEvents
{
public:
	virtual ~ITReceiveEvents() = default;

	/// <summary>
	/// Functionality to be executed when the object receives an event from the mediator
	/// </summary>
	/// <param name="eventArgs"></param>
	virtual void VOnEventReceived(TEventType eventArgs) = 0;
};

#endif