// Name of class:	CShadow
// Main author:		Tomasz Snopek
// Summary:			This class is responsible for S.H.A.D.O.W. - a drone following the player
//					in the game.
// Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnResourceRelease, FollowPlayer,
//					AddShadowLabel, RemoveLabels, FloatLerp
// ToDo:				Template FloatLerp function, move Label functions to it's own utility class.

#include "CShadow.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "ImpossibleRescue/Player/CPlayer.h"
#include <math/MathUtil.h>
#include <complex>


CShadow::CShadow()
	: CGCObjSpritePhysics	( GetGCTypeIDOf( CShadow ) )
	, m_v2OffsetFromPlayer	( 0.0f, 0.0f )
	, m_v2SpritePosition	( 0.0f, 0.0f )
	, m_pcPlaceholderShadow	( nullptr )
{
	m_v2OffsetFromPlayer = cocos2d::Vec2( 80.0f, 0.0f );
}


CShadow::~CShadow()
{
}


//Helper macro for acquiring assets and attaching box2d base fixture
IN_CPP_CREATION_PARAMS_DECLARE( CShadow, "TexturePacker/Sprites/SHADOW/SHADOW.plist", "SHADOW", b2_kinematicBody, true);

//Summary:		Virtual function to be called exactly once for each CGCObject derived class instance
//				registered with CGCObjectManager as soon as the TGB level file has stopped
//				loading- it is an "explicit constructor". (Note from GCFramework)
//				
void CShadow::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CShadow );

	CGCObjSpritePhysics::VOnResourceAcquire();

	const char* pszAnim_Shadow = "Hovering";

	// Animation loop
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist( GetFactoryCreationParams()->strPlistFile );
	RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( dicPList, pszAnim_Shadow ) ) );

}


//Summary:	Called for each CGCObject derived class when CGCObjectManager is reset.	
//			(Note from GCFramework)
//			
void CShadow::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();

	if (GetPhysicsBody())
	{
		m_v2SpritePosition = GetSpritePosition();
		GetPhysicsBody()->SetLinearVelocity( b2Vec2( 0.0f, 0.0f ) );
		GetPhysicsBody()->SetTransform( IGCGameLayer::B2dPixelsToWorld( b2Vec2( m_v2SpritePosition.x, m_v2SpritePosition.y ) ), 0.0f );
		GetPhysicsBody()->SetFixedRotation( true );
	}
}


//Summary:		Called for each CGCObject derived class when CGCObjectManager is 
//				updated in t2dSCeneGraph onProcessTick() (Note from GCFramework)
//Parameters:	fTimeStep - float indicating timestep in main gameloop
//				
void CShadow::VOnUpdate(f32 fTimeStep)
{

}


//Summary:		Called immediately before the managing object group releases its own assets
//				(Note from GCFramework)
//				
void CShadow::VOnResourceRelease()
{
		CGCObjSpritePhysics::VOnResourceRelease();
}


//Summary:		The functionality for SHADOW to follow the live player
//Parameters:	rcPlayer	- for live player reference,
//				fTimeStep	- for update TimeStep value.
//ToDo:			SHADOW should only follow at certain distance, so it won't move when player passes by it
//
void CShadow::FollowPlayer(CPlayer& rcPlayer, float fTimeStep)
{
	//ToDo: Fix commented code - doesn't work with all of the player states
	//if (	std::abs(GetSpritePosition().x - rcPlayer.GetSpritePosition().x) > 90.0f
	//	||	std::abs(GetSpritePosition().y - rcPlayer.GetSpritePosition().y) > 1.0f)
	//{

	bool bIsPlayerFacingLeft = false;

	if(rcPlayer.GetVelocity().x >= 0.0f)
	{
		bIsPlayerFacingLeft = false;
	}
	else if(rcPlayer.GetVelocity().x < 0.0f)
	{
		bIsPlayerFacingLeft = true;
	}
	
		if (!bIsPlayerFacingLeft)
		{
			GetPhysicsBody()->SetTransform(
				IGCGameLayer::B2dPixelsToWorld( b2Vec2(
					FloatLerp( GetSpritePosition().x, rcPlayer.GetSpritePosition().x - m_v2OffsetFromPlayer.x, fTimeStep ),
					FloatLerp( GetSpritePosition().y, rcPlayer.GetSpritePosition().y - m_v2OffsetFromPlayer.y, fTimeStep ) ) ),
				0.0f
			);

			SetFlippedX( false );

		}
		else
		{
			GetPhysicsBody()->SetTransform(
				IGCGameLayer::B2dPixelsToWorld( b2Vec2(
					FloatLerp( GetSpritePosition().x, rcPlayer.GetSpritePosition().x + m_v2OffsetFromPlayer.x, fTimeStep),
					FloatLerp( GetSpritePosition().y, rcPlayer.GetSpritePosition().y + m_v2OffsetFromPlayer.y, fTimeStep ) ) ),
				0.0f
			);
			SetFlippedX( true );
		}
	//}
}


//Summary:		Function responsible for cleaning up UI cues created by S.H.A.D.O.W
//Parameters:	pcCurrentLayer* - pointer to current scene's layer, required for
//								  adding the labels
//ToDo: Add label creation logic
//
void CShadow::AddShadowLabel(IGCGameLayer* pcCurrentLayer)
{
	
}


//Summary:		Function responsible for cleaning up UI cues created by S.H.A.D.O.W.
//Parameters:	pcCurrentLayer* - pointer to current scene's layer, required for
//								  removal of labels
//ToDo: Add label removal logic here
//
void CShadow::RemoveLabels(IGCGameLayer* pcCurrentLayer)
{
	
}


//Summary:		Lerp function - could be static and/or template as a helper function
//Parameters:	rfStart - reference to value at the start of interpolation
//				rfEnd	- reference to value at the end of interpolation
//				rfAlpha - reference to percentage of the interpolation completion
float CShadow::FloatLerp( const float& rfStart, const float& rfEnd, const float& rfAlpha )
{
	return rfStart + rfAlpha * ( rfEnd - rfStart );
}

