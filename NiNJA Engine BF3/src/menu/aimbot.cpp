#include "stdafx.h"

Aimbot pAimbot;

float DegToRad(float d) {
	return d * (M_PI / 180);
}

void Aimbot::ProcessVisibility() {
	if (!AimbotMenuVars::vars.bVisibilityCheck) return;

	auto context = pGame.GetClientGameContext();
	if (!ValidPtr(context->pOnlineManager->pGame->pClientLevel)) return;
	if (!ValidPtr(context->pOnlineManager->pGame->pClientLevel->pPhysicsManager)) return;
	if (!ValidPtr(context->pOnlineManager->pGame->pClientLevel->pPhysicsManager->pRayCaster)) return;

	auto caster = context->pOnlineManager->pGame->pClientLevel->pPhysicsManager->pRayCaster;

	auto myPlayer = pGame.GetLocalPlayer();

	if (ValidPtr(context) && ValidPtr(context->pClientPlayerManager)) {
		for (int i = 0; i < 24; i++) {
			auto player = context->pClientPlayerManager->GetPlayer(i);

			if (!ValidPtr(player)) {
				szVisible[i] = false;
				continue;
			}

			if (player == myPlayer) {
				szVisible[i] = false;
				continue;
			}

			auto soldier = player->GetClientSoldier();

			if (!player->InVehicle()) {
				if (!ValidPtr(soldier)) {
					szVisible[i] = false;
					continue;
				}

				if (!player->IsAlive()) {
					szVisible[i] = false;
					continue;
				}
			}

			if (!ValidPtr(myPlayer)) {
				szVisible[i] = false;
				continue;
			}

			if (!ValidPtr(myPlayer->GetClientSoldier())) {
				szVisible[i] = false;
				continue;
			}

			
			if (!myPlayer->IsAlive()) {
				szVisible[i] = false;
				continue;
			}

			bool isFriend = pPlayer.IsFriendly(player);
			if (isFriend) {
				if (!AimbotMenuVars::vars.bAimOnFriendlies) {
					szVisible[i] = false;
					continue;
				}
			} else {
				if (!AimbotMenuVars::vars.bAimOnEnemies) {
					szVisible[i] = false;
					continue;
				}
			}

			if (player->InVehicle() && !AimbotMenuVars::vars.bAimOnVehicles) {
				szVisible[i] = false;
				continue;
			}

			if (!ValidPtr(myPlayer->GetClientSoldier()->pReplicatedController)) {
				szVisible[i] = false;
				continue;
			}

			if (!ValidPtr(soldier->pReplicatedController)) {
				szVisible[i] = false;
				continue;
			}

			Vec3 bonePosition;
			if (!pPlayer.GetBonePosition(soldier, AimbotMenuVars::TargetBone[AimbotMenuVars::vars.iTargetBone].Result, bonePosition)) continue;

			RayCastHit ray;
			Vec3 _from = myPlayer->GetClientSoldier()->pReplicatedController->Position;
			Vec3 _to = bonePosition;

			szVisible[i] = !caster->PhysicsRayQuery("ControllableFinder", &_from, &_to, &ray, (0x4 | 0x10 | 0x20 | 0x80), nullptr); // (0x4 | 0x10 | 0x20 | 0x80)
		}
	}
}

void Aimbot::ProcessAutoWall() {
	if (!AimbotMenuVars::vars.bAutoWall) return;

	auto context = pGame.GetClientGameContext();
	if (!ValidPtr(context->pOnlineManager->pGame->pClientLevel)) return;
	if (!ValidPtr(context->pOnlineManager->pGame->pClientLevel->pPhysicsManager)) return;
	if (!ValidPtr(context->pOnlineManager->pGame->pClientLevel->pPhysicsManager->pRayCaster)) return;

	auto caster = context->pOnlineManager->pGame->pClientLevel->pPhysicsManager->pRayCaster;
	auto myPlayer = pGame.GetLocalPlayer();

	if (ValidPtr(context) && ValidPtr(context->pClientPlayerManager)) {
		for (int i = 0; i < 24; i++) {
			auto player = context->pClientPlayerManager->GetPlayer(i);

			if (!ValidPtr(player)) {
				szWallbangable[i] = false;
				continue;
			}

			if (player == myPlayer) {
				szWallbangable[i] = false;
				continue;
			}

			auto soldier = player->GetClientSoldier();

			if (!player->InVehicle()) {
				if (!ValidPtr(soldier)) {
					szWallbangable[i] = false;
					continue;
				}

				if (!player->IsAlive()) {
					szWallbangable[i] = false;
					continue;
				}
			}

			if (!ValidPtr(myPlayer)) {
				szWallbangable[i] = false;
				continue;
			}

			if (!ValidPtr(myPlayer->GetClientSoldier())) {
				szWallbangable[i] = false;
				continue;
			}

			if (!myPlayer->IsAlive()) {
				szWallbangable[i] = false;
				continue;
			}

			bool isFriend = pPlayer.IsFriendly(player);
			if (isFriend) {
				if (!AimbotMenuVars::vars.bAimOnFriendlies) {
					szWallbangable[i] = false;
					continue;
				}
			} else {
				if (!AimbotMenuVars::vars.bAimOnEnemies) {
					szWallbangable[i] = false;
					continue;
				}
			}

			if (player->InVehicle() && !AimbotMenuVars::vars.bAimOnVehicles) {
				szWallbangable[i] = false;
				continue;
			}

			Vec3 bonePosition;
			if (!pPlayer.GetBonePosition(soldier, AimbotMenuVars::TargetBone[AimbotMenuVars::vars.iTargetBone].Result, bonePosition)) {
				szWallbangable[i] = false;
				continue;
			}

			bool bReturn = false;
			RayCastHit ray;

			Vec3 _from;
			pPlayer.GetBonePosition(myPlayer->GetClientSoldier(), Wep_Bipod1, _from);

			Vec3 _to = bonePosition;
			Vec3 dir = ((_to - _from) / 1000.f);

			int wallCount = 0;

			while ((bReturn = caster->PhysicsRayQuery("ControllableFinder", &_from, &_to, &ray, (0x4 | 0x10 | 0x20 | 0x80), NULL))) {
				if (ray.pMaterial->IsPenetrable() || ray.pMaterial->IsSeeThrough()) {
					if (!ray.pRigidBody)
						break;

					wallCount++;
					if (wallCount > 2) {
						break;
					}

					_from = ray.Position + dir;
				} else break;
			}

			szWallbangable[i] = !bReturn;
		}
	}
}

