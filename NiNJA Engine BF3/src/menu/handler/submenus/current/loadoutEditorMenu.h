#pragma once
#include "menu/handler/submenu.h"

class LoadoutEditorMenu : public Submenu {
public:
	static LoadoutEditorMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadoutEditorMenu() : Submenu() {}
	~LoadoutEditorMenu();
};

namespace LoadoutEditorMenuVars
{
	struct Vars {
		DWORD szWeaponAssets[400];
	};

	extern Vars vars;
}