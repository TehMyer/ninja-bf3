#pragma once
#include "../submenus/mainMenu.h"
#include "../submenus/currentGameMenu.h"
#include "../submenus/weaponMenu.h"
#include "../submenus/aimbotMenu.h"
#include "../submenus/visualMenu.h"
#include "../submenus/clientMenu.h"
#include "../submenus/settingsMenu.h"

#define TAB_COUNT 7

static bool IsOptionPressed() {
	return IsJustPressed(A);
}

static bool IsOpenPressed() {
	return IsDown(LEFT_TRIGGER) && IsDown(DPAD_LEFT); // fix sebs shit
}

static void Up() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption--;
	if (pMenu.iScrollOffset > 0 && pMenu.iCurrentOption - pMenu.iScrollOffset == -1) pMenu.iScrollOffset--;
	pMenu.iBreakScroll = 1;

	pMenu.bShouldUpdateDrawToggles = true;
}

static void Down() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption++;
	if (pMenu.iScrollOffset < pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions && pMenu.iCurrentOption - pMenu.iScrollOffset == pMenu.iMaxOptions) pMenu.iScrollOffset++;
	if (pSubmenuHandler.GetTotalOptions() >= pMenu.iMaxOptions && pMenu.iScrollOffset > pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions) pMenu.iScrollOffset = pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions;
	pMenu.iBreakScroll = 2;

	pMenu.bShouldUpdateDrawToggles = true;
}

static void Bottom() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption = pSubmenuHandler.GetTotalOptions() - 1;
	if (pSubmenuHandler.GetTotalOptions() >= pMenu.iMaxOptions) pMenu.iScrollOffset = pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions;
	pMenu.iBreakScroll = 3;

	pMenu.bShouldUpdateDrawToggles = true;
}

static void Top() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption = 0;
	pMenu.iScrollOffset = 0;
	pMenu.iBreakScroll = 4;

	pMenu.bShouldUpdateDrawToggles = true;
}

static void MenuControls() {
	pMenu.bFastPressLeft = false;
	pMenu.bFastPressRight = false;

	pMenu.bFastPressLeft = IsDown(DPAD_LEFT);
	pMenu.bFastPressRight = IsDown(DPAD_RIGHT);

	static int timers[10];

	// up
	if (GetTickCount() - timers[0] > 100) {
		timers[0] = GetTickCount();

		if (IsDown(DPAD_UP)) {
			if (pMenu.iCurrentOption == 0) {
				Bottom();
			} else {
				Up();
			}
		}
	}

	// down
	if (GetTickCount() - timers[1] > 100) {
		timers[1] = GetTickCount();

		if (IsDown(DPAD_DOWN)) {
			if (pMenu.iCurrentOption == pSubmenuHandler.GetTotalOptions() - 1) {
				Top();
			} else {
				Down();
			}
		}
	}

	// left bumper
	if (IsJustPressed(LEFT_SHOULDER)) {
		if (pMenu.IsOpen()) {
			pMenu.iCurrentOption = 0;
			pMenu.iScrollOffset = 0;
			pMenu.iSelectedTab--;
			pMenu.iSelectedTab = pMenu.iSelectedTab < 0 ? (TAB_COUNT - 1) : pMenu.iSelectedTab;

			switch (pMenu.iSelectedTab) {
			case 0: pSubmenuHandler.SetSubmenu(MainMenu::GetInstance()); break;
			case 1: pSubmenuHandler.SetSubmenu(CurrentGameMenu::GetInstance()); break;
			case 2: pSubmenuHandler.SetSubmenu(WeaponMenu::GetInstance()); break;
			case 3: pSubmenuHandler.SetSubmenu(AimbotMenu::GetInstance()); break;
			case 4: pSubmenuHandler.SetSubmenu(VisualMenu::GetInstance()); break;
			case 5: pSubmenuHandler.SetSubmenu(ClientMenu::GetInstance()); break;
			case 6: pSubmenuHandler.SetSubmenu(SettingsMenu::GetInstance()); break;
			}
		}
	}

	// RIGHT bumper
	if (IsJustPressed(RIGHT_SHOULDER)) {
		if (pMenu.IsOpen()) {
			pMenu.iCurrentOption = 0;
			pMenu.iScrollOffset = 0;
			pMenu.iSelectedTab++;
			pMenu.iSelectedTab = pMenu.iSelectedTab > (TAB_COUNT - 1) ? 0 : pMenu.iSelectedTab;

			switch (pMenu.iSelectedTab) {
			case 0: pSubmenuHandler.SetSubmenu(MainMenu::GetInstance()); break;
			case 1: pSubmenuHandler.SetSubmenu(CurrentGameMenu::GetInstance()); break;
			case 2: pSubmenuHandler.SetSubmenu(WeaponMenu::GetInstance()); break;
			case 3: pSubmenuHandler.SetSubmenu(AimbotMenu::GetInstance()); break;
			case 4: pSubmenuHandler.SetSubmenu(VisualMenu::GetInstance()); break;
			case 5: pSubmenuHandler.SetSubmenu(ClientMenu::GetInstance()); break;
			case 6: pSubmenuHandler.SetSubmenu(SettingsMenu::GetInstance()); break;
			}
		}
	}

	if (IsJustPressed(B)) {
		pSubmenuHandler.SetSubmenuPrevious(false);
	}
}
