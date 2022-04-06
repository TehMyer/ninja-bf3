#include "stdafx.h"

Controller pController;

void Controller::Update(XINPUT_STATE* pState) {
	PadState[A].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_A) || bABypass;
	PadState[X].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_X);
	PadState[Y].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_Y);
	PadState[B].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_B) || bBBypass;
	PadState[DPAD_UP].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) || bUpBypass;
	PadState[DPAD_DOWN].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) || bDownBypass;
	PadState[DPAD_LEFT].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) || bLeftBypass;
	PadState[DPAD_RIGHT].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) || bRightBypass;
	PadState[START].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_START);
	PadState[BACK].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
	PadState[LEFT_THUMB].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	PadState[RIGHT_THUMB].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
	PadState[LEFT_SHOULDER].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) || bLBBypass;
	PadState[RIGHT_SHOULDER].bIsDown = (pState->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) || bRBBypass;
	PadState[LEFT_TRIGGER].bIsDown = pState->Gamepad.bLeftTrigger >= 125;
	PadState[RIGHT_TRIGGER].bIsDown = pState->Gamepad.bRightTrigger >= 125;

	for (int i = 0; i < 16; i++) {
		PadState[i].bWasJustPressed = !PadState[i].bWasJustDown && PadState[i].bIsDown;
		PadState[i].bWasJustDown = PadState[i].bIsDown;
	}

	bABypass = false;
	bBBypass = false;
	bDownBypass = false;
	bLeftBypass = false;
	bRightBypass = false;
	bUpBypass = false;
	bLBBypass = false;
	bRBBypass = false;
}

bool Controller::WasJustPressed(int nKey) {
	return PadState[nKey].bWasJustPressed;
}

bool Controller::IsDown(int nKey) {
	return PadState[nKey].bIsDown;
}

bool IsDown(int key) {
	return pController.IsDown(key);
}

bool IsJustPressed(int key) {
	return pController.WasJustPressed(key);
}