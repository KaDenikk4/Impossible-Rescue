
//Name of class:	CTurret
//Main author:		Toyan Green
//Summary:			This class is responsible for stationary enemy turrets
//					in the game.
//Functions:		VOnResourceAcquire, VOnReset, VOnUpdate, VOnCollisionEnter,
//					ResetTurret, SetFireCoolDowns, SetNumberOfShotsInBurst,
//					SetFireVelocity
#ifndef _CTURRET_H_
#define _CTURRET_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#ifndef _GCFACTORY_OBJSPRITEPHYSICS_H_
#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"
#endif

#ifndef	_ISOUNDEFFECT_H_
#include "ImpossibleRescue/Audio/ISoundEffect.h"
#endif

#include "CTurretProjectileGroup.h"
#include "ImpossibleRescue/Gameplay/IHackable.h"
#include "ImpossibleRescue/Utilities/CTimerHelper.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"

enum class ETurretStates;

class CTurret
	: public CGCObjSpritePhysics
	, public IHackable
	, ITReceiveEvents< CStationHackedEvent >
{
private:
	CTurretProjectileGroup* m_pProjectileManager; //Turret projectile group
	f32                     m_fBetweenBurstsCoolDown; //Time (in seconds) between turret bursts
	f32                     m_fBetweenBurstsCoolDownRemaining; //Time remaining (in seconds) between turret bursts
	f32                     m_fBetweenShotsCoolDown; //Time (in seconds) between turret shots
	f32                     m_fBetweenShotsCoolDownRemaining; //Time remaining (in seconds) between turret bursts
	f32						m_fDisabledCooldown; //Time that turret gets disabled for
	int                     m_iNumBurstShots; //Number of shots in a turret burst
	int                     m_iNumBurstShotsRemaining; //Number of shots remaining in a turret burst
	bool                    m_bCanFire; //Flag to check if the turret can fire
	bool					m_bIsTurretDisabled; //Flag to check if turret is disabled
	cocos2d::Vec2			m_v2FireVelocity; //Velocity at which turret projectiles travel
	

	CTimerHelper*			m_cDisabledTimer;

	ETurretStates			m_eCurrentTurretState;

	CActionOnRelease		m_aorHackedEventHandler;
	const char*				m_pszHackingID;

	ISoundEffect*			m_psfxTurretShot;
	ISoundEffect*			m_psfxDisabledSound;
	ISoundEffect*			m_psfxEnabledSound;

	//Animations params
	cocos2d::ValueMap			m_dicPList;

	const char*			mk_pszAnim_TurretEnabled				= "BaseModel";
	const char*			mk_pszAnim_TurretTemporarilyDisabled	= "TempDisabled";
	const char*			mk_pszAnim_TurretPermanentlyDisabled	= "PermDisabled";
	
	//Reset the turret using the current configuration
	void ResetTurret();
public:
	CTurret();

	GCFACTORY_DECLARE_CREATABLECLASS( CTurret );


	virtual ~CTurret();

	//Set the time (in seconds) between turret bursts, and set the time (in seconds) between turret shots
	void SetFireCoolDowns(f32 fBetweenBurstsCoolDown, f32 fBetweenShotsCoolDown);
	//Set the number of shots in a turret burst
	void SetNumberOfShotsInBurst(int iNumShots);
	//Set the velocity of turret shots
	void SetFireVelocity(const cocos2d::Vec2& fireVelocity);

	//Virtual function to be called exactly once for each CGCObject derived class instance
	//registered with CGCObjectManager as soon as the TGB level file has stopped
	//loading- it is an "explicit constructor". (Note from GCFramework)
	virtual void VOnResourceAcquire(void) override;

	// OnReset is called for each CGCObject derived class when CGCObjectManager is 
	// reset. (Note from GCFramework)
	virtual void VOnReset() override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnResurrected(void) override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick(). (Note from GCFramework)
	virtual void VOnUpdate(float fTimeStep) override;

	virtual void VOnKilled() override;
	
	//Handle collisions with b2Fixture (called every frame)
	virtual void VOnCollisionEnter( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture ) override;
	virtual void VOnCollisionEnter(GCTypeID typeOfObj) override;
		

	//Called from parent CHackingStation when it is successfully hacked.
	virtual void VHack() override;

	void DisableTurret();

	void SetTurretState(float fTimestep);
	
	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	// Set entity variables using editor data
	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	
	virtual void VOnEventReceived( CStationHackedEvent eventArgs ) override;

	float GetProjectileRotation() const;
	cocos2d::Vec2 GetProjectileSpawnPosition() const;
};

enum class ETurretStates
{
	Unknown				= 0,
	NotFiring			= 1,
	Firing				= 2,
	TemporarilyDisabled	= 3,
	PermanentlyDisabled = 4
};

#endif