class Memory {
public:
	template<typename T>
	void Write(DWORD dwAddress, T value) {
		*(T*)dwAddress = value;
	}

	template<typename T>
	T Read(DWORD dwAddress) {
		return *(T*)dwAddress;
	}

	bool compare(const BYTE* pData, const BYTE* bMask, const char* sMask) {
		for (; *sMask; ++sMask, ++pData, ++bMask)
			if (*sMask == 'x' && *pData != *bMask)
				return false;
		return *sMask == NULL;
	}

	vector<DWORD> GetMemoryAddresses(const char* pSearchFor) {
		vector<DWORD> addresses;

		string mask;
		for (int i = 0; i < strlen(pSearchFor); i++) mask += "x";

		for (DWORD i = 0x30000000; i < 0x80000000; i++) {
			if (compare((BYTE *)(i), (BYTE *)mask.c_str(), mask.c_str())) {
				addresses.push_back(i);
			}
		}

		for (DWORD i = 0xC0000000; i < 0xE0000000; i++) {
			if (compare((BYTE *)(i), (BYTE *)mask.c_str(), mask.c_str())) {
				addresses.push_back(i);
			}
		}

		return addresses;
	}
};

extern Memory pMemory;