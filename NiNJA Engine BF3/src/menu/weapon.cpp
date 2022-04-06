#include "stdafx.h"

Weapon pWeapon;

void Weapon::SetDamagePerHit(float f) {
	auto bullet = GetBulletEntityData();

	if (ValidPtr(bullet)) {
		bullet->flStartDamage = f;
	}
}

void Weapon::NoSway(bool fix) {
	auto weapon = pGame.GetSoldierWeapon();

	if (ValidPtr(weapon)) {
		if (ValidPtr(weapon->pAuthorativeAiming)) {
			if (ValidPtr(weapon->pAuthorativeAiming->pData)) {
				if (ValidPtr(weapon->pAuthorativeAiming->pData->pZoomLevels)) {
					if (ValidPtr(weapon->pAuthorativeAiming->pData->pZoomLevels[0])) {
						if (!fix) {
							if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].bEnabled) {
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].bEnabled = true;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flSwayPitchMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flSwayPitchMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flSwayYawMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flSwayYawMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flDispersionMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flDispersionMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flRecoilMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flRecoilMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flRecoilFovMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flRecoilFovMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flCameraImpulseMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flCameraImpulseMultiplier;
							}

							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flSwayPitchMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flSwayYawMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flDispersionMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flRecoilMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flRecoilFovMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flCameraImpulseMultiplier = 0.0f;
						} else {
							if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].bEnabled) {
								return;
							}

							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flSwayPitchMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flSwayPitchMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flSwayYawMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flSwayYawMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flDispersionMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flDispersionMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flRecoilMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flRecoilMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flRecoilFovMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flRecoilFovMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[0]->flCameraImpulseMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[0].flCameraImpulseMultiplier;
						}
					}

					if (ValidPtr(weapon->pAuthorativeAiming->pData->pZoomLevels[1])) {
						if (!fix) {
							if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].bEnabled) {
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].bEnabled = true;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flSwayPitchMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flSwayPitchMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flSwayYawMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flSwayYawMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flDispersionMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flDispersionMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flRecoilMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flRecoilMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flRecoilFovMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flRecoilFovMultiplier;
								Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flCameraImpulseMultiplier = weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flCameraImpulseMultiplier;
							}

							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flSwayPitchMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flSwayYawMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flDispersionMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flRecoilMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flRecoilFovMultiplier = 0.0f;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flCameraImpulseMultiplier = 0.0f;
						} else {
							if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].bEnabled) {
								return;
							}

							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flSwayPitchMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flSwayPitchMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flSwayYawMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flSwayYawMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flDispersionMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flDispersionMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flRecoilMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flRecoilMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flRecoilFovMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flRecoilFovMultiplier;
							weapon->pAuthorativeAiming->pData->pZoomLevels[1]->flCameraImpulseMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoSwayRestore[1].flCameraImpulseMultiplier;
						}
					}
				}
			}
		}
	}
}

void Weapon::NoBreath(bool fix) {
	auto soldier = pGame.GetMySoldierEntity();

	if (ValidPtr(soldier)) {
		if (ValidPtr(soldier->pBreathControlHandler)) {
			if (!fix) {
				if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.bEnabled) {
					Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.bEnabled = true;
					Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlMultiplier = soldier->pBreathControlHandler->flBreathControlMultiplier;
					Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlTimer = soldier->pBreathControlHandler->flBreathControlTimer;
					Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlPenaltyMultiplier = soldier->pBreathControlHandler->flBreathControlPenaltyMultiplier;
					Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlPenaltyTimer = soldier->pBreathControlHandler->flBreathControlPenaltyTimer;
				}

				soldier->pBreathControlHandler->flBreathControlMultiplier = 0.0f;
				soldier->pBreathControlHandler->flBreathControlTimer = 0.0f;
				soldier->pBreathControlHandler->flBreathControlPenaltyMultiplier = 0.0f;
				soldier->pBreathControlHandler->flBreathControlPenaltyTimer = 0.0f;
			} else {
				if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.bEnabled) {
					return;
				}

				soldier->pBreathControlHandler->flBreathControlMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlMultiplier;
				soldier->pBreathControlHandler->flBreathControlTimer = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlTimer;
				soldier->pBreathControlHandler->flBreathControlPenaltyMultiplier = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlPenaltyMultiplier;
				soldier->pBreathControlHandler->flBreathControlPenaltyTimer = Restore[(DWORD)pGame.GetSoldierWeapon()]._NoBreathRestore.flBreathControlPenaltyTimer;
			}
		}
	}
}

void Weapon::NoParachuteConstraints(bool fix) {
	auto soldier = pGame.GetMySoldierEntity();
	if (ValidPtr(soldier)) {
		auto parachute = soldier->GetClientSoldierParachiteComponent();
		if (ValidPtr(parachute)) {
			auto constraint = parachute->pAimingConstraints;
			if (ValidPtr(constraint)) {
				if (fix) {
					constraint->flMinYaw = -45.0f;
					constraint->flMaxYaw = 45.0f;
					constraint->flMinPitch = -85.0f;
					constraint->flMaxPitch = 70.0f;
					constraint->flMinYawDefault = -45.0f;
					constraint->flMaxYawDefault = 45.0f;
				} else {
					constraint->flMinYaw = -180.0f;
					constraint->flMaxYaw = 180.0f;
					constraint->flMinPitch = -180.0f;
					constraint->flMaxPitch = 180.0f;
					constraint->flMinYawDefault = -180.0f;
					constraint->flMaxYawDefault = 180.0f;
				}
			}
		}
	}
}

