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

#include "CPlayer.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "../Player/Movement/CPlayerMovementState.h"
#include "../Player/Movement/CPlayerMovementStates.h"
#include "../Player/Equipment/CPlayerEquipmentStates.h"
#include "../Player/Equipment/Shooting/PrimaryShooting/CPrimaryShootingPlayerEquipmentState.h"
#include "../Gameplay/CHackingStation.h"
#include "ImpossibleRescue/Enemies/Turret/CTurretProjectile.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Environment/Hazards/CHazardCables2m.h"
#include "ImpossibleRescue/Environment/Hazards/CHazardCables3m.h"
#include "ImpossibleRescue/Enemies/Turret/CTurret.h"
#include "ImpossibleRescue/Environment/LevelTransitionBorders/CVerticalLevelTransitionBorder.h"
#include "ImpossibleRescue/Environment/LevelTransitionBorders/CHorizontalLevelTransitionBorder.h"
#include "ImpossibleRescue/Environment/Hazards/CVerticalHazard.h"
#include "ImpossibleRescue/Environment/Door/CDoor.h"

USING_NS_CC;

// action/button map arrays must match in length
static EPlayerActions s_aePlayerActions[] = {
	EPlayerActions::MoveLeft, EPlayerActions::MoveRight, EPlayerActions::MoveXAxis, EPlayerActions::Jump, EPlayerActions::Shoot,
	EPlayerActions::SwitchWeapon, EPlayerActions::Hack, EPlayerActions::Crouch,
};
static cocos2d::Controller::Key s_aeKeys[] = {
	cocos2d::Controller::Key::BUTTON_DPAD_LEFT, cocos2d::Controller::Key::BUTTON_DPAD_RIGHT, cocos2d::Controller::Key::JOYSTICK_LEFT_X, cocos2d::Controller::Key::BUTTON_A
	, cocos2d::Controller::Key::BUTTON_X, cocos2d::Controller::Key::BUTTON_RIGHT_SHOULDER, cocos2d::Controller::Key::BUTTON_Y, cocos2d::Controller::Key::BUTTON_B,
};

//testing menu movement here
//making another action/button map array


// implement the factory method to enable this to be created via CGCFactory_ObjSpritePhysics 
GCFACTORY_IMPLEMENT_CREATEABLECLASS(CPlayer);

CPlayer::CPlayer( )
	: CGCObjSpritePhysics( GetGCTypeIDOf( CPlayer ) )
	  , m_pcControllerActionToButtonMap					( nullptr )
	  , m_fMaximumMoveForceHorizontalGrounded			( 35.0f )
	  , m_fMaximumMoveForceHorizontalGroundedCrouching	( 24.0f )
	  , m_fMaximumMoveForceHorizontalJumping			( 47.0f )
	  , m_fMaximumMoveForceVerticalJumping				( 27000.0f )
	  , m_fGravityScale									( 35.0f )
	  , m_pcPlayerData									( nullptr )
	  , m_pcPlayerMovementStates						( nullptr )
	  , m_pcPlayerEquipmentStates						( nullptr )
	  , m_PsfxPlayerHit									( nullptr )
	  , m_bPlayerNeedsInitialising						( true )
	  , m_pLevelTransitionEventHandler					( nullptr )
	  , m_bPlayerTransitioningToNextLevel				( false )
	  , m_bIsGrounded									( false )
{
	m_PsfxPlayerHit = AppDelegate::GetAssetManager()->VGetSoundEffect(ESoundFX::PlayerHit);
	// Subscribe to level transition events
	m_pLevelTransitionEventHandler = AppDelegate::GetEventMediator()->VSubscribeToLevelTransitionEvents(*this);
	
}


CPlayer::~CPlayer()
{
	m_pLevelTransitionEventHandler.Release();
	if (m_PsfxPlayerHit)
	{
		delete m_PsfxPlayerHit;
		m_PsfxPlayerHit = nullptr;
	}

}

// This will be called exactly once for each CGCObject derived class instance 
// registered with CGCObjectManager as soon as the TGB level file has stopped 
// loading- it is an "explicit constructor". (Note from GCFramework)
void CPlayer::VOnResourceAcquire ( )
{
	CGCObjSpritePhysics::VOnResourceAcquire();
		
	m_pcControllerActionToButtonMap = std::unique_ptr< TGCActionToKeyMap< EPlayerActions >	> ( TCreateActionToKeyMap ( s_aePlayerActions, s_aeKeys ) );
	//creating the map here

	m_pcPlayerData = AppDelegate::GetPlayerDataManager()->GetPlayerData();
	m_pcPlayerMovementStates = AppDelegate::GetPlayerDataManager()->GetPlayerMovementStates();
	m_pcPlayerEquipmentStates = AppDelegate::GetPlayerDataManager()->GetPlayerEquipmentStates();
}

