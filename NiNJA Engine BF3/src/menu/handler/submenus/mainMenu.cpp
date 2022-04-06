#include "stdafx.h"
#include "mainMenu.h"
#include "main/movementMenu.h"
#include "main/warningMenu.h"
#include "main/chatMessageMenu.h"
#include "current/ordersMenu.h"
#include "settings/soundsMenu.h"
#include "current/loadoutEditorMenu.h"
#include "current/serverSettingMenu.h"

using namespace MainMenuVars;

namespace MainMenuVars {
	Vars vars;

	ScrollStruct<int> Presets[] = {
		//"Rage Railgun", 2,
		"Rage Snap Aim", 0,
		"Rage Silent Aim", 1,
		"Legit", 3,
		"Default", 4
	};

	string SplitToLastWord(const char* pStr) {
		string str(pStr);
		size_t found = str.find_last_of("//");

		if (found) {
			return str.substr(found + 1);
		}

		return pStr;
	}

	const char* GetReadableLevelName() {
		const char* pReturn = "Unknown";

		if (ValidPtr(pGame.GetClientGameContext())) {
			if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager)) {
				if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager->pGame)) {
					if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel)) {
						if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel->pLevelSetup)) {
							auto hash = pUtils.Joaat(SplitToLastWord(pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel->pLevelName).c_str());

							switch (hash) {
								case 0x6c1ae31f: return "Grand Bazaar";
								case 0x500f2b08: return "Teheran Highway";
								case 0x7c39a1a: return "Caspian Border";
								case 0xefe2ebc1: return "Seine Crossing";
								case 0xdda7c74b: return "Operation Firestorm";
								case 0xd350329c: return "Damavand Peak";
								case 0x182b3c51: return "Noshahr Canals";
								case 0x67998ee: return "Kharg Island";
								case 0xee4d9d2c: return "Operation Metro";
								case 0xc5d7e8b8: return "Gulf of Oman";
								case 0x7f39f22b: return "Bandar Desert";
								case 0x99a2a96c: return "Alborz Mountains";
								case 0x833ea7b2: return "Armored Shield";
								case 0x74511000: return "Death Valley";
								case 0x6617c495: return "Markaz Monolith";
								case 0x25b3c923: return "Azadi Palace";
								case 0xe725f4d0: return "Epicenter";
								case 0xa38787b1: return "Operation Riverside";
								case 0xd89771d0: return "Nebandan Flats";
								case 0xce555d4c: return "Kiasar Railroad";
								case 0x95116ad1: return "Sabalan Pipeline";
								case 0xb40dc524: return "Strike at Karkand";
								case 0x941a853e: return "Sharqi Peninsula";
								case 0xa59ca842: return "Wake Island";
								case 0x80f38321: return "Talah Market";
								case 0x9e566b72: return "Scrapmetal";
								case 0x88f4f808: return "Operation 925";
								case 0xd540309: return "Donya Fortress";
								case 0xcff87617: return "Ziba Tower";
							}

							pReturn = pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel->pLevelName;
						}
					}
				}
			}
		}

		return pReturn;
	}

	const char* GetReadableGameType() {
		const char* pReturn = "Unknown";

		if (ValidPtr(pGame.GetClientGameContext())) {
			if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager)) {
				if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager->pGame)) {
					if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel)) {
						if (ValidPtr(pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel->pLevelSetup)) {
							auto hash = pUtils.Joaat(pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel->pLevelSetup->pGameType);

							switch (hash) {
							case 0x49d75453: return "Conquest Large"; // ConquestLarge0
							case 0x9b7a2c62: return "Conquest Small"; // ConquestSmall0
							case 0x36657b42: return "Rush"; // RushLarge0
							case 0xd7794724: return "Squad Deathmatch"; // SquadDeathMatch0
							case 0x57b5297d: return "Team Deathmatch"; // TeamDeathMatch0
							case 0xd8d99758: return "Domination"; // Domination0
							case 0xee30604e: return "Air Superiority"; // AirSuperiority0
							case 0xe55554c7: return "Capture The Flag"; // CaptureTheFlag0
							case 0xe80f2c70: return "Defuse"; // Elimination0
							case 0xbc1e8e64: return "Obliteration"; // Obliteration
							case 0x6004b22e: return "Carrier Assault Large"; // CarrierAssaultLarge0
							case 0x7dba2323: return "Carrier Assault Small"; // CarrierAssaultSmall0
							case 0xcacb8b0c: return "Chain Link"; // Chainlink0
							case 0x8baa6b2b: return "Squad Obliteration"; // SquadObliteration0
							case 0x955c235c: return "Gun Master"; // GunMaster0
							case 0x8b490f36: return "Gun Master v2"; // GunMaster1
							case 0xe9946b5a: return "Squad Deathmatch v2"; // SquadDeathMatch1
							case 0x486e8af0: return "Team Deathmatch v2"; // TeamDeathMatch1
							}

							pReturn = pGame.GetClientGameContext()->pOnlineManager->pGame->pClientLevel->pLevelSetup->pGameType;
						}
					}
				}
			}
		}

		return pReturn;
	}

	void SetPreset() {
		switch (Presets[vars.iPreset].Result) {
			case 0: {
				AimbotMenuVars::vars.iAimbotType = 1;
				AimbotMenuVars::vars.iTargetBone = 7;
				AimbotMenuVars::vars.iMaxDistance = 300;
				AimbotMenuVars::vars.bAimRequried = true;
				AimbotMenuVars::vars.bLimitToFOV = false;
				AimbotMenuVars::vars.bDrawFOV = false;
				AimbotMenuVars::vars.fFOVRadius = 250.f;
				AimbotMenuVars::vars.iIngores = 0;
				AimbotMenuVars::vars.bAutoWall = true;
				AimbotMenuVars::vars.bAutoAim = false;
				AimbotMenuVars::vars.bAutoShoot = true;
				AimbotMenuVars::vars.iAutoShootDelay = 100;
				AimbotMenuVars::vars.bOffscreenTargeting = true;
				AimbotMenuVars::vars.bUnfair = true;
				AimbotMenuVars::vars.bVisibilityCheck = true;
				AimbotMenuVars::vars.bAimOnFriendlies = false;
				AimbotMenuVars::vars.bAimOnEnemies = true;
				AimbotMenuVars::vars.bAimOnVehicles = false;
				AimbotMenuVars::vars.bSpoofWeaponToTarget = false;
				AimbotMenuVars::vars.iSpoofWeapon = 0;

				vars.bDisableKillFeed = false;
				vars.bShowNiNJAWatermark = true;
				vars.bShowMenuInstructions = true;
				vars.bShowFrameRate = false;
				vars.bShowMapInfo = false;

				VisualMenuVars::vars.iBones = 3;
				VisualMenuVars::vars.iBoxes = 3;
				VisualMenuVars::vars.iBoxType = 2;
				VisualMenuVars::vars.iCrosshair = 2;
				VisualMenuVars::vars.iDistance = 0;
				VisualMenuVars::vars.iName = 2;
				VisualMenuVars::vars.iWeapon = 0;
				VisualMenuVars::vars.iHealth = 0;
				VisualMenuVars::vars.iOccupiedVehicles = 0;
				VisualMenuVars::vars.iSnapline = 0;
				VisualMenuVars::vars.iSnaplinePosition = 1;
				VisualMenuVars::vars.bSupplyCrates = false;
				VisualMenuVars::vars.bExplosives = false;
				VisualMenuVars::vars.bGrenades = false;
				VisualMenuVars::vars.bPickups = false;
				VisualMenuVars::vars.bVehicles = false;
				VisualMenuVars::vars.bShowAimbotInfo = true;

				WeaponMenuVars::vars.bNoRecoil = true;
				WeaponMenuVars::vars.bNoSway = true;
				WeaponMenuVars::vars.bNoBreath = true;
				WeaponMenuVars::vars.bNoSpread = true;
				WeaponMenuVars::vars.bNoParachuteConstraints = true;
				WeaponMenuVars::vars.bInstantHit = true;
				WeaponMenuVars::vars.bInstantKill = true;
				WeaponMenuVars::vars.bAlwaysHeadshot = false;
				WeaponMenuVars::vars.bLongerBulletLife = true;
				WeaponMenuVars::vars.bSelfHealGun = true;
				WeaponMenuVars::vars.bTeamHealGun = false;
				WeaponMenuVars::vars.bUnlimitedAmmo = true;
				WeaponMenuVars::vars.bAutoReload = false;

				ChatMessageMenuVars::vars.iChannelType = 0;
				ChatMessageMenuVars::vars.iMessageType = 0;
				ChatMessageMenuVars::vars.bCustomKillFeedDeath = false;
				ChatMessageMenuVars::vars.bCustomKillFeedKill = false;

				OrdersMenuVars::vars.bAlwaysOrder = false;
				OrdersMenuVars::vars.iOrder = 0;

				WarningMenuVars::vars.iProximity = 0;
				WarningMenuVars::vars.iAimAngle = 0;
				WarningMenuVars::vars.iVisible = 0;

				SoundsMenuVars::vars.bKillingSpree = true;
				SoundsMenuVars::vars.bKillingStreak = true;
				SoundsMenuVars::vars.iOnKill = 0;
				SoundsMenuVars::vars.iOnDeath = 0;

				VisualMenu::GetInstance()->FeatureUpdate();
				AimbotMenu::GetInstance()->FeatureUpdate();
				SettingsMenu::GetInstance()->UpdateOnce();
				SoundsMenu::GetInstance()->UpdateOnce();
				WeaponMenu::GetInstance()->FeatureUpdate();
				WeaponMenu::GetInstance()->UpdateOnce();
				ChatMessageMenu::GetInstance()->FeatureUpdate();
				ServerSettingMenu::GetInstance()->UpdateOnce();
				ServerSettingMenuVars::UpdateStuff();
				break;
			}
			case 1: {
				AimbotMenuVars::vars.iAimbotType = 2;
				AimbotMenuVars::vars.iTargetBone = 7;
				AimbotMenuVars::vars.iMaxDistance = 300;
				AimbotMenuVars::vars.bAimRequried = false;
				AimbotMenuVars::vars.bLimitToFOV = false;
				AimbotMenuVars::vars.bDrawFOV = false;
				AimbotMenuVars::vars.fFOVRadius = 250.f;
				AimbotMenuVars::vars.iIngores = 0;
				AimbotMenuVars::vars.bAutoWall = true;
				AimbotMenuVars::vars.bAutoAim = false;
				AimbotMenuVars::vars.bAutoShoot = true;
				AimbotMenuVars::vars.iAutoShootDelay = 10;
				AimbotMenuVars::vars.bOffscreenTargeting = true;
				AimbotMenuVars::vars.bUnfair = true;
				AimbotMenuVars::vars.bVisibilityCheck = true;
				AimbotMenuVars::vars.bAimOnFriendlies = false;
				AimbotMenuVars::vars.bAimOnEnemies = true;
				AimbotMenuVars::vars.bAimOnVehicles = false;
				AimbotMenuVars::vars.bSpoofWeaponToTarget = false;
				AimbotMenuVars::vars.iSpoofWeapon = 0;

				vars.bDisableKillFeed = false;
				vars.bShowNiNJAWatermark = true;
				vars.bShowMenuInstructions = true;
				vars.bShowFrameRate = false;
				vars.bShowMapInfo = false;

				VisualMenuVars::vars.iBones = 3;
				VisualMenuVars::vars.iBoxes = 3;
				VisualMenuVars::vars.iBoxType = 2;
				VisualMenuVars::vars.iCrosshair = 2;
				VisualMenuVars::vars.iDistance = 0;
				VisualMenuVars::vars.iName = 2;
				VisualMenuVars::vars.iWeapon = 0;
				VisualMenuVars::vars.iHealth = 0;
				VisualMenuVars::vars.iOccupiedVehicles = 0;
				VisualMenuVars::vars.iSnapline = 2;
				VisualMenuVars::vars.iSnaplinePosition = 1;
				VisualMenuVars::vars.bSupplyCrates = false;
				VisualMenuVars::vars.bExplosives = false;
				VisualMenuVars::vars.bGrenades = false;
				VisualMenuVars::vars.bPickups = false;
				VisualMenuVars::vars.bVehicles = false;
				VisualMenuVars::vars.bShowAimbotInfo = true;

				WeaponMenuVars::vars.bNoRecoil = true;
				WeaponMenuVars::vars.bNoSway = true;
				WeaponMenuVars::vars.bNoBreath = true;
				WeaponMenuVars::vars.bNoSpread = true;
				WeaponMenuVars::vars.bNoParachuteConstraints = true;
				WeaponMenuVars::vars.bInstantHit = true;
				WeaponMenuVars::vars.bInstantKill = true;
				WeaponMenuVars::vars.bAlwaysHeadshot = false;
				WeaponMenuVars::vars.bLongerBulletLife = true;
				WeaponMenuVars::vars.bSelfHealGun = true;
				WeaponMenuVars::vars.bTeamHealGun = false;
				WeaponMenuVars::vars.bUnlimitedAmmo = true;
				WeaponMenuVars::vars.bAutoReload = false;

				ChatMessageMenuVars::vars.iChannelType = 0;
				ChatMessageMenuVars::vars.iMessageType = 0;
				ChatMessageMenuVars::vars.bCustomKillFeedDeath = false;
				ChatMessageMenuVars::vars.bCustomKillFeedKill = false;

				OrdersMenuVars::vars.bAlwaysOrder = false;
				OrdersMenuVars::vars.iOrder = 0;

				WarningMenuVars::vars.iProximity = 0;
				WarningMenuVars::vars.iAimAngle = 0;
				WarningMenuVars::vars.iVisible = 0;

				SoundsMenuVars::vars.bKillingSpree = true;
				SoundsMenuVars::vars.bKillingStreak = true;
				SoundsMenuVars::vars.iOnKill = 0;
				SoundsMenuVars::vars.iOnDeath = 0;

				VisualMenu::GetInstance()->FeatureUpdate();
				AimbotMenu::GetInstance()->FeatureUpdate();
				SettingsMenu::GetInstance()->UpdateOnce();
				WeaponMenu::GetInstance()->FeatureUpdate();
				WeaponMenu::GetInstance()->UpdateOnce();
				SoundsMenu::GetInstance()->UpdateOnce();
				MovementMenu::GetInstance()->FeatureUpdate();
				ChatMessageMenu::GetInstance()->FeatureUpdate();
				ServerSettingMenu::GetInstance()->UpdateOnce();
				ServerSettingMenuVars::UpdateStuff();
				break;
			}
			case 2: {
				AimbotMenuVars::vars.iAimbotType = 2;
				AimbotMenuVars::vars.iTargetBone = 1;
				AimbotMenuVars::vars.iMaxDistance = 2000;
				AimbotMenuVars::vars.bAimRequried = false;
				AimbotMenuVars::vars.bLimitToFOV = false;
				AimbotMenuVars::vars.bDrawFOV = false;
				AimbotMenuVars::vars.fFOVRadius = 250.f;
				AimbotMenuVars::vars.iIngores = 0;
				AimbotMenuVars::vars.bAutoWall = true;
				AimbotMenuVars::vars.bAutoAim = false;
				AimbotMenuVars::vars.bAutoShoot = true;
				AimbotMenuVars::vars.iAutoShootDelay = 0;
				AimbotMenuVars::vars.bOffscreenTargeting = true;
				AimbotMenuVars::vars.bUnfair = true;
				AimbotMenuVars::vars.bVisibilityCheck = false;
				AimbotMenuVars::vars.bAimOnFriendlies = false;
				AimbotMenuVars::vars.bAimOnEnemies = true;
				AimbotMenuVars::vars.bAimOnVehicles = false;
				AimbotMenuVars::vars.bSpoofWeaponToTarget = false;
				AimbotMenuVars::vars.iSpoofWeapon = 0;

				vars.bDisableKillFeed = false;
				vars.bShowNiNJAWatermark = true;
				vars.bShowMenuInstructions = true;
				vars.bShowFrameRate = false;
				vars.bShowMapInfo = false;

				VisualMenuVars::vars.iBones = 3;
				VisualMenuVars::vars.iBoxes = 3;
				VisualMenuVars::vars.iBoxType = 2;
				VisualMenuVars::vars.iCrosshair = 2;
				VisualMenuVars::vars.iDistance = 0;
				VisualMenuVars::vars.iName = 2;
				VisualMenuVars::vars.iWeapon = 0;
				VisualMenuVars::vars.iHealth = 0;
				VisualMenuVars::vars.iOccupiedVehicles = 0;
				VisualMenuVars::vars.iSnapline = 2;
				VisualMenuVars::vars.iSnaplinePosition = 1;
				VisualMenuVars::vars.bSupplyCrates = false;
				VisualMenuVars::vars.bExplosives = false;
				VisualMenuVars::vars.bGrenades = false;
				VisualMenuVars::vars.bPickups = false;
				VisualMenuVars::vars.bVehicles = false;
				VisualMenuVars::vars.bShowAimbotInfo = true;

				WeaponMenuVars::vars.bNoRecoil = true;
				WeaponMenuVars::vars.bNoSway = true;
				WeaponMenuVars::vars.bNoBreath = true;
				WeaponMenuVars::vars.bNoSpread = true;
				WeaponMenuVars::vars.bNoParachuteConstraints = true;
				WeaponMenuVars::vars.bInstantHit = true;
				WeaponMenuVars::vars.bInstantKill = true;
				WeaponMenuVars::vars.bAlwaysHeadshot = false;
				WeaponMenuVars::vars.bLongerBulletLife = true;
				WeaponMenuVars::vars.bSelfHealGun = true;
				WeaponMenuVars::vars.bTeamHealGun = false;
				WeaponMenuVars::vars.bUnlimitedAmmo = true;
				WeaponMenuVars::vars.bAutoReload = false;

				ChatMessageMenuVars::vars.iChannelType = 0;
				ChatMessageMenuVars::vars.iMessageType = 0;
				ChatMessageMenuVars::vars.bCustomKillFeedDeath = false;
				ChatMessageMenuVars::vars.bCustomKillFeedKill = false;

				OrdersMenuVars::vars.bAlwaysOrder = false;
				OrdersMenuVars::vars.iOrder = 0;

				WarningMenuVars::vars.iProximity = 0;
				WarningMenuVars::vars.iAimAngle = 0;
				WarningMenuVars::vars.iVisible = 0;

				SoundsMenuVars::vars.bKillingSpree = true;
				SoundsMenuVars::vars.bKillingStreak = true;
				SoundsMenuVars::vars.iOnKill = 0;
				SoundsMenuVars::vars.iOnDeath = 0;

				VisualMenu::GetInstance()->FeatureUpdate();
				AimbotMenu::GetInstance()->FeatureUpdate();
				SettingsMenu::GetInstance()->UpdateOnce();
				WeaponMenu::GetInstance()->FeatureUpdate();
				WeaponMenu::GetInstance()->UpdateOnce();
				SoundsMenu::GetInstance()->UpdateOnce();
				MovementMenu::GetInstance()->FeatureUpdate();
				ChatMessageMenu::GetInstance()->FeatureUpdate();
				ServerSettingMenu::GetInstance()->UpdateOnce();
				ServerSettingMenuVars::UpdateStuff();
				break;
			}
			case 3: { // legit
				AimbotMenuVars::vars.iAimbotType = 3;
				AimbotMenuVars::vars.iTargetBone = 1;
				AimbotMenuVars::vars.iMaxDistance = 100;
				AimbotMenuVars::vars.bAimRequried = true;
				AimbotMenuVars::vars.bLimitToFOV = true;
				AimbotMenuVars::vars.bDrawFOV = true;
				AimbotMenuVars::vars.fFOVRadius = 200.f;
				AimbotMenuVars::vars.iIngores = 3;
				AimbotMenuVars::vars.bAutoWall = false;
				AimbotMenuVars::vars.bAutoAim = false;
				AimbotMenuVars::vars.bAutoShoot = false;
				AimbotMenuVars::vars.iAutoShootDelay = 100;
				AimbotMenuVars::vars.bOffscreenTargeting = false;
				AimbotMenuVars::vars.bUnfair = true;
				AimbotMenuVars::vars.bVisibilityCheck = true;
				AimbotMenuVars::vars.bAimOnFriendlies = false;
				AimbotMenuVars::vars.bAimOnEnemies = true;
				AimbotMenuVars::vars.bAimOnVehicles = false;
				AimbotMenuVars::vars.bSpoofWeaponToTarget = false;
				AimbotMenuVars::vars.iSpoofWeapon = 0;

				vars.bDisableKillFeed = false;
				vars.bShowNiNJAWatermark = true;
				vars.bShowMenuInstructions = true;
				vars.bShowFrameRate = false;
				vars.bShowMapInfo = false;

				VisualMenuVars::vars.iBones = 3;
				VisualMenuVars::vars.iBoxes = 3;
				VisualMenuVars::vars.iBoxType = 2;
				VisualMenuVars::vars.iCrosshair = 2;
				VisualMenuVars::vars.iDistance = 0;
				VisualMenuVars::vars.iName = 2;
				VisualMenuVars::vars.iWeapon = 0;
				VisualMenuVars::vars.iHealth = 0;
				VisualMenuVars::vars.iOccupiedVehicles = 0;
				VisualMenuVars::vars.iSnapline = 0;
				VisualMenuVars::vars.iSnaplinePosition = 1;
				VisualMenuVars::vars.bSupplyCrates = false;
				VisualMenuVars::vars.bExplosives = false;
				VisualMenuVars::vars.bGrenades = false;
				VisualMenuVars::vars.bPickups = false;
				VisualMenuVars::vars.bVehicles = false;
				VisualMenuVars::vars.bShowAimbotInfo = true;

				WeaponMenuVars::vars.bNoRecoil = true;
				WeaponMenuVars::vars.bNoSway = true;
				WeaponMenuVars::vars.bNoBreath = true;
				WeaponMenuVars::vars.bNoSpread = true;
				WeaponMenuVars::vars.bNoParachuteConstraints = true;
				WeaponMenuVars::vars.bInstantHit = true;
				WeaponMenuVars::vars.bInstantKill = false;
				WeaponMenuVars::vars.bAlwaysHeadshot = false;
				WeaponMenuVars::vars.bLongerBulletLife = true;
				WeaponMenuVars::vars.bSelfHealGun = true;
				WeaponMenuVars::vars.bTeamHealGun = false;
				WeaponMenuVars::vars.bUnlimitedAmmo = true;
				WeaponMenuVars::vars.bAutoReload = false;

				ChatMessageMenuVars::vars.iChannelType = 0;
				ChatMessageMenuVars::vars.iMessageType = 0;
				ChatMessageMenuVars::vars.bCustomKillFeedDeath = false;
				ChatMessageMenuVars::vars.bCustomKillFeedKill = false;

				OrdersMenuVars::vars.bAlwaysOrder = false;
				OrdersMenuVars::vars.iOrder = 0;

				WarningMenuVars::vars.iProximity = 0;
				WarningMenuVars::vars.iAimAngle = 0;
				WarningMenuVars::vars.iVisible = 0;

				SoundsMenuVars::vars.bKillingSpree = true;
				SoundsMenuVars::vars.bKillingStreak = true;
				SoundsMenuVars::vars.iOnKill = 0;
				SoundsMenuVars::vars.iOnDeath = 0;

				VisualMenu::GetInstance()->FeatureUpdate();
				AimbotMenu::GetInstance()->FeatureUpdate();
				SettingsMenu::GetInstance()->UpdateOnce();
				SoundsMenu::GetInstance()->UpdateOnce();
				WeaponMenu::GetInstance()->FeatureUpdate();
				WeaponMenu::GetInstance()->UpdateOnce();
				ChatMessageMenu::GetInstance()->FeatureUpdate();
				ServerSettingMenu::GetInstance()->UpdateOnce();
				ServerSettingMenuVars::UpdateStuff();
				break;
			}
			case 4: { // default
				AimbotMenuVars::vars.iAimbotType = 3;
				AimbotMenuVars::vars.iTargetBone = 1;
				AimbotMenuVars::vars.fSmoothScale = 1.f;
				AimbotMenuVars::vars.iMaxDistance = 300;
				AimbotMenuVars::vars.bAimRequried = false;
				AimbotMenuVars::vars.bLimitToFOV = false;
				AimbotMenuVars::vars.bDrawFOV = false;
				AimbotMenuVars::vars.fFOVRadius = 250.f;
				AimbotMenuVars::vars.iIngores = 0;
				AimbotMenuVars::vars.bAutoWall = false;
				AimbotMenuVars::vars.bAutoAim = false;
				AimbotMenuVars::vars.bAutoShoot = false;
				AimbotMenuVars::vars.iAutoShootDelay = 100;
				AimbotMenuVars::vars.bOffscreenTargeting = false;
				AimbotMenuVars::vars.bUnfair = false;
				AimbotMenuVars::vars.bVisibilityCheck = false;
				AimbotMenuVars::vars.bAimOnFriendlies = false;
				AimbotMenuVars::vars.bAimOnEnemies = false;
				AimbotMenuVars::vars.bAimOnVehicles = false;
				AimbotMenuVars::vars.bSpoofWeaponToTarget = false;
				AimbotMenuVars::vars.iSpoofWeapon = 0;

				vars.bDisableKillFeed = false;
				vars.bShowNiNJAWatermark = true;
				vars.bShowMenuInstructions = true;
				vars.bShowFrameRate = false;
				vars.bShowMapInfo = false;

				VisualMenuVars::vars.iBones = 0;
				VisualMenuVars::vars.iBoxes = 0;
				VisualMenuVars::vars.iBoxType = 0;
				VisualMenuVars::vars.iCrosshair = 0;
				VisualMenuVars::vars.iDistance = 0;
				VisualMenuVars::vars.iName = 0;
				VisualMenuVars::vars.iWeapon = 0;
				VisualMenuVars::vars.iHealth = 0;
				VisualMenuVars::vars.iOccupiedVehicles = 0;
				VisualMenuVars::vars.iSnapline = 0;
				VisualMenuVars::vars.iSnaplinePosition = 0;
				VisualMenuVars::vars.bSupplyCrates = false;
				VisualMenuVars::vars.bExplosives = false;
				VisualMenuVars::vars.bGrenades = false;
				VisualMenuVars::vars.bPickups = false;
				VisualMenuVars::vars.bVehicles = false;
				VisualMenuVars::vars.bShowAimbotInfo = false;

				WeaponMenuVars::vars.bNoRecoil = false;
				WeaponMenuVars::vars.bNoSway = false;
				WeaponMenuVars::vars.bNoBreath = false;
				WeaponMenuVars::vars.bNoSpread = false;
				WeaponMenuVars::vars.bNoParachuteConstraints = false;
				WeaponMenuVars::vars.bInstantHit = false;
				WeaponMenuVars::vars.bInstantKill = false;
				WeaponMenuVars::vars.bAlwaysHeadshot = false;
				WeaponMenuVars::vars.bLongerBulletLife = false;
				WeaponMenuVars::vars.bSelfHealGun = false;
				WeaponMenuVars::vars.bTeamHealGun = false;
				WeaponMenuVars::vars.bUnlimitedAmmo = false;
				WeaponMenuVars::vars.bAutoReload = false;

				ChatMessageMenuVars::vars.iChannelType = 0;
				ChatMessageMenuVars::vars.iMessageType = 0;
				ChatMessageMenuVars::vars.bCustomKillFeedDeath = false;
				ChatMessageMenuVars::vars.bCustomKillFeedKill = false;

				OrdersMenuVars::vars.bAlwaysOrder = false;
				OrdersMenuVars::vars.iOrder = 0;

				WarningMenuVars::vars.iProximity = 0;
				WarningMenuVars::vars.iAimAngle = 0;
				WarningMenuVars::vars.iVisible = 0;

				SoundsMenuVars::vars.bKillingSpree = true;
				SoundsMenuVars::vars.bKillingStreak = true;
				SoundsMenuVars::vars.iOnKill = 0;
				SoundsMenuVars::vars.iOnDeath = 0;

				VisualMenu::GetInstance()->FeatureUpdate();
				AimbotMenu::GetInstance()->FeatureUpdate();
				SettingsMenu::GetInstance()->UpdateOnce();
				SoundsMenu::GetInstance()->UpdateOnce();
				WeaponMenu::GetInstance()->FeatureUpdate();
				WeaponMenu::GetInstance()->UpdateOnce();
				ChatMessageMenu::GetInstance()->FeatureUpdate();
				ServerSettingMenu::GetInstance()->UpdateOnce();
				ServerSettingMenuVars::UpdateStuff();
				break;
			}
		}
	}
}

