// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <tchar.h>
#include <Imm.h>
#include <atlstr.h>
#pragma comment(lib, "Imm32.lib")

#include "InputMoniter.h"

HINSTANCE g_hHinstance = NULL;
HHOOK g_hHook;

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}
	if (nCode != HC_ACTION)
	{
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}

	if (!::FindWindow(0, _T("KeyBoard Locked")))
	{
		::MessageBox(0, _T("键盘锁定！"), _T("KeyBoard Locked"), MB_OK);
	}
	return 1;
}

BOOL EnableKeyboardCapture()
{
	if (!(g_hHook=SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)HookProc, g_hHinstance, 0)))
	{
		return FALSE;
	}
	return TRUE;
}
// 导出函数：解除键盘锁定
BOOL DisableKeyboardCapture()
{
	return UnhookWindowsHookEx(g_hHook);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	g_hHinstance = (HINSTANCE)hModule;
	return TRUE;
}