// OnReset is called for each CGCObject derived class when CGCObjectManager is reset. (Note from GCFramework)
void CPlayer::VOnReset ( )
{
	CGCObjSpritePhysics::VOnReset();

	SetVisible(false);
	
	m_bPlayerNeedsInitialising = true;

	//If current equipment state is not null then we are transitioning from one "area" to another within a level
	if (m_pcPlayerEquipmentStates->GetCurrentPlayerEquipmentState())
	{
	 // Don't change which weapon is active
	}
	else
	{
	 //We are starting a new level, or restarting, so reset the movement state
	 m_pcPlayerEquipmentStates->SetCurrentPlayerEquipmentState(m_pcPlayerEquipmentStates->GetSecondaryShootingPlayerEquipmentState());
	 m_pcPlayerEquipmentStates->GetCurrentPlayerEquipmentState()->VEnter(*this);
	}

	// reset velocity and flip state
	SetFlippedX(false);
	SetFlippedY(false);
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CPlayer::VOnUpdate ( float fTimeStep )
{
	GetPhysicsBody()->SetGravityScale(m_fGravityScale);
	
	if (m_bPlayerNeedsInitialising)
	{
		InitialisePlayerState( );

		m_bPlayerNeedsInitialising = false;
	}
	if (!m_bPlayerTransitioningToNextLevel)
	{
		TGCController< EPlayerActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, *m_pcControllerActionToButtonMap);

		//If a controller is active, handle input of the current player states
		if (cController.IsActive())
		{
			CheckForMovementStateTransition(m_pcPlayerMovementStates->GetCurrentPlayerMovementState()->VHandleInput(*this, cController));
			CheckForEquipmentStateTransition(m_pcPlayerEquipmentStates->GetCurrentPlayerEquipmentState()->VHandleInput(*this, cController));
		}
		else
		{
			//ToDo No active controller found
		}

		//Update the current movement state
		CheckForMovementStateTransition(m_pcPlayerMovementStates->GetCurrentPlayerMovementState()->VUpdate(*this));

		//Update the current equipment stategra
		CheckForEquipmentStateTransition(m_pcPlayerEquipmentStates->GetCurrentPlayerEquipmentState()->VUpdate(*this));
		
		// We purposefully set the player CAN stand AFTER the input has been handled. If the player should not be able to stand
		// the VHandleCollision method will be called and set the player to the correct state within the same frame.
		// This allows crouching to work correctly.
		SetPlayerCanStand();
	}
}

// called immediately before the managing object group releases its own assets. (Note from GCFramework)
void CPlayer::VOnResourceRelease ( )
{
	CGCObjSpritePhysics::VOnResourceRelease();

	//Free unique_ptr
	m_pcControllerActionToButtonMap.reset ( );

	// We don't delete these as the objects they point to are cleaned up elsewhere
	m_pcPlayerMovementStates = nullptr;
	m_pcPlayerEquipmentStates = nullptr;
	m_pcPlayerData = nullptr;
}

// Check if there is valid editor data
bool CPlayer::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
	return true;
}

void CPlayer::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	// No data needed from the editor
}

//Handle collisions with b2Fixture (called every frame)
void CPlayer::VHandleCollision( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture )
{
	//If self fixture is not the player then we should return
	if (FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID())
	{
		return;
	}
	
	CheckIfPlayerCannotStand( b2fSelfFixture, b2fCollidingFixture );
}

//Handle collisions with own b2Fixture and other b2Fixture (called once when collision first occurs) 
void CPlayer::VOnCollisionEnter(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture)
{
	//If self fixture is not the player then we should return
	if(FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID( ) )
	{
		return;
	}

	DamagePlayerBodyOnly( b2fSelfFixture, b2fCollidingFixture );

	CheckIfPlayerHitVerticalHazard(b2fSelfFixture, b2fCollidingFixture);

	//Check if the player is on the ground
	if(CheckForContactBetweenThePlayerAndTheFloor( b2fSelfFixture, b2fCollidingFixture ))
	{
		SetPlayerIsGrounded();
	}
}

