#pragma once

class Game {
public:
	bool bInitialized;

	bool Initialize();
	void Run();
	bool CanRun();
	void Shutdown();
	Vec2 BaseAimCorrection();
	void DownloadChangelog();
	void DownloadSoundPacks();

	bool bCanRun;
	Vec2 vOldAngles;
	bool bReload;
	int iKillFeedRand[2];
	ClientPlayer* pAimbotPlayer;
	TargetInformation AimbotTargetInfo;
	char szMessageBoxTitle[100];

	ClientGameContext* GetClientGameContext();
	DWORD GetClientGameContextPointer();
	GameRenderer* GetGameRenderer();
	UIEngine* GetUIEngine();
	DxRenderer* GetDxRenderer();
	SyncedBFSettings* GetSyncedBFSettings();
	ClientPlayer* GetLocalPlayer();
	ClientSoldierEntity* GetMySoldierEntity();
	ClientSoldierWeapon* GetSoldierWeapon();
	ResourceManager* GetResourceManager();

	D3DXMATRIX GetViewProjectionMatrix();
	char GetDamageID();
	void HealTeam();
	bool WorldToScreen(Vec3 world, Vec3& out);
	void MessageBoxAccept(const char* pTitle, const char* pDesc, UIPopupType PopupType);
	void SendDamageToClient(ClientSoldierHealthModule* healthComponent, char damageID, ClientDamageInfo* damageInfo, float damage, ClientPlayer* target, bool unk, int type, ClientDamageGiverInfo* giver);
};

extern Game pGame;