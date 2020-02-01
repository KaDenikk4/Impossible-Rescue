//Name of class:	CTurret
//Main author:		Toyan Green
//Summary:			This class is responsible for stationary enemy turrets
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnCollisionEnter,
//					ResetTurret, SetFireCoolDowns, SetNumberOfShotsInBurst,
//					SetFireVelocity
#include <memory.h>
#include "CTurret.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "ImpossibleRescue/Player/Equipment/Shooting/SecondaryShooting/CPlayerSecondaryProjectile.h"
#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

USING_NS_CC;

static const char* k_pszXmlAttr_FireVelocityX		= "ShootVelocityX";
static const char* k_pszXmlAttr_FireVelocityY		= "ShootVelocityY";
static const char* k_pszXmlAttr_ShotsInBurst		= "ShotsInBurst";
static const char* k_pszXmlAttr_CDBetweenBursts		= "CDBetweenBursts";
static const char* k_pszXmlAttr_CDBetweenBullets	= "CDBetweenBullets";
static const char* k_pszXmlAttr_HackingId			= "HackingID";

GCFACTORY_IMPLEMENT_CREATEABLECLASS( CTurret );

CTurret::CTurret( )
	: CGCObjSpritePhysics( GetGCTypeIDOf( CTurret ) )
	, m_pProjectileManager( nullptr )
	, m_fBetweenBurstsCoolDown( 0.0f )
	, m_fBetweenShotsCoolDown( 0.0f )
	, m_iNumBurstShots( 0.0f )
	, m_bCanFire( false )
	, m_bIsTurretDisabled( false )
	, m_cDisabledTimer( nullptr )
	, m_aorHackedEventHandler( nullptr )
{
	m_psfxTurretShot	= AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::EnemyShoot );
	m_psfxDisabledSound = AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::EnemyDisabled );
	m_psfxEnabledSound	= AppDelegate::GetAssetManager()->VGetSoundEffect( ESoundFX::EnemyEnabled );
	
	m_aorHackedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToStationHackedEvents(*this);
}

CTurret::~CTurret()
{
	if( m_cDisabledTimer )
	{
		delete m_cDisabledTimer;
		m_cDisabledTimer = nullptr;
	}

	m_aorHackedEventHandler.Release();
}

//Set the time (in seconds) between turret bursts, and set the time (in seconds) between turret shots
void CTurret::SetFireCoolDowns(f32 fBetweenBurstsCoolDown, f32 fBetweenShotsCoolDown)
{
	m_fBetweenBurstsCoolDown = fBetweenBurstsCoolDown;
	m_fBetweenShotsCoolDown = fBetweenShotsCoolDown;
	ResetTurret();
}

//Set the number of shots in a turret burst
void CTurret::SetNumberOfShotsInBurst( int iNumShots )
{
	m_iNumBurstShots = iNumShots;
	ResetTurret();
}

//Set the velocity of turret shots
void CTurret::SetFireVelocity(const cocos2d::Vec2& fireVelocity )
{
	m_v2FireVelocity = fireVelocity;
}

//Reset the turret using the current configuration
void CTurret::ResetTurret()
{
	m_fBetweenBurstsCoolDownRemaining	= m_fBetweenBurstsCoolDown;
	m_fBetweenShotsCoolDownRemaining	= m_fBetweenShotsCoolDown;
	m_iNumBurstShotsRemaining			= m_iNumBurstShots;
	//m_bCanFire = false;

	m_eCurrentTurretState = ETurretStates::NotFiring;
}

IN_CPP_CREATION_PARAMS_DECLARE(CTurret, "TexturePacker/Sprites/Turret/Turret.plist", "Turret", b2_staticBody, true);
//Virtual function to be called exactly once for each CGCObject derived class instance
//registered with CGCObjectManager as soon as the TGB level file has stopped
//loading- it is an "explicit constructor". (Note from GCFramework)
void CTurret::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CTurret);
	CGCObjSpritePhysics::VOnResourceAcquire();
	
	// Animation loop
	m_dicPList = GCCocosHelpers::CreateDictionaryFromPlist( GetFactoryCreationParams()->strPlistFile );
	RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_TurretEnabled ) ) );
	
	m_pProjectileManager = static_cast<CTurretProjectileGroup*>
		(CGCObjectManager::FindObjectGroupByID(GetGCTypeIDOf(CTurretProjectileGroup)));

	m_cDisabledTimer	= new CTimerHelper;
	m_fDisabledCooldown = 5.0f;

	if ( m_v2FireVelocity == Vec2::ZERO )
	{
		RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_TurretPermanentlyDisabled  ) ) );
	}
	
}

