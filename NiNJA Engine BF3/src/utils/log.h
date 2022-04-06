#pragma once

#ifdef DEBUG
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define DbgPrint(x, ...) { printf("[%s %s::%s] -> "  x  "\n", __GAMENAME__,  __FILENAME__, __FUNCTION__, __VA_ARGS__); }

static void printBytes(PBYTE bytes, DWORD len) {
	if (!bytes) return;
	for (DWORD i = 0; i < len; i++) {
		if (i % 16 == 0 && i != 0) printf("\n");
		printf("%02X", bytes[i]);
	}
	printf("\n");
}

#else
#define DbgPrint
#define printBytes
#endif