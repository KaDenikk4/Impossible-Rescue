#include "CMovingPlatform3m.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"

USING_NS_CC;

// IN_CPP_CREATION_PARAMS_DECLARE( CMovingPlatform3m, "TexturePacker/Sprites/Platforms/PlatMoving3m/PlatMoving3m.plist", "PlatMoving3m", b2_staticBody, true );

static const char* k_pszXmlAttr_TargetPositionX		= "x";
static const char* k_pszXmlAttr_TargetPositionY		= "y";
static const char* k_pszXmlAttr_MovementDuration	= "MovingPlatformMovementDuration";
static const char* k_pszXmlAttr_MovementCoolDown	= "MovingPlatformMovementCoolDown";
static const char* k_pszXmlAttr_HackingId			= "HackingID";

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CMovingPlatform3m );

CMovingPlatform3m::CMovingPlatform3m()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CMovingPlatform3m ) )
	, m_ePlatformMovementState( EMovingPlatformStates::Unknown )
	, m_v2StartPosition( cocos2d::Vec2() )
	, m_v2TargetPosition( cocos2d::Vec2() )
	, m_v2CurrentStartPosition( cocos2d::Vec2() )
	, m_v2CurrentTargetPosition( cocos2d::Vec2() )
	, m_fMovementDuration( 1.0f )
	, m_fMovementCoolDown( 0.0f )
	, m_fMovementCoolDownRemaining( 0.0f )
	, m_psfxMoving(nullptr)
	, m_pLevelTransitionEventHandler(nullptr)
	, m_pPlayerHasDiedEventHandler(nullptr)
	, m_aorHackedEventHandler(nullptr)
	, m_bIsEnabled(false)
{
	m_psfxMoving = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::MovingPlatform);
	// Subscribe to level transition events
	m_pLevelTransitionEventHandler = AppDelegate::GetEventMediator()->VSubscribeToLevelTransitionEvents(*this);
	// Subscribe to player has died events
	m_pPlayerHasDiedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToPlayerHasDiedEvents(*this);
	//Subscribe to station was hacked events
	m_aorHackedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToStationHackedEvents(*this);
}

CMovingPlatform3m::~CMovingPlatform3m( )
{
	m_pLevelTransitionEventHandler.Release();
	m_pPlayerHasDiedEventHandler.Release();
	m_aorHackedEventHandler.Release();
	
	m_psfxMoving->VStop();

	if (m_psfxMoving)
	{
		delete m_psfxMoving;
		m_psfxMoving = nullptr;
	}
}

void CMovingPlatform3m::VOnResourceAcquire( void )
{
	// IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CMovingPlatform3m );
	CGCObjSpritePhysics::VOnResourceAcquire();
}


// OnReset is called for each CGCObject derived class when CGCObjectManager is reset. (Note from GCFramework)
void CMovingPlatform3m::VOnReset()
{
	//Reset platform resets the position so need to be called before the base method is called
	ResetPlatform();

	// Check if the player transition data contains the hacking ID for this platform
	// If the ID is found set the platform to be enabled, otherwise set it to be disabled

	// If the moving platform has no hacking ID, it is auto enabled by default
	if (strcmp(m_pszHackingID, "") == 0 ||AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->CheckHackingIDHasBeenObtained(m_pszHackingID))
	{
		m_bIsEnabled = true;
	}
	else
	{
		m_bIsEnabled = false;
	}

	CGCObjSpritePhysics::VOnReset();
}

// Check if there is valid editor data
bool CMovingPlatform3m::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	if (nullptr == rxmlElement)
	{
		return false;
	}

	const tinyxml2::XMLAttribute* pTargetPositionX = rxmlElement->FirstChildElement( )->FindAttribute(k_pszXmlAttr_TargetPositionX);
	const tinyxml2::XMLAttribute* pTargetPositionY = rxmlElement->FirstChildElement( )->FindAttribute(k_pszXmlAttr_TargetPositionY);
	const tinyxml2::XMLAttribute* pMovementDuration = rxmlElement->FindAttribute(k_pszXmlAttr_MovementDuration);
	const tinyxml2::XMLAttribute* pMovementCoolDown = rxmlElement->FindAttribute(k_pszXmlAttr_MovementCoolDown);
	const tinyxml2::XMLAttribute* pHackingId = rxmlElement->FindAttribute(k_pszXmlAttr_HackingId);

	return((nullptr != pTargetPositionX)
		&& (nullptr != pTargetPositionY)
		&& (nullptr != pMovementDuration)
		&& (nullptr != pMovementCoolDown)
		&& (nullptr != pHackingId)
		);
}

void CMovingPlatform3m::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	SetStartPosition( GetResetPosition( ) );
	SetTargetPosition( Vec2(rxmlElement->FirstChildElement()->IntAttribute(k_pszXmlAttr_TargetPositionX), 1080.0f - rxmlElement->FirstChildElement()->IntAttribute(k_pszXmlAttr_TargetPositionY) ) );

	SetMovementDuration( rxmlElement->FloatAttribute(k_pszXmlAttr_MovementDuration) );
	SetMovementCoolDown( rxmlElement->FloatAttribute(k_pszXmlAttr_MovementCoolDown) );
	m_pszHackingID = rxmlElement->Attribute(k_pszXmlAttr_HackingId);

	ResetPlatform();
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CMovingPlatform3m::VOnUpdate( float fTimeStep )
{
	CGCObjSpritePhysics::VOnUpdate( fTimeStep );

	if( m_bIsEnabled )
	{
		SetPlatformMovementState();

		if(EMovingPlatformStates::NotMoving == m_ePlatformMovementState)
		{
			m_fMovementCoolDownRemaining -= fTimeStep;
		}
	}
}