void MainMenu::Init() {
	SetName("Main");

	vars.bShowMenuInstructions = true;

	addOption(ScrollOption<int>(SCROLLSELECT, "Preset").canLoop()
		.addScroll(vars.iPreset, 0, NUMOF(Presets) - 1, Presets)
		.addFunction(SetPreset)
		.addTooltip("Welcome to NiNJA Engine! To get started \nwith the best settings for you, choose a \npreset that best describes your play style!"));

	addOption(SubmenuOption("Movement")
		.addSubmenu<MovementMenu>()
		.addTooltip("Options based on modifying your movement."));

	addOption(SubmenuOption("Chat Messages")
		.addSubmenu<ChatMessageMenu>()
		.addTooltip("Sends a message in the chat, either one of \nour presets or your own inputted message."));

	addOption(SubmenuOption("Warnings")
		.addSubmenu<WarningMenu>()
		.addTooltip("Shows you a warning on screen on an \nevent."));

	addOption(ToggleOption("Disable Killfeed")
		.addToggle(vars.bDisableKillFeed)
		.addTooltip("Disables the killfeed on the top right."));

	addOption(ToggleOption("Show Engine Logo")
		.addToggle(vars.bShowNiNJAWatermark)
		.addTooltip("Displays the NiNJA Engine logo in the top \nleft corner."));

	addOption(ToggleOption("Show FPS")
		.addToggle(vars.bShowFrameRate)
		.addTooltip("Displays the current FPS in the top left \ncorner."));

	addOption(ToggleOption("Show Map Info")
		.addToggle(vars.bShowMapInfo)
		.addTooltip("Displays the current mapname, gametype \nand server type in the top left corner."));

	addOption(ToggleOption("Show Menu Instructions")
		.addToggle(vars.bShowMenuInstructions)
		.addTooltip("Displays instructions on how to open the \nmenu."));

	addOption(ButtonOption("Unload Engine")
		.addFunction([] { NiNJA.bTerminateProcess = true; })
		.addTooltip("Unload the engine."));
}

