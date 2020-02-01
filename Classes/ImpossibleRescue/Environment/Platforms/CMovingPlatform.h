//Name of class:	CMovingPlatform
//Main author:		Toyan Green
//Summary:			This class is the base class for all moving platforms
//					in the game.
//Functions:		VOnReset, VOnUpdate, HandleMovement, SetPlatformMovementState, SetTargetPosition,
//					HasPlatformReachedItsTargetPosition, CalculatePositionVectorDifferenceInPhysicsWorldSpace,
//					ResetPlatform, SetStartPosition, SetTargetPosition, SetMovementDuration, SetMovementCoolDown

#ifndef _CMOVINGPLATFORM_H_
#define _CMOVINGPLATFORM_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

enum class EMovingPlatformState;

class CMovingPlatform
	: public CGCObjSpritePhysics
{

protected:
	//CMovingPlatform() = delete;
	CMovingPlatform(GCTypeID idDerivedType);
	
public:

	virtual ~CMovingPlatform() override;
	// OnReset is called for each CGCObject derived class when CGCObjectManager is reset. (Note from GCFramework)
	virtual void VOnReset() override;
	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnUpdate( float fTimeStep ) override;

	// Execute platform moving logic
	void HandleMovement(float fTimeStep);
	// Set whether or not the platform can move
	void SetPlatformMovementState();
	// Set the new target position based on where the platform has come from
	void SetTargetPosition();
	// Check if the platform has reached its target position
	bool HasPlatformReachedItsTargetPosition() const;
	// Update the physics transform to move the platform
	void MovePlatform(float fTimeStep);
	// Calculate the vector difference between the current start position and target position
	cocos2d::Vec2& CalculatePositionVectorDifferenceInPhysicsWorldSpace() const;
	// Reinitialize the platform
	void ResetPlatform();
	// Set the starting position for the platform to move from
	void SetStartPosition( const cocos2d::Vec2& v2StartPosition ); // ToDo pass all values like this in by const reference
	// Set the ending position for the platform to move to
	void SetTargetPosition(const cocos2d::Vec2& v2TargetPosition );
	// Set the time (in seconds) for the platform to move from one position to another
	void SetMovementDuration( f32 fMovementDuration );
	// Set the time (in seconds) before the platform will move to its next position
	void SetMovementCoolDown( f32 fMovementCoolDown );

private:

	// Enum to check if the platform is moving
	EMovingPlatformState		m_ePlatformMovementState;
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
};

enum class EMovingPlatformState
{
	//ToDo remove the prefix
	Unknown = 0,	
	NotMoving = 1,	
	Moving = 2,	
};

#endif // _CMOVINGPLATFORM_H_