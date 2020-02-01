#ifndef _CMOVINGPLATFORM3M_H_
#define _CMOVINGPLATFORM3M_H_

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

#include "ImpossibleRescue/Audio/ISoundEffect.h"
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Events/EventTypes/CLevelTransitionEvent.h"
#include "ImpossibleRescue/Events/EventTypes/CPlayerHasDiedEvent.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"

enum class EMovingPlatformStates;

class CMovingPlatform3m
	: public CGCObjSpritePhysics
	, public ITReceiveEvents<CLevelTransitionEvent>
	, public ITReceiveEvents<CPlayerHasDiedEvent>
	, ITReceiveEvents< CStationHackedEvent >
{
public:
	CMovingPlatform3m();
	~CMovingPlatform3m();
	
	GCFACTORY_DECLARE_CREATABLECLASS( CMovingPlatform3m );

	virtual void VOnResourceAcquire( void ) override;
	virtual void VOnReset() override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	
	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnUpdate( float fTimeStep ) override;

	// Set whether or not the platform can move
	void SetPlatformMovementState();
	// Set the new target position based on where the platform has come from
	void SetTargetPosition();
	// Check if the platform has reached its target position
	bool HasPlatformReachedItsTargetPosition() const;
	// Calculate the vector difference between the current start position and target position
	cocos2d::Vec2& CalculatePositionVectorDifferenceInPhysicsWorldSpace() const;
	// Reinitialize the platform
	void ResetPlatform();
	// Set the starting position for the platform to move from
	void SetStartPosition( const cocos2d::Vec2& v2StartPosition ); // ToDo pass all values like this in by const reference
	// Set the ending position for the platform to move to
	void SetTargetPosition( const cocos2d::Vec2& v2TargetPosition );
	// Set the time (in seconds) for the platform to move from one position to another
	void SetMovementDuration( f32 fMovementDuration );
	// Set the time (in seconds) before the platform will move to its next position
	void SetMovementCoolDown( f32 fMovementCoolDown );

	void VOnEventReceived( CLevelTransitionEvent eventArgs ) override;
	void VOnEventReceived( CPlayerHasDiedEvent eventArgs ) override;
	void VOnEventReceived( CStationHackedEvent eventArgs ) override;
	
private:
	// Enum to check if the platform is moving
	EMovingPlatformStates		m_ePlatformMovementState;
	// Starting position for the platform to move from
	cocos2d::Vec2				m_v2StartPosition;
	// Ending position for the platform to move to
	cocos2d::Vec2				m_v2TargetPosition;
	// Current start position of the moving platform
	cocos2d::Vec2				m_v2CurrentStartPosition;
	// Current target position for the platform to move to
	cocos2d::Vec2				m_v2CurrentTargetPosition;
	// Time (in seconds) for the platform to move from one position to another
	f32							m_fMovementDuration;
	// Time (in seconds) before the platform will move to its next position
	f32							m_fMovementCoolDown;
	// Time remaining (in seconds) before the platform will move to its next position
	f32							m_fMovementCoolDownRemaining;
	// Vector variance length used for calculating if platform positions are "equal"
	float						m_fPlatformPositionVariance;

	ISoundEffect*				m_psfxMoving;
	CActionOnRelease			m_pLevelTransitionEventHandler;
	CActionOnRelease			m_pPlayerHasDiedEventHandler;
	CActionOnRelease			m_aorHackedEventHandler;
	bool						m_bIsEnabled;
	const char*					m_pszHackingID;
};

enum class EMovingPlatformStates
{
	//ToDo remove the prefix
	Unknown = 0,
	NotMoving = 1,
	Moving = 2,
};


#endif // _CMOVINGPLATFORM3M_H_