//Name of class:	CPlayer
//Summary:			Base class for the player. It contains main game controls and is the main
//					file to reference all player functionality to.
//
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnResourceRelease, 
//					VIsValidEditorData,	VSetEditorData,	VOnEventReceived
//					VHandleCollision, VOnCollisionEnter, VOnCollisionEnter,
//					VOnCollisionExit, GetMaximumGroundedHorizontalMovementForce
//					GetMaximumGroundedCrouchingHorizontalMovement,
//					GetMaximumJumpingHorizontalMovementForce,
//					GetMaximumJumpingVerticalMovementForce, SetIsInputInactive,
//					SetPlayerIsGrounded, SetPlayerIsNotGrounded, GetPlayerIsGrounded
//					SetPlayerCanStand, SetPlayerCannotStand, GetCanPlayerStand
//					HackTheStation, CheckIfPlayerHitVerticalHazard, CheckForMovementStateTransition
//					CheckForEquipmentStateTransition, CheckIfPlayerCannotStand, CheckForContactBetweenThePlayerAndTheFloor
//					DamagePlayerBodyOnly, InitialisePlayerState, PlayerHitInstaKillObject
//
//Base on:			CGCObjSpritePhysics

#ifndef	_CPLAYER_H_
#define	_CPLAYER_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "../Classes/GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

#include "../Player/Movement/CPlayerMovementState.h"
#include "../Player/Equipment/CPlayerEquipmentState.h"
#include "EPlayerActions.h"
#include "GamerCamp/GameController/GCController.h"
#include "PlayerData/CPlayerDataManager.h"
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#include "ImpossibleRescue/Events/EventTypes/CLevelTransitionEvent.h"
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"

class CPlayerEquipmentState;
class CPlayerMovementState;
class CPlayerPrimaryProjectile;
class CHackingStation;
class CPlayerEquipmentStates;
class CPlayerMovementStates;


class CPlayer
	: public CGCObjSpritePhysics
	, public ITReceiveEvents<CLevelTransitionEvent>
{
public:
	CPlayer( );

	// declare the factory method to enable this to be created via CGCFactory_ObjSpritePhysics 
	GCFACTORY_DECLARE_CREATABLECLASS(CPlayer);

	// we need a virtual destructor since delete will be called on pointers of 
	// this class to delete derived types. (Note from GCFramework)
	virtual ~CPlayer ( );

	// This will be called exactly once for each CGCObject derived class instance 
	// registered with CGCObjectManager as soon as the TGB level file has stopped 
	// loading- it is an "explicit constructor". (Note from GCFramework)
	virtual void VOnResourceAcquire ( ) override;

	// OnReset is called for each CGCObject derived class when CGCObjectManager is reset. (Note from GCFramework)
	virtual void VOnReset ( ) override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnUpdate ( float fTimeStep ) override;

	// called immediately before the managing object group releases its own assets. (Note from GCFramework)
	virtual void VOnResourceRelease ( ) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	virtual void VOnEventReceived(CLevelTransitionEvent eventArgs) override;
	
	//Handle collisions with b2Fixture (called every frame)
	virtual void VHandleCollision(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture) override;

	//Handle collisions with own b2Fixture and other b2Fixture (called once when collision first occurs) 
	virtual void VOnCollisionEnter(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture) override;
	
	//Handle collisions with a CGCObjSpritePhysics of a given type id (called once when collision first occurs)
	virtual void VOnCollisionEnter( GCTypeID typeOfObj ) override;
	
	//Handle collisions with own b2Fixture and other b2Fixture (called once when collision ends)
	virtual void VOnCollisionExit(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture) override;
	
	//Return the player maximum horizontal movement force whilst grounded (walking)
	f32 GetMaximumGroundedHorizontalMovementForce ( ) const;

	//Return the player maximum horizontal movement force whilst grounded (crouching)
	f32 GetMaximumGroundedCrouchingHorizontalMovementForce() const;

	//Return the player maximum horizontal movement force whilst jumping
	f32 GetMaximumJumpingHorizontalMovementForce() const;
	
	//Return the player maximum jump movement force
	f32 GetMaximumJumpingVerticalMovementForce() const;

	//Set whether input has been applied this frame or not
	void SetIsInputInactive(f32 fIsInputInactive);

	//ToDo There is definitely a better way to do this, consider refactoring away these methods.
	//Set the m_bIsGrounded flag to true
	void SetPlayerIsGrounded( );
	//Set the m_bIsGrounded flag to false
	void SetPlayerIsNotGrounded( );
	//Get the m_bIsGrounded flag
	bool GetPlayerIsGrounded( ) const;

	//Set the m_bCanStand flag to true
	void SetPlayerCanStand();
	//Set the m_bCanStand flag to false
	void SetPlayerCannotStand();
	//Get the m_bCanStand flag
	bool GetCanPlayerStand() const;

	void HackTheStation( CHackingStation& station );

	void CheckIfPlayerHitVerticalHazard(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture);

private:
	//Check if the movement state changed
	void CheckForMovementStateTransition(CPlayerMovementState* movementState);
	//Check if the equipment state changed
	void CheckForEquipmentStateTransition(CPlayerEquipmentState* equipmentState);

	//Check if there is a fixture colliding with the player crawling "player_headspace" fixture
	void CheckIfPlayerCannotStand(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture);
	//Check if there is a fixture colliding with the player "player_bottom" fixture
	bool CheckForContactBetweenThePlayerAndTheFloor(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture);
			
	void DamagePlayerBodyOnly( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture );

	void InitialisePlayerState();

	void PlayerHitInstaKillObject() const;

private:
	std::unique_ptr< TGCActionToKeyMap< EPlayerActions > >     m_pcControllerActionToButtonMap;
	f32                                                        m_fMaximumMoveForceHorizontalGrounded;
	f32                                                        m_fMaximumMoveForceHorizontalGroundedCrouching;
	f32                                                        m_fMaximumMoveForceHorizontalJumping;
	f32                                                        m_fMaximumMoveForceVerticalJumping;
	f32                                                        m_fGravityScale;
	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied in a frame
	f32                                                         m_fIsInputInactive = 1.0f;
	bool                                                        m_bIsGrounded; // Flag to check if player is on the floor
	bool                                                        m_bCanStand; // Flag to check if the player can stand
	CPlayerData*											    m_pcPlayerData; // Player data (Health etc.)
	CPlayerMovementStates*										m_pcPlayerMovementStates;
	CPlayerEquipmentStates*										m_pcPlayerEquipmentStates;
	ISoundEffect*												m_PsfxPlayerHit;
	bool														m_bPlayerNeedsInitialising;
	CActionOnRelease											m_pLevelTransitionEventHandler;
	bool m_bPlayerTransitioningToNextLevel;
	
	const float mk_fRightPlayerTransitionBoundary = 1800;
	const float mk_fLeftPlayerTransitionBoundary = 40;
	
	const float mk_fLeftPlayerTransitionSpawnPositionX = 44;
	const float mk_fRightPlayerTransitionSpawnPositionX = 1876;
};

#endif