// OnReset is called for each CGCObject derived class when CGCObjectManager is 
// reset. (Note from GCFramework)
void CTurret::VOnReset( )
{
	CGCObjSpritePhysics::VOnReset();

	// ToDo this only needs to be set once, and could possibly be set from the editor
	m_fDisabledCooldown		= 5.0f;
	
	ResetTurret();

	if (AppDelegate::GetPlayerDataManager()->GetPlayerData()->GetPlayerLevelTransitionData()->CheckHackingIDHasBeenObtained(m_pszHackingID))
	{
		RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_TurretPermanentlyDisabled ) ) );
		m_eCurrentTurretState = ETurretStates::PermanentlyDisabled;
	}
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CTurret::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();

	GetPhysicsBody()->SetGravityScale(0.0f);

	const float fProjectileRotation = GetProjectileRotation( );

	if(m_v2FireVelocity.x < 0)
	{
		SetFlippedX( true );
	}
		
	SetSpriteRotation(fProjectileRotation);
	SetPhysicsTransform(Vec2(GetPhysicsTransform().p.x, GetPhysicsTransform().p.y), -GetSpriteRotation());
}

// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
void CTurret::VOnUpdate(float fTimeStep)
{
	SetTurretState( fTimeStep );
	
}

void CTurret::VOnKilled()
{
	
}

//Handle collisions with b2Fixture (called every frame)
void CTurret::VOnCollisionEnter( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture )
{
	//If self fixture is not the player then we should return
	if (FromB2DFixtureGetSpritePhysics(&b2fSelfFixture) && FromB2DFixtureGetSpritePhysics(&b2fSelfFixture)->GetGCTypeID() != GetGCTypeID())
	{
		return;
	}
}

void CTurret::VOnCollisionEnter( GCTypeID typeOfObj )
{
	if( GetGCTypeIDOf( CPlayerSecondaryProjectile ) == typeOfObj  && (ETurretStates::PermanentlyDisabled != m_eCurrentTurretState && ETurretStates::TemporarilyDisabled != m_eCurrentTurretState) && m_v2FireVelocity != Vec2::ZERO)
	{
		m_psfxDisabledSound->VPlay();
		RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_TurretTemporarilyDisabled ) ) );
		m_eCurrentTurretState = ETurretStates::TemporarilyDisabled;
	}
}

//Called from parent CHackingStation when it is successfully hacked.
void CTurret::VHack( )
{
	m_eCurrentTurretState = ETurretStates::PermanentlyDisabled;
}

void CTurret::DisableTurret()
{
	
}

void CTurret::SetTurretState(float fTimestep)
{
	//Condition in which a turret can fire a burst of shots
	const bool bCanTurretFireABurst			= m_fBetweenBurstsCoolDownRemaining <= 0.0f;
	//Condition in which a turret can fire a shot in a burst
	const bool bCanTurretFireAShotInABurst	= m_fBetweenShotsCoolDownRemaining <= 0.0f;
	
	switch(m_eCurrentTurretState )
	{

	case ETurretStates::NotFiring:
		
		m_fBetweenBurstsCoolDownRemaining -= fTimestep;
		
		if( bCanTurretFireABurst )
		{
			//Set time between shots to 0 so that the turret's first shot is instant
			m_fBetweenShotsCoolDownRemaining	= 0.0f;
			m_eCurrentTurretState				= ETurretStates::Firing;
		}
		break;
		

	case ETurretStates::Firing:
		m_fBetweenShotsCoolDownRemaining -= fTimestep;
		
		if( bCanTurretFireAShotInABurst && 0 < m_iNumBurstShotsRemaining)
		{
			m_psfxTurretShot->VPlay(0.5, false);
			//Spawn projectile just ahead of the firing direction
			m_pProjectileManager->SpawnProjectile(GetProjectileSpawnPosition() + (m_v2FireVelocity.getNormalized() * 60),
				m_v2FireVelocity
				, 3.0f
				, GetProjectileRotation());
				// , 0.0f );
			m_iNumBurstShotsRemaining--;
			//Reset the shot cooldown
			m_fBetweenShotsCoolDownRemaining += m_fBetweenShotsCoolDown;
		}

		//Reset the turret when it has finished firing a burst
		if( m_iNumBurstShotsRemaining <= 0 )
		{
			ResetTurret();
		}
		m_cDisabledTimer->ResetTimer();
		break;
		

	case ETurretStates::TemporarilyDisabled:

		m_cDisabledTimer->RunTimer( m_fDisabledCooldown , fTimestep );
		if( m_cDisabledTimer->GetTimerCompleted() )
		{
			m_psfxEnabledSound->VPlay();
			RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_TurretEnabled ) ) );
			m_eCurrentTurretState = ETurretStates::Firing;
		}
		
		break;

	case ETurretStates::PermanentlyDisabled:
		//Debug to check if turret is permanently disabled.
		CCLOG( "TurretDisabled" );
		
		break;
		
	default:
		CCASSERT( false, "Turret is in invalid state!" );
	}
}