//Handle collisions with a CGCObjSpritePhysics of a given type id (called once when collision first occurs)
void CPlayer::VOnCollisionEnter( GCTypeID typeOfObj )
{
	if (GetGCTypeIDOf(CPlayerSecondaryProjectile) == typeOfObj)
	{
		return;
	}
	if (GetGCTypeIDOf(CHazardCables2m) == typeOfObj || GetGCTypeIDOf(CHazardCables3m) == typeOfObj || GetGCTypeIDOf(CTurret) == typeOfObj)
	{
		PlayerHitInstaKillObject( );
	}
}

//Handle collisions with own b2Fixture and other b2Fixture (called once when collision ends)
void CPlayer::VOnCollisionExit(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture)
{
	//If self fixture is not the player then we should return
	if (FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID())
	{
		return;
	}

	//Check if the player was on the ground
	if (CheckForContactBetweenThePlayerAndTheFloor(b2fSelfFixture, b2fCollidingFixture))
	{
		SetPlayerIsNotGrounded();
	}
}

//Return the player maximum horizontal movement force
f32 CPlayer::GetMaximumGroundedHorizontalMovementForce ( ) const
{
	return m_fMaximumMoveForceHorizontalGrounded;
}

f32 CPlayer::GetMaximumGroundedCrouchingHorizontalMovementForce( ) const
{
	return m_fMaximumMoveForceHorizontalGroundedCrouching;
}

//Return the player maximum horizontal movement force
f32 CPlayer::GetMaximumJumpingHorizontalMovementForce( ) const
{
	return m_fMaximumMoveForceHorizontalJumping;
}

//Return the player maximum jump movement force
f32 CPlayer::GetMaximumJumpingVerticalMovementForce() const
{
	return m_fMaximumMoveForceVerticalJumping;
}

//Set whether input has been applied this frame or not
void CPlayer::SetIsInputInactive( f32 fIsInputInactive )
{
	m_fIsInputInactive = fIsInputInactive;
}

//Set the m_bIsGrounded flag to true
void CPlayer::SetPlayerIsGrounded( )
{
	m_bIsGrounded = true;
}

//Set the m_bIsGrounded flag to false
void CPlayer::SetPlayerIsNotGrounded( )
{
	m_bIsGrounded = false;
}

//Get the m_bIsGrounded flag
bool CPlayer::GetPlayerIsGrounded( ) const
{
	return m_bIsGrounded;
}

//Set the m_bCanStand flag to true
void CPlayer::SetPlayerCanStand()
{
	m_bCanStand = true;
}

//Set the m_bCanStand flag to false
void CPlayer::SetPlayerCannotStand()
{
	m_bCanStand = false;
}

//Get the m_bCanStand flag
bool CPlayer::GetCanPlayerStand() const
{
	return m_bCanStand;
}

//Player input and logic for hacking the terminals
void CPlayer::HackTheStation( CHackingStation& station )
{
	TGCController< EPlayerActions > cController = TGetActionMappedController( CGCControllerManager::eControllerOne, *m_pcControllerActionToButtonMap );

	if (station.GetIsStationActive())
	{
		if (cController.ButtonIsPressed( EPlayerActions::Hack ))
		{
			station.SetStationIsBeingHacked( true );
		}
		if (cController.ButtonHasJustBeenReleased(EPlayerActions::Hack))
		{
			station.SetStationIsBeingHacked( false );
		}
	}
	if(!station.GetIsStationActive())
	{
		station.SetStationIsBeingHacked(false);
	}
	
}

void CPlayer::CheckIfPlayerHitVerticalHazard(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture)
{
	CGCObjSpritePhysics* pSprPhysColliding = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture);

	if (pSprPhysColliding && GetGCTypeIDOf(CVerticalHazard) == pSprPhysColliding->GetGCTypeID())
	{
		if(CVerticalHazard* pcVerticalHazard = dynamic_cast<CVerticalHazard* >(pSprPhysColliding))
		{
			if(pcVerticalHazard->GetIsHazardEnabled())
			{
				PlayerHitInstaKillObject();
			}
		}
	}
}

