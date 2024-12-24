#include <ctime>
#include <stdio.h>
#include <windows.h>
#include "discord_rpc.h"

static const char* APPLICATION_ID = "1320912247551299585";
#define UPD_INTVL 5000

static DWORD WINAPI ThreadEntry(LPVOID lpParam) {
    char state[64];
    char details[64];

    Discord_Initialize(APPLICATION_ID, 0, 0, 0);

    DiscordRichPresence discord_presence;
    memset(&discord_presence, 0, sizeof(discord_presence));

    discord_presence.startTimestamp = std::time(nullptr);
    discord_presence.largeImageKey = "icon";
    //discord_presence.largeImageText = "Disney Infinity 1.0";

    discord_presence.state = "Playing Disney Infinity 1.0";
    //discord_presence.details = "test";

    details[0] = 0;

    while (1) {
        //discord_presence.state = "test";
        //discord_presence.details = "test";

        Discord_UpdatePresence(&discord_presence);
        Discord_RunCallbacks();
        Sleep(UPD_INTVL);
    }
}

extern "C" __declspec(dllexport)
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(0, 0, ThreadEntry, 0, 0, 0);
        break;
    case DLL_PROCESS_DETACH:
        Discord_Shutdown();
        break;
    }

    return 1;
}