/*Update once when submenu is opened*/
void MainMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MainMenu::Update() {}

/*Background update*/
void MainMenu::FeatureUpdate() {
	if (vars.bShowMenuInstructions) {
		if (!pMenu.IsOpen()) {
			pDrawText.DrawOptionTextBoldCenterAlignWithBox("Press D-LEFT & LT to open NiNJA Engine", -4.f, 640.f, 30.f, 14.f, GColor(255, 255, 255, 255), GColor(0, 0, 0, 150));
		}
	}

	int displayIndex = 0;

	if (vars.bShowNiNJAWatermark) {
		pDrawText.DrawOptionTextWithBox("NiNJA Engine v1.0.0 - RELEASE CANDIDATE", 20.f, 30.f + (displayIndex * 25.f), 16.f, GColor(255, 255, 255, 255), GColor(0, 0, 0, 150), false);
		displayIndex++;
	}

	if (vars.bShowMapInfo) {
		auto gameType = GetReadableGameType();
		if (strcmp(gameType, "Unknown")) {
			auto levelName = GetReadableLevelName();
			if (strcmp(levelName, "Unknown")) {
				pDrawText.DrawOptionTextWithBox(pUtils.va("Playing %s on %s", gameType, levelName), 20.f, 30.f + (displayIndex * 25.f), 16.f, GColor(255, 255, 255, 255), GColor(0, 0, 0, 150), false);
				displayIndex++;
			}
		}

		if (*(DWORD*)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwServerInfo)) {
			auto base = *(DWORD*)decryptDWORD(Not(NiNJA.pPatches)->BF3.dwServerInfo);
			if (base) {
				base += 0x17C;
				auto next = *(DWORD*)(base + 0x44);
				if (next) {
					DWORD again = *(DWORD*)(next + 0xC);
					if (again) {
						DWORD yesAgain = *(DWORD*)(again + 0x4);
						if (yesAgain) {
							auto str = (char*)yesAgain;
							if (!str || strlen(str) <= 2) {
								str = "[DICE]";
							}

							pDrawText.DrawOptionTextWithBox(pUtils.va("Server Name: %s", str), 20.f, 30.f + (displayIndex * 25.f), 16.f, GColor(255, 255, 255, 255), GColor(0, 0, 0, 150), false);
							displayIndex++;
						}
					}
				}
			}
		}
	}

	if (vars.bShowFrameRate) {
		static float fps;
		static int timer;

		auto context = pGame.GetClientGameContext();
		if (ValidPtr(context)) {
			auto manager = context->pOnlineManager;
			if (ValidPtr(manager)) {
				auto connection = manager->pConnection;
				if (ValidPtr(connection)) {
					if (GetTickCount() - timer > 1000) {
						timer = GetTickCount();
						fps = *(float*)((DWORD)connection + 0x2E5C);
					}
				}
			}
		}

		pDrawText.DrawOptionTextWithBox(pUtils.va("FPS: %.0f", fps), 20.f, 30.f + (displayIndex * 25.f), 16.f, GColor(255, 255, 255, 255), GColor(0, 0, 0, 150), false);
		displayIndex++;
	}
}

/*Singleton*/
MainMenu* _instance;
MainMenu* MainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MainMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
MainMenu::~MainMenu() { DbgPrint("Destructed"); delete _instance; }