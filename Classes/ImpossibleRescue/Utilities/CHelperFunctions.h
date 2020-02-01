//Name of class:	CActionOnRelease
//Main author:		Toyan Green
//Summary:			This class is stores a function to remove an object from its event subscriber list when it is released
//Functions:		Contains (std::vector)

#ifndef	_CHELPERFUNCTIONS_H_
#define	_CHELPERFUNCTIONS_H_

#include <vector>

class CHelperFunctions
{
public:
	class CVectorFunctions
	{
	public:
		template <typename T>
		static bool Contains(std::vector<T>& vec, const T& value);
	};	
};

//Function implementation found here: https://stackoverflow.com/questions/6194797/what-is-a-c-container-with-a-contains-operation
template < typename T >
bool CHelperFunctions::CVectorFunctions::Contains(std::vector< T >& vec, const T& value)
{
	return std::find(vec.begin(), vec.end(), value) != vec.end();
}

#endif
