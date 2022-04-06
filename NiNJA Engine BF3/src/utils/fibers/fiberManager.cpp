#include "stdafx.h"

FiberManager pFiberManager;

void FiberManager::Init(const char* pName_) {
	if (bInitialized) return;
	ConvertThreadToFiber(nullptr);
	pName = pName_;
	pMainFiber = GetCurrentFiber();
	bInitialized = true;

	DbgPrint("[Threads] %s initialized", pName_);
}

struct FiberCallParams {
	function<void()> func;
	void* pMainFiber;
};

void WINAPI FiberHandler(LPVOID fiberParam) {
	FiberCallParams* arguments = (FiberCallParams*)fiberParam;

	while (!(NiNJA.bTerminateProcess || NiNJA.bShutdownCheats || NiNJA.bExternUnload)) {
		arguments->func();
		SwitchToFiber(arguments->pMainFiber);
	}
}

void FiberManager::AddFiber(const char* pName, function<void()> func) {
	FiberCallParams* args = new FiberCallParams();
	args->func = func;
	args->pMainFiber = pMainFiber;

	void* fiber = CreateFiber(NULL, FiberHandler, args);
	if (!fiber) {
		DbgPrint("Last error: %i", GetLastError());
		bool suc = false;
		for (int i = 0; i < 5; i++) {
			DbgPrint("[Threads] Failed to create %s fiber, retrying...", pName);
			fiber = CreateFiber(NULL, FiberHandler, args);
			if (fiber) { suc = true; break; }
		}

		if (!suc) {
			DbgPrint("[Threads] Failed to create %s fiber", pName);
			return;
		}
	}

	Fiber newFiber = Fiber(nullptr, fiber, pUtils.timeGetTime(), pName);
	Fibers.push_back(newFiber);

	for (auto& fiber = Fibers.begin(); fiber != Fibers.end(); ++fiber) {
		auto& nextFiber = fiber + 1;
		if (nextFiber != Fibers.end()) fiber->pNextFiber = &*nextFiber;
		else fiber->pNextFiber = &Fibers.front();
	}

	pCurrentFiber = &Fibers.front();
	DbgPrint("[Threads] Created %s fiber", pName);
}

void FiberManager::Tick() {
	if (!pCurrentFiber || !bInitialized) return;

	if (!(NiNJA.bTerminateProcess || NiNJA.bShutdownCheats || NiNJA.bExternUnload)) {
		for (int i = 0; i < Fibers.size(); i++) {
			if (pUtils.timeGetTime() >= Fibers[i].ulWakeTime) {
				if (Fibers[i].pFiber) {
					SwitchToFiber(Fibers[i].pFiber);
				}
			}
		}

		pCurrentFiber = pCurrentFiber->pNextFiber;
	}
}

void FiberManager::Sleep(unsigned long ulDelay) {
	auto& fiber = find_if(Fibers.begin(), Fibers.end(), [](const Fiber& fiber) -> bool { return fiber.pFiber == GetCurrentFiber(); });
	if (fiber != Fibers.end()) {
		fiber->ulWakeTime = pUtils.timeGetTime() + ulDelay;
		SwitchToFiber(pMainFiber);
	}
}

void FiberManager::GoToMainFiber() {
	SwitchToFiber(pMainFiber);
}

void FiberManager::Cleanup() {
	if (!bCleaned) {
		for (int i = 0; i < Fibers.size(); i++) {
			DeleteFiber(Fibers[i].pFiber);
			DbgPrint("[Threads] Deleted %s fiber", Fibers[i].pName);
		}

		bCleaned = true;
	}
}

void WAIT(unsigned long ulDelay) {
	pFiberManager.Sleep(ulDelay);
}