//Check if the movement state changed
void CPlayer::CheckForMovementStateTransition( CPlayerMovementState* movementState )
{
	//If there is a movement state, clean up the current state and transition to the new state
	if (movementState)
	{
		if (m_pcPlayerMovementStates->GetCurrentPlayerMovementState())
		{
			m_pcPlayerMovementStates->GetCurrentPlayerMovementState()->VExit(*this);

			m_pcPlayerMovementStates->SetCurrentPlayerMovementState(nullptr);
		}

		m_pcPlayerMovementStates->SetCurrentPlayerMovementState(movementState);

		m_pcPlayerMovementStates->GetCurrentPlayerMovementState()->VEnter(*this);
	}
}

//Check if the equipment state changed
void CPlayer::CheckForEquipmentStateTransition(CPlayerEquipmentState* equipmentState)
{
	//If there is a equipmentState state, clean up the current state and transition to the new state
	if (equipmentState)
	{
		if (m_pcPlayerEquipmentStates->GetCurrentPlayerEquipmentState())
		{
			m_pcPlayerEquipmentStates->SetCurrentPlayerEquipmentState(nullptr);
		}

		m_pcPlayerEquipmentStates->SetCurrentPlayerEquipmentState(equipmentState);

		m_pcPlayerEquipmentStates->GetCurrentPlayerEquipmentState()->VEnter(*this);
	}
}

//Check if there is a fixture colliding with the player crawling "player_headspace" fixture
void CPlayer::CheckIfPlayerCannotStand(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture)
{
	const std::string* pstrCheckMe = cocos2d::GB2ShapeCache::getFixtureIdText(&b2fSelfFixture);
	bool               bHeadspaceSensorNameMatches = (0 == pstrCheckMe->compare("player_headspace"));
	bool               bIsASensor = b2fSelfFixture.IsSensor();

	bool bIsThereASpritePhysicsObjectThatWontPreventThePlayerStandingAboveThePlayerWhilstCrouching = pstrCheckMe
		&& bHeadspaceSensorNameMatches
		&& bIsASensor
		&& FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture)
		&& GetGCTypeIDOf(CTurretProjectile) != FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture)->GetGCTypeID()
		&& GetGCTypeIDOf(CDoor) != FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture)->GetGCTypeID()
		&& GetGCTypeIDOf(CHackingStation) != FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture)->GetGCTypeID();

	//Check if the player is able to stand
	if (bIsThereASpritePhysicsObjectThatWontPreventThePlayerStandingAboveThePlayerWhilstCrouching)
	{
		SetPlayerCannotStand();
	}
}

//Check if there is a fixture colliding with the player "player_bottom" fixture
bool CPlayer::CheckForContactBetweenThePlayerAndTheFloor(const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture)
{
	const std::string*	pstrCheckMe = cocos2d::GB2ShapeCache::getFixtureIdText(&b2fSelfFixture);
	const bool          bBottomSensorNameMatches = (0 == pstrCheckMe->compare("player_bottom"));
	const bool          bIsASensor = b2fSelfFixture.IsSensor();

	const GCTypeID		tidCollidingFixtureID = FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture )->GetGCTypeID( );

	const bool			bIsThereAFloorLikeTouchingTheBottomOfThePlayer =	pstrCheckMe
																			&& bBottomSensorNameMatches
																			&& bIsASensor
																			&& FromB2DFixtureGetSpritePhysics(&b2fCollidingFixture)
																			&& GetGCTypeIDOf(CTurretProjectile) != tidCollidingFixtureID
																			&& GetGCTypeIDOf(CDoor) != tidCollidingFixtureID
																			&& GetGCTypeIDOf(CHackingStation) != tidCollidingFixtureID
																			&& GetGCTypeIDOf(CVerticalLevelTransitionBorder) != tidCollidingFixtureID
																			&& GetGCTypeIDOf(CHorizontalLevelTransitionBorder) != tidCollidingFixtureID;

	//Check if the player is on the ground
	return bIsThereAFloorLikeTouchingTheBottomOfThePlayer;
}

void CPlayer::DamagePlayerBodyOnly( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture )
{
	const std::string* pstrCheckMe = cocos2d::GB2ShapeCache::getFixtureIdText( &b2fSelfFixture );
	bool               bBodyFixtureNameMatches = (0 == pstrCheckMe->compare( "player_headspace" ));
	bool               bIsASensor = b2fSelfFixture.IsSensor();

	bool bIsProjectileCollidingWithPlayerHeadspace = pstrCheckMe
		&& !bBodyFixtureNameMatches
		&& !bIsASensor
		&& GetGCTypeIDOf( CTurretProjectile ) == FromB2DFixtureGetSpritePhysics( &b2fCollidingFixture )->GetGCTypeID();

	if( bIsProjectileCollidingWithPlayerHeadspace )
	{
		m_PsfxPlayerHit->VPlay();
		m_pcPlayerData->GetPlayerHealth()->DepleteHealthPoints( 1 );
	}
}

