//Name of class:	CStationHackedEvent
//Main author:		Toyan Green
//Summary:			This class is used to broadcast a message that the game was paused
//					in the game.
//
//Functions:		GetHackID					

#ifndef	_CSTATIONHACKEDEVENT_H_
#define	_CSTATIONHACKEDEVENT_H_

class CStationHackedEvent
{
public:

	CStationHackedEvent() = delete;
	CStationHackedEvent(const char* psHackId);
	~CStationHackedEvent();
	const char* GetHackID() const;

private:
	const char* m_psHackID;
};

inline CStationHackedEvent::CStationHackedEvent( const char* psHackId )
	: m_psHackID( psHackId )
{
}

inline CStationHackedEvent::~CStationHackedEvent( )
{
}

inline const char* CStationHackedEvent::GetHackID( ) const
{
	return m_psHackID;
}

#endif

