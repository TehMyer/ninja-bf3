#pragma once

class ButtonOption : public Option {
private:
	function<void()> FuncOnAction;
	function<void(const char*)> FuncOnActionWithArg;
	function<void()> FuncCurrentOption;
	function<void()> FuncOnUpdate;

	const char* pFuncArg;

	bool bHasKeyboard;
	function<void(const char*)> FuncKeyboardCallback;
public:
	ButtonOption(const char* name) : Option(name), bHasKeyboard(false), FuncOnActionWithArg([](const char*) {}), FuncOnAction([] {}), FuncCurrentOption([] {}), FuncOnUpdate([] {}) {}

	ButtonOption& addFunction(function<void()> func) {
		FuncOnAction = func;
		return *this;
	}

	ButtonOption& addFunctionArg(function<void(const char*)> func, const char* arg) {
		pFuncArg = arg;
		FuncOnActionWithArg = func;
		return *this;
	}

	ButtonOption& addOnUpdate(function<void()> func) {
		FuncOnUpdate = func;
		return *this;
	}

	ButtonOption& addOnHover(function<void()> func) {
		FuncCurrentOption = func;
		return *this;
	}

	ButtonOption& addRequirement(function<bool()> func) {
		FuncRequirement = func;
		return *this;
	}

	ButtonOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	ButtonOption& addKeyboard(void(*func)(const char* str)) {
		FuncKeyboardCallback = func;
		bHasKeyboard = true;
		return *this;
	}

	void Render(int pos);
	void RenderSelected(int pos);
};