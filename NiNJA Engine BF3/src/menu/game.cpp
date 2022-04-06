#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>

Game pGame;

static char* pServerNames[] = {
	"arnold.xbl.ninja",
	"bernard.xbl.ninja",
	"charlie.xbl.ninja",
	"ford.xbl.ninja",
	"sylvester.xbl.ninja",
	"felix.xbl.ninja",
	"dolores.xbl.ninja",
	"elsie.xbl.ninja"
};

static char* GetRandomSubDomain() {
	srand(time(0));
	int iValue = rand() % 8;
	if (iValue > 7) {
		iValue = 0;
	}
	return pServerNames[iValue];
}

namespace Polynomial {
#define     EQN_EPS     1e-9
#define	    IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)
#define PI 3.141592654

	int SolveQuadratic(float a, float b, float c, std::vector<double>& Sol) {
		double Determinant = b * b - 4 * a*c;
		if (Determinant > 0) {
			double X = (-b + std::sqrt(Determinant)) / (2 * a);
			double X2 = (-b - std::sqrt(Determinant)) / (2 * a);
			Sol.push_back(X);
			Sol.push_back(X2);
			return 2;
		}

		if (IsZero(Determinant)) {
			double X = (-b + std::sqrt(Determinant)) / (2 * a);
			Sol.push_back(X);
			return 2;
		}

		//Only 1 real solution
		double X = -b / (2 * a);
		Sol.push_back(X);
		return 1;
	}

	int SolveCubic(float a, float b, float c, float d, std::vector<double>& Sol) {
		double A = b / a;
		double B = c / a;
		double C = d / a;

		double ASq = A * A;
		double p = 1.0f / 3.0f * (-1.0f / 3.0f * ASq + B);
		double q = 1.0f / 2.0f * (2.0f / 27.0f * A * ASq - 1.0f / 3.0f * A * B + C);

		double PCube = p * p*p;
		double D = q * q + PCube;

		double Sub = 1.0f / 3.0f * A;

		if (IsZero(D)) {
			if (IsZero(q)) {
				Sol.push_back(0 - Sub);
				return 1;
			} else {
				double u = pow(-q, 1 / 3.);
				Sol.push_back(2.0f * u - Sub);
				Sol.push_back(-u - Sub);
				return 2;
			}
		}

		if (D < 0) {
			double phi = 1.0f / 3.0f * acos(-q / sqrt(-PCube));
			double t = 2.0f * sqrt(-p);

			Sol.push_back((t*cos(phi)) - Sub);
			Sol.push_back((-t * cos(phi + PI / 3.0f)) - Sub);
			Sol.push_back((-t * cos(phi - PI / 3.0f)) - Sub);
			return 3;
		}

		double DSqrt = sqrt(D);
		double u = pow(DSqrt - q, 1 / 3.);
		double v = -pow(DSqrt + q, 1 / 3.);
		Sol.push_back(u + v - Sub);
		return 1;
	}

	int SolveQuartic(float a, float b, float c, float d, float e, std::vector<double>& Sol) {
		//  A            B           C          D         E
		//c[4] * x^4 + c[3] * x^3 + c[2] *x^2 + c[1] *x + c[0]
		double A = b / a;
		double B = c / a;
		double C = d / a;
		double D = e / a;

		/* substitute x = y - A/4 to eliminate cubic term:
		x^4 + px^2 + qx + r = 0 */
		double ASqr = A * A;
		double p = -3.0f / 8.0f *ASqr + B;
		double q = 1.0f / 8.0f *ASqr*A - 1.0f / 2.0f *A*B + C;
		double r = -3.0f / 256.0f *ASqr*ASqr + 1.0f / 16.0f*ASqr*B - 1.0f / 4.0f*A*C + D;
		double sub = 1.0f / 4.0f *A;

		if (IsZero(r)) {
			/*no absolute term: y(y^3 + py + q) = 0 */
			std::vector<double> QSol;
			int SolCount = SolveCubic(1, 0, p, q, QSol);
			for (int i = 0; i < SolCount; i++) {
				Sol.push_back(QSol[i] - sub);
			}
			Sol.push_back(0 - sub);
			return SolCount + 1;
		}

		double td = 1.0f / 2 * r * p - 1.0f / 8.0f *q*q;
		double tc = -r;
		double tb = -1.0f / 2 * p;
		double ta = 1;

		std::vector<double> QSol;
		SolveCubic(ta, tb, tc, td, QSol);

		double z = QSol[0];
		double u = z * z - r;
		double v = 2.0f *z - p;

		if (IsZero(u))
			u = 0.0f;
		else if (u > 0.0f)
			u = sqrt(u);
		else
			return 0;

		if (IsZero(v))
			v = 0.0f;
		else if (v > 0.0f)
			v = sqrt(v);
		else
			return 0;

		tc = z - u;
		tb = q < 0 ? -v : v;
		ta = 1;

		std::vector<double> QSol2;
		int Sol2Num = SolveQuadratic(ta, tb, tc, QSol2);

		tc = z + u;
		tb = q < 0 ? v : -v;
		ta = 1;

		int Sol3Num = SolveQuadratic(ta, tb, tc, QSol2);
		int TotalSol = Sol2Num + Sol3Num;
		for (int i = 0; i < TotalSol; i++) {
			Sol.push_back(QSol2[i] - sub);
		}
		return TotalSol;
	}
}

