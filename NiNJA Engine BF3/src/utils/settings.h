#pragma once

#define RELEASE_VERSION
#define DEBUG

#define __GAMENAME__ "BF3"

//#define DUMP_BINS

#ifdef RELEASE_VERSION
#undef DEBUG
#define PATCH_SVR
#define ANTIHACK
#endif

#define GetTitleId() (XamGetCurrentTitleId() ^ 0x690690)
#define __TITLEID__ 0x45280FC0 // 0x45410950 ^ 0x690690
#define __MSGRIDENT__ 0x69458CE3 // Unique XBLSMsgr ID, must be 4 bytes of data (should be completely random)
#define __TIMEDATESTAMP__ 0x50C2F865 // The timestamp for the latest default.xex/default_mp.xex for this game, grabbed from PLDR_DATA_TABLE_ENTRY->TimeDateStamp

#define JOIN_LEFT_DWORD(left, dwordVal) ((left << 16) | ((dwordVal & 0xFFFF0000) >> 16))
#define JOIN_RIGHT_DWORD(right, dwordVal) ((right << 16) | (((dwordVal & 0x0000FFFF) << 16) >> 16))