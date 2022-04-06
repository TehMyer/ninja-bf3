#include "stdafx.h"

Hooking pHooking;
BranchHooking pBranchHooking;

void __declspec(naked) GLPR(void) {
	__asm {
		std     r14, -0x98(sp)
		std     r15, -0x90(sp)
		std     r16, -0x88(sp)
		std     r17, -0x80(sp)
		std     r18, -0x78(sp)
		std     r19, -0x70(sp)
		std     r20, -0x68(sp)
		std     r21, -0x60(sp)
		std     r22, -0x58(sp)
		std     r23, -0x50(sp)
		std     r24, -0x48(sp)
		std     r25, -0x40(sp)
		std     r26, -0x38(sp)
		std     r27, -0x30(sp)
		std     r28, -0x28(sp)
		std     r29, -0x20(sp)
		std     r30, -0x18(sp)
		std     r31, -0x10(sp)
		stw     r12, -0x8(sp)
		blr
	}
}

DWORD Hooking::RelinkGPLR(DWORD dwSFSOffset, DWORD* dwSaveStubAddress, DWORD* dwOriginalAddress) {
	DWORD Instruction = 0, Replacing;
	PDWORD Saver = (PDWORD)GLPR;

	if (dwSFSOffset & 0x2000000) {
		dwSFSOffset = dwSFSOffset | 0xFC000000;
	}

	Replacing = dwOriginalAddress[dwSFSOffset / 4];

	for (int i = 0; i < 20; i++) {
		if (Replacing == Saver[i]) {
			DWORD NewOffset = (DWORD)&Saver[i] - (DWORD)dwSaveStubAddress;
			Instruction = 0x48000001 | (NewOffset & 0x3FFFFFC);
		}
	}

	return Instruction;
}

void Hooking::PatchInJump(DWORD* dwAddress, DWORD dwDestination, bool bLinked) {
	if (dwDestination & 0x8000)
		dwAddress[0] = 0x3D600000 + (((dwDestination >> 16) & 0xFFFF) + 1);
	else
		dwAddress[0] = 0x3D600000 + ((dwDestination >> 16) & 0xFFFF);

	dwAddress[1] = 0x396B0000 + (dwDestination & 0xFFFF);
	dwAddress[2] = 0x7D6903A6;
	dwAddress[3] = 0x4E800420 | (bLinked ? 1 : 0);
}

void Hooking::HookFunctionStart(DWORD* dwAddress, DWORD* dwSaveStub, DWORD dwDestination) {
	if ((dwSaveStub != NULL) && (dwAddress != NULL)) {
		DWORD AddressRelocation = (DWORD)(&dwAddress[4]);

		if (AddressRelocation & 0x8000) {
			dwSaveStub[0] = 0x3D600000 + (((AddressRelocation >> 16) & 0xFFFF) + 1);
		} else {
			dwSaveStub[0] = 0x3D600000 + ((AddressRelocation >> 16) & 0xFFFF);
		}

		dwSaveStub[1] = 0x396B0000 + (AddressRelocation & 0xFFFF);
		dwSaveStub[2] = 0x7D6903A6;

		for (int i = 0; i < 4; i++) {
			if ((dwAddress[i] & 0x48000003) == 0x48000001) {
				dwSaveStub[i + 3] = RelinkGPLR((dwAddress[i] & ~0x48000003), &dwSaveStub[i + 3], &dwAddress[i]);
			} else {
				dwSaveStub[i + 3] = dwAddress[i];
			}
		}

		dwSaveStub[7] = 0x4E800420;
		__dcbst(0, dwSaveStub);
		__sync();
		__isync();

		PatchInJump(dwAddress, dwDestination);
	} else {
		DbgPrint("FAILED TO HOOK!");
	}
}

void Hooking::Unhook(DWORD dwAddress) {
	for (int i = 0; i < vHookContext.size(); i++) {
		if (dwAddress == vHookContext.at(i).dwAddress) {
			memcpy((void*)vHookContext.at(i).dwAddress, vHookContext.at(i).szAsm, vHookContext.at(i).nWriteSize);
			DbgPrint("Unhooked: Address=0x%X", vHookContext.at(i).dwAddress);
			break;
		}
	}
}

void Hooking::UnhookAll() {
	for (int i = 0; i < vHookContext.size(); i++) {
		memcpy((void*)vHookContext.at(i).dwAddress, vHookContext.at(i).szAsm, vHookContext.at(i).nWriteSize);
		DbgPrint("Unhooked: Address=0x%X", vHookContext.at(i).dwAddress);
	}
}

void BranchHooking::Branch(DWORD dwFrom, DWORD dwTo) {
	DWORD jump = decryptDWORD(Not(NiNJA.pPatches)->BF3.dwBranchHookLoc) + (dwHookCount * 0x14);
	DWORD* jumper = (DWORD*)(jump);
	dwHookCount++;

	pHooking.PatchInJump(jumper, dwTo);
	jumper[4] = 0x4e800020;

	HookContext cxt;
	cxt.dwAddress = dwFrom;
	cxt.nWriteSize = 0x4;
	memcpy(cxt.szAsm, (void*)dwFrom, 0x4);

	vHookContext.push_back(cxt);

	*(DWORD*)dwFrom = (dwFrom > jump) ? 0x4C000000 - (dwFrom - jump) + 1 : jump - dwFrom + 0x48000000 + 1;
}

void BranchHooking::Unhook(DWORD dwAddress) {
	for (int i = 0; i < vHookContext.size(); i++) {
		if (dwAddress == vHookContext.at(i).dwAddress) {
			memcpy((void*)vHookContext.at(i).dwAddress, vHookContext.at(i).szAsm, vHookContext.at(i).nWriteSize);
			DbgPrint("Unhooked: Address=0x%X", vHookContext.at(i).dwAddress);
			break;
		}
	}
}

void BranchHooking::UnhookAll() {
	for (int i = 0; i < vHookContext.size(); i++) {
		memcpy((void*)vHookContext.at(i).dwAddress, vHookContext.at(i).szAsm, vHookContext.at(i).nWriteSize);
		DbgPrint("Unhooked: Address=0x%X", vHookContext.at(i).dwAddress);
	}
}