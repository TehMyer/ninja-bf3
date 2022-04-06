#pragma once

class Player {
public:
	bool GetBonePosition(ClientSoldierEntity* pSoldier, int nBone, Vec3& vec);
	void Heal(ClientPlayer* pPlayer);
	void Kill(ClientPlayer* pPlayer);
	bool IsFriendly(ClientPlayer* pPlayer);
	void BoneToBone(ClientSoldierEntity* pEntity, PlayerBones from, PlayerBones to, GColor color);
	void PlayerCallback(bool excludeMe, void(*func)(ClientPlayer*), bool bypassHealth = false, bool onlyClientPlayer = false);
};

extern Player pPlayer;