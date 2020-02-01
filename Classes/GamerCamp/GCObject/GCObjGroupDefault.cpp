////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GamerCamp/GCObject/GCObjGroupDefault.h"

#include "GamerCamp/GCObject/GCObjectManager.h"


//////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////
CGCObjGroupDefault::CGCObjGroupDefault()
{
}



//////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupDefault::~CGCObjGroupDefault()
{}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupDefault::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return true;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupDefault::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupDefault );
}