void CPlayer::InitialisePlayerState()
{
	// If current movement state is not null then we are transitioning from one "area" to another within a level
	if (m_pcPlayerMovementStates->GetCurrentPlayerMovementState())
	{
		if (GetPhysicsBody())
		{
			// Set the player animation using transition data
			const char*         pszAnim_DanielleAnimationName = m_pcPlayerData->GetPlayerLevelTransitionData()->GetAnimationName();
			ValueMap            dicPList = GetAnimationDictionary();
			cocos2d::Animation* pNewAnimation = GCCocosHelpers::CreateAnimation(dicPList, pszAnim_DanielleAnimationName);
			RunAction(GCCocosHelpers::CreateAnimationActionLoop(pNewAnimation));

			// Set the player position using transition data
			const Vec2 v2SpritePos = m_pcPlayerData->GetPlayerLevelTransitionData()->GetSpritePosition();
			GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
			SetSpritePosition(v2SpritePos);
			
			// Set the player physics shape using transition data
			const char* pszPhys_DaniellePhysicsShape = m_pcPlayerData->GetPlayerLevelTransitionData()->GetPhysicsShapeName();
			SetPhysicsShape(pszPhys_DaniellePhysicsShape);

			// Set player physics body variables using transition data
			b2Vec2 b2v2Velocity = m_pcPlayerData->GetPlayerLevelTransitionData()->GetLinearVelocity();
			GetPhysicsBody()->SetLinearVelocity(b2v2Velocity);
			GetPhysicsBody()->SetFixedRotation(true);
		}
	}
	else
	{
		//We are starting a new level, or restarting, so reset the movement state
		m_pcPlayerMovementStates->SetCurrentPlayerMovementState(m_pcPlayerMovementStates->GetIdleStandingPlayerMovementState( ));
		m_pcPlayerMovementStates->GetCurrentPlayerMovementState()->VEnter(*this);

		// Reset Physics properties
		if (GetPhysicsBody())
		{
			const Vec2 v2SpritePos = GetSpritePosition();
			GetPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
			GetPhysicsBody()->SetFixedRotation(true);
		}
	}
}

void CPlayer::VOnEventReceived(CLevelTransitionEvent eventArgs)
{
	// Cache the current player position
	cocos2d::Vec2 v2Position = GetSpritePosition();

	// Set player spawn position and physics body variables
	switch( eventArgs.GetTransitionType(  ) )
	{
		case ELevelTransitionType::PreviousArea:
		case ELevelTransitionType::NextArea:

			// Set the players spawn position depending on where they were when
			// they hit the transition border
			if( v2Position.x > mk_fRightPlayerTransitionBoundary )
			{
				v2Position.x = mk_fLeftPlayerTransitionSpawnPositionX;
			}
			else if( v2Position.x < mk_fLeftPlayerTransitionBoundary )
			{
				v2Position.x = mk_fRightPlayerTransitionSpawnPositionX;
			}

			// Set the player spawn position in transitional data
			m_pcPlayerData->GetPlayerLevelTransitionData( )->SetSpritePosition( v2Position );
			// Set the player velocity in the transitional data
			m_pcPlayerData->GetPlayerLevelTransitionData( )->SetLinearVelocity( GetPhysicsBody( )->GetLinearVelocity( ) );
		break;
		case ELevelTransitionType::NextLevel:
			// Clear the current movement state so that we no we are starting a new level, rather than a new area
			m_pcPlayerMovementStates->SetCurrentPlayerMovementState( nullptr );
			m_bPlayerTransitioningToNextLevel = true;
		break;
		default:
		break;
	}	
}

void CPlayer::PlayerHitInstaKillObject() const
{
	m_PsfxPlayerHit->VPlay();
	// Hazards are a 1 hit kill
	m_pcPlayerData->GetPlayerHealth()->DepleteHealthPoints(m_pcPlayerData->GetPlayerHealth()->GetMaxHealthPoints());
}
