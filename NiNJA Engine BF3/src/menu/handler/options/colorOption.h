#pragma once

#include "menu/handler/submenu.h"

enum eColorOptionSelection {
	COLOR_R,
	COLOR_G,
	COLOR_B,
	COLOR_A,
	COLOR_PREVIEW
};

class ColorOption : public Option {
private:
	function<void()> FuncOnAction;
	function<void()> FuncCurrentOption;
	function<void()> FuncOnUpdate;

	Submenu* pSubmenu;
	bool bPreviewBox;

	GColor* pColor;
	GColor pDefColor;

	bool bCanBeSaved;
	string pConfigName;
public:
	ColorOption(const char* name) : Option(name), FuncOnAction([] {}), FuncOnUpdate([] {}), FuncCurrentOption([] {}), bPreviewBox(false), pSubmenu(nullptr) { bCanBeSaved = false; }

	ColorOption& addPreviewBox() {
		bPreviewBox = true;
		return *this;
	}

	ColorOption& addColor(GColor& color) {
		pDefColor = color;
		pColor = &color;
		return *this;
	}

	template<typename T>
	ColorOption& addSubmenu() {
		pSubmenu = T::GetInstance();
		return *this;
	}

	ColorOption& addFunction(function<void()> func) {
		FuncOnAction = func;
		return *this;
	}

	ColorOption& addOnUpdate(function<void()> func) {
		FuncOnUpdate = func;
		return *this;
	}

	ColorOption& addOnHover(function<void()> func) {
		FuncCurrentOption = func;
		return *this;
	}

	ColorOption& addRequirement(function<bool()> func) {
		FuncRequirement = func;
		return *this;
	}

	ColorOption& addTooltip(string tooltip) {
		Tooltip = tooltip;
		return *this;
	}

	void Render(int pos);
	void RenderSelected(int pos);
};