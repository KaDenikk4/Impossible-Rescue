//Name of class:	CPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is the base class for all player movement states
//					in the game.
//Functions:		VInitialise, VEnter, VUpdate, VHandleInput

#ifndef	_CPLAYERMOVEMENTSTATE_H_
#define	_CPLAYERMOVEMENTSTATE_H_

#include "../EPlayerActions.h"
#include "../CPlayer.h"
#include "GamerCamp/GameController/GCController.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Environment/Door/CDoor.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

class CPlayer;

class CPlayerMovementState
{
public:
	//ToDo Add code comments
	virtual ~CPlayerMovementState();
	// Initialise the movement state.
	virtual void VInitialise();
	// State beginning transition. Called once when current player movement state is set to this state.
	virtual void VEnter(CPlayer& player);
	// State ending transition. Called once when current player movement state is set to another state.
	virtual void VExit(CPlayer& player)
	{
		SetControlForceDirectionX( 0.0f );
		SetControlForceDirectionY( 0.0f );
	};
	// Update loop. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VUpdate(CPlayer& player);
	// Handle player input. Called from CPlayer VOnUpdate.
	virtual CPlayerMovementState* VHandleInput(CPlayer& player, TGCController<EPlayerActions>& input) { return nullptr; }

protected:

	// Get the sprite animation name
	virtual const char* VGetAnimationName() const = 0;
	// Get the sprite physics shape
	virtual const char* VGetPhysicsShapeName() const = 0;
	// Get whether or not the animation is looping
	virtual bool VGetIsAnimationLooping();
	//Get X Axis Deadzone value
	float GetXAxisDeadzone() const;
	Vec2 GetControlForceDirection() const;
	void SetControlForceDirectionX(float fControlForceDirectionX);
	void SetControlForceDirectionY(float fControlForceDirectionY);
	void SetStateIsTransitioning(bool bIsTransitioning);
	bool GetStateIsTransitioning() const;
	void PlayLandedSound() const;
	void SetAnimationSpeed(float fAnimationSpeed) const;
	float GetRunningThreshold() const;
	float GetMaxGroundedVelocityX() const;	
	
private:

	void SetAnimation(CPlayer& rcPlayer, const char* pszAnimationName);
	void SetPhysicsShape(CPlayer& rcPlayer, const char* pszPhysicsShapeName);
		
	void CleanupAnimation();
	void CleanupAnimationSpeedAction();

	// Set the sprite animation name for level transitioning
	void SetPlayerAnimationName(const char* psAnimationName);
	// Set the physics shape name for level transitioning
	void SetPlayerPhysicsShapeName(const char* psPhysicsShapeName);
	
	const float mk_fXAxisDeadzone = 0.20f;
	const float mk_fRunningThreshold = 0.70f;
	// THIS IS VERY BAD. HAD TO LOG THE PLAYER VELOCITY AS ALL VARIABLES TO CALCULATE MAX X VELOCITY COULD NOT BE FOUND (FRICTION etc.)
	const float mk_fMaxXVelocity = 47.0f;

	Vec2			m_v2ControlForceDirection   = Vec2::ZERO;
	bool			m_bIsTransitioning          = false;
	ISoundEffect*	m_psfxPlayerLanded          = nullptr;
	Speed*			m_pcAnimationSpeedAction    = nullptr;
	float			m_fPlayerNewAnimationWidth  = 0;
	float			m_fPlayerNewAnimationHeight = 0;
	Animation*		m_pNewAnimation				= nullptr;
};

#endif
