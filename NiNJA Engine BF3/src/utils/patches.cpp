#include "stdafx.h"

BYTE dumpBuf[sizeof(CheatPatches)];
#define dumpBF3Patch(a) ((DWORD)(docryptoBypass(a, (QWORD)((((DWORD*)&a - (DWORD*)&BF3))))))
#define DumpName "NiNJA:\\ninjacache\\" __GAMENAME__ ".bin"

#ifdef DUMP_BINS
void Cheats::DumpPatchBinary(char* file) {
	if (!bHasPatches)
		return;

	DbgPrint("Dumping!");

	memset(dumpBuf, 0, sizeof(CheatPatches));

	DWORD *fileBuff = (DWORD*)&dumpBuf[0];
	for (int i = 0; i * 4 < sizeof(CheatPatches); i += 1) {
		fileBuff[i] = (DWORD)dumpBF3Patch(*(DWORD*)((DWORD)&BF3 + ((DWORD)i * 4)));
	}

	DbgPrint("Writing!");

	if (pUtils.MountPath(MOUNT_NAME, pUtils.GetMountPath(), FALSE) == 0) {
		DbgPrint("Mounted path successfully!");
	} else {
		DbgPrint("Failed to mount path!");
		return;
	}

	pUtils.BinToFile(file != NULL ? file : DumpName, dumpBuf, sizeof(CheatPatches));
}
#endif