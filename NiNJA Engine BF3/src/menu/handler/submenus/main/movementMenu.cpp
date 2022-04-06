#include "stdafx.h"
#include "movementMenu.h"
#include "../mainMenu.h"

using namespace MovementMenuVars;

namespace MovementMenuVars {
	Vars vars;
	
}

void MovementMenu::Init() {
	SetParentSubmenu<MainMenu>();
	SetName("Movement");

	vars.fFlyHackSpeed = 20.f;

	addOption(ToggleOption("Fly Mode")
		.addToggle(vars.bFlyHack)
		.addTooltip("Walk into the sky! You can also toggle this \nwithout the menu open by pressing LS & LT."));

	addOption(NumberOption<float>(SCROLL, "Fly Speed")
		.addNumber(vars.fFlyHackSpeed, "%.0f", 1.f).addMin(5.f).addMax(100.f).setScrollSpeed(10)
		.addTooltip("Changes the speed of the fly mode. Hold in \nLS to get a speed boost."));

	addOption(ToggleOption("Fly Toggle Bind")
		.addToggle(vars.bFlyHackBind)
		.addTooltip("Bind LS & LT to toggle fly mode."));
}

/*Update once when submenu is opened*/
void MovementMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MovementMenu::Update() {}

/*Background update*/
void MovementMenu::FeatureUpdate() {
	static int toggleTimer = 0;

	if (vars.bFlyHackBind) {
		if (IsDown(LEFT_THUMB) && IsDown(LEFT_TRIGGER)) {
			if (GetTickCount() - toggleTimer > 1500) {
				toggleTimer = GetTickCount();

				vars.bFlyHack ^= true;
			}
		}
	}
}

/*Singleton*/
MovementMenu* _instance;
MovementMenu* MovementMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MovementMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
MovementMenu::~MovementMenu() { delete _instance; }