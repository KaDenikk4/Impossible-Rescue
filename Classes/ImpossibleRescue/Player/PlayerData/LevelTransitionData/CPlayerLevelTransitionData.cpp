#include "CPlayerLevelTransitionData.h"
#include "AppDelegate.h"
#include "ImpossibleRescue/Utilities/CHelperFunctions.h"

CPlayerLevelTransitionData::CPlayerLevelTransitionData( )
: m_v2SpritePosition( cocos2d::Vec2(0.0f,0.0f) )
, m_b2v2LinearVelocity( b2Vec2(0.0f,0.0f) )
, m_aorLevelTransitionEventHandler(nullptr)
, m_aorStationHackedEventHandler(nullptr)
, m_aorPlayerHasDiedEventHandler(nullptr)
, m_bIsTransitioningBetweenAreas(false)
{
	m_aorLevelTransitionEventHandler = AppDelegate::GetEventMediator()->VSubscribeToLevelTransitionEvents(*this);
	m_aorStationHackedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToStationHackedEvents(*this);
	m_aorPlayerHasDiedEventHandler = AppDelegate::GetEventMediator()->VSubscribeToPlayerHasDiedEvents(*this);
}

CPlayerLevelTransitionData::~CPlayerLevelTransitionData( )
{
	m_aorLevelTransitionEventHandler.Release();
	m_aorStationHackedEventHandler.Release();
	m_aorPlayerHasDiedEventHandler.Release();
}

// Initialise the player health
void CPlayerLevelTransitionData::Initialise( )
{
	m_v2SpritePosition = cocos2d::Vec2(0.0f, 0.0f);
	m_b2v2LinearVelocity = b2Vec2(0.0f, 0.0f);

	InitialiseHackingIDs();
}

cocos2d::Vec2 CPlayerLevelTransitionData::GetSpritePosition( ) const
{
	return m_v2SpritePosition;
}

void CPlayerLevelTransitionData::SetSpritePosition( cocos2d::Vec2 v2SpritePosition )
{
	m_v2SpritePosition = v2SpritePosition;
}

b2Vec2& CPlayerLevelTransitionData::GetLinearVelocity( ) const
{
	return m_b2v2LinearVelocity;
}

void CPlayerLevelTransitionData::SetLinearVelocity( b2Vec2 b2v2LinearVelocity )
{
	m_b2v2LinearVelocity = b2v2LinearVelocity;
}

const char* CPlayerLevelTransitionData::GetAnimationName( ) const
{
	return m_psAnimationName;
}

void CPlayerLevelTransitionData::SetAnimationName( const char* psAnimationName )
{
	m_psAnimationName = psAnimationName;
}

const char* CPlayerLevelTransitionData::GetPhysicsShapeName( ) const
{
	return m_psPhysicsShapeName;
}

void CPlayerLevelTransitionData::SetPhysicsShapeName( const char* psPhysicsShapeName )
{
	m_psPhysicsShapeName = psPhysicsShapeName;
}

void CPlayerLevelTransitionData::SetLevelTimerRemainingTime( float fTimeRemaining )
{
	m_fTimeRemainingOnLevelTimer = fTimeRemaining;
}

float CPlayerLevelTransitionData::GetLevelRemainingTimeFromPreviousArea() const
{
	return m_fTimeRemainingOnLevelTimer;
}

bool CPlayerLevelTransitionData::CheckHackingIDHasBeenObtained(std::string sHackingID )
{
	if ( !sHackingID.empty() )
	{
		for (const std::string kHackedID : m_vsHackedIDs)
		{
			if (kHackedID == sHackingID)
			{
				return true;
			}
		}
	}
	return false;
}

void CPlayerLevelTransitionData::InitialiseHackingIDs( )
{
	m_vsHackedIDs.clear();
}

void CPlayerLevelTransitionData::AddHackingID( std::string sHackingID )
{
	if( !sHackingID.empty() )
	{
		m_vsHackedIDs.push_back(sHackingID);
	}	
}

void CPlayerLevelTransitionData::VOnEventReceived( CLevelTransitionEvent eventArgs )
{
	if (ELevelTransitionType::NewGame == eventArgs.GetTransitionType() || ELevelTransitionType::NextLevel == eventArgs.GetTransitionType())
	{
		InitialiseHackingIDs();
	}
}

void CPlayerLevelTransitionData::VOnEventReceived( CStationHackedEvent eventArgs )
{
	AddHackingID(eventArgs.GetHackID());
}

void CPlayerLevelTransitionData::VOnEventReceived( CPlayerHasDiedEvent eventArgs )
{
	InitialiseHackingIDs();
}

bool CPlayerLevelTransitionData::GetIsTransitioningBetweenAreas()
{
	return m_bIsTransitioningBetweenAreas;
}

void CPlayerLevelTransitionData::SetIsTransitioningBetweenAreas( bool bIsTransitioningBetweenAreas )
{
	m_bIsTransitioningBetweenAreas = bIsTransitioningBetweenAreas;
}
