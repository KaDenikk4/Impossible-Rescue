#ifndef _BASELEVEL_
#define _BASELEVEL_

#include "ImpossibleRescue/Levels/CBaseLevel.h"



class TemplateLevel
	: public CBaseLevel
{
public:
	TemplateLevel();
	~TemplateLevel();

	// called from VOnUpdate
	virtual void HandleCollisions(void);

	//////////////////////////////////////////////////////////////////////////
	// CCNode interface...
	virtual void onEnter();
	// CCNode interface...
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// IGCGameLayer interface

	virtual	void VOnCreate(void);
	virtual void VOnUpdate(f32 fTimeStep);
	virtual	void VOnDestroy(void);

	// IGCGameLayer interface
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are

	virtual void BeginContact(b2Contact* pB2Contact);
	virtual void EndContact(b2Contact* pB2Contact);
	virtual void PreSolve(b2Contact* pB2Contact, const b2Manifold* pOldManifold);
	virtual void PostSolve(b2Contact* pB2Contact, const b2ContactImpulse* pImpulse);

	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////// 
	// reset handling
};

#endif //_BASELEVEL_
