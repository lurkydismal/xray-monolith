//-----------------------------------------------------------------------------
// File: x_ray_winmain.cpp
//
// Programmers:
// Oles - Oles Shishkovtsov
// AlexMX - Alexander Maksimchuk
//-----------------------------------------------------------------------------
#include "stdafx.h"

extern "C" void XR_EARLY_INIT();

int APIENTRY WinMain_impl(HINSTANCE hInstance,
                          HINSTANCE hPrevInstance,
                          char* lpCmdLine,
                          int nCmdShow);

// Translates stack-overflow structured exceptions into an executable handler path.
int stack_overflow_exception_filter(int exception_code)
{
	if (exception_code == EXCEPTION_STACK_OVERFLOW)
	{
		// Do not call _resetstkoflw here, because
		// at this point, the stack is not yet unwound.
		// Instead, signal that the handler (the __except block)
		// is to be executed.
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
		return EXCEPTION_CONTINUE_SEARCH;
}

//extern BOOL DllMainOpenAL32(HANDLE module, DWORD reason, LPVOID reserved);
extern BOOL DllMainXrCore(HANDLE hinstDLL, DWORD ul_reason_for_call, LPVOID lpvReserved);
extern BOOL DllMainXrPhysics(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);

//extern BOOL DllMainXrGame(HANDLE hModule, u32 ul_reason_for_call, LPVOID lpReserved);
//
//extern BOOL DllMainXrRenderR1(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
//extern BOOL DllMainXrRenderR2(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
//extern BOOL DllMainXrRenderR3(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);
//extern BOOL DllMainXrRenderR4(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

// Owns process-level startup and shutdown before entering the engine main loop.
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     char* lpCmdLine,
                     int nCmdShow)
{
    // Initialize LuaJIT low-memory pool FIRST, before any DLLs load and fragment
	// the lower 2GB address space.
	XR_EARLY_INIT();

	// Enable per-monitor DPI awareness so GetMonitorInfo returns real pixel sizes.
	// Without this, monitors with different DPI scaling report wrong resolutions
	// (e.g. a 1920x1080 secondary monitor reports 2400x1290 when primary is at 125%).
	// Uses dynamic loading since _WIN32_WINNT is too old for these APIs.
	// Try Win10 1703+ API first, fall back to Win 8.1+ API, silently skip on Win 7 or older.
	{
		bool dpi_set = false;
		HMODULE user32 = GetModuleHandleA("user32.dll");
		if (user32)
		{
			typedef BOOL(WINAPI* pfnSetProcessDpiAwarenessContext)(HANDLE);
			auto fn = (pfnSetProcessDpiAwarenessContext)GetProcAddress(user32, "SetProcessDpiAwarenessContext");
			if (fn)
				dpi_set = fn(/*DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2*/ (HANDLE)-4) != FALSE;
		}
		if (!dpi_set)
		{
			HMODULE shcore = LoadLibraryA("Shcore.dll");
			if (shcore)
			{
				typedef HRESULT(WINAPI* pfnSetProcessDpiAwareness)(int);
				auto fn = (pfnSetProcessDpiAwareness)GetProcAddress(shcore, "SetProcessDpiAwareness");
				if (fn)
					fn(/*PROCESS_PER_MONITOR_DPI_AWARE*/ 2);
				FreeLibrary(shcore);
			}
		}
	}

	//DllMainOpenAL32(NULL, DLL_PROCESS_ATTACH, NULL);
	DllMainXrCore(NULL, DLL_PROCESS_ATTACH, NULL);
	DllMainXrPhysics(NULL, DLL_PROCESS_ATTACH, NULL);

	DllMainXrCore(NULL, DLL_THREAD_ATTACH, NULL);

	__try
	{
		WinMain_impl(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	__except (stack_overflow_exception_filter(GetExceptionCode()))
	{
		_resetstkoflw();
		FATAL("stack overflow");
	}

	DllMainXrPhysics(NULL, DLL_PROCESS_DETACH, NULL);
	DllMainXrCore(NULL, DLL_PROCESS_DETACH, NULL);
	//DllMainOpenAL32(NULL, DLL_PROCESS_DETACH, NULL);

	return (0);
}