ClientPlayer* Aimbot::GetTarget(TargetInformation& target) {
	ClientPlayer* ret = nullptr;
	float closestDistance = FLT_MAX;

	auto context = pGame.GetClientGameContext();
	auto myPlayer = pGame.GetLocalPlayer();

	vector<ClientPlayer*> readyPlayers;

	if (ValidPtr(context) && ValidPtr(context->pClientPlayerManager)) {
		for (int i = 0; i < 24; i++) {
			auto player = context->pClientPlayerManager->GetPlayer(i);

			if (!ValidPtr(player)) continue;
			if (player == pGame.GetLocalPlayer()) continue;

			bool stop = false;
			bool foundList = false;

			for (int j = 0; j < WBList.size(); j++) {
				if (!strcmp(WBList[j].szName, player->pNamePtr->szName)) {
					foundList = true;
					if (WBList[j].bWhitelist) {
						stop = true;
					}

					break;
				}
			}

			if (stop) continue;

			auto soldier = player->GetClientSoldier();

			if (!player->InVehicle()) {
				if (!ValidPtr(soldier)) continue;
				if (!player->IsAlive()) continue;
			}

			if (!ValidPtr(myPlayer)) continue;
			if (!ValidPtr(myPlayer->GetClientSoldier())) continue;
			if (!myPlayer->IsAlive()) continue;

			auto mySoldier = myPlayer->GetClientSoldier();

			if (!ValidPtr(mySoldier->pHealthModule)) continue;

			if (AimbotMenuVars::vars.iIngores) {
				bool ret = false;

				auto chute = soldier->GetClientSoldierParachiteComponent();
				if (ValidPtr(chute)) {
					switch (AimbotMenuVars::vars.iIngores) {
						case 4:
						case 1: { // In Air
							ret = chute->IsInAir();

							if (AimbotMenuVars::vars.iIngores != 4)
								break;
						}

						case 2: { // Falling
							ret = chute->IsFalling();

							if (AimbotMenuVars::vars.iIngores != 4)
								break;
						}

						case 3: { // Parachuting
							ret = chute->IsParachuting();
							break;
						}
					}
				}

				if (ret) {
					continue;
				}
			}

			bool isFriend = pPlayer.IsFriendly(player);
			if (isFriend) {
				if (!AimbotMenuVars::vars.bAimOnFriendlies) continue;
			} else {
				if (!AimbotMenuVars::vars.bAimOnEnemies) continue;
			}

			if (player->InVehicle() && !AimbotMenuVars::vars.bAimOnVehicles) continue;

			Vec3 bonePosition;
			if (!pPlayer.GetBonePosition(soldier, AimbotMenuVars::TargetBone[AimbotMenuVars::vars.iTargetBone].Result, bonePosition)) continue;

			if (!ValidPtr(mySoldier->pReplicatedController)) continue;
			if (pUtils.GetDistance(bonePosition, mySoldier->pReplicatedController->Position) > (float)AimbotMenuVars::vars.iMaxDistance) continue;

			Vec3 screenPos;
			bool onscreen = pGame.WorldToScreen(bonePosition, screenPos);

			if (!AimbotMenuVars::vars.bOffscreenTargeting)
				if (!onscreen) continue;

			if (AimbotMenuVars::vars.bLimitToFOV) {
				Vec3 end(640.f, 360.f, 0.f);
				if (pUtils.GetDistance(screenPos, end) > (AimbotMenuVars::vars.fFOVRadius + (AimbotMenuVars::vars.fFOVRadius / 4))) continue;
			}

			Vec3 _from;
			pPlayer.GetBonePosition(mySoldier, Wep_Bipod1, _from);

			RayCastHit ray;
			Vec3 _to = bonePosition;
			szVisible[i] = !context->pOnlineManager->pGame->pClientLevel->pPhysicsManager->pRayCaster->PhysicsRayQuery("ControllableFinder", &_from, &_to, &ray, (0x4 | 0x10 | 0x20 | 0x80), nullptr)
				&& ValidPtr(ray.pMaterial) && ray.pMaterial->IsPenetrable();

			target.pUsingBone = AimbotMenuVars::TargetBone[AimbotMenuVars::vars.iTargetBone].pName; 
			target.bHittable = szWallbangable[i] || szVisible[i];

			if (AimbotMenuVars::vars.bVisibilityCheck) {
				if (!szVisible[i] && !soldier->IsVisible()) continue;
			} else {
				if (AimbotMenuVars::vars.bAutoWall) {
					if (!target.bHittable) continue;
				}
			}

			if (WBList.size() > 0)
				readyPlayers.push_back(player);

			if (!ValidPtr(mySoldier->pReplicatedController)) continue;
			float distance = pUtils.GetDistance(mySoldier->pReplicatedController->Position, soldier->pReplicatedController->Position);
			if (distance < closestDistance) {
				ret = player;
				target.bVisible = szVisible[i];
				target.BonePosition = bonePosition;
				closestDistance = distance;
			}
		}
	}

	// handle blacklist
	if (WBList.size() > 0) {
		for (int i = 0; i < readyPlayers.size(); i++) {
			auto player = readyPlayers[i];

			if (!ValidPtr(player) 
				|| !ValidPtr(player->GetClientSoldier())) {
				continue;
			}

			auto soldier = player->GetClientSoldier();

			bool stop = false;
			for (int j = 0; j < WBList.size(); j++) {
				if (!strcmp(WBList[j].szName, player->pNamePtr->szName)) {
					if (!WBList[j].bBlacklist) {
						stop = true;
					}
					break;
				}
			}

			if (stop) continue;

			Vec3 bonePosition;
			if (!pPlayer.GetBonePosition(soldier, AimbotMenuVars::TargetBone[AimbotMenuVars::vars.iTargetBone].Result, bonePosition)) continue;

			if (!ValidPtr(myPlayer->GetClientSoldier()->pReplicatedController)) continue;
			float distance = pUtils.GetDistance(myPlayer->GetClientSoldier()->pReplicatedController->Position, soldier->pReplicatedController->Position);
			if (distance < closestDistance) {
				ret = player;
				target.bVisible = szVisible[i];
				target.BonePosition = bonePosition;
				closestDistance = distance;
			}
		}
	} readyPlayers.clear();

	return ret;
}

