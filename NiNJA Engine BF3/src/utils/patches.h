#pragma once

#define docryptoBypass(a,b)  ((QWORD)((QWORD)( ((QWORD)0x120b7a1372b75012) * ((QWORD)(b)) ) ^ (~(QWORD)(a))))

#if defined(PATCH_SVR)
#define decryptDWORD(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&Not(NiNJA.pPatches)->BF3))))))
#else
#define	decryptDWORD(a) (a)
#endif

struct CheatPatches {
	DWORD dwASMBLR;

	DWORD dwUnlimitedAmmo[6];
	DWORD dwMessageBox[6];

	DWORD dwInitStringCheck;
	DWORD dwHijackTexture;
	DWORD dwGetPlayerScore;
	DWORD dwSomePhysics;
	DWORD dwAimbot;
	DWORD dwPrimaryFireCallback;
	DWORD dwAddDamageData;
	DWORD dwUIMessageCompOnMessage;
	DWORD dwClientConnectionAddMove;
	DWORD dwXamInputGetState;
	DWORD dwRenderUI;
	DWORD dwOopsie;
	DWORD dwGetCreateKillMessageClient;
	DWORD dwGetClientPlayerEntryPrimaryFire;
	DWORD dwClientGameContext;
	DWORD dwGameRenderer;
	DWORD dwUIEngine;
	DWORD dwDxRenderer;
	DWORD dwSyncedBFSettings;
	DWORD dwResourceManager;
	DWORD dwSendDamageToClient;
	DWORD dwSendMessage;
	DWORD dwRenderingCreateVertexBuffer;
	DWORD dwRenderingCreateIndexBuffer;
	DWORD dwRenderingCreateRenderCommand;
	DWORD dwRenderingPopulateTexture;
	DWORD dwRenderingGetVertexBuffer;
	DWORD dwRenderingGetIndexBuffer;
	DWORD dwRenderingAddRenderCommand;
	DWORD dwRenderingBeginText;
	DWORD dwRenderingEndText;
	DWORD dwRenderingCreateText;
	DWORD dwRenderingInitTextParams;
	DWORD dwRenderingInitFilterByDefaultValues;
	DWORD dwRenderingRelease;
	DWORD dwRenderingGetWidth;
	DWORD dwRenderingGetHeight;
	DWORD dwServerInfo;
	DWORD dwSendOrder;
	DWORD dwSoldierWeaponUnlockAssetVTable;
	DWORD dwBranchHookLoc;
};

class Cheats {
public:
	bool bHasPatches;
	CheatPatches BF3;

	HRESULT SetAddresses(PVOID data) {
#ifndef PATCH_SVR
		BF3.dwASMBLR = 0x4e800020;

		BF3.dwInitStringCheck = 0x82EA7658;
		BF3.dwHijackTexture = 0x833DBE50;
		BF3.dwGetPlayerScore = 0x83212338;
		BF3.dwSomePhysics = 0x83116A38;
		BF3.dwAimbot = 0x831B6A30;
		BF3.dwPrimaryFireCallback = 0x83294D30;
		BF3.dwAddDamageData = 0x836E0BA8;
		BF3.dwUIMessageCompOnMessage = 0x834DE8F0;
		BF3.dwClientConnectionAddMove = 0x83D00B58;
		BF3.dwXamInputGetState = 0x83F277AC;
		BF3.dwRenderUI = 0x833E60A0;
		BF3.dwOopsie = 0x8302E6C8;
		BF3.dwGetCreateKillMessageClient = 0x83F9FCD0;
		BF3.dwGetClientPlayerEntryPrimaryFire = 0x831C4338;
		BF3.dwClientGameContext = 0x84122028;
		BF3.dwGameRenderer = 0x84125D80;
		BF3.dwUIEngine = 0x8417A480;
		BF3.dwDxRenderer = 0x84121644;
		BF3.dwSyncedBFSettings = 0x8412FAA0;
		BF3.dwResourceManager = 0x84118510;
		BF3.dwSendDamageToClient = 0x833FA3F0;
		BF3.dwSendMessage = 0x83D131D0;
		BF3.dwRenderingCreateVertexBuffer = 0x83D2E140;
		BF3.dwRenderingCreateIndexBuffer = 0x83D2E1E8;
		BF3.dwRenderingCreateRenderCommand = 0x83D2E0A0;
		BF3.dwRenderingPopulateTexture = 0x833D45B8;
		BF3.dwRenderingGetVertexBuffer = 0x83D2F8A0;
		BF3.dwRenderingGetIndexBuffer = 0x83D2F8B8;
		BF3.dwRenderingAddRenderCommand = 0x83D323E8;
		BF3.dwRenderingBeginText = 0x83D2F3F0;
		BF3.dwRenderingEndText = 0x83D2E098;
		BF3.dwRenderingCreateText = 0x839FBE80;
		BF3.dwRenderingInitTextParams = 0x839F53F8;
		BF3.dwRenderingInitFilterByDefaultValues = 0x839F5328;
		BF3.dwRenderingRelease = 0x839DF670;
		BF3.dwRenderingGetWidth = 0x83A8E120;
		BF3.dwRenderingGetHeight = 0x83A8E1A8;
		BF3.dwServerInfo = 0x841289FC;
		BF3.dwSendOrder = 0x834115C0;
		BF3.dwSoldierWeaponUnlockAssetVTable = 0x82E6DC40;
		BF3.dwBranchHookLoc = 0x83B4EC10;

		BF3.dwUnlimitedAmmo[0] = 0x832655B8;
		BF3.dwUnlimitedAmmo[1] = 0x83266ac0;
		BF3.dwUnlimitedAmmo[2] = 0x8420E50C;
		BF3.dwUnlimitedAmmo[3] = 0x834928D8;
		BF3.dwUnlimitedAmmo[4] = 0x83488218;
		BF3.dwUnlimitedAmmo[5] = 0x83497760;

		BF3.dwMessageBox[0] = 0x833F284F;
		BF3.dwMessageBox[1] = 0x833F2864;
		BF3.dwMessageBox[2] = 0x833F2790;
		BF3.dwMessageBox[3] = 0x833F2798;
		BF3.dwMessageBox[4] = 0x833F2797;
		BF3.dwMessageBox[5] = 0x833F2760;

		bHasPatches = true;
#else
		if (data) {
			memcpy(&BF3, data, sizeof(CheatPatches));
			bHasPatches = true;
			return ERROR_SUCCESS;
		} else {
			bHasPatches = FALSE;
			return E_FAIL;
		}
#endif
		return ERROR_SUCCESS;
	}

	void DissolveAddresses() {
		if (bHasPatches) {
			XeCryptRandom((PBYTE)&BF3, sizeof(CheatPatches));
			bHasPatches = false;
		}
	}

	void Initialize() {
		bHasPatches = false;
#ifndef PATCH_SVR
		ZeroMemory(&BF3, sizeof(CheatPatches));
		SetAddresses(NULL);
		bHasPatches = true;
#endif
	}

	Cheats() {
		Initialize();
	}

#ifdef DUMP_BINS
	void DumpPatchBinary(char* pFile = NULL);
#endif
};