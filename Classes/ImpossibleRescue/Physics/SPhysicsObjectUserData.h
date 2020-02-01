//Name of struct:	SPhysicsObjectUserData
//Main author:		Toyan Green
//Summary:			This struct is responsible for setting user data on physics objects created in code
//					in the game.

#ifndef _SPHYSICSOBJECTUSERDATA_H_
#define _SPHYSICSOBJECTUSERDATA_H_

struct SPhysicsObjectUserData
{
	SPhysicsObjectUserData(const char* name);
	
	const char* m_sName;
};

#endif