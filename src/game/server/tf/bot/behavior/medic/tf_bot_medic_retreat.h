#ifndef TF_BOT_MEDIC_RETREAT_H
#define TF_BOT_MEDIC_RETREAT_H
#ifdef _WIN32
#pragma once
#endif


#include "NextBotBehavior.h"
#include "NextBotUtil.h"

class CTFBotMedicRetreat : public Action<CTFBot>
{
public:
	CTFBotMedicRetreat();
	virtual ~CTFBotMedicRetreat();

	virtual const char *GetName() const OVERRIDE;

	virtual ActionResult<CTFBot> OnStart( CTFBot *me, Action<CTFBot> *priorAction ) OVERRIDE;
	virtual ActionResult<CTFBot> Update( CTFBot *me, float dt ) OVERRIDE;
	virtual ActionResult<CTFBot> OnResume( CTFBot *me, Action<CTFBot> *priorAction ) OVERRIDE;

	virtual EventDesiredResult<CTFBot> OnMoveToSuccess( CTFBot *me, const Path *path ) OVERRIDE;
	virtual EventDesiredResult<CTFBot> OnMoveToFailure( CTFBot *me, const Path *path, MoveToFailureType fail ) OVERRIDE;
	virtual EventDesiredResult<CTFBot> OnStuck( CTFBot *me ) OVERRIDE;

	virtual QueryResultType ShouldAttack( const INextBot *me, const CKnownEntity *threat ) const OVERRIDE;

private:
	PathFollower m_PathFollower;
	CountdownTimer m_lookForPatientsTimer;
};

#endif