// Name of class:	CShadow
// Main author:		Tomasz Snopek
// Summary:			This class is responsible for S.H.A.D.O.W. - a drone following the player
//					in the game.
// Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnResourceRelease, FollowPlayer,
//					AddShadowLabel, RemoveLabels, FloatLerp
// ToDo:				Template FloatLerp function, move Label functions to it's own utility class.

#ifndef	SHADOW_H
#define SHADOW_H

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif
#include "2d/CCLabel.h"

class IGCGameLayer;
class CPlayer;

class CShadow :
	public CGCObjSpritePhysics
{
public:
	CShadow();
	virtual ~CShadow();

	// This will be called exactly once for each CGCObject derived class instance 
	// registered with CGCObjectManager as soon as the TGB level file has stopped 
	// loading- it is an "explicit constructor".
	// (Note from GCFramework)
	virtual void VOnResourceAcquire() override;

	// OnReset is called for each CGCObject derived class when CGCObjectManager is 
	// reset
	// (Note from GCFramework)
	virtual void VOnReset() override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick()
	// (Note from GCFramework)
	virtual void VOnUpdate( f32 fTimeStep ) override;

	// Called immediately before the managing object group releases its own assets
	// (Note from GCFramework)
	virtual void VOnResourceRelease() override;

	//Function for SHADOW to follow the live player during runtime
	void FollowPlayer	( CPlayer& rcPlayer, float fTimeStep );

	//ToDo: Add labels for UI hints
	//Functions which will need to handle displaying UI cues according to the design documents (could be templates in the future)
	void AddShadowLabel	( IGCGameLayer* pcCurrentLayer );
	void RemoveLabels	( IGCGameLayer* pcCurrentLayer );
	
private:
	cocos2d::Vec2	m_v2OffsetFromPlayer;
	cocos2d::Vec2	m_v2SpritePosition;
	cocos2d::Label* m_pcPlaceholderShadow;

	
	//Locally made float interpolation function, to be improved: template this function.
	float FloatLerp( const float& rfStart, const float& rfEnd, const float& rfAlpha );
};

#endif //endif SHADOW_H