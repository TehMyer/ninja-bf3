#include "stdafx.h"
#include "menu/handler/submenus/main/movementMenu.h"
#include "menu/handler/submenus/main/chatMessageMenu.h"
#include "menu/handler/submenus/settings/soundsMenu.h"

typedef DWORD(*tXamInputGetState)(int r3, int r4, XINPUT_STATE* state);
tXamInputGetState OriginalXamInputGetState;
DWORD XamInputGetStateHook(int r3, int r4, XINPUT_STATE* state) {
	DWORD ret = OriginalXamInputGetState(r3, r4, state);

	pController.Update(state);

	pController.bCanFly = state->Gamepad.sThumbLY >= 23000;
	pController.FlyThumb = state->Gamepad.sThumbLY;

	if (pGame.bReload) {
		pGame.bReload = false;

		static int lastReload = 0;
		if (GetTickCount() - lastReload > 5000) {
			lastReload = GetTickCount();
			state->Gamepad.wButtons &= XINPUT_GAMEPAD_X;
		}
	}

	if (pController.bCanFly) {
		if (MovementMenuVars::vars.bFlyHack) {
			state->Gamepad.sThumbLY = 0;
			state->Gamepad.sThumbLX = 0;
		}
	}

	if (pGame.bCanRun) {
		if (AimbotMenuVars::vars.bAimRequried && !pController.IsDown(LEFT_TRIGGER)) goto jJump;

		if (AimbotMenuVars::vars.iAimbotType
			&& ValidPtr(pGame.pAimbotPlayer)
			&& ValidPtr(pGame.pAimbotPlayer->GetClientSoldier())) {
			if (AimbotMenuVars::vars.bAutoAim) {
				state->Gamepad.bLeftTrigger = 255;
			}

			if (AimbotMenuVars::vars.bAutoShoot) {
				static int timer = 0;
				if (GetTickCount() - timer > AimbotMenuVars::vars.iAutoShootDelay) {
					timer = GetTickCount();
					state->Gamepad.bRightTrigger = 255;
				}
			}
		}

	jJump:
		if (pMenu.IsOpen() && !IsOpenPressed()) {
			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
				pController.bLeftBypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
				pController.bRightBypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
				pController.bUpBypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
				pController.bDownBypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
				pController.bABypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_LEFT_SHOULDER;
				pController.bLBBypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_RIGHT_SHOULDER;
				pController.bRBBypass = true;
			}

			if (state->Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				state->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
				pController.bBBypass = true;
			}
		}
	}

	return ret;
}

typedef int(*tRenderUI)(DWORD, float);
tRenderUI OriginalRenderUI;
DWORD RenderUIHook(DWORD r3, float r4) {
	if (pConfig.bShouldShowChangelog) {
		pConfig.bShouldShowChangelog = false;

		pGame.MessageBoxAccept("Welcome to Battlefield 3 with the NiNJA Engine!", pConfig.szChangelogData, PopupType_PrivacyPolicy);
	}

	static bool init = false;
	if (!init) {
		init = true;

		pRenderer.Init();
		pMenu.Init();
	}

	auto engine = pGame.GetUIEngine();
	if (engine && engine->pRenderer && engine->pDrawTextManager) {
		if (pGame.bCanRun) {
			pMenu.Render();
			if (pMenu.bOpen) pSubmenuHandler.Update();
			pSubmenuHandler.ASyncUpdate();
			pMenu.ASyncUpdate();
		}
	}

	return OriginalRenderUI(r3, r4);
}

