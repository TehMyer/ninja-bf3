#pragma once
#include "menu/handler/submenu.h"

class MainMenu : public Submenu {
public:
	static MainMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MainMenu() : Submenu() {}
	~MainMenu();
};

namespace MainMenuVars
{
	struct Vars {
		int iPreset;

		bool bDisableKillFeed;
		bool bShowNiNJAWatermark;
		bool bShowMenuInstructions;
		bool bShowMapInfo;
		bool bShowFrameRate;
	};

	extern Vars vars;
}