Vec3 PredictAimingPos(Vec3 position, Vec3 targetPosition, Vec3 targetVelocity, float bulletVelocity, float bulletGravity) {
	Vec3 predictedAimingPosition = targetPosition;
	Vec3 p1 = predictedAimingPosition - position;

	double a = bulletGravity * bulletGravity * 0.25;
	double b = -bulletGravity * targetVelocity.y;
	double c = targetVelocity.x * targetVelocity.x + targetVelocity.y * targetVelocity.y + targetVelocity.z * targetVelocity.z - bulletGravity * p1.y - bulletVelocity * bulletVelocity;
	double d = 2.0 * (p1.x * targetVelocity.x + p1.y * targetVelocity.y + p1.z * targetVelocity.z);
	double e = p1.x * p1.x + p1.y * p1.y + p1.z * p1.z;

	vector<double> roots;
	auto num_roots = Polynomial::SolveQuartic(a, b, c, d, e, roots);

	if (num_roots > 0) {
		double hitTime = 0.0;
		for (int i = 0; i < num_roots; ++i) {
			if (roots[i] > 0.0 && (hitTime == 0.0 || roots[i] < hitTime))
				hitTime = roots[i];
		}

		if (hitTime > 0.0) {
			double hitVelX = p1.x / hitTime + targetVelocity.x;
			double hitVelY = p1.y / hitTime + targetVelocity.y - 0.5 * bulletGravity * hitTime;
			double hitVelZ = p1.z / hitTime + targetVelocity.z;

			predictedAimingPosition.x = (float)(position.x + hitVelX * hitTime);
			predictedAimingPosition.y = (float)(position.y + hitVelY * hitTime);
			predictedAimingPosition.z = (float)(position.z + hitVelZ * hitTime);
		}
	}

	return predictedAimingPosition;
}

Vec2 Game::BaseAimCorrection() {
	auto renderer = pGame.GetGameRenderer();
	if (!ValidPtr(renderer)) return Vec2();

	renderer->ViewParams.Update();
	Vec3 trans = pUtils.MatrixToTranslation(renderer->ViewParams.ViewMatrixInverse);

	if (ValidPtr(pWeapon.GetBulletEntityData())) {
		if (ValidPtr(pWeapon.GetFiringFunctionData())) {
			Vec3 before = pGame.AimbotTargetInfo.BonePosition;
			pGame.AimbotTargetInfo.BonePosition = PredictAimingPos(trans, pGame.AimbotTargetInfo.BonePosition, pGame.pAimbotPlayer->GetClientSoldier()->pReplicatedController->Velocity, pWeapon.GetFiringFunctionData()->Shot.InitialSpeed.z, pWeapon.GetBulletEntityData()->flGravity);
		}
	}

	/*if (ValidPtr(pGame.pAimbotPlayer)) {
		if (ValidPtr(pGame.pAimbotPlayer->GetClientSoldier()->GetClientSoldierParachiteComponent())) {
			if (pGame.pAimbotPlayer->GetClientSoldier()->GetClientSoldierParachiteComponent()->IsParachuting()) {
				pGame.AimbotTargetInfo.BonePosition.y -= (pUtils.GetDistance(trans, pGame.AimbotTargetInfo.BonePosition) * 0.2f) / 100;
			} else if (pGame.pAimbotPlayer->GetClientSoldier()->GetClientSoldierParachiteComponent()->IsFalling()) {
				pGame.AimbotTargetInfo.BonePosition.y -= (pUtils.GetDistance(trans, pGame.AimbotTargetInfo.BonePosition) * 0.4f) / 100;
			}
		}
	}*/

	Vec3 direction = pGame.AimbotTargetInfo.BonePosition - trans;
	direction.Normalize();
	return Vec2(-atan2(direction.x, direction.z), atan2(direction.y, direction.VectorLength2()));
}

