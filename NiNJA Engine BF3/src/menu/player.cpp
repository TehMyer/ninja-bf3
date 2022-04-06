#include "stdafx.h"

Player pPlayer;

bool Player::GetBonePosition(ClientSoldierEntity* pSoldier, int nBone, Vec3& vec) {
	if (ValidPtr(pSoldier)) {
		if (ValidPtr(pSoldier->pAnimatableComponent1)) {
			if (ValidPtr(pSoldier->pAnimatableComponent1->pAnimatable)) {
				pSoldier->pAnimatableComponent1->bHadVisualUpdate = true;
				if (pSoldier->pAnimatableComponent1->pAnimatable->bValidTransforms) {
					if (ValidPtr(pSoldier->pAnimatableComponent1->pAnimatable->pActiveWorldTransforms)) {
						vec = pSoldier->pAnimatableComponent1->pAnimatable->pActiveWorldTransforms[nBone].TransAndScale;
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Player::IsFriendly(ClientPlayer* pPlayer) {
	if (ValidPtr(pPlayer)) {
		auto myPlayer = pGame.GetLocalPlayer();
		if (ValidPtr(myPlayer)) {
			return pPlayer->nTeam == myPlayer->nTeam;
		}
	}

	return false;
}

void Player::Heal(ClientPlayer* pPlayer) {
	if (ValidPtr(pPlayer)) {
		if (ValidPtr(pPlayer->GetClientSoldier())) {
			if (ValidPtr(pPlayer->GetClientSoldier()->pHealthModule)) {
				if (ValidPtr(pGame.GetSoldierWeapon())) {
					if (ValidPtr(pGame.GetSoldierWeapon()->WeaponModifier.pCurrentSoldierWeaponUnlockAsset)) {
						ClientDamageInfo* damageInfo = new ClientDamageInfo();
						ClientDamageGiverInfo* damageGiverInfo = new ClientDamageGiverInfo();

						damageGiverInfo->pDamageGiver = pGame.GetLocalPlayer();
						damageGiverInfo->pWeaponUnlockAsset = pGame.GetSoldierWeapon()->WeaponModifier.pCurrentSoldierWeaponUnlockAsset;

						pGame.SendDamageToClient(pPlayer->GetClientSoldier()->pHealthModule, pGame.GetDamageID(), damageInfo, -100.f, pPlayer, false, 0, damageGiverInfo);

						delete damageInfo;
						delete damageGiverInfo;
					}
				}
			}
		}
	}
}

void Player::Kill(ClientPlayer* pPlayer) {
	if (ValidPtr(pPlayer)) {
		if (ValidPtr(pPlayer->GetClientSoldier())) {
			if (ValidPtr(pPlayer->GetClientSoldier()->pHealthModule)) {
				if (ValidPtr(pGame.GetSoldierWeapon())) {
					if (ValidPtr(pGame.GetSoldierWeapon()->WeaponModifier.pCurrentSoldierWeaponUnlockAsset)) {
						ClientDamageInfo* damageInfo = new ClientDamageInfo();
						ClientDamageGiverInfo* damageGiverInfo = new ClientDamageGiverInfo();

						damageGiverInfo->pDamageGiver = pGame.GetLocalPlayer();
						damageGiverInfo->pWeaponUnlockAsset = pGame.GetSoldierWeapon()->WeaponModifier.pCurrentSoldierWeaponUnlockAsset;

						pGame.SendDamageToClient(pPlayer->GetClientSoldier()->pHealthModule, pGame.GetDamageID(), damageInfo, 100.f, pPlayer, false, 0, damageGiverInfo);

						delete damageInfo;
						delete damageGiverInfo;
					}
				}
			}
		}
	}
}

void Player::PlayerCallback(bool excludeMe, void(*func)(ClientPlayer*), bool bypassHealth, bool onlyClientPlayer) {
	if (!pGame.bCanRun) {
		return;
	}

	auto localPlayer = pGame.GetLocalPlayer();

	if (ValidPtr(localPlayer)) {
		auto mySoldier = localPlayer->GetClientSoldier();
		auto context = pGame.GetClientGameContext();

		if (ValidPtr(context) && ValidPtr(context->pClientPlayerManager)) {
			for (int i = 0; i < 24; i++) {
				if (!ValidPtr(localPlayer->GetClientSoldier()) && !ValidPtr(localPlayer->GetVehicleEntity())) continue;
				if (!ValidPtr(localPlayer->GetClientSoldier()->pSoldierWeaponsComponent) && !ValidPtr(localPlayer->GetVehicleEntity())) continue;

				auto player = context->pClientPlayerManager->GetPlayer(i);
				if (!ValidPtr(player)) continue;

				if (onlyClientPlayer) {
					if (ValidPtr(player->pNamePtr)) {
						func(player);
						continue;
					}
				}

				if (player == localPlayer && excludeMe) continue;
				auto soldier = player->GetClientSoldier();

				if (!player->InVehicle()) {
					if (!ValidPtr(soldier)) continue;

					if (bypassHealth) {
						func(player);
						continue;
					}

					if (!ValidPtr(soldier->pReplicatedController)) continue;
					if (!ValidPtr(soldier->pHealthModule)) continue;
				}

				func(player);
			}
		}
	}
}

void Player::BoneToBone(ClientSoldierEntity* pEntity, PlayerBones from, PlayerBones to, GColor color) {
	if (!ValidPtr(pEntity))
		return;

	Vec3 bonePos1, bonePos2;
	Vec3 boneScreenPos1, boneScreenPos2;

	if (!GetBonePosition(pEntity, from, bonePos1))
		return;

	if (!GetBonePosition(pEntity, to, bonePos2))
		return;

	if (!pGame.WorldToScreen(bonePos1, boneScreenPos1))
		return;

	if (!pGame.WorldToScreen(bonePos2, boneScreenPos2))
		return;

	pShapes.Line(boneScreenPos1.x, boneScreenPos1.y, boneScreenPos2.x, boneScreenPos2.y, color, 1);
}