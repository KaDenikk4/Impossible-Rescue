#include "CTemplateLevel.h"



TemplateLevel::TemplateLevel()
	: CBaseLevel(GetGCTypeIDOf(TemplateLevel))
{
}


TemplateLevel::~TemplateLevel()
{
}

void TemplateLevel::HandleCollisions(void)
{
	CBaseLevel::HandleCollisions();
}

void TemplateLevel::onEnter()
{
	CBaseLevel::onEnter();
}

void TemplateLevel::VOnCreate(void)
{
	CBaseLevel::VOnCreate();
}

void TemplateLevel::VOnUpdate(f32 fTimeStep)
{
	CBaseLevel::VOnUpdate(fTimeStep);
}

void TemplateLevel::VOnDestroy(void)
{
	CBaseLevel::VOnDestroy();
}

void TemplateLevel::BeginContact(b2Contact* pB2Contact)
{
	CBaseLevel::BeginContact(pB2Contact);
}

void TemplateLevel::EndContact(b2Contact* pB2Contact)
{
	CBaseLevel::EndContact(pB2Contact);
}

void TemplateLevel::PreSolve(b2Contact* pB2Contact, const b2Manifold* pOldManifold)
{
	CBaseLevel::PreSolve(pB2Contact, pOldManifold);
}

void TemplateLevel::PostSolve(b2Contact* pB2Contact, const b2ContactImpulse* pImpulse)
{
	CBaseLevel::PostSolve(pB2Contact, pImpulse);
}