void Game::Run() {
	bCanRun = CanRun() && pShapes.bHasTexture;

	if (bCanRun) {
		static bool seed = false;
		if (!seed) { seed = true; srand(time(0)); }

		iKillFeedRand[0] = rand() % 8;
		if (iKillFeedRand[0] > 7) {
			iKillFeedRand[0] = 0;
		}

		iKillFeedRand[1] = rand() % 5;
		if (iKillFeedRand[1] > 4) {
			iKillFeedRand[1] = 0;
		}
	}

	if (pConfig.bLoadCurrentSettings) {
		pConfig.bLoadCurrentSettings = false;
		Sleep(1500);
		pConfig.LoadConfig("NINJA:\\BF3-Engine.ini");
	}

	if (pConfig.bSaveCurrentSettings) {
		pConfig.bSaveCurrentSettings = false;
		pConfig.UpdateCurrentSettings();
	}

	if (pConfig.bCreateConfigExt) {
		pConfig.bCreateConfigExt = false;

		pUtils.vaBuff(pConfig.szCreateConfigNameBuffer, 80, "NINJA:\\BF-Engine\\%s.ini", pConfig.pCreateConfigName.c_str());
		pConfig.CreateConfig(pConfig.szCreateConfigNameBuffer);
	}

	if (pConfig.bLoadConfigExt) {
		pConfig.bLoadConfigExt = false;

		pUtils.vaBuff(pConfig.szLoadConfigNameBuffer, 80, "NINJA:\\BF-Engine\\%s.ini", pConfig.pLoadConfigName.c_str());
		pConfig.LoadConfig(pConfig.szLoadConfigNameBuffer);
	}
}

void Game::DownloadSoundPacks() {
	vector<char*> toDownload;

	auto dir = GetWebDirectoryListing(GetRandomSubDomain(), "/authed/sounds/oof/");
	for (int i = 0; i < dir.size(); i++) {
		if (!pUtils.FileExists(pUtils.va("NINJA:\\ninjacache\\media\\sounds\\%s", dir[i]))) {
			toDownload.push_back(dir[i]);
		}
	}

	if (toDownload.size() > 0) {
		HttpRequest req;
		for (int i = 0; i < toDownload.size(); i++) {
			req.DownloadFile(GetRandomSubDomain(), pUtils.va("/authed/sounds/oof/%s", toDownload[i]), pUtils.va("NINJA:\\ninjacache\\media\\sounds\\%s", dir[i]), 11000, false);
		}
	}
}

void Game::DownloadChangelog() {
	auto ini = IniParse("NINJA:\\BF3-Engine.ini");
	if (ini.IsGood()) {
		pConfig.iServerChangelogVersion = ini.ReadInt("Internal Settings", "Last Version", pConfig.iServerChangelogVersion);
	}

	HttpRequest req;
	if (req.DownloadFile(GetRandomSubDomain(), "/authed/changelog-bf3", "NINJA:\\ninjacache\\media\\changelog-bf3.txt", 11000, false)) {
		auto file = fopen("NINJA:\\ninjacache\\media\\changelog-bf3.txt", "r+");
		if (file) {
			fseek(file, 0, SEEK_END);
			auto size = ftell(file) - 1;
			fseek(file, 0, SEEK_SET);

			char* text = new char[size];
			fread(text, 1, size, file);

			char val[5];
			strncpy(val, text, 3);

			pConfig.iServerChangelogVersion = atoi(val);

			if (ini.ReadInt("Internal Settings", "Last Version", 0) != pConfig.iServerChangelogVersion) {
				strncpy(pConfig.szChangelogData, text + 4, size - 7);
				pConfig.bShouldShowChangelog = true;
			}

			delete[] text;
			fclose(file);
			remove("NINJA:\\ninjacache\\media\\changelog-bf3.txt");
		}
	}
}

