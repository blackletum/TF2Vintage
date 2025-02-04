#ifndef TF_BOT_ENGINEER_BUILD_TELEPORT_EXIt_H
#define TF_BOT_ENGINEER_BUILD_TELEPORT_EXIT_H
#ifdef _WIN32
#pragma once
#endif


#include "NextBotBehavior.h"

class CTFBotEngineerBuildTeleportExit : public Action<CTFBot>
{
public:
	CTFBotEngineerBuildTeleportExit();
	CTFBotEngineerBuildTeleportExit( const Vector& vecSpot, float yaw );
	virtual ~CTFBotEngineerBuildTeleportExit();

	virtual const char *GetName() const OVERRIDE;

	virtual ActionResult<CTFBot> OnStart( CTFBot *me, Action<CTFBot> *priorAction ) OVERRIDE;
	virtual ActionResult<CTFBot> Update( CTFBot *me, float dt ) OVERRIDE;
	virtual ActionResult<CTFBot> OnResume( CTFBot *me, Action<CTFBot> *priorAction ) OVERRIDE;

	virtual EventDesiredResult<CTFBot> OnStuck( CTFBot *me ) OVERRIDE;

private:
	PathFollower m_PathFollower;
	bool m_bSpotPreDetermined;
	Vector m_vecBuildSpot;
	float m_flBuildYaw;
	CountdownTimer m_attemptBuildDuration;
	CountdownTimer m_fetchAmmoTimer;
	CountdownTimer m_recomputePathTimer;
	CountdownTimer m_retryTimer;
};

#endif
