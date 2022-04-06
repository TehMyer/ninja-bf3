#include "stdafx.h"
#include "ordersMenu.h"
#include "../currentGameMenu.h"

using namespace OrdersMenuVars;

namespace OrdersMenuVars {
	Vars vars;
	
	ScrollStruct<OrderType> Orders[] = {
		"Request Heal", OrderType_RequestHeal,
		"Let Me Heal", OrderType_LetMeHeal,
		"Request Ammo", OrderType_RequestAmmo,
		"Let Me Give Ammo", OrderType_LetMeGiveAmmo,
		"Let Me Repair", OrderType_LetMeRepair,
		"Request Ride", OrderType_RequestRide,
		"Go Go Go", OrderType_GoGoGo,
		"Follow Me", OrderType_FollowMe,
		"Negative", OrderType_Negative,
		"Sorry", OrderType_Sorry,
		"Thank You", OrderType_ThankYou,
		"Roger That", OrderType_RogerThat,
		"Need Backup", OrderType_NeedBackup,
	};

	void Send() {
		auto player = pGame.GetLocalPlayer();
		if (ValidPtr(player)) {
			auto controller = player->pControlledControllable;
			if (ValidPtr(controller)) {
				Invoke::Call<int>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwSendOrder), controller->GetClientSpottingTargetComponent(false), pGame.GetLocalPlayer(), Orders[vars.iOrder].Result);
			}
		}
	}
}

void OrdersMenu::Init() {
	SetParentSubmenu<CurrentGameMenu>();
	SetName("Orders");

	addOption(ScrollOption<OrderType>(SCROLLSELECT, "Order to Send").canLoop()
		.addScroll(vars.iOrder, 0, NUMOF(Orders) - 1, Orders)
		.addTooltip("Choose an Order to Send."));

	addOption(ButtonOption("Send Order")
		.addFunction(Send)
		.addTooltip("Sends the order once."));

	addOption(ToggleOption("Always Order")
		.addToggle(vars.bAlwaysOrder)
		.addTooltip("Always sends the order."));
}

/*Update once when submenu is opened*/
void OrdersMenu::UpdateOnce() {}

/*Update while submenu is active*/
void OrdersMenu::Update() {}

/*Background update*/
void OrdersMenu::FeatureUpdate() {
	if (vars.bAlwaysOrder) {
		static int timer = 0;
		if (GetTickCount() - timer > 2000) {
			timer = GetTickCount();
			Send();
		}
	}
}

/*Singleton*/
OrdersMenu* _instance;
OrdersMenu* OrdersMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new OrdersMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
OrdersMenu::~OrdersMenu() { delete _instance; }