D3DXMATRIX Game::GetViewProjectionMatrix() {
	float aspect = 1280.0f / 720.0f;

	D3DXMATRIX firstPersonTransform = pGame.GetGameRenderer()->ViewParams.Transform;
	float fovY = pGame.GetGameRenderer()->ViewParams.flFovY;

	D3DXVECTOR3 vOrigin = D3DXVECTOR3(firstPersonTransform.m[3][0], firstPersonTransform.m[3][1], firstPersonTransform.m[3][2]);
	D3DXVECTOR3 vLeft = D3DXVECTOR3(firstPersonTransform.m[0][0], firstPersonTransform.m[0][1], firstPersonTransform.m[0][2]);
	D3DXVECTOR3 vUp = D3DXVECTOR3(firstPersonTransform.m[1][0], firstPersonTransform.m[1][1], firstPersonTransform.m[1][2]);
	D3DXVECTOR3 vForward = D3DXVECTOR3(firstPersonTransform.m[2][0], firstPersonTransform.m[2][1], firstPersonTransform.m[2][2]);

	D3DXMATRIX viewMatrix;
	D3DXMatrixIdentity(&viewMatrix);
	viewMatrix._11 = vLeft.x; viewMatrix._12 = vUp.x; viewMatrix._13 = vForward.x;
	viewMatrix._21 = vLeft.y; viewMatrix._22 = vUp.y; viewMatrix._23 = vForward.y;
	viewMatrix._31 = vLeft.z; viewMatrix._32 = vUp.z; viewMatrix._33 = vForward.z;
	viewMatrix._41 = -D3DXVec3Dot(&vOrigin, &vLeft);
	viewMatrix._42 = -D3DXVec3Dot(&vOrigin, &vUp);
	viewMatrix._43 = -D3DXVec3Dot(&vOrigin, &vForward);

	D3DXMATRIXA16 Proj;
	D3DXMatrixPerspectiveFovRH(&Proj, fovY, aspect, 0.1f, 10000.0f);
	return viewMatrix * Proj;
}

bool Game::WorldToScreen(Vec3 world, Vec3& out) {
	D3DXMATRIX viewProjectionMatrix = GetViewProjectionMatrix();

	float w = viewProjectionMatrix(0, 3) * world.x +
		viewProjectionMatrix(1, 3) * world.y +
		viewProjectionMatrix(2, 3) * world.z +
		viewProjectionMatrix(3, 3);

	if (w < 0.0001f) {
		return false;
	}

	float x = viewProjectionMatrix(0, 0) * world.x +
		viewProjectionMatrix(1, 0) * world.y +
		viewProjectionMatrix(2, 0) * world.z +
		viewProjectionMatrix(3, 0);

	float y = viewProjectionMatrix(0, 1) * world.x +
		viewProjectionMatrix(1, 1) * world.y +
		viewProjectionMatrix(2, 1) * world.z +
		viewProjectionMatrix(3, 1);

	out.x = (1280.0f * 0.5f) + (1280.0f * 0.5f) * x / w;
	out.y = (720.0f * 0.5f) - (720.0f * 0.5f) * y / w;
	out.z = w;

	return true;
}

bool Game::CanRun() {
	auto context = pGame.GetClientGameContext();
	auto player = GetLocalPlayer();

	if (!ValidPtr(context)) { return false; }
	if (!ValidPtr(player)) { return false; }

	if (!ValidPtr(context->pClientPlayerManager)) { return false; }
	if (!ValidPtr(player->GetClientSoldier()) && !ValidPtr(player->GetVehicleEntity())) { return false; }
	if (!ValidPtr(player->GetClientSoldier()->pSoldierWeaponsComponent) && !ValidPtr(player->GetVehicleEntity())) { return false; }

	return true;
}

bool Game::Initialize() {
	if (!XexExecutableModuleHandle) { DbgPrint("Failed 1"); return false; }
	if (!*XexExecutableModuleHandle) { DbgPrint("Failed 2"); return false; }

	PLDR_DATA_TABLE_ENTRY Title = *XexExecutableModuleHandle;

	DbgPrint("Game compiled on %i", Title->TimeDateStamp);
	if (Title->TimeDateStamp != __TIMEDATESTAMP__) {
		DbgPrint("Invalid game version!");
		return false;
	}

	// lets setup folders and what-not.
	pConfig.Initialize();

	if (!TitleHooks::Apply()) {
		DbgPrint("Failed to apply hooks! Removing any that were successful!");
		TitleHooks::Remove(true);
		return false;
	}

	if (!pSounds.Start()) {
		DbgPrint("Failed to initialize sound engine!");
		return false;
	}

	XNotifyQueueUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, 0, XNOTIFYUI_PRIORITY_HIGH, L"NiNJA Engine Loaded", NULL);

	DbgPrint("Game initialized!");
	NiNJA.bGameInitialized = true;
	bInitialized = true;
	return true;
}

void Game::Shutdown() {
	TitleHooks::Remove();

	NiNJA.bShutdownCheats = false;
	DbgPrint("Game uninitialized!");
}

