//Name of class:	CPlayerMovementState
//Main author:		Toyan Green
//Summary:			This class is the base class for all player movement states
//					in the game.
//Functions:		VInitialise, VEnter, VUpdate, VHandleInput

#include "CPlayerMovementState.h"

CPlayerMovementState::~CPlayerMovementState()
{
	if (m_psfxPlayerLanded)
	{
		delete m_psfxPlayerLanded;
		m_psfxPlayerLanded = nullptr;
	}

	CleanupAnimation();
	CleanupAnimationSpeedAction();
}

void CPlayerMovementState::VInitialise()
{
	m_psfxPlayerLanded = AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::PlayerLand );

	// Clean up existing action
	CleanupAnimationSpeedAction();

	// Create and retain a speed action, used to control how fast the animation will play
	m_pcAnimationSpeedAction = new Speed();
	m_pcAnimationSpeedAction->retain();
}

void CPlayerMovementState::VEnter(CPlayer& player)
{
	SetStateIsTransitioning(true);

	SetAnimation(player, VGetAnimationName());

	SetPhysicsShape(player, VGetPhysicsShapeName());
}

CPlayerMovementState* CPlayerMovementState::VUpdate( CPlayer& player )
{
	// Flip the player if necessary
	if (GetControlForceDirection().x > 0.0f)
	{
		player.SetFlippedX(false);
	}
	else if (GetControlForceDirection().x < 0.0f)
	{
		player.SetFlippedX(true);
	}
	
	return nullptr;
};

void CPlayerMovementState::SetPlayerAnimationName( const char* psAnimationName)
{
	// Set the sprite animation name for level transitioning
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetAnimationName(psAnimationName);
}

void CPlayerMovementState::SetPlayerPhysicsShapeName( const char* psPhysicsShapeName)
{
	// Set the physics shape name for level transitioning
	AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->SetPhysicsShapeName(psPhysicsShapeName);
}

bool CPlayerMovementState::VGetIsAnimationLooping( )
{
	return true;
}

float CPlayerMovementState::GetXAxisDeadzone( ) const
{
	return mk_fXAxisDeadzone;
}

Vec2 CPlayerMovementState::GetControlForceDirection() const
{
	return m_v2ControlForceDirection;
}

void CPlayerMovementState::SetControlForceDirectionX( float fControlForceDirectionX )
{
	m_v2ControlForceDirection.x = fControlForceDirectionX;
}

void CPlayerMovementState::SetControlForceDirectionY( float fControlForceDirectionY )
{
	m_v2ControlForceDirection.y = fControlForceDirectionY;
}

void CPlayerMovementState::SetStateIsTransitioning(bool bIsTransitioning)
{
	m_bIsTransitioning = bIsTransitioning;
}

bool CPlayerMovementState::GetStateIsTransitioning() const
{
	return m_bIsTransitioning;
}

void CPlayerMovementState::PlayLandedSound() const
{
	m_psfxPlayerLanded->VPlay();
}

void CPlayerMovementState::SetAnimationSpeed( float fAnimationSpeed ) const
{
	m_pcAnimationSpeedAction->setSpeed(fAnimationSpeed);
}

void CPlayerMovementState::SetAnimation(CPlayer& rcPlayer, const char* pszAnimationName )
{
	//Set the sprite animation name for level transitioning
	SetPlayerAnimationName(pszAnimationName);
	
	if( !m_pNewAnimation )
	{
		ValueMap dicPList = rcPlayer.GetAnimationDictionary();
		m_pNewAnimation = GCCocosHelpers::CreateAnimation(dicPList, pszAnimationName);
		m_pNewAnimation->retain();
		
		// Cache the animation dimensions for later use
		m_fPlayerNewAnimationWidth  = m_pNewAnimation->getFrames().front()->getSpriteFrame()->getRectInPixels().size.width;
		m_fPlayerNewAnimationHeight = m_pNewAnimation->getFrames().front()->getSpriteFrame()->getRectInPixels().size.height;

		// Set the frames per second time the animation should run at
		m_pNewAnimation->setDelayPerUnit(AppDelegate::gks_fTimeStep);
	}

	if(VGetIsAnimationLooping())
	{
		// Create looping animation
		m_pcAnimationSpeedAction->setInnerAction(GCCocosHelpers::CreateAnimationActionLoop(m_pNewAnimation));
	}
	else
	{
		// Create non looping animation
		m_pcAnimationSpeedAction->setInnerAction(GCCocosHelpers::CreateAnimationActionOnce(m_pNewAnimation));
	}
	
	// Set the animation speed
	m_pcAnimationSpeedAction->setSpeed(0);

	rcPlayer.RunAction(m_pcAnimationSpeedAction);
}

void CPlayerMovementState::SetPhysicsShape(CPlayer& rcPlayer, const char* pszPhysicsShapeName)
{
	//Set the physics shape name for level transitioning
	SetPlayerPhysicsShapeName(pszPhysicsShapeName);
	
	//Set the walking physics shape
	rcPlayer.SetPhysicsShape(pszPhysicsShapeName);

	//Get the player's current size
	const float fPlayerCurrentWidth = rcPlayer.GetBoundingBox().size.width;
	const float fPlayerCurrentHeight = rcPlayer.GetBoundingBox().size.height;

	//Calculate difference in position from the floor between the old player size and the new player size
	const float fPlayerXOffset = -((fPlayerCurrentWidth - m_fPlayerNewAnimationWidth) / 2);
	const float fPlayerYOffset = -((fPlayerCurrentHeight - m_fPlayerNewAnimationHeight) / 2);

	//Set the crouching position
	const b2Vec2 b2v2PlayerPhysicsOffsetVector = IGCGameLayer::B2dPixelsToWorld(b2Vec2(fPlayerXOffset, fPlayerYOffset));

	//Set the physics transform (and thus the player sprite) so the player is touching the floor
	rcPlayer.SetPhysicsTransform(Vec2(rcPlayer.GetPhysicsTransform().p.x + b2v2PlayerPhysicsOffsetVector.x,
		rcPlayer.GetPhysicsTransform().p.y + b2v2PlayerPhysicsOffsetVector.y),
		rcPlayer.GetPhysicsTransform().q.GetAngle());
}

float CPlayerMovementState::GetRunningThreshold( ) const
{
	return mk_fRunningThreshold;
}

float CPlayerMovementState::GetMaxGroundedVelocityX() const
{
	// THIS IS VERY BAD. HAD TO LOG THE PLAYER VELOCITY AS ALL VARIABLES TO CALCULATE MAX X VELOCITY COULD NOT BE FOUND (FRICTION etc.)
	return mk_fMaxXVelocity;
}

void CPlayerMovementState::CleanupAnimation()
{
	if (m_pNewAnimation)
	{
		m_pNewAnimation->release();
		m_pNewAnimation = nullptr;
	}
}

void CPlayerMovementState::CleanupAnimationSpeedAction()
{
	if (m_pcAnimationSpeedAction)
	{
		m_pcAnimationSpeedAction->release();
		m_pcAnimationSpeedAction = nullptr;
	}
}