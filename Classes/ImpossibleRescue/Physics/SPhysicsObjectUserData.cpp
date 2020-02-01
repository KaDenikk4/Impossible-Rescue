//Name of struct:	SPhysicsObjectUserData
//Main author:		Toyan Green
//Summary:			This struct is responsible for setting user data on physics objects created in code
//					in the game.

#ifndef _SPHYSICSOBJECTUSERDATA_H_
#include "SPhysicsObjectUserData.h"
#endif

SPhysicsObjectUserData::SPhysicsObjectUserData( const char* name )
{
	m_sName = name;
}
