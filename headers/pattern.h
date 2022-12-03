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
patternData comboConvert(const char* byteArray);

// Get information from module
MODULEINFO ModuleInfo(const char* mod);

// Pattern scan
DWORD Scan(const char* pattern, const char* mask, int offset, MODULEINFO modInfo);

// Finding the offset from the address
DWORD ReadAddress(const char* mod, const char* pattern, const char* mask, int offset, int extra, bool rel);