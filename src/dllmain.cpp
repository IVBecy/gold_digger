#include <windows.h>
#include <iostream>
#include "scanner.h"

// Main opeartion thread
DWORD WINAPI mainThread(HMODULE hModule) {
    Scanner(); // --> Scanning
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;

}

// DLLMAIN
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        const auto thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainThread, hModule, 0, nullptr);
        if (thread) {
            CloseHandle(thread);
        };
    }
    return TRUE;
}