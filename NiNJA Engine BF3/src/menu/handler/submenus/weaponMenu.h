#pragma once
#include "menu/handler/submenu.h"

class WeaponMenu : public Submenu {
public:
	static WeaponMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponMenu() : Submenu() {}
	~WeaponMenu();
};

namespace WeaponMenuVars
{
	struct Vars {
		bool bNoRecoil;
		bool bNoSway;
		bool bNoBreath;
		bool bNoSpread;
		bool bNoParachuteConstraints;
		bool bInstantHit;
		bool bInstantKill;
		bool bAlwaysHeadshot;
		bool bLongerBulletLife;
		bool bSelfHealGun;
		bool bTeamHealGun;
		bool bUnlimitedAmmo;
		bool bAutoReload;

		float fDamagePerHit;

		int iNumOfBulletsPerBurst;
		int iNumOfBulletsPerShell;
		int iNumOfBulletsPerShot;
	};

	extern Vars vars;
}