/*

Pattern scanning

*/
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

// Structure for pattern data when converting
struct patternData {
	char bytes[1000]{};
	char mask[1000]{};
};

// Generate mask and AOB from IDA styled patterns
patternData comboConvert(const char* byteArray) {
	patternData data{ };
	int j = 0;
	for (int i = 0; i < strlen(byteArray) - 1; i++) {
		if (byteArray[i] == '?') {
			data.mask[j] = '?';
			data.bytes[j] = (char)strtol("00", 0, 16);
			j++;
		}
		if (byteArray[i] != ' ' && byteArray[i + 1] != ' ') {
			data.mask[j] = 'x';
			data.bytes[j] = (char)strtol(&byteArray[i], 0, 16);
			j++;
		}
	}
	return data;
}

// Get information from module
MODULEINFO ModuleInfo(const char* mod) {
	MODULEINFO modInfo = { 0 };
	HMODULE hModule = GetModuleHandle(mod);
	if (hModule != 0) {
		GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
	}
	return modInfo;
};

// Pattern scan
DWORD Scan(const char* pattern, const char* mask, int offset, MODULEINFO modInfo) {
	DWORD base = (DWORD)modInfo.lpBaseOfDll;
	DWORD size = (DWORD)modInfo.SizeOfImage;
	DWORD patternLength = strlen(mask);

	// Loop over the module and look for the byte pattern
	for (int i = 0; i < size; i++){
		bool found = true;
		for (int j = 0; j < patternLength; j++){
			if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j)) {
				found = false;
				break;
			}
		}
		// Return address either with offset or by itself
		if (found){
			if (offset) {
				return (base + i + offset);
			}
			else {
				return (base + i);
			}
		}
	}
	return 0;
}

// Finding the offset from the address
DWORD ReadAddress(const char* mod, const char* pattern, const char* mask, int offset, int extra, bool rel) {
	MODULEINFO modInfo = ModuleInfo(mod);
	uintptr_t addr = Scan(pattern, mask, offset, modInfo);
	DWORD off = addr;

	// Check if offset is present
	if (off == 0) {
		return 0;
	}

	// Read address with any extra / relative values
	if (rel) {
		if (extra) {
			off = *(DWORD*)off - (DWORD)modInfo.lpBaseOfDll + extra;
		}
		else {
			off = *(DWORD*)off - (DWORD)modInfo.lpBaseOfDll;
		}
	}
	else {
		if (extra) {
			off = *(DWORD*)off + extra;
		}
		else {
			off  = *(DWORD*)off;
		}
	}
	return off;
}