#include "stdafx.h"
#include "colorEditorMenu.h"

using namespace ColorEditorMenuVars;

namespace ColorEditorMenuVars {
	Vars vars;
	
	void UpdateIt() {
		if (vars.pToUpdate) {
			*vars.pToUpdate = vars.ColorValue;
			vars.pToUpdate->R = (BYTE)(vars.ColorVals[0] * 255.f);
			vars.pToUpdate->G = (BYTE)(vars.ColorVals[1] * 255.f);
			vars.pToUpdate->B = (BYTE)(vars.ColorVals[2] * 255.f);
			vars.pToUpdate->A = (BYTE)(vars.ColorVals[3] * 255.f);

			vars.ColorValue = *vars.pToUpdate;
		}
	}
}

void ColorEditorMenu::Init() {
	// SetParentSubmenu<ColorMenu>();
	SetName("");

	addOption(NumberOption<float>(SCROLL, "Red")
		.addNumber(vars.ColorVals[0], "%.2f", 0.01f).addMin(0.f).addMax(1.0f).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Choose the amount of red in the final color."));

	addOption(NumberOption<float>(SCROLL, "Green")
		.addNumber(vars.ColorVals[1], "%.2f", 0.01f).addMin(0.f).addMax(1.0f).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Choose the amount of green in the final \ncolor."));

	addOption(NumberOption<float>(SCROLL, "Blue")
		.addNumber(vars.ColorVals[2], "%.2f", 0.01f).addMin(0.f).addMax(1.0f).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Choose the amount of blue in the final \ncolor."));

	addOption(NumberOption<float>(SCROLL, "Alpha")
		.addNumber(vars.ColorVals[3], "%.2f", 0.01f).addMin(0.f).addMax(1.0f).setScrollSpeed(20)
		.addFunction(UpdateIt)
		.addTooltip("Choose the transparency of the final color."));

	addOption(ColorOption("Preview")
		.addPreviewBox()
		.addColor(vars.ColorValue)
		.addTooltip("Shows what the color will look like before \nyou exit the menu."));
}

/*Update once when submenu is opened*/
void ColorEditorMenu::UpdateOnce() {
	if (vars.pToUpdate) {
		vars.ColorVals[0] = vars.pToUpdate->R / 255.f;
		vars.ColorVals[1] = vars.pToUpdate->G / 255.f;
		vars.ColorVals[2] = vars.pToUpdate->B / 255.f;
		vars.ColorVals[3] = vars.pToUpdate->A / 255.f;
	}
}

/*Update while submenu is active*/
void ColorEditorMenu::Update() {}

/*Background update*/
void ColorEditorMenu::FeatureUpdate() {}

/*Singleton*/
ColorEditorMenu* _instance;
ColorEditorMenu* ColorEditorMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ColorEditorMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
ColorEditorMenu::~ColorEditorMenu() { delete _instance; }