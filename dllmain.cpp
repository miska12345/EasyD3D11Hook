/*
Built by miska123\
Please feel free to use this code in your projects
Github: https://github.com/miska12345
*/

#include "framework.h"
#include "PolyHook/PolyHook.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d10.lib")

// Function declarations for D3DX
typedef HRESULT(__stdcall* tD3D11Present)(IDXGISwapChain* pThis, UINT uSyncInternal, UINT uFlags);
typedef HRESULT(__stdcall* tD3D11ResizeBuffer)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

HMODULE hMod;
HWND hwnd;

ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;

DWORD_PTR* pSwapChain_vtable;
DWORD_PTR* pContext_vtable;

tD3D11Present oD3D11Present;
tD3D11ResizeBuffer oD3D11ResizeBuffer;

std::shared_ptr<PLH::Detour> dx_detour;
std::shared_ptr<PLH::Detour> dx_rsbuffer;

BOOL a_init = FALSE;

D3DMenu Menu;

// Item/Folder status
// User may manipulate these values through menu
int Folder1 = 1;
int Item1 = 0;
int Item2 = 0;
int Item3 = 0;

int Folder2 = 1;
int Item4 = 0;
int Item5 = 0;

// D3D11 Renderer helper
std::shared_ptr<D3D11Renderer> render;

// for std::call_once
std::once_flag g_isInitialized;

WNDPROC prevWndProc;

VOID InitializeMenu() {
	Menu.AddFolder(L"General", &Folder1);
	Menu.AddOption(L"Wireframe", &Item1, &Folder1);
	Menu.AddOption(L"Disable Z_Buffer", &Item2, &Folder1);
	Menu.AddOption(L"Shader Filtering", &Item3, &Folder1);

	Menu.AddFolder(L"Debug", &Folder2);
	Menu.AddOption(L"Show Status", &Item4, &Folder2);
	Menu.AddOption(L"Force Update", &Item5, &Folder2);

	Menu.Color_Current = GREY;
	
	Menu.Color_On = GREEN;
	Menu.Color_Off = RED;
	Menu.Color_Font = WHITE;
	Menu.Color_Folder = ORANGE;
	Menu.Color_Tips = GREY2;

	Menu.Color_Background = Color(150, 0, 0, 0);
	Menu.Color_Line = Color(255, 0, 0, 255);
}

void ImplHookDX11_Present(ID3D11Device* device, ID3D11DeviceContext* ctx, IDXGISwapChain* swap_chain)
{
	Menu.DrawMenu();
	Menu.Navigation();
}

HRESULT __stdcall hkD3D11Present(IDXGISwapChain* pThis, UINT uSyncInternal, UINT uFlags) {
	std::call_once(g_isInitialized, [&]() {
		pThis->GetDevice(__uuidof(pDevice), reinterpret_cast<void**>(&pDevice));
		pDevice->GetImmediateContext(&pContext);
		render.reset(new D3D11Renderer(pThis));
		render->Initialize();
		Menu.InitMenu(render, L"Miska D3D11 Hook Base", 0, 25);
		InitializeMenu();
	});

	render->BeginScene();
	// Draw your stuff
	ImplHookDX11_Present(pDevice, pContext, pThis);
	// End drawing
	render->EndScene();
	return oD3D11Present(pThis, uSyncInternal, uFlags);
}

HRESULT __stdcall hkD3D11ResizeBuffer(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	return oD3D11ResizeBuffer(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

LRESULT CALLBACK hkWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		// You can catch windows events here...
	case WM_LBUTTONDOWN:
		break;
	}
	return CallWindowProc(prevWndProc, hwnd, uMsg, wParam, lParam);
}

DWORD __stdcall InitializeHook(HMODULE hModule) {
	hMod = hModule;
	hwnd = GetForegroundWindow();

	dx_detour.reset(new PLH::Detour);
	dx_rsbuffer.reset(new PLH::Detour);    

	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featureLevel, 1
		, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext)))
	{   
		MessageBox(hwnd, L"Failed to create directX device and swapchain!", L"uBoos?", MB_ICONERROR);
		return NULL;
	}

	pSwapChain_vtable = (DWORD_PTR*)pSwapChain;
	pSwapChain_vtable = (DWORD_PTR*)pSwapChain_vtable[0];

	// pContext_vtable = (DWORD_PTR*)pContext;
	// pContext_vtable = (DWORD_PTR*)pContext_vtable[0];

	dx_detour->SetupHook((BYTE*)pSwapChain_vtable[8], (BYTE*)hkD3D11Present);
	dx_detour->Hook();
	oD3D11Present = dx_detour->GetOriginal<tD3D11Present>();

	dx_rsbuffer->SetupHook((BYTE*)pSwapChain_vtable[13], (BYTE*)hkD3D11ResizeBuffer);
	dx_rsbuffer->Hook();
	oD3D11ResizeBuffer = dx_rsbuffer->GetOriginal<tD3D11ResizeBuffer>();

	prevWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)& hkWndProc);
	DWORD old_protect;
	VirtualProtect(hkD3D11Present, 2, PAGE_EXECUTE_READWRITE, &old_protect);

	do {
		Sleep(100);
	} while (!(GetAsyncKeyState(VK_DELETE) & 0x1));

	dx_detour->UnHook();
	dx_rsbuffer->UnHook();

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	FreeLibraryAndExitThread(hMod, 0);
	return S_OK;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitializeHook, hModule, NULL, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

