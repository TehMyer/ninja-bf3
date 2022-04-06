#include "stdafx.h"

SystemHooks::SystemHooks() {
	bInitialized = false;
}

typedef void(*tExTerminateTitleProcess)(int);
tExTerminateTitleProcess OriginalExTerminateTitleProcess;
void ExTerminateTitleProcessHook(int r3) {
	DbgPrint("ExTerminateTitleProcess!");
	
	Terminate();

	OriginalExTerminateTitleProcess(0);
}

bool SystemHooks::Apply() {
	if (!bInitialized) {
		if (!pHooking.HookFunction(pUtils.ResolveFunction(GetModuleHandleA("xboxkrnl.exe"), 0x1A), &ExTerminateTitleProcessHook, &OriginalExTerminateTitleProcess)) {
			DbgPrint("Failed to hook ExTerminateTitleProcess! Cannot continue!");
			return false;
		}

		DbgPrint("Applied detours!");
		bInitialized = true;
		return true;
	} else {
		DbgPrint("System hooks already initialized!");
	}

	return false;
}

void SystemHooks::Remove() {
	if (bInitialized) {
		pHooking.Unhook(pUtils.ResolveFunction(GetModuleHandleA("xboxkrnl.exe"), 0x1A));

		bInitialized = FALSE;
	} else {
		DbgPrint("TitleHooks have not been initialized!");
	}
}