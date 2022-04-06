#pragma once

class Submenu;

class SubmenuOption : public Option {
private:
	function<void()> FuncOnAction;
	function<void()> FuncCurrentOption;
	function<void()> FuncOnUpdate;

	Submenu* pSubmenu;

public:
	SubmenuOption(const char* name) : Option(name), pSubmenu(nullptr), FuncOnAction([] {}), FuncCurrentOption([] {}), FuncOnUpdate([] {}) {}

	template<typename T>
	SubmenuOption& addSubmenu() {
		pSubmenu = T::GetInstance();
		return *this;
	}

	SubmenuOption& addSubmenu(Submenu* submenu) {
		pSubmenu = submenu;
		return *this;
	}

	SubmenuOption& addFunction(function<void()> func) {
		FuncOnAction = func;
		return *this;
	}

	SubmenuOption& addOnUpdate(function<void()> func) {
		FuncOnUpdate = func;
		return *this;
	}

	SubmenuOption& addOnHover(function<void()> func) {
		FuncCurrentOption = func;
		return *this;
	}

	SubmenuOption& setVisible(bool visible) {
		bVisible = visible;
		return *this;
	}

	SubmenuOption& addName(const char* name) {
		strcpy(szName, name);
		return *this;
	}

	SubmenuOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	SubmenuOption& addRequirement(function<bool()> func) {
		FuncRequirement = func;
		return *this;
	}

	void Render(int pos);
	void RenderSelected(int pos);
};