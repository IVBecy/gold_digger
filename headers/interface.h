/* 

Getting interfaces

*/
#pragma once
#include <windows.h>

typedef void* (__cdecl* tCreateInterface)(const char* name, int* retCode);

void* GetInterface(const char* interfaceName, const char* dll);