typedef DWORD(*tTestRender)(DWORD r3, DWORD r4, DWORD r5, DWORD r6, float f1, float f2, DWORD r9, DWORD r10);
tTestRender OriginalTestRender;
DWORD TestRenderHook(DWORD r3, DWORD r4, DWORD r5, DWORD r6, float f1, float f2, DWORD r9, DWORD r10) {
	static bool test = false;
	if (!test) {
		test = true;

		DbgPrint("ExecValue: [saveGame] -> %s", Invoke::Call<const char*>(0x8304E5F0, "saveGame", "", nullptr));
		DbgPrint("ExecValue: [name] -> %s", Invoke::Call<const char*>(0x8304E5F0, "name", "", nullptr));
		DbgPrint("ExecValue: [listen] -> %s", Invoke::Call<const char*>(0x8304E5F0, "listen", "", nullptr));
		DbgPrint("ExecValue: [skipFastLevelLoad] -> %s", Invoke::Call<const char*>(0x8304E5F0, "skipFastLevelLoad", "0", nullptr));
		DbgPrint("ExecValue: [super] -> %s", Invoke::Call<const char*>(0x8304E5F0, "super", "", nullptr));
		DbgPrint("ExecValue: [instanceName] -> %s", Invoke::Call<const char*>(0x8304E5F0, "instanceName", "", nullptr));
		DbgPrint("ExecValue: [hostUserDomain] -> %s", Invoke::Call<const char*>(0x8304E5F0, "hostUserDomain", "DICE", nullptr));
		DbgPrint("ExecValue: [hostUser] -> %s", Invoke::Call<const char*>(0x8304E5F0, "hostUser", "DICEMONKEY", nullptr));
		DbgPrint("ExecValue: [host] -> %s", Invoke::Call<const char*>(0x8304E5F0, "host", "127.0.0.1", nullptr));
		DbgPrint("ExecValue: [dedicated] -> %s", Invoke::Call<const char*>(0x8304E5F0, "dedicated", "", nullptr));
		DbgPrint("ExecValue: [serverInstancePath] -> %s", Invoke::Call<const char*>(0x8304E5F0, "serverInstancePath", "", nullptr));
		DbgPrint("ExecValue: [level] -> %s", Invoke::Call<const char*>(0x8304E5F0, "level", "default", nullptr));
		DbgPrint("ExecValue: [branch] -> %s", Invoke::Call<const char*>(0x8304E5F0, "branch", "", nullptr));
		DbgPrint("ExecValue: [databaseId] -> %s", Invoke::Call<const char*>(0x8304E5F0, "databaseId", "", nullptr));
		DbgPrint("ExecValue: [url] -> %s", Invoke::Call<const char*>(0x8304E5F0, "url", "", nullptr));
	}

	if (pConfig.bShouldShowChangelog) {
		pConfig.bShouldShowChangelog = false;

		pGame.MessageBoxAccept("Welcome to Battlefield 3 with the NiNJA Engine!", pConfig.szChangelogData, PopupType_PrivacyPolicy);
	}

	static bool init = false;
	if (!init) {
		init = true;

		pRenderer.Init();
		pMenu.Init();
	}

	auto engine = pGame.GetUIEngine();
	if (engine && engine->pRenderer && engine->pDrawTextManager) {
		pTextRenderer.BeginText(engine->pRenderer, engine->pDrawTextManager, true, false);

		if (pGame.bCanRun) {
			pMenu.Render();
			pSubmenuHandler.ASyncUpdate();

			if (pMenu.bOpen) {
				pSubmenuHandler.Update();
			}

			pMenu.ASyncUpdate();
		}

		pTextRenderer.EndText(engine->pRenderer, engine->pDrawTextManager);
	}

	return OriginalTestRender(r3, r4, r5, r6, f1, f2, r9, r10);
}

Detour<DWORD> OriginalHijackRenderTexture;
DWORD HijackRenderTextureHook(DWORD r3, float f1) {
	DWORD ret = OriginalHijackRenderTexture.CallOriginal(r3, f1);
	
	if (!pShapes.bHasTexture) {
		pShapes.bHasTexture = true;
		DbgPrint("HIJACKED TEXTURE - ptr: %X", *(DWORD*)(r3 + 0x80));
		memcpy(pShapes.szTextureBuffer, (void*)(r3 + 0x80), 0x200);
	}

	return ret;
}

