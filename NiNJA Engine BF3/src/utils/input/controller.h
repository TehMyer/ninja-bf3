#pragma once

struct GamePadState {
	bool bIsDown;
	bool bWasJustPressed;
	bool bWasJustDown;

	inline void Reset() {
		bIsDown = false;
		bWasJustDown = false;
	}
};

enum eGamepadButtons {
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,
	START,
	BACK,
	LEFT_THUMB,
	RIGHT_THUMB,
	LEFT_SHOULDER,
	RIGHT_SHOULDER,
	A,
	B,
	X,
	Y,
	LEFT_TRIGGER,
	RIGHT_TRIGGER,
};

class Controller {
public:
	GamePadState PadState[16];
	bool bLeftBypass, bRightBypass, bUpBypass, bDownBypass, bABypass, bBBypass, bLBBypass, bRBBypass;
	bool bCanFly;
	int FlyThumb;
	
	void Update(XINPUT_STATE* state);
	bool WasJustPressed(int nKey);
	bool IsDown(int nKey);
};

extern Controller pController;

bool IsDown(int nKey);
bool IsJustPressed(int nKey);