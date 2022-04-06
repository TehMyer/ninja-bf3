#pragma once
#include "menu/handler/submenu.h"

class VisualMenu : public Submenu {
public:
	static VisualMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VisualMenu() : Submenu() {}
	~VisualMenu();
};

namespace VisualMenuVars
{
	struct Vars {
		GColor cEnemy;
		GColor cFriendly;
		GColor cPreferred;
		GColor cWallbangable;
		GColor cWhitelisted;
		GColor cVisible;

		int iBones;
		int iBoxes;
		int iBoxType;
		int iCrosshair;
		int iDistance;
		int iWeapon;
		int iHealth;
		int iName;
		int iOccupiedVehicles;
		int iSnapline;
		int iSnaplinePosition;

		bool bSupplyCrates;
		bool bExplosives;
		bool bGrenades;
		bool bPickups;
		bool bVehicles;
		bool bShowAimbotInfo;
	};

	extern Vars vars;
}