// Set whether or not the platform can move
void CMovingPlatform3m::SetPlatformMovementState()
{
	switch( m_ePlatformMovementState )
	{
	case EMovingPlatformStates::NotMoving:
		// If the platform is not currently moving and it is time to move, the platform should start moving
		if( 0.0f >= m_fMovementCoolDownRemaining )
		{
			m_ePlatformMovementState = EMovingPlatformStates::Moving;
			// Reset the cooldown timer 
			m_fMovementCoolDownRemaining = m_fMovementCoolDown;

			m_psfxMoving->VPlay(0.2f, true );

			// Set velocity
			// velocity  = ((final position) - (initial position)) / time

			const Vec2 v2Velocity = CalculatePositionVectorDifferenceInPhysicsWorldSpace() / m_fMovementDuration;

			SetVelocity(v2Velocity);			
		}
		break;
	case EMovingPlatformStates::Moving:
		// If the platform is currently moving and has reached its target position, the platform should stop moving
		if( HasPlatformReachedItsTargetPosition() )
		{
			SetVelocity(Vec2::ZERO);
			
			m_ePlatformMovementState = EMovingPlatformStates::NotMoving;
			// Set the platforms new target position
			SetTargetPosition();

			m_psfxMoving->VStop();
		}
		break;
	default:
		CCASSERT( false, "Moving platform is in an invalid state" );
		break;
	}
}

// Set the new target position based on where the platform has come from
void CMovingPlatform3m::SetTargetPosition()
{
	// Swap the start and target positions
	if( m_v2CurrentStartPosition == m_v2StartPosition )
	{
		m_v2CurrentStartPosition = m_v2TargetPosition;
		m_v2CurrentTargetPosition = m_v2StartPosition;
	}
	else if( m_v2CurrentStartPosition == m_v2TargetPosition )
	{
		m_v2CurrentStartPosition = m_v2StartPosition;
		m_v2CurrentTargetPosition = m_v2TargetPosition;
	}
}

// Check if the platform has reached its target position
bool CMovingPlatform3m::HasPlatformReachedItsTargetPosition() const
{
	const b2Transform kb2tCurrentPhysicsTransform = GetPhysicsTransform();

	return cocos2d::Vec2( kb2tCurrentPhysicsTransform.p.x, kb2tCurrentPhysicsTransform.p.y ).fuzzyEquals( IGCGameLayer::B2dPixelsToWorld( m_v2CurrentTargetPosition ), m_fPlatformPositionVariance );
}

// Calculate the vector difference between the current start position and target position
cocos2d::Vec2& CMovingPlatform3m::CalculatePositionVectorDifferenceInPhysicsWorldSpace() const
{
	// Current start position in physics world space
	const cocos2d::Vec2 kv2CurrentStartPositionInB2dWorldSpace = IGCGameLayer::B2dPixelsToWorld( m_v2CurrentStartPosition );
	// Current target position in physics world space
	const cocos2d::Vec2 kv2CurrentTargetPositionInB2dWorldSpace = IGCGameLayer::B2dPixelsToWorld( m_v2CurrentTargetPosition );

	return kv2CurrentTargetPositionInB2dWorldSpace - kv2CurrentStartPositionInB2dWorldSpace;
}

// Reinitialize the platform
void CMovingPlatform3m::ResetPlatform()
{
	m_ePlatformMovementState = EMovingPlatformStates::NotMoving;
	m_fMovementCoolDownRemaining = m_fMovementCoolDown;
	m_v2CurrentStartPosition = m_v2StartPosition;
	m_v2CurrentTargetPosition = m_v2TargetPosition;

	//Get the vector difference between the current start position and target position
	const cocos2d::Vec2 kv2VectorDifferenceInPhysicsWorldSpace = CalculatePositionVectorDifferenceInPhysicsWorldSpace();

	// Movement delta = (Vector difference / time to move) * delta time
	const cocos2d::Vec2 kv2MovementDelta = (kv2VectorDifferenceInPhysicsWorldSpace / m_fMovementDuration) * AppDelegate::gks_fTimeStep;

	// Variance for platform positions being "equal" is set to how far the platform could move in a single frame
	m_fPlatformPositionVariance = kv2MovementDelta.length();
}

// Set the starting position for the platform to move from
void CMovingPlatform3m::SetStartPosition( const cocos2d::Vec2& v2StartPosition )
{
	m_v2StartPosition = v2StartPosition;
}

// Set the ending position for the platform to move to
void CMovingPlatform3m::SetTargetPosition( const cocos2d::Vec2& v2TargetPosition )
{
	m_v2TargetPosition = v2TargetPosition;
}

// Set the time (in seconds) for the platform to move from one position to another
void CMovingPlatform3m::SetMovementDuration( f32 fMovementDuration )
{
	m_fMovementDuration = fMovementDuration;
}

// Set the time (in seconds) before the platform will move to its next position
void CMovingPlatform3m::SetMovementCoolDown( f32 fMovementCoolDown )
{
	m_fMovementCoolDown = fMovementCoolDown;
}

void CMovingPlatform3m::VOnEventReceived( CLevelTransitionEvent eventArgs )
{
	m_psfxMoving->VStop();
}

void CMovingPlatform3m::VOnEventReceived( CPlayerHasDiedEvent eventArgs )
{
	m_psfxMoving->VStop();
}

void CMovingPlatform3m::VOnEventReceived(CStationHackedEvent eventArgs)
{
	if (strcmp("", eventArgs.GetHackID()) == 0)
	{
		return;
	}

	// If the platform receives a station hacked event with an Id that matches its own hacking ID, set the platform to enabled
	if (strcmp(m_pszHackingID, eventArgs.GetHackID()) == 0)
	{
		m_bIsEnabled = true;
	}
}