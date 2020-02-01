#include "CActionOnRelease.h"

CActionOnRelease::CActionOnRelease( std::function<void()> fnReleaseFunction )
	: m_fnReleaseFunction(fnReleaseFunction)
{
}

// Method to execute release behaviour
void CActionOnRelease::Release( )
{
	if (m_fnReleaseFunction)
	{
		m_fnReleaseFunction();
	}
	
	m_fnReleaseFunction = nullptr;
}
