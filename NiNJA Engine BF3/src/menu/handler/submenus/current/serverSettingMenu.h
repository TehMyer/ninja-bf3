#pragma once
#include "menu/handler/submenu.h"

class ServerSettingMenu : public Submenu {
public:
	static ServerSettingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ServerSettingMenu() : Submenu() {}
	~ServerSettingMenu();
};

namespace ServerSettingMenuVars
{
	struct Vars {
		bool bHideMinimap;
		bool bHideHUD;
		bool bNoMinimapSpotting;
		bool bNo3DSpotting;
		bool bOnlySquadLeaderSpawn;
		bool bNoNameTags;
	};

	void UpdateStuff();
	extern Vars vars;
}