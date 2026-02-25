// dllmain.cpp : Defines the entry point for the library application.

#include "PlatformConfig.h"
#include "stdio.h"

#if (GM_TARGET_PLATFORM == GM_PLATFORM_WIN32)

  #include <windows.h>

  // #############################################################################################
  //
  // We don't really use this, but you can if it helps......
  //
  // #############################################################################################
  BOOL APIENTRY DllMain(HMODULE hModule,
                        DWORD ul_reason_for_call,
                        LPVOID lpReserved) {
    switch (ul_reason_for_call) {
      case DLL_PROCESS_ATTACH:
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
  }

#endif  // GM_TARGET_PLATFORM == GM_PLATFORM_WIN32