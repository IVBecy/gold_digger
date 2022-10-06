/*

Getting interfaces

*/
#pragma once
#include <windows.h>

typedef void* (__cdecl* tCreateInterface)(const char* name, int* retCode);

void* GetInterface(const char* interfaceName,const char* dll){
	tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandle(dll),"CreateInterface");
	int retCode = 0;
	void* interFace = CreateInterface(interfaceName,&retCode);
	return interFace;
};
