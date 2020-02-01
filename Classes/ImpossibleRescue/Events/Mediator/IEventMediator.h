//Name of class:	IEventMediator
//Main author:		Toyan Green
//Summary:			This class is an interface for the event system
//					in the game.

#ifndef	_IEVENTMEDIATOR_H_
#define	_IEVENTMEDIATOR_H_

#ifndef _IEVENTSOURCE_H_
#include "IEventSource.h"
#endif

#ifndef _IEVENTPUBLISHER_H_
#include "IEventPublisher.h"
#endif

class IEventMediator: public IEventSource, public IEventPublisher
{
public:
};

#endif