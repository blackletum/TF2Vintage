#ifndef TF_BOT_SPY_HIDE_H
#define TF_BOT_SPY_HIDE_H
#ifdef _WIN32
#pragma once
#endif


#include "NextBotBehavior.h"

class CTFBotSpyHide : public Action<CTFBot>
{
public:
	CTFBotSpyHide( CTFPlayer *victim );
	virtual ~CTFBotSpyHide();

	virtual const char *GetName() const OVERRIDE;

	virtual ActionResult<CTFBot> OnStart( CTFBot *me, Action<CTFBot> *action ) OVERRIDE;
	virtual ActionResult<CTFBot> Update( CTFBot *me, float dt ) OVERRIDE;
	virtual ActionResult<CTFBot> OnResume( CTFBot *me, Action<CTFBot> *action ) OVERRIDE;

	virtual EventDesiredResult<CTFBot> OnMoveToSuccess( CTFBot *me, const Path *path ) OVERRIDE;
	virtual EventDesiredResult<CTFBot> OnMoveToFailure( CTFBot *me, const Path *path, MoveToFailureType reason ) OVERRIDE;

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *threat ) const OVERRIDE;

private:
	bool FindHidingSpot( CTFBot *actor );

	CHandle<CTFPlayer> m_hVictim;
	HidingSpot *m_HidingSpot;
	CountdownTimer m_findHidingSpotDelay;
	PathFollower m_PathFollower;
	CountdownTimer m_recomputePath;
	bool m_bAtHidingSpot;
	float m_flEnemyIncursionDistance;
	CountdownTimer m_teaseTimer;
};


struct IncursionEntry_t
{
	int teamnum;
	CTFNavArea *area;
};


class SpyHideIncursionDistanceLess
{
public:
	bool Less( const IncursionEntry_t& lhs, const IncursionEntry_t& rhs, void* );
};

#endif