void Weapon::InstantHit(bool fix) {
	auto bullet = GetBulletEntityData();
	auto firing = GetFiringFunctionData();

	if (ValidPtr(bullet) && ValidPtr(firing)) {
		if (!fix) {
			if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantHitRestore.bEnabled) {
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantHitRestore.bEnabled = true;
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantHitRestore.bInstantHit = bullet->bInstantHit;
			}

			// firing->Shot.InitialSpeed.z = 99999.f;
			bullet->bInstantHit = true;
		} else {
			if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantHitRestore.bEnabled) {
				return;
			}

			bullet->bInstantHit = Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantHitRestore.bInstantHit;
		}
	}
}

void Weapon::InstantKill(bool fix) {
	auto bullet = GetBulletEntityData();
	if (ValidPtr(bullet)) {
		if (!fix) {
			if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.bEnabled) {
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.bEnabled = true;
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fStartDamage = bullet->flStartDamage;
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fEndDamage = bullet->flEndDamage;
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fDamageFalloffStartDistance = bullet->flDamageFalloffStartDistance;
				Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fDamageFalloffEndDistance = bullet->flDamageFalloffEndDistance;
			}

			bullet->flStartDamage = WeaponMenuVars::vars.fDamagePerHit < 1000.f ? 1000.f : WeaponMenuVars::vars.fDamagePerHit;
			bullet->flEndDamage = WeaponMenuVars::vars.fDamagePerHit < 1000.f ? 1000.f : WeaponMenuVars::vars.fDamagePerHit;
			bullet->flDamageFalloffStartDistance = -0.0001f;
			bullet->flDamageFalloffEndDistance = -0.0001f;
		} else {
			if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.bEnabled) {
				return;
			}

			bullet->flStartDamage = Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fStartDamage;
			bullet->flEndDamage = Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fEndDamage;
			bullet->flDamageFalloffStartDistance = Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fDamageFalloffStartDistance;
			bullet->flDamageFalloffEndDistance = Restore[(DWORD)pGame.GetSoldierWeapon()]._InstantKillRestore.fDamageFalloffEndDistance;
		}
	}
}

void Weapon::LongerBulletLife(bool fix) {
	auto bullet = GetBulletEntityData();
	if (ValidPtr(bullet)) {
		if (!fix) {
			if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._LongerBulletLifeRestore.bEnabled) {
				Restore[(DWORD)pGame.GetSoldierWeapon()]._LongerBulletLifeRestore.bEnabled = true;
				Restore[(DWORD)pGame.GetSoldierWeapon()]._LongerBulletLifeRestore.fTimeToLive = bullet->flTimeToLive;
			}

			bullet->flTimeToLive = 20.f;
		} else {
			if (!Restore[(DWORD)pGame.GetSoldierWeapon()]._LongerBulletLifeRestore.bEnabled) {
				return;
			}

			bullet->flTimeToLive = Restore[(DWORD)pGame.GetSoldierWeapon()]._LongerBulletLifeRestore.fTimeToLive;
		}
	}
}

void Weapon::SetNumberOf(GetNumberOf what) {
	auto firing = GetFiringFunctionData();
	if (ValidPtr(firing)) {
		firing->Shot.dwNumberOfBulletsPerBurst = what.iBurst;
		firing->Shot.dwNumberOfBulletsPerShell = what.iShell;
		firing->Shot.dwNumberOfBulletsPerShot = what.iShot;
	}
}

GetNumberOf Weapon::GetNumberOfValues() {
	GetNumberOf num;

	auto firing = GetFiringFunctionData();
	if (ValidPtr(firing)) {
		num.iBurst = firing->Shot.dwNumberOfBulletsPerBurst;
		num.iShell = firing->Shot.dwNumberOfBulletsPerShell;
		num.iShot = firing->Shot.dwNumberOfBulletsPerShot;
	}

	return num;
}

float Weapon::GetDamagePerHit() {
	auto soldier = pGame.GetMySoldierEntity();
	if (ValidPtr(soldier)) {
		if (ValidPtr(soldier->pSoldierWeaponsComponent)) {
			auto bullet = GetBulletEntityData();

			if (ValidPtr(bullet)) {
				return bullet->flStartDamage;
			}
		}
	}

	return 0.f;
}

BulletEntityData* Weapon::GetBulletEntityData() {
	auto weapon = pGame.GetSoldierWeapon();
	if (ValidPtr(weapon)) {
		if (ValidPtr(weapon->pReplicatedFiring)) {
			if (ValidPtr(weapon->pReplicatedFiring->pData)) {
				auto firingFunctionData = weapon->pReplicatedFiring->pData->pPrimaryFire;
				if (ValidPtr(firingFunctionData)) {
					BulletEntityData* bullet;

					if (ValidPtr(weapon->WeaponModifier.pWeaponProjectileModifier)
						&& ValidPtr(weapon->WeaponModifier.pWeaponProjectileModifier->pProjectileData)) {
						bullet = (BulletEntityData*)(weapon->WeaponModifier.pWeaponProjectileModifier->pProjectileData);
					} else {
						bullet = firingFunctionData->Shot.pProjectileData;
					}

					if (ValidPtr(bullet)) {
						if (*(DWORD*)((DWORD)bullet) == 0x82E7235C) {
							return bullet;
						}
					}
				}
			}
		}
	}

	return nullptr;
}

FiringFunctionData* Weapon::GetFiringFunctionData() {
	auto weapon = pGame.GetSoldierWeapon();
	if (ValidPtr(weapon)) {
		if (ValidPtr(weapon->pReplicatedFiring)) {
			if (ValidPtr(weapon->pReplicatedFiring->pData)) {
				return weapon->pReplicatedFiring->pData->pPrimaryFire;
			}
		}
	}

	return nullptr;
}