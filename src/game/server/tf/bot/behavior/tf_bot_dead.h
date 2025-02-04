#ifndef TF_BOT_DEAD_H
#define TF_BOT_DEAD_H
#ifdef _WIN32
#pragma once
#endif


#include "NextBotBehavior.h"

class CTFBotDead : public Action<CTFBot>
{
	DECLARE_CLASS( CTFBotDead, Action<CTFBot> )
public:
	CTFBotDead();
	virtual ~CTFBotDead();

	virtual const char *GetName() const OVERRIDE;

	virtual ActionResult<CTFBot> OnStart( CTFBot *me, Action<CTFBot> *priorAction ) OVERRIDE;
	virtual ActionResult<CTFBot> Update( CTFBot *me, float dt ) OVERRIDE;

private:
	float m_flDeathTimestamp;
};

#endif