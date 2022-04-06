#include "stdafx.h"

Messages pMessages;

void Messages::SendTextMessage(ChatChannelType channelType, ChatChannelType messageType, const char* message) {
	NetworkChatMessage msg;
	msg.dwPlayerID = pGame.GetLocalPlayer()->nID;
	msg.bSenderIsDead = false;
	msg.RecipientMask = -1;
	msg.dwChannelID = messageType;

	switch (channelType) {
		case CctSayAll: {
			DbgPrint("Sending text message to everyone - %s", message);
			break;
		}

		case CctTeam: {
			if (pGame.GetLocalPlayer()) {
				DbgPrint("Sending text message to team - %s", message);
				msg.RecipientMask = pGame.GetLocalPlayer()->nTeam;
			}
			break;
		}
	}

	int textSize = strlen(message) + 1;
	wchar_t* wc = new wchar_t[textSize];
	mbstowcs(wc, message, textSize);

	wcscpy(msg.szBuffer, wc);

	msg.pBuffer = (wchar_t*)&msg.szBuffer;
	msg.pPos = msg.pBuffer;
	msg.pMax = &wc[strlen(message) - 1];

	Invoke::Call<DWORD>(decryptDWORD(Not(NiNJA.pPatches)->BF3.dwSendMessage), *(DWORD*)((DWORD)pGame.GetClientGameContext()->pOnlineManager->pConnection + 0x2E2C), &msg);

	delete[] wc;
}