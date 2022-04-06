#pragma once
#include "menu/handler/submenu.h"

class OrdersMenu : public Submenu {
public:
	static OrdersMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	OrdersMenu() : Submenu() {}
	~OrdersMenu();
};

namespace OrdersMenuVars
{
	struct Vars {
		bool bAlwaysOrder;

		int iOrder;
	};

	extern Vars vars;
}