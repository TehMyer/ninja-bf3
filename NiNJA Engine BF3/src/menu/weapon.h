#pragma once

struct NoSwayRestore {
	bool bEnabled;
	float flSwayPitchMultiplier;
	float flSwayYawMultiplier;
	float flDispersionMultiplier;
	float flRecoilMultiplier;
	float flRecoilFovMultiplier;
	float flCameraImpulseMultiplier;
};

struct NoBreathRestore {
	bool bEnabled;
	bool flBreathControlMultiplier;
	bool flBreathControlTimer;
	bool flBreathControlPenaltyMultiplier;
	bool flBreathControlPenaltyTimer;
};

struct InstantHitRestore {
	bool bEnabled;
	bool bInstantHit;
	float fTimeToLive;
	float fInitialSpeed;
};

struct InstantKillRestore {
	bool bEnabled;
	float fStartDamage;
	float fEndDamage;
	float fDamageFalloffStartDistance;
	float fDamageFalloffEndDistance;
};

struct LongerBulletLifeRestore {
	bool bEnabled;
	float fTimeToLive;
};

struct WeaponRestore {
	NoSwayRestore _NoSwayRestore[2];
	NoBreathRestore _NoBreathRestore;
	InstantHitRestore _InstantHitRestore;
	InstantKillRestore _InstantKillRestore;
	LongerBulletLifeRestore _LongerBulletLifeRestore;
};

struct GetNumberOf {
	int iShell;
	int iShot;
	int iBurst;
};

class Weapon {
public:
	map<DWORD, WeaponRestore> Restore;

	float GetDamagePerHit();
	GetNumberOf GetNumberOfValues();
	void SetDamagePerHit(float f);
	void SetNumberOf(GetNumberOf what);

	void NoBreath(bool fix = false);
	void NoSway(bool fix = false);
	void NoParachuteConstraints(bool fix = false);
	void InstantHit(bool fix = false);
	void InstantKill(bool fix = false);
	void LongerBulletLife(bool fix = false);

	BulletEntityData* GetBulletEntityData();
	FiringFunctionData* GetFiringFunctionData();
};

extern Weapon pWeapon;