#include "stdafx.h"
#include "loadoutEditorMenu.h"
#include "../currentGameMenu.h"

using namespace LoadoutEditorMenuVars;

namespace LoadoutEditorMenuVars {
	Vars vars;

	ScrollStruct<DWORD> Types[] = {
		"Primary", 0x0,
		"Secondary", 0x0,
		"Gadget 1", 0x0,
		"Gadget 2", 0x0,
		"Grenade", 0x0,
		"Knife", 0x0
	};

	SoldierWeaponUnlockAsset* SoldierWeaponUnlockAssetFromName(const char* pName) {
		for (int i = 0; i < 400; i++) {
			if (vars.szWeaponAssets[i] != 0) {
				auto asset = (SoldierWeaponUnlockAsset*)vars.szWeaponAssets[i];
				if (ValidPtr(asset)) {
					if (asset->pName) {
						if (!strcmp(asset->pName, pName)) {
							return asset;
						}
					}
				}
			}
		}

		return nullptr;
	}


}

void LoadoutEditorMenu::Init() {
	SetParentSubmenu<CurrentGameMenu>();
	SetName("Loadout Editor");


}

/*Update once when submenu is opened*/
void LoadoutEditorMenu::UpdateOnce() {
	int index = 0;

	auto ptr = pGame.GetResourceManager();
	if (ptr) {
		for (int i = 0; i < 50; i++) {
			auto comp = ptr->pCompartments[i];
			if (ValidPtr(comp)) {
				DWORD size = (comp->dwPtrToEndList - comp->dwPtrToFirstList) / 4;
				for (int j = 0; j < size; j++) {
					DWORD dwAddress = *(DWORD*)(comp->dwPtrToFirstList + (j * 4));
					if (dwAddress) {
						if (*(DWORD*)dwAddress == decryptDWORD(Not(NiNJA.pPatches)->BF3.dwSoldierWeaponUnlockAssetVTable)) {
							vars.szWeaponAssets[index] = dwAddress;
							index++;
						}
					}
				}
			}
		}
	}
}

/*Update while submenu is active*/
void LoadoutEditorMenu::Update() {}

/*Background update*/
void LoadoutEditorMenu::FeatureUpdate() {}

/*Singleton*/
LoadoutEditorMenu* _instance;
LoadoutEditorMenu* LoadoutEditorMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadoutEditorMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
LoadoutEditorMenu::~LoadoutEditorMenu() { delete _instance; }