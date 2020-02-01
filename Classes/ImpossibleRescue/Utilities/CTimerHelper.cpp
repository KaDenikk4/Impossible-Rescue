//Name of class:	CTimerHelper
//Summary:			Helper class for creating functional timers
//Functions:		RunTimer, ExecuteFuncWithDelay, GetTimerCompleted, ResetTimer


#include "CTimerHelper.h"

CTimerHelper::CTimerHelper()
	: m_fTimerAmount		( 0.0f )
	, m_fTimeOnConstructor	( 0.0f )
	, m_bWasTimeSet			( false )
	, m_bTimerCompleted		( false )
{

}

CTimerHelper::CTimerHelper	( float fTimerAmount )
	: m_fTimerAmount		( fTimerAmount )
	, m_fTimeOnConstructor	( m_fTimerAmount )
	, m_bWasTimeSet			( false )
	, m_bTimerCompleted( false )
{

}

CTimerHelper::~CTimerHelper()
{

}

void CTimerHelper::RunTimer( float fSeconds, float fTimeStep )
{
	if (!m_bWasTimeSet)
	{
		m_fTimerAmount = fSeconds;
		m_bWasTimeSet = true;
	}
	if( m_fTimerAmount > 0.0f )
	{
		m_fTimerAmount -= fTimeStep;
	}
	else
	{
		m_bTimerCompleted = true;
	}	
}

void CTimerHelper::RunTimer( float fTimeStep )
{
	if( m_fTimerAmount > 0.0f )
	{
		m_fTimerAmount -= fTimeStep;
	}
	else
	{
		m_bTimerCompleted = true;
	}
}

//This function executes a function with delay. Once it was hit, it runs the timer for set delay.
//It executes the function once after the timer runs out.
void CTimerHelper::ExecuteFuncWithDelay(float fDelay, float fTimeStep, std::function<void()> pfnFunctionToExecute, bool bToBeExecutedOnce)
{
	if( !m_bWasTimeSet )
	{
		m_fTimerAmount = fDelay;
		m_bWasTimeSet = true;
	}
	
	if ( m_fTimerAmount > 0.0f )
	{
		m_fTimerAmount -= fTimeStep;
	}

	if( m_fTimerAmount <= 0.0f && bToBeExecutedOnce)
	{
		pfnFunctionToExecute();
		bToBeExecutedOnce = false;		
	}
}

const bool CTimerHelper::GetTimerCompleted()
{
	return m_bTimerCompleted;
}

void CTimerHelper::ResetTimer()
{
	m_fTimerAmount		= m_fTimeOnConstructor;
	m_bWasTimeSet		= false;
	m_bTimerCompleted	= false;
}