ClientGameContext* Game::GetClientGameContext() {
	return *(ClientGameContext**)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwClientGameContext);
}

DWORD Game::GetClientGameContextPointer() {
	return *(DWORD*)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwClientGameContext);
}

GameRenderer* Game::GetGameRenderer() {
	return *(GameRenderer**)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwGameRenderer);
}

UIEngine* Game::GetUIEngine() {
	return *(UIEngine**)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUIEngine);
}

DxRenderer* Game::GetDxRenderer() {
	return *(DxRenderer**)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwDxRenderer);
}

SyncedBFSettings* Game::GetSyncedBFSettings() {
	return *(SyncedBFSettings**)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwSyncedBFSettings);
}

ClientPlayer* Game::GetLocalPlayer() {
	auto context = GetClientGameContext();
	if (ValidPtr(context)) {
		if (ValidPtr(context->pClientPlayerManager)) {
			if (ValidPtr(context->pClientPlayerManager->pLocalPlayer)) {
				return context->pClientPlayerManager->pLocalPlayer;
			}
		}
	}

	return nullptr;
}

ClientSoldierEntity* Game::GetMySoldierEntity() {
	auto player = GetLocalPlayer();
	if (ValidPtr(player)) {
		if (player->pAttachedControllable)
			return nullptr;
		return (ClientSoldierEntity*)player->pControlledControllable;
	}

	return nullptr;
}

ClientSoldierWeapon* Game::GetSoldierWeapon() {
	auto soldier = GetMySoldierEntity();
	if (ValidPtr(soldier)) {
		if (ValidPtr(soldier->pSoldierWeaponsComponent)) {
			if (ValidPtr(soldier->pSoldierWeaponsComponent->pCurrentAnimatedWeaponHandler)) {
				return soldier->pSoldierWeaponsComponent->pCurrentAnimatedWeaponHandler->pCurrentWeapon;
			}
		}
	}

	return nullptr;
}

ResourceManager* Game::GetResourceManager() {
	return *(ResourceManager**)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwResourceManager);
}

char Game::GetDamageID() {
	DWORD r28 = *(DWORD*)(GetClientGameContextPointer() + 0x10);
	return (*(DWORD*)(r28)+(*(DWORD*)(r28 + 4) << 1)) & 0x3F;
}

void Game::SendDamageToClient(ClientSoldierHealthModule* healthComponent, char damageID, ClientDamageInfo* damageInfo, float damage, ClientPlayer* target, bool unk, int type, ClientDamageGiverInfo* giver) {
	Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwSendDamageToClient), healthComponent, damageID, damageInfo, damage, target, unk, type, giver);
}

void HealTeamCallback(ClientPlayer* pEntity) {
	if (ValidPtr(pEntity)) {
		if (pPlayer.IsFriendly(pEntity)) {
			pPlayer.Heal(pEntity);
		}
	}
}

void Game::HealTeam() {
	pPlayer.PlayerCallback(true, HealTeamCallback);
}

void Game::MessageBoxAccept(const char* pTitle, const char* pDesc, UIPopupType PopupType) {
	// patch the default popup type to ours.
	Natives::Write1Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[0]), PopupType);

	// nop out something that i can't remember.
	Natives::Write4Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[1]), 0x60000000);

	struct LeaderboardComp {
		char _0x0000[0xD0];
		bool bIsShowing;
	};

	LeaderboardComp comp;
	comp.bIsShowing = false;

	strcpy(szMessageBoxTitle, pTitle);

	DWORD stringAddress = (DWORD)szMessageBoxTitle;

	// patch out the default label "ID_M_LEADERBOARD_FAILED" load to point to the section we wrote the title to.
	// because our title isn't a registered label, it'll just use the value instead of trying to convert it thru the gxt table.
	Natives::Write4Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[2]), JOIN_LEFT_DWORD(0x3D60, stringAddress));
	Natives::Write4Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[3]), JOIN_RIGHT_DWORD(0x388B, stringAddress));

	// patch the size of the title. This will be fine, as long as the title string is below 255 chars.
	Natives::Write1Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[4]), (BYTE)strlen(pTitle));

	Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[5]), &comp, pDesc);

	// patch back the default popup type.
	Natives::Write1Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[0]), 6);

	// patch back the thing that i can't remember.
	Natives::Write4Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[1]), 0x914100AC);

	// patch back the original title load
	Natives::Write4Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[2]), 0x3D6082DD);
	Natives::Write4Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[3]), 0x388B1334);

	// patch back the size of the title gxt.
	Natives::Write1Byte(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwMessageBox[4]), 0x17);
}