#include "CMovingPlatform.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

CMovingPlatform::CMovingPlatform( GCTypeID idDerivedType )
	: CGCObjSpritePhysics(idDerivedType)
	, m_ePlatformMovementState(EMovingPlatformState::Unknown)
	, m_v2StartPosition( cocos2d::Vec2() )
	, m_v2TargetPosition(cocos2d::Vec2())
	, m_v2CurrentStartPosition(cocos2d::Vec2())
	, m_v2CurrentTargetPosition(cocos2d::Vec2())
	, m_fMovementDuration(0.0f)
	, m_fMovementCoolDown(0.0f)
	, m_fMovementCoolDownRemaining(0.0f)
{
}

CMovingPlatform::~CMovingPlatform( )
{
}

// OnReset is called for each CGCObject derived class when CGCObjectManager is reset. (Note from GCFramework)
void CMovingPlatform::VOnReset( )
{
	//Reset platform resets the position so need to be called before the base method is called
	ResetPlatform();
	
	CGCObjSpritePhysics::VOnReset();	
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CMovingPlatform::VOnUpdate( float fTimeStep )
{
	CGCObjSpritePhysics::VOnUpdate(fTimeStep);

	SetPlatformMovementState();
	
	HandleMovement( fTimeStep );
}

// Execute platform moving logic
void CMovingPlatform::HandleMovement(float fTimeStep)
{
	switch (m_ePlatformMovementState)
	{
	case EMovingPlatformState::NotMoving:
		// If the platform isn't moving, count down until it can
		m_fMovementCoolDownRemaining -= fTimeStep;
		break;

	case EMovingPlatformState::Moving:
		// If the platform is moving, move the platform
		MovePlatform(fTimeStep);
		break;

	default:
		CCASSERT(false, "Moving platform is in an invalid state");
	}
}

// Set whether or not the platform can move
void CMovingPlatform::SetPlatformMovementState()
{
	switch( m_ePlatformMovementState )
	{
		case EMovingPlatformState::NotMoving:
			// If the platform is not currently moving and it is time to move, the platform should start moving
			if( 0.0f >= m_fMovementCoolDownRemaining )
			{
				m_ePlatformMovementState = EMovingPlatformState::Moving;
				// Reset the cooldown timer 
				m_fMovementCoolDownRemaining = m_fMovementCoolDown;
			}
		break;
		case EMovingPlatformState::Moving:
			// If the platform is currently moving and has reached its target position, the platform should stop moving
			if( HasPlatformReachedItsTargetPosition( ) )
			{
				m_ePlatformMovementState = EMovingPlatformState::NotMoving;
				// Set the platforms new target position
				SetTargetPosition();
			}
			break;
		default:
			CCASSERT(false, "Moving platform is in an invalid state");
		break;
	}
}

// Set the new target position based on where the platform has come from
void CMovingPlatform::SetTargetPosition( )
{
	// Swap the start and target positions
	if( m_v2CurrentStartPosition == m_v2StartPosition)
	{
		m_v2CurrentStartPosition = m_v2TargetPosition;
		m_v2CurrentTargetPosition = m_v2StartPosition;
	}
	else if ( m_v2CurrentStartPosition == m_v2TargetPosition )
	{
		m_v2CurrentStartPosition = m_v2StartPosition;
		m_v2CurrentTargetPosition = m_v2TargetPosition;
	}
}

// Check if the platform has reached its target position
bool CMovingPlatform::HasPlatformReachedItsTargetPosition( ) const
{
	const b2Transform kb2tCurrentPhysicsTransform = GetPhysicsTransform();

	return cocos2d::Vec2(kb2tCurrentPhysicsTransform.p.x, kb2tCurrentPhysicsTransform.p.y).fuzzyEquals(IGCGameLayer::B2dPixelsToWorld(m_v2CurrentTargetPosition), m_fPlatformPositionVariance );
}

// Update the physics transform to move the platform
void CMovingPlatform::MovePlatform( float fTimeStep )
{
	//Get the vector difference between the current start position and target position
	const cocos2d::Vec2 kv2VectorDifferenceInPhysicsWorldSpace = CalculatePositionVectorDifferenceInPhysicsWorldSpace( );

	// Movement delta = (Vector difference / time to move) * delta time
	const cocos2d::Vec2 kv2MovementDelta = ( kv2VectorDifferenceInPhysicsWorldSpace / m_fMovementDuration ) * fTimeStep;

	//Get current physics transform
	const b2Transform kb2tCurrentPhysicsTransform = GetPhysicsTransform( );

	// Set physics transform position to (current position + movement delta)
	SetPhysicsTransform( cocos2d::Vec2( kb2tCurrentPhysicsTransform.p.x, kb2tCurrentPhysicsTransform.p.y )
	                     + kv2MovementDelta, kb2tCurrentPhysicsTransform.q.GetAngle( ) );
}

// Calculate the vector difference between the current start position and target position
cocos2d::Vec2& CMovingPlatform::CalculatePositionVectorDifferenceInPhysicsWorldSpace() const
{
	// Current start position in physics world space
	const cocos2d::Vec2 kv2CurrentStartPositionInB2dWorldSpace = IGCGameLayer::B2dPixelsToWorld(m_v2CurrentStartPosition);
	// Current target position in physics world space
	const cocos2d::Vec2 kv2CurrentTargetPositionInB2dWorldSpace = IGCGameLayer::B2dPixelsToWorld(m_v2CurrentTargetPosition);

	return kv2CurrentTargetPositionInB2dWorldSpace - kv2CurrentStartPositionInB2dWorldSpace;
}

// Reinitialize the platform
void CMovingPlatform::ResetPlatform()
{
	SetResetPosition(m_v2StartPosition);
	m_ePlatformMovementState     = EMovingPlatformState::NotMoving;
	m_fMovementCoolDownRemaining = m_fMovementCoolDown;
	m_v2CurrentStartPosition     = m_v2StartPosition;
	m_v2CurrentTargetPosition    = m_v2TargetPosition;

	//Get the vector difference between the current start position and target position
	const cocos2d::Vec2 kv2VectorDifferenceInPhysicsWorldSpace = CalculatePositionVectorDifferenceInPhysicsWorldSpace();

	// Movement delta = (Vector difference / time to move) * delta time
	const cocos2d::Vec2 kv2MovementDelta = (kv2VectorDifferenceInPhysicsWorldSpace / m_fMovementDuration) * AppDelegate::gks_fTimeStep;

	// Variance for platform positions being "equal" is set to how far the platform could move in a single frame
	m_fPlatformPositionVariance = kv2MovementDelta.length( );
}

// Set the starting position for the platform to move from
void CMovingPlatform::SetStartPosition( const cocos2d::Vec2& v2StartPosition )
{
	m_v2StartPosition = v2StartPosition;
}

// Set the ending position for the platform to move to
void CMovingPlatform::SetTargetPosition(const cocos2d::Vec2& v2TargetPosition )
{
	m_v2TargetPosition = v2TargetPosition;
}

// Set the time (in seconds) for the platform to move from one position to another
void CMovingPlatform::SetMovementDuration( f32 fMovementDuration )
{
	m_fMovementDuration = fMovementDuration;
}

// Set the time (in seconds) before the platform will move to its next position
void CMovingPlatform::SetMovementCoolDown( f32 fMovementCoolDown )
{
	m_fMovementCoolDown = fMovementCoolDown;
}
