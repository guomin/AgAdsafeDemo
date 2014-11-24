#include "StdAfx.h"
#include "WinHttpHook.h"

static CWinHttpHook * pHook = NULL;

void WinHttpInstallHooks(void)
{
	if(!pHook)
		pHook = new CWinHttpHook();
}

void WinHttpRemoveHook(void)
{
	if(pHook)
	{
		delete pHook;
		pHook = NULL;
	}
}

HINTERNET __stdcall WinHttpOpenW_Hook(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
	//
	lpszProxy = _T("http://127.0.0.1:8888");
	dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
	//

	HINTERNET ret = NULL;
	__try{
		if(pHook)
			ret = pHook->WinHttpOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}__except(1){}
	return ret;
}

HINTERNET __stdcall WinHttpOpenA_Hook(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags)
{
	//
	lpszProxy = "http://127.0.0.1:8888";
	dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
	//

	HINTERNET ret = NULL;
	__try{
		if(pHook)
			ret = pHook->WinHttpOpenA(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}__except(1){}
	return ret;
}

CWinHttpHook::CWinHttpHook()
{
	InitializeCriticalSection(&cs);

	//
	
	_WinHttpOpenW = hook.createHookByName("winhttp.dll", "WinHttpOpenW", WinHttpOpenW_Hook);
	_WinHttpOpenA = hook.createHookByName("winhttp.dll", "WinHttpOpenA", WinHttpOpenA_Hook);
}

CWinHttpHook::~CWinHttpHook()
{
	if (pHook == this)
	{
		pHook = NULL;
	}

	DeleteCriticalSection(&cs);
}

HINTERNET CWinHttpHook::WinHttpOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
	HINTERNET ret = NULL;

	if(_WinHttpOpenW)
	{
		ret = _WinHttpOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}

	return ret;
}

HINTERNET CWinHttpHook::WinHttpOpenA(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags)
{
	HINTERNET ret = NULL;

	if (_WinHttpOpenA)
	{
		ret = _WinHttpOpenA(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}

	return ret;
}
