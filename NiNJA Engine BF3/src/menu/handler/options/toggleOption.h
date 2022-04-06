#pragma once

class ToggleOption : public Option {
private:
	function<void()> FuncOnAction;
	function<void()> FuncCurrentOption;
	function<void()> FuncOnUpdate;

	bool* pBool;
	bool pDefBool;
	bool bCanBeSaved;
	string pConfigName;
public:
	ToggleOption(const char* name) : Option(name), FuncOnAction([] {}), FuncOnUpdate([] {}), FuncCurrentOption([] {}), pBool(nullptr) { bCanBeSaved = false; }

	ToggleOption &addToggle(bool& toggle) {
		pBool = &toggle;
		pDefBool = toggle;
		return *this;
	}

	ToggleOption& addFunction(function<void()> func) {
		FuncOnAction = func;
		return *this;
	}

	ToggleOption& addOnUpdate(function<void()> func) {
		FuncOnUpdate = func;
		return *this;
	}

	ToggleOption& addOnHover(function<void()> func) {
		FuncCurrentOption = func;
		return *this;
	}

	ToggleOption& addRequirement(function<bool()> func) {
		FuncRequirement = func;
		return *this;
	}

	ToggleOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	void Render(int pos);
	void RenderSelected(int pos);
};