// Check if there is valid editor data
bool CTurret::VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	if (nullptr == rxmlElement)
	{
		return false;
	}

	const tinyxml2::XMLAttribute* pFireX = rxmlElement->FindAttribute(k_pszXmlAttr_FireVelocityX);
	const tinyxml2::XMLAttribute* pFireY = rxmlElement->FindAttribute(k_pszXmlAttr_FireVelocityY);
	const tinyxml2::XMLAttribute* pShotsInBurst = rxmlElement->FindAttribute(k_pszXmlAttr_ShotsInBurst);
	const tinyxml2::XMLAttribute* pCDBetweenBursts = rxmlElement->FindAttribute(k_pszXmlAttr_CDBetweenBursts);
	const tinyxml2::XMLAttribute* pCDBetweenBullets = rxmlElement->FindAttribute(k_pszXmlAttr_CDBetweenBullets);
	const tinyxml2::XMLAttribute* pHackingId = rxmlElement->FindAttribute(k_pszXmlAttr_HackingId);

	return((nullptr != pFireX)
		&& (nullptr != pFireY)
		&& (nullptr != pShotsInBurst)
		&& (nullptr != pCDBetweenBursts)
		&& (nullptr != pCDBetweenBullets)
		&& (nullptr != pHackingId)
		);
}

void CTurret::VSetEditorData( const tinyxml2::XMLElement* rxmlElement )
{
	SetNumberOfShotsInBurst(rxmlElement->IntAttribute(k_pszXmlAttr_ShotsInBurst));

	SetFireCoolDowns(rxmlElement->FloatAttribute(k_pszXmlAttr_CDBetweenBursts)
		, rxmlElement->FloatAttribute(k_pszXmlAttr_CDBetweenBullets));

	SetFireVelocity(Vec2(rxmlElement->FloatAttribute(k_pszXmlAttr_FireVelocityX)
		, rxmlElement->FloatAttribute(k_pszXmlAttr_FireVelocityY)));

	m_pszHackingID = rxmlElement->Attribute(k_pszXmlAttr_HackingId);
}

void CTurret::VOnEventReceived( CStationHackedEvent eventArgs )
{
	if (strcmp("", eventArgs.GetHackID()) == 0)
	{
		return;
	}
	
	if( strcmp(m_pszHackingID, eventArgs.GetHackID(  ) ) == 0)
	{
		RunAction( GCCocosHelpers::CreateAnimationActionLoop( GCCocosHelpers::CreateAnimation( m_dicPList, mk_pszAnim_TurretPermanentlyDisabled ) ) );
		m_psfxDisabledSound->VPlay();
		m_eCurrentTurretState = ETurretStates::PermanentlyDisabled;
	}	
}

float CTurret::GetProjectileRotation() const
{
	// https://answers.unity.com/questions/796648/how-do-i-rotate-a-2d-object-based-on-its-velocity.html
	return atan2(m_v2FireVelocity.x, m_v2FireVelocity.y);
}

Vec2 CTurret::GetProjectileSpawnPosition() const
{
	Vec2 m_kv2ShootingRightOffset( GetSpritePosition().x + 26.0f, GetSpritePosition().y + 26.0f );
	Vec2 m_kv2ShootingLeftOffset( GetSpritePosition().x - 26.0f, GetSpritePosition().y + 26.0f );
	Vec2 m_kv2ShootingUpOffset( GetSpritePosition().x - 26.0f, GetSpritePosition().y + 26.0f );
	Vec2 m_kv2ShootingDownOffset( GetSpritePosition().x + 26.0f, GetSpritePosition().y - 26.0f );

	if( m_v2FireVelocity.x > 0 )
	{
		return m_kv2ShootingRightOffset;
	}
	if( m_v2FireVelocity.x < 0 )
	{
		return m_kv2ShootingLeftOffset;
	}
	if( m_v2FireVelocity.y > 0 )
	{
		return m_kv2ShootingUpOffset;
	}
	if( m_v2FireVelocity.y < 0 )
	{
		return m_kv2ShootingDownOffset;
	}
}