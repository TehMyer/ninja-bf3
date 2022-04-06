#pragma once
#include "menu/handler/submenu.h"

class ChatMessageMenu : public Submenu {
public:
	static ChatMessageMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ChatMessageMenu() : Submenu() {}
	~ChatMessageMenu();
};

namespace ChatMessageMenuVars
{
	struct Vars {
		bool bCustomKillFeedKill;
		bool bCustomKillFeedDeath;

		int iChannelType;
		int iMessageType;
	};

	extern Vars vars;
}