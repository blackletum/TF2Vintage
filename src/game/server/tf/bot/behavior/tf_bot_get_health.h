#ifndef TF_BOT_GET_HEALTH_H
#define TF_BOT_GET_HEALTH_H
#ifdef _WIN32
#pragma once
#endif


#include "NextBotBehavior.h"

class CTFBotGetHealth : public Action<CTFBot>
{
public:
	CTFBotGetHealth();
	virtual ~CTFBotGetHealth();

	virtual const char *GetName() const OVERRIDE;

	virtual ActionResult<CTFBot> OnStart( CTFBot *me, Action<CTFBot> *priorAction ) OVERRIDE;
	virtual ActionResult<CTFBot> Update( CTFBot *me, float dt ) OVERRIDE;

	virtual EventDesiredResult<CTFBot> OnMoveToSuccess( CTFBot *me, const Path *path ) OVERRIDE;
	virtual EventDesiredResult<CTFBot> OnMoveToFailure( CTFBot *me, const Path *path, MoveToFailureType reason ) OVERRIDE;
	virtual EventDesiredResult<CTFBot> OnStuck( CTFBot *me ) OVERRIDE;

	virtual QueryResultType ShouldHurry( const INextBot *me ) const OVERRIDE;

	static bool IsPossible( CTFBot *actor );

private:
	PathFollower m_PathFollower;
	CHandle<CBaseEntity> m_hHealth;
	// 4808 CHandle<T>
	bool m_bUsingDispenser;
};

extern ConVar tf_bot_health_critical_ratio;
extern ConVar tf_bot_health_ok_ratio;

class CHealthFilter : public INextBotFilter
{
public:
	CHealthFilter( CTFPlayer *actor );

	virtual bool IsSelected( const CBaseEntity *candidate ) const OVERRIDE;

private:
	CTFPlayer *m_pActor;
	mutable float m_flMinCost;
};

#endif