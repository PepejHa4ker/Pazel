#include <Windows.h>
#include <thread>
#include <chrono>
#include "sdk/hack/hooks/hooks.h"


void on_unload(HINSTANCE mod) {
    g_console.release();
    hooks::detach();

    FreeLibraryAndExitThread(mod, EXIT_SUCCESS);
}

void on_attach(HINSTANCE mod) {
#ifdef _DEBUG
    g_console.initialize( _( "Pazel" ) );
#endif

    hooks::attach();

    // wait for unload key
    while (!(GetAsyncKeyState(VK_END) & 0x8000))
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    on_unload(mod);
}

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD call_reason, LPVOID reserved) {
    if (call_reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module_handle);
        CreateThread(0, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( on_attach ),
                     reinterpret_cast< HMODULE >( module_handle ), 0, 0);
    }

    return TRUE;
}