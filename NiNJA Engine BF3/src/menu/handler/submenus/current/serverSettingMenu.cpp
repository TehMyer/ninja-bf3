#include "stdafx.h"
#include "serverSettingMenu.h"
#include "../currentGameMenu.h"

using namespace ServerSettingMenuVars;

namespace ServerSettingMenuVars {
	Vars vars;
	
	void UpdateStuff() {
		auto synced = pGame.GetSyncedBFSettings();
		if (ValidPtr(synced)) {
			synced->bHideMinimap = vars.bHideMinimap;
			synced->bHideHUD = vars.bHideHUD;
			synced->bNoMinimapSpotting = vars.bNoMinimapSpotting;
			synced->bNo3DSpotting = vars.bNo3DSpotting;
			synced->bOnlySquadLeaderSpawn = vars.bOnlySquadLeaderSpawn;
			synced->bNoNameTags = vars.bNoNameTags;
		}
	}
}

void ServerSettingMenu::Init() {
	SetParentSubmenu<CurrentGameMenu>();
	SetName("Server Settings");

	addOption(ToggleOption("Disable Minimap")
		.addToggle(vars.bHideMinimap)
		.addFunction(UpdateStuff)
		.addTooltip("Stops the minimap from showing. Must \nrespawn."));

	addOption(ToggleOption("Disable HUD")
		.addToggle(vars.bHideHUD)
		.addFunction(UpdateStuff)
		.addTooltip("Stops the HUD elements from showing \n(ammo counter, etc). Must \nrespawn."));

	addOption(ToggleOption("Disable Minimap Spotting")
		.addToggle(vars.bNoMinimapSpotting)
		.addFunction(UpdateStuff)
		.addTooltip("Stops spots showing on the minimap. Must \nrespawn."));

	addOption(ToggleOption("Disable 3D Spotting")
		.addToggle(vars.bNo3DSpotting)
		.addFunction(UpdateStuff)
		.addTooltip("Stops spots showing on the screen. \nMust respawn."));

	addOption(ToggleOption("Disable Name Tags")
		.addToggle(vars.bNoNameTags)
		.addFunction(UpdateStuff)
		.addTooltip("Stops name tags showing on the screen. Must respawn."));

	addOption(ToggleOption("Only Squad Leader Spawn")
		.addToggle(vars.bOnlySquadLeaderSpawn)
		.addFunction(UpdateStuff)
		.addTooltip("For when you're in hardcore. Must respawn."));
}

/*Update once when submenu is opened*/
void ServerSettingMenu::UpdateOnce() {
	auto synced = pGame.GetSyncedBFSettings();
	if (ValidPtr(synced)) {
		vars.bHideMinimap = synced->bHideMinimap;
		vars.bHideHUD = synced->bHideHUD;
		vars.bNoMinimapSpotting = synced->bNoMinimapSpotting;
		vars.bNo3DSpotting = synced->bNo3DSpotting;
		vars.bNoNameTags = synced->bNoNameTags;
		vars.bOnlySquadLeaderSpawn = synced->bOnlySquadLeaderSpawn;
	}
}

/*Update while submenu is active*/
void ServerSettingMenu::Update() {}

/*Background update*/
void ServerSettingMenu::FeatureUpdate() {}

/*Singleton*/
ServerSettingMenu* _instance;
ServerSettingMenu* ServerSettingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ServerSettingMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
ServerSettingMenu::~ServerSettingMenu() { delete _instance; }