//Name of class:	CActionOnRelease
//Main author:		Toyan Green
//Summary:			This class is stores a function to remove an object from its event subscriber list when it is released
//Functions:		Release

#ifndef	_CACTIONONRELEASE_H_
#define	_CACTIONONRELEASE_H_
#include <functional>

class CActionOnRelease
{
public:
	CActionOnRelease() = delete;
	CActionOnRelease(std::function<void()> fnReleaseFunction);

	// Method to execute release behaviour
	void Release();

private:
	std::function< void()> m_fnReleaseFunction;
};

#endif
