//
// Created by pepej on 09.06.2022.
//

#include "hooks.h"

void hooks::attach( ) {
    {
        IDXGISwapChain* swap_chin = nullptr;
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* context = nullptr;
        auto featureLevel = D3D_FEATURE_LEVEL_11_0;

        DXGI_SWAP_CHAIN_DESC sd = { 0 };
        sd.BufferCount = 1;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.OutputWindow = GetForegroundWindow( );
        sd.SampleDesc.Count = 1;
        sd.Windowed = TRUE;

        if( FAILED( D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swap_chin, &device, nullptr, &context ) ) ) {
            return;
        }

        auto table = *reinterpret_cast< void*** >( swap_chin );
        auto present = table[ 8 ];
        auto resize = table[ 13 ];

        context->Release( );
        device->Release( );
        swap_chin->Release( );

        MH_Initialize( );

        MH_CreateHook( present, (LPVOID)hk_present, reinterpret_cast< void** >( &hooks::o::present ) );
        MH_CreateHook( resize, (LPVOID)&hk_resize, reinterpret_cast< void** >( &hooks::o::resize ) );

        MH_EnableHook( MH_ALL_HOOKS );
    }
}

void hooks::detach( ) {
    // disable and remove our hooks
    MH_DisableHook( MH_ALL_HOOKS );
    MH_RemoveHook( MH_ALL_HOOKS );
    MH_Uninitialize( );

    // restore the original game wnd_proc
    SetWindowLongPtr( hooks::window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hooks::o::wnd_proc ));

    // de-initialize ImGui instance
    ImGui::DestroyContext( );
    ImGui_ImplWin32_Shutdown( );
    ImGui_ImplDX11_Shutdown( );
}