float Aimbot::GetAngleDelta(float firstAngle, float secondAngle) {
	float difference = secondAngle - firstAngle;
	while (difference < DegToRad(-180.f)) difference += DegToRad(360.f);
	while (difference > DegToRad(180.f)) difference -= DegToRad(360.f);
	return difference;
}

Vec2 Aimbot::SmoothAimbotAngles(Vec2 pClientActiveViewAngles, Vec2 &pAimbotAngles) {
	Vec2 FinishedAngles; float smoothdiff[3];

	pAimbotAngles.x -= pClientActiveViewAngles.x;
	pAimbotAngles.y -= pClientActiveViewAngles.y;

	pAimbotAngles.x = AngleNormalize(pAimbotAngles.x);
	pAimbotAngles.y = AngleNormalize(pAimbotAngles.y);

	float fSmoothValue = abs(GetAngleDelta(pClientActiveViewAngles.y, pGame.vOldAngles.y));
	float fSmoothAmount = AimbotMenuVars::vars.fSmoothScale;

	smoothdiff[0] = pAimbotAngles.x / fSmoothAmount;
	smoothdiff[1] = pAimbotAngles.y / fSmoothAmount;

	if (fSmoothValue > 9.0f) {
		smoothdiff[1] *= (fSmoothValue * 0.2f);
	}

	FinishedAngles.x = pClientActiveViewAngles.x + smoothdiff[0];
	FinishedAngles.y = pClientActiveViewAngles.y + smoothdiff[1];

	FinishedAngles.x = AngleNormalize(FinishedAngles.x);
	FinishedAngles.y = AngleNormalize(FinishedAngles.y);
	return FinishedAngles;
}

float Aimbot::AngleNormalize(float angle) {
	while (angle < DegToRad(-180.f)) angle += DegToRad(360.f);
	while (angle > DegToRad(180.f)) angle -= DegToRad(360.f);
	return angle;
}