//Name of class:	CPlayerHasDiedEvent
//Main author:		Toyan Green
//Summary:			This class is used to broadcast a message that the player has died
//					in the game.

#ifndef	_CPLAYERHASDIEDEVENT_H_
#define	_CPLAYERHASDIEDEVENT_H_

class CPlayerHasDiedEvent
{
public:
	
	CPlayerHasDiedEvent() = delete;
	
	CPlayerHasDiedEvent( int iLivesRemaining )
		: m_iLivesRemaining( iLivesRemaining )
	{
	}
	
	int GetLivesRemaining() const;

private:
	int m_iLivesRemaining;
};

inline int CPlayerHasDiedEvent::GetLivesRemaining() const
{
	return m_iLivesRemaining;
}

#endif