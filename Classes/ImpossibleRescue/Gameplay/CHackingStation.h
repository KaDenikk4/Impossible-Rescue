// Name of class:	CHackingStation
// Summary:			Class responsible for creating a hacking station player can interact with.
//					Once it's hacked, it can relate that information to doors and other objects.
//					
// Functions:		VOnResourceAcquire, VIsValidEditorData, VSetEditorData,  SetProgressBar, InitialiseProgressBar,
//					VOnReset, VOnUpdate, VOnResourceRelease, VOnCollisionEnter,	VOnCollisionExit,
//					SetHackingID, SetStationIsHacked, SetStationIsBeingHacked, SetStationTimer,
//					GetIsStationActive, GetIsStationHacked, AddHackingLabels, DisplayLabelForSeconds,
//					RemoveLabels, GetLabelsOffset, Hack
//					
// ToDo:			Refactor class to use enum for states rather than multiple bools and functions

#ifndef _CHACKINGSTATION_H_
#define _CHACKINGSTATION_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
	#include "Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

#include "GamerCamp/GCCocosInterface/GCFactory_ObjSpritePhysics.h"

#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "IHackable.h"
#include "../Utilities/CLabelHelper.h"
#include "ImpossibleRescue/Player/Movement/Crouching/CCrouchingPlayerMovementState.h"
#include "ui/UILoadingBar.h"

class CHackingStation
	: public CGCObjSpritePhysics
{
public:
	CHackingStation();
	virtual ~CHackingStation();
	
	GCFACTORY_DECLARE_CREATABLECLASS( CHackingStation );

	// This will be called exactly once for each CGCObject derived class instance 
	// registered with CGCObjectManager as soon as the TGB level file has stopped 
	// loading- it is an "explicit constructor".
	virtual void VOnResourceAcquire(void) override;

	// Check if there is valid editor data
	virtual bool VIsValidEditorData( const tinyxml2::XMLElement* rxmlElement ) override;

	virtual void VSetEditorData( const tinyxml2::XMLElement* rxmlElement ) override;
	void SetProgressBar( ) const;
	void InitialiseProgressBar( );

	// OnReset is called for each CGCObject derived class when CGCObjectManager is 
	// reset
	virtual void VOnReset(void) override;

	// OnUpdate is called for each CGCObject derived class when CGCObjectManager is 
	// updated in t2dSCeneGraph onProcessTick()
	virtual void VOnUpdate( f32 fTimeStep ) override;

	// called immediately before the managing object group releases its own assets
	virtual void VOnResourceRelease( void ) override;

	//Functions handling collisions - particularly used to detect player to set station to Active
	virtual void VOnCollisionEnter( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture ) override;
	virtual void VOnCollisionExit( const b2Fixture& b2fSelfFixture, const b2Fixture& b2fCollidingFixture ) override;
	
	void SetHackingID(const char* psHackingID);
	
	//Setters for station being hacked
	void SetStationIsBeingHacked( bool bPlayerIsHacking );

	//Setter for the amount of time it takes to hack the station
	void SetStationTimer		( float fStationMaxTimer );

	//Getters for if station is active
	bool GetIsStationActive();
	bool GetIsStationHacked();

	//Getter for label offset
	cocos2d::Vec2 GetLabelsOffset();

	//Called when the station is successfully hacked
	void Hack( );
	
private:
	enum HackingStationState { HSS_NotHacked, HSS_Hacking, HSS_HackingCompleted };

	HackingStationState m_eCurrentProgress;
	HackingStationState m_eCurrentProgressOld;
	
	CLabelHelper m_cHackingLabel;
	CLabelHelper m_cHackedLabel;
	
	const cocos2d::Vec2 m_kv2LabelOffset = cocos2d::Vec2(0.0f, 80.0f);
	cocos2d::Vec2		m_v2StartingPos;
	cocos2d::Vec2		m_v2SpritePos;

	ui::LoadingBar*		m_pcHackingBackgroundBar;
	ui::LoadingBar*		m_pcHackingInProgressBar;
		
	bool				m_bHackingInProgress;
	bool				m_bIsStationActive;
	bool				m_bIsStationHacked;
	bool				m_bWasLabelDisplayed;

	float				m_fTimeToHackStation;
	float				m_fPlayerHackingTime;
	float				m_fLabelDisplayTime;

	const char*			m_psHackingID;
	CPlayer*			m_pcPlayer;
	ISoundEffect*		m_psfxHacking;
	ISoundEffect*		m_psfxHackingCompleted;


	//Animations params
	ValueMap			m_dicPList;

	const char*			mk_pszAnim_HackingStationNotHacked	= "A1HackingStationRedIdle";
	const char*			mk_pszAnimHackingInProgress			= "A1HackingStationBlueIdle";
	const char*			mk_pszAnimHackingCompleted			= "A1HackingStationGreenIdle";
};

#endif //#ifndef _CHACKINGSTATION_H_