//Name of class:	CPlayerLevelTransitionData
//Main author:		Toyan Green
//Summary:			This class is responsible for the for storing player data need when transitioning between levels
//					in the game.
//Functions:		Initialise, GetCurrentHealthPoints, GetMaxHealthPoints
//					, ReplenishHealthPoints, DepleteHealthPoints
//					, GetCurrentLives, GetMaxLives, ReplenishALife,
//					, DepleteALife, InitialiseHealthPoints, InitialiseLives

#ifndef	_CPLAYERLEVELTRANSITIONDATA_H_
#define	_CPLAYERLEVELTRANSITIONDATA_H_

#include "math/Vec2.h"
#include "Box2D/Common/b2Math.h"
#include <vector>
#include "ImpossibleRescue/Events/EventTypes/CLevelTransitionEvent.h"
#include "ImpossibleRescue/Events/Mediator/ITReceiveEvents.h"
#include "ImpossibleRescue/Events/Mediator/CActionOnRelease.h"
#include "ImpossibleRescue/Events/EventTypes/CStationHackedEvent.h"
#include "ImpossibleRescue/Events/EventTypes/CPlayerHasDiedEvent.h"

class CPlayerLevelTransitionData
: ITReceiveEvents< CLevelTransitionEvent >
, ITReceiveEvents< CStationHackedEvent >
, ITReceiveEvents< CPlayerHasDiedEvent >
{
public:
	CPlayerLevelTransitionData();
	~CPlayerLevelTransitionData();

	// Initialise the player health
	void Initialise( );
	
	cocos2d::Vec2 GetSpritePosition( ) const;
	void SetSpritePosition(cocos2d::Vec2 v2SpritePosition);
	
	b2Vec2& GetLinearVelocity( ) const;
	void SetLinearVelocity(b2Vec2 b2v2LinearVelocity);

	const char* GetAnimationName() const;
	void SetAnimationName(const char* psAnimationName);

	const char* GetPhysicsShapeName() const;
	void SetPhysicsShapeName(const char* psPhysicsShapeName);

	void SetLevelTimerRemainingTime( float fTimeRemaining );
	float GetLevelRemainingTimeFromPreviousArea() const;

	bool CheckHackingIDHasBeenObtained(std::string sHackingID);
	
	virtual void VOnEventReceived( CLevelTransitionEvent eventArgs ) override;
	virtual void VOnEventReceived( CStationHackedEvent eventArgs ) override;
	virtual void VOnEventReceived( CPlayerHasDiedEvent eventArgs ) override;

	bool GetIsTransitioningBetweenAreas();
	void SetIsTransitioningBetweenAreas(bool bIsTransitioningBetweenAreas);
	
private:
	void InitialiseHackingIDs();
	void AddHackingID(std::string hackingID);

private:
	cocos2d::Vec2 m_v2SpritePosition;
	b2Vec2& m_b2v2LinearVelocity;

	float m_fTimeRemainingOnLevelTimer;
	const char* m_psAnimationName;
	const char* m_psPhysicsShapeName;

	std::vector<std::string> m_vsHackedIDs;

	CActionOnRelease m_aorLevelTransitionEventHandler;
	CActionOnRelease m_aorStationHackedEventHandler;
	CActionOnRelease m_aorPlayerHasDiedEventHandler;

	bool m_bIsTransitioningBetweenAreas;
};

#endif