typedef DWORD(*tUpdatePosition)(void*, EntryInputStateNetworkMove*);
tUpdatePosition OriginalClientConnectionAddMove;
DWORD ClientConnectionAddMoveHook(void* pConnection, EntryInputStateNetworkMove* pState) {
	if (MovementMenuVars::vars.bFlyHack) {
		if (pController.bCanFly) {
			pState->State.dwCustomBitFlags += 2;

			float speed = 5.f + ((MovementMenuVars::vars.fFlyHackSpeed - 5.f) / (0x8000 - 23000)) * (pController.FlyThumb - 23000);

			if (IsDown(LEFT_THUMB))
				speed *= 1.5f;

			Vec3 shit = pUtils.MatrixToForward(pGame.GetGameRenderer()->ViewParams.Transform) * speed;
			shit.Negate();

			pState->State.VaultPosition += shit;
		} else {
			pState->State.dwCustomBitFlags += 2;
			pState->State.VaultPosition = Vec3();
		}
	}

	if (pState && AimbotMenuVars::vars.iAimbotType == 2) {
		if (ValidPtr(pGame.pAimbotPlayer)) {
			if (ValidPtr(pGame.GetMySoldierEntity())) {
				pState->State.AuthoritiveViewAngles = pAimbot.vSavedAngles;

				pAimbot.MovementFix(pState);

				auto wep = pGame.GetSoldierWeapon();
				if (ValidPtr(wep)) {
					auto swayHead = wep->pPredictedFiring;
					if (ValidPtr(swayHead)) {
						auto sway = swayHead->pWeaponSway;
						if (ValidPtr(sway)) {
							if ((DWORD)&sway->CurrentDispersionDeviation
								&& (DWORD)&sway->CurrentRecoilDeviation) {
								pState->State.AuthoritiveViewAngles.x += sway->CurrentDispersionDeviation.flYaw;
								pState->State.AuthoritiveViewAngles.y += sway->CurrentDispersionDeviation.flPitch;

								pState->State.AuthoritiveViewAngles.x += asinf(sway->CurrentRecoilDeviation.flYaw);
								pState->State.AuthoritiveViewAngles.y += asinf(sway->CurrentRecoilDeviation.flPitch);
							}
						}
					}
				}
			}
		}
	}

	return OriginalClientConnectionAddMove(pConnection, pState);
}

typedef void(*tUIMessageCompOnMessage)(DWORD* pThis, Message* pMessage);
tUIMessageCompOnMessage OriginalUIMessageCompOnMessage;
void UIMessageCompOnMessageHook(DWORD* pThis, Message* pMessage) {
	char* messages[] = {
		"I just wrecked",
		"My dad works at Microsoft",
		"I just shat on",
		"Shoulda bought NiNJA",
		"How does it feel?",
		"Why you heff to be mad, is just game",
		"Sorry, I'm too OP",
		"Yo praise the lord for ronins shit"
	};
	char* messagesDeath[] = {
		"I just got yeeted by",
		"My NiNJAs don't die we just vossi bop",
		"Small penis alert:",
		"Eat shoes",
		"Lucky shot"
	};

	if (pMessage->nType == -1957189686) {
		// CreateSelfKilledMessage

		UINetworkOwnPlayerKilledMessage* message = (UINetworkOwnPlayerKilledMessage*)pMessage;

		if (ChatMessageMenuVars::vars.bCustomKillFeedDeath) {
			if (ValidPtr(message)) {
				ClientPlayer* killer = Invoke::Call<ClientPlayer*>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwGetCreateKillMessageClient), message);
				if (ValidPtr(killer)) {
					if (ValidPtr(killer->pNamePtr)) {
						if (killer == pGame.GetLocalPlayer()) {
							pMessages.SendTextMessage(CctSayAll, CctAdmin, "NiNJAs don't die we just vossi bop");
						} else {
							pMessages.SendTextMessage(CctSayAll, CctAdmin, pUtils.va("%s %s", messagesDeath[pGame.iKillFeedRand[1]], killer->pNamePtr->szName));
						}

						if (SoundsMenuVars::vars.iOnDeath != 0) {
							if (ValidPtr(pGame.GetLocalPlayer()) && ValidPtr(killer)) {
								pSounds.QueueBF(SoundsMenuVars::SoundsTest[SoundsMenuVars::vars.iOnDeath].pName);
							}
						}
					}
				}
			}
		}

		if (MainMenuVars::vars.bDisableKillFeed) {
			return;
		}
	}

	if (pMessage->nType == -1963112840) {
		// CreateKilledOtherMessage

		UINetworkKilledOtherPlayerMessage* message = (UINetworkKilledOtherPlayerMessage*)pMessage;

		if (ChatMessageMenuVars::vars.bCustomKillFeedKill) {
			if (ValidPtr(message)) {
				ClientPlayer* victim = Invoke::Call<ClientPlayer*>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwGetCreateKillMessageClient), message);
				if (ValidPtr(victim)) {
					if (ValidPtr(victim->pNamePtr)) {
						if (ValidPtr(pGame.GetLocalPlayer())) {
							pMessages.SendTextMessage(CctSayAll, CctAdmin, pUtils.va("%s %s", messages[pGame.iKillFeedRand[0]], victim->pNamePtr->szName));
						}
					}
				}
			}
		}

		if (MainMenuVars::vars.bDisableKillFeed) {
			return;
		}
	}

	return OriginalUIMessageCompOnMessage(pThis, pMessage);
}

typedef void(*tAddDamageData)(void*, DamageData*);
tAddDamageData OriginalAddDamageData;
void AddDamageDataHook(void* pConnection, DamageData* pDamageData) {
	if (WeaponMenuVars::vars.bAlwaysHeadshot) {
		pDamageData->nHitType = 1;
	}

	if (ValidPtr(pGame.GetLocalPlayer())) {
		if (ValidPtr(pGame.GetLocalPlayer()->GetClientSoldier())) {
			if (ValidPtr(pGame.GetLocalPlayer()->GetClientSoldier()->pHealthModule)) {
				if (pGame.GetLocalPlayer()->IsAlive()) {
					auto wep = pGame.GetLocalPlayer()->GetClientSoldier()->GetSoldierWeapon();
					if (ValidPtr(wep)) {
						if (ValidPtr(wep->WeaponModifier.pCurrentSoldierWeaponUnlockAsset)) {
							pDamageData->pWeaponUnlockAsset = wep->WeaponModifier.pCurrentSoldierWeaponUnlockAsset;
						}
					}
				}
			}
		}
	}

	if (AimbotMenuVars::vars.bSpoofWeaponToTarget) {
		if (ValidPtr(pGame.pAimbotPlayer)) {
			if (ValidPtr(pGame.pAimbotPlayer->GetClientSoldier())) {
				if (ValidPtr(pGame.pAimbotPlayer->GetClientSoldier()->pHealthModule)) {
					if (pGame.pAimbotPlayer->IsAlive()) {
						auto wep = pGame.pAimbotPlayer->GetClientSoldier()->GetSoldierWeapon();
						if (ValidPtr(wep)) {
							if (ValidPtr(wep->WeaponModifier.pCurrentSoldierWeaponUnlockAsset)) {
								pDamageData->pWeaponUnlockAsset = wep->WeaponModifier.pCurrentSoldierWeaponUnlockAsset;
							}
						}
					}
				}
			}
		}
	}

	if (AimbotMenuVars::vars.iSpoofWeapon != 0) {
		auto soldier = pGame.GetMySoldierEntity();
		if (ValidPtr(soldier)) {
			auto comp = soldier->pSoldierWeaponsComponent;
			if (ValidPtr(comp)) {
				auto wep = comp->GetWeaponAtIndex(AimbotMenuVars::SpoofWeapons[AimbotMenuVars::vars.iSpoofWeapon].Result);
				if (ValidPtr(wep)) {
					pDamageData->pWeaponUnlockAsset = wep->WeaponModifier.pCurrentSoldierWeaponUnlockAsset;
				}
			}
		}
	}

	OriginalAddDamageData(pConnection, pDamageData);
}

typedef void(*tPrimaryFireCallback)(DWORD);
tPrimaryFireCallback OriginalPrimaryFireCallback;
void PrimaryFireCallbackHook(DWORD r3) {
	DWORD ptr = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwGetClientPlayerEntryPrimaryFire), r3 - 0x64);
	if (ptr) {
		ClientPlayer* shooter = (ClientPlayer*)*(DWORD*)(ptr + 0x128);
		if (ValidPtr(shooter)) {
			if (shooter == pGame.GetLocalPlayer()) {
				if (AimbotMenuVars::vars.bUnfair || AimbotMenuVars::vars.iAimbotType == 2) {
					if (ValidPtr(pGame.pAimbotPlayer)) {
						if (ValidPtr(pGame.pAimbotPlayer->GetClientSoldier())) {
							pPlayer.Kill(pGame.pAimbotPlayer);
						}
					}
				}

				if (WeaponMenuVars::vars.bSelfHealGun) {
					pPlayer.Heal(pGame.GetLocalPlayer());
				}

				if (WeaponMenuVars::vars.bTeamHealGun) {
					pGame.HealTeam();
				}
			}
		}
	}

	OriginalPrimaryFireCallback(r3);
}

typedef DWORD(*tAimbot)(DWORD, DWORD);
tAimbot OriginalAimbot;
DWORD AimbotHook(DWORD r3, DWORD r4) {
	DWORD resp = OriginalAimbot(r3, r4);

	if (pGame.bCanRun) {
		static int cached_kills = -1;
		static int cached_deaths = -1;
		static int cached_spree = 0;
		static int cached_streak = 0;
		static int cached_spree_timeout = 0;

		auto player = pGame.GetLocalPlayer();
		if (ValidPtr(player)) {
			auto soldier = player->GetClientSoldier();
			if (ValidPtr(soldier)) {
				auto wep = soldier->GetSoldierWeapon();
				if (ValidPtr(wep)) {
					auto firing = wep->pCorrectedFiring;
					if (!ValidPtr(firing)) {
						firing = wep->pPredictedFiring;
					}

					if (ValidPtr(firing)) {
						auto currentAmmo = firing->PrimaryFire.nAmmoInClip;
						auto ammoInPile = firing->PrimaryFire.nAmmoInReserve;

						if (WeaponMenuVars::vars.bAutoReload && !WeaponMenuVars::vars.bUnlimitedAmmo) {
							if (ammoInPile > 0) {
								if (currentAmmo == 0) {
									pGame.bReload = true;
								}
							}
						}

						if (WeaponMenuVars::vars.bUnlimitedAmmo) {
							if (currentAmmo == 0 && ammoInPile > 0) {
								static int timer = 0;
								if (GetTickCount() - timer > 2000) {
									timer = GetTickCount();

									DWORD ui = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUnlimitedAmmo[0]));
									if (ui) {
										DWORD r = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUnlimitedAmmo[1]), ui, decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUnlimitedAmmo[2]), 1);
										if (r) {
											DWORD r4 = Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUnlimitedAmmo[3]), pGame.GetLocalPlayer()->nTeam, Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUnlimitedAmmo[4])));
											Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUnlimitedAmmo[5]), r, r4, pGame.GetLocalPlayer(), 1, 1);
										}
									}
								}
							}
						}
					}
				}
			}

			if (ValidPtr(pGame.GetClientGameContext()->pClientPlayerScoreManager)) {
				auto manager = pGame.GetClientGameContext()->pClientPlayerScoreManager->GetPlayerScore(pGame.GetLocalPlayer());
				if (ValidPtr(manager)) {
					if (cached_kills == -1 || cached_deaths == -1) {
						cached_kills = manager->nKills;
						cached_deaths = manager->nDeaths;
					}

					if (manager->nKills > cached_kills) {
						cached_spree_timeout = GetTickCount();
						cached_kills++;
						cached_spree++;
						cached_streak++;

						if (SoundsMenuVars::vars.bKillingSpree) {
							pSounds.Queue(SOUND_KILLSPREE, cached_spree);
						}

						if (SoundsMenuVars::vars.bKillingStreak) {
							pSounds.Queue(SOUND_KILLSTREAK, cached_streak);
						}

						if (SoundsMenuVars::vars.iOnKill != 0) {
							pSounds.QueueBF(SoundsMenuVars::SoundsTest[SoundsMenuVars::vars.iOnKill].pName);
						}
					}

					if ((GetTickCount() - cached_spree_timeout) > 4500) {
						cached_spree = 0;
					}

					if (manager->nDeaths > cached_deaths) {
						cached_deaths = manager->nDeaths;
						cached_spree = 0;
						cached_streak = 0;
					}
				}
			}
		} else {
			cached_kills = -1;
			cached_deaths = -1;
			cached_spree = 0;
			cached_streak = 0;
			cached_spree_timeout = 0;
		}

		if (AimbotMenuVars::vars.iAimbotType != 0) {
			if (AimbotMenuVars::vars.bAimRequried && !pController.IsDown(LEFT_TRIGGER)) return resp;

			pGame.pAimbotPlayer = pAimbot.GetTarget(pGame.AimbotTargetInfo);

			if (ValidPtr(pGame.pAimbotPlayer) && ValidPtr(pGame.pAimbotPlayer->GetClientSoldier())) {
				auto weapon = pGame.GetSoldierWeapon();
				if (ValidPtr(weapon)) {
					if (ValidPtr(weapon->pAuthorativeAiming)) {
						if (ValidPtr(weapon->pAuthorativeAiming->pAimAssist)) {
							if (ValidPtr(pGame.GetMySoldierEntity())) {
								if (ValidPtr(pGame.GetMySoldierEntity()->pReplicatedController)) {
									auto mySoldier = pGame.GetMySoldierEntity();
									if (!ValidPtr(mySoldier)) return resp;

									if (!ValidPtr(pWeapon.GetBulletEntityData())) {
										DbgPrint("Can't execute aimbot logic, bulletentitydata isn't valid.");
										return resp;
									}

									if (!ValidPtr(pWeapon.GetFiringFunctionData())) {
										DbgPrint("Can't execute aimbot logic, firingfunctiondata isn't valid.");
										return resp;
									}

									pAimbot.vSavedAngles = pGame.BaseAimCorrection();

									if (pAimbot.vSavedAngles.x < 0.f) {
										pAimbot.vSavedAngles.x += M_PI * 2;
									}

									switch (AimbotMenuVars::vars.iAimbotType) {
									case 1: // normal (snap)
										if (ValidPtr(weapon) && ValidPtr(weapon->pAuthorativeAiming)) {
											if (ValidPtr(weapon->pAuthorativeAiming->pAimAssist)) {
												weapon->pAuthorativeAiming->pAimAssist->flYaw = pAimbot.vSavedAngles.x;
												weapon->pAuthorativeAiming->pAimAssist->flPitch = pAimbot.vSavedAngles.y;

												auto wep = pGame.GetSoldierWeapon();
												if (ValidPtr(wep)) {
													auto firing = wep->pPredictedFiring;
													if (ValidPtr(firing)) {
														auto sway = firing->pWeaponSway;
														if (ValidPtr(sway)) {
															weapon->pAuthorativeAiming->pAimAssist->flYaw += asinf(sway->CurrentRecoilDeviation.flYaw);
															weapon->pAuthorativeAiming->pAimAssist->flPitch += asinf(sway->CurrentRecoilDeviation.flPitch);
														}
													}
												}
											}
										}
										break;
									case 3: // humanized
										if (ValidPtr(weapon) && ValidPtr(weapon->pAuthorativeAiming)) {
											if (ValidPtr(weapon->pAuthorativeAiming->pAimAssist)) {
												Vec2 angles = pAimbot.SmoothAimbotAngles(Vec2(weapon->pAuthorativeAiming->pAimAssist->flYaw, weapon->pAuthorativeAiming->pAimAssist->flPitch), pAimbot.vSavedAngles);

												weapon->pAuthorativeAiming->pAimAssist->flYaw = angles.x;
												weapon->pAuthorativeAiming->pAimAssist->flPitch = angles.y;

												auto wep = pGame.GetSoldierWeapon();
												if (ValidPtr(wep)) {
													auto firing = wep->pPredictedFiring;
													if (ValidPtr(firing)) {
														auto sway = firing->pWeaponSway;
														if (ValidPtr(sway)) {
															weapon->pAuthorativeAiming->pAimAssist->flYaw += asinf(sway->CurrentRecoilDeviation.flYaw);
															weapon->pAuthorativeAiming->pAimAssist->flPitch += asinf(sway->CurrentRecoilDeviation.flPitch);
														}
													}
												}

												pGame.vOldAngles = Vec2(weapon->pAuthorativeAiming->pAimAssist->flYaw, weapon->pAuthorativeAiming->pAimAssist->flPitch);
											}
										}
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return resp;
}

typedef void(*tSomePhysicsFunction)(DWORD* r3, DWORD* r4, DWORD* r5, DWORD* r6);
tSomePhysicsFunction OriginalSomePhysicsFunction;
void SomePhysicsFunctionHook(DWORD* r3, DWORD* r4, DWORD* r5, DWORD* r6) {
	OriginalSomePhysicsFunction(r3, r4, r5, r6);

	if (AimbotMenuVars::vars.bAutoWall || AimbotMenuVars::vars.bVisibilityCheck) {
		if (pGame.bCanRun) {
			static int timer = 0;
			if (GetTickCount() - timer > 250) {
				timer = GetTickCount();

				pAimbot.ProcessAutoWall();
				// pAimbot.ProcessVisibility();
			}
		}
	}
}

bool TitleHooks::bInitialized = false;
bool TitleHooks::Apply() {
	if (!bInitialized) {
		// hook functions

		OriginalHijackRenderTexture.SetupDetour(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwHijackTexture), &HijackRenderTextureHook);

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwSomePhysics), &SomePhysicsFunctionHook, &OriginalSomePhysicsFunction)) {
			DbgPrint("Failed to hook SomePhysicsFunction!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwAimbot), &AimbotHook, &OriginalAimbot)) {
			DbgPrint("Failed to hook Aimbot!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwPrimaryFireCallback), &PrimaryFireCallbackHook, &OriginalPrimaryFireCallback)) {
			DbgPrint("Failed to hook PrimaryFireCallback!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwAddDamageData), &AddDamageDataHook, &OriginalAddDamageData)) {
			DbgPrint("Failed to hook AddDamageData!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwUIMessageCompOnMessage), &UIMessageCompOnMessageHook, &OriginalUIMessageCompOnMessage)) {
			DbgPrint("Failed to hook UIMessageCompOnMessage!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwClientConnectionAddMove), &ClientConnectionAddMoveHook, &OriginalClientConnectionAddMove)) {
			DbgPrint("Failed to hook ClientConnectionAddMove!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwXamInputGetState), &XamInputGetStateHook, &OriginalXamInputGetState)) {
			DbgPrint("Failed to hook XamInputGetState!");
			return false;
		}

		if (!pHooking.HookFunction(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwRenderUI), &RenderUIHook, &OriginalRenderUI)) {
			DbgPrint("Failed to hook RenderUI!");
			return false;
		}

		Sleep(1000);

		DbgPrint("Applied detours!");
		bInitialized = true;
		return true;
	} else {
		DbgPrint("TitleHooks already initialized!");
	}

	return false;
}

void TitleHooks::Remove(bool bOverride) {
	if (bInitialized || bOverride) {
		pHooking.UnhookAll();
		pBranchHooking.UnhookAll();
		OriginalHijackRenderTexture.TakeDownDetour();

		Sleep(1000);

		DbgPrint("Removed detours!");
		bInitialized = FALSE;
	} else {
		DbgPrint("TitleHooks have not been initialized!");
	}
}