#ifndef TFMAINMENUPAUSEPANEL_H
#define TFMAINMENUPAUSEPANEL_H

#include "tf_mainmenupanelbase.h"

class CTFMainMenuRGBPanel;

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CTFMainMenuPausePanel : public CTFMainMenuPanelBase
{
	DECLARE_CLASS_SIMPLE(CTFMainMenuPausePanel, CTFMainMenuPanelBase);

public:
	CTFMainMenuPausePanel(vgui::Panel* parent, const char *panelName);
	virtual ~CTFMainMenuPausePanel();
	bool Init();

	void PerformLayout();
	void ApplySchemeSettings(vgui::IScheme *pScheme);
	void OnThink();
	void OnTick();
	void OnCommand(const char* command);
	void DefaultLayout();
	void GameLayout();

private:
	CTFMainMenuRGBPanel	*m_pRGBPanel;
};

#endif // TFMAINMENUPAUSEPANEL_H