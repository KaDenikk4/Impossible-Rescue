//Name of class:	CTimerHelper
//Summary:			Helper class for creating functional timers
//Functions:		RunTimer, ExecuteFuncWithDelay, GetTimerCompleted, ResetTimer

#ifndef CTIMER_HELPER
#define	CTIMER_HELPER
#include <functional>


class CTimerHelper
{
public:
	CTimerHelper	();
	CTimerHelper	( float fTimerAmount );
	~CTimerHelper	();

	void RunTimer					( float fSeconds, float fTimeStep );
	void RunTimer					( float fTimeStep );
	void ExecuteFuncWithDelay		( float fDelay, float fTimeStep, std::function<void()> pfnFunctionToExecute, bool bToBeExecutedOnce );
	const bool GetTimerCompleted	( );
	void ResetTimer();

private:
	float	m_fTimerAmount;
	float	m_fTimeOnConstructor;
	bool	m_bWasTimeSet;
	bool	m_bTimerCompleted;
};

#endif // !CTIMER_HELPER

