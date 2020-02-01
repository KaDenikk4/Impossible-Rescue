//Name of class:	TNotificationChannel
//Main author:		Toyan Green
//Summary:			This template class stores a list of subscribers that it can send events to
//					in the game.
//Functions:		AddSubscriber, PublishEvent

#ifndef	_TNOTIFICATIONCHANNEL_H_
#define	_TNOTIFICATIONCHANNEL_H_

#ifndef	_CACTIONONRELEASE_H_
#include "CActionOnRelease.h"
#endif

#ifndef	_ITRECEIVEEVENTS_H_
#include "ITReceiveEvents.h"
#endif

#include "base/ccMacros.h"
#include "ImpossibleRescue/Utilities/CHelperFunctions.h"

template < typename TEventType >
class TNotificationChannel
{
public:

	TNotificationChannel() = default;
	
	/// <summary>
	/// Add an object to the list of subscribers that receive events via this channel.
	/// </summary>
	/// <param name="ireTHandler"></param>
	CActionOnRelease AddSubscriber( ITReceiveEvents<TEventType>& ireTHandler);

	/// <summary>
	/// Publish an event to all subscribers of this channel.
	/// </summary>
	/// <param name="eTArgument"></param>
	void PublishEvent(const TEventType& eTArgument);

private:

	// Container of objects that are receiving events
	std::vector< ITReceiveEvents< TEventType >* > m_vireEventHandlers;
};

template< typename TEventType >
CActionOnRelease TNotificationChannel<TEventType>::AddSubscriber( ITReceiveEvents<TEventType>& ireTHandler )
{
	// Check if the passed handler is already receiving events of this type
	if (CHelperFunctions::CVectorFunctions::Contains(m_vireEventHandlers, &ireTHandler))
	{
		// Object is already receiving events
		CCASSERT(false, "Object is already subscribed to events");
	}

	// Add handler to the list of event listeners
	m_vireEventHandlers.push_back(&ireTHandler);

	// Return an object that can be used to remove the handler from the list of event listeners
	return CActionOnRelease([&]() -> void
	{
		m_vireEventHandlers.erase(std::remove(m_vireEventHandlers.begin(),
			m_vireEventHandlers.end(), &ireTHandler), m_vireEventHandlers.end());
	});
}

template< typename TEventType >
void TNotificationChannel<TEventType>::PublishEvent(const TEventType& eTArgument)
{
	const size_t iNumNotificationHandlers = m_vireEventHandlers.size();

	// Publish the event to all handlers registered to listen to events of this type
	for (int i = 0; i < iNumNotificationHandlers; ++i)
	{
		m_vireEventHandlers[i]->VOnEventReceived(eTArgument);
	}
}

#endif
