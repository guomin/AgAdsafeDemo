#include "StdAfx.h"
#include "WinInetHook.h"
#include <WinInet.h>

static CWinInetHook * pHook = NULL;

void WinInetInstallHooks(void)
{
	if(!pHook)
		pHook = new CWinInetHook();
}

void WinInetRemoveHooks(void)
{
	if(pHook)
	{
		delete pHook;
		pHook = NULL;
	}
}

HINTERNET __stdcall InternetOpenW_Hook(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
	lpszProxy = _T("http://127.0.0.1:8888");
	dwAccessType = INTERNET_OPEN_TYPE_PROXY;

	HINTERNET ret = NULL;
	__try{
		if(pHook)
			ret = pHook->InternetOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}__except(1){}
	return ret;
}

HINTERNET __stdcall InternetOpenA_Hook(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags)
{
	//
	lpszProxy = "http://127.0.0.1:8888";
	dwAccessType = INTERNET_OPEN_TYPE_PROXY;
	//
	HINTERNET ret = NULL;
	__try{
		if(pHook)
			ret = pHook->InternetOpenA(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}__except(1){}
	return ret;
}

CWinInetHook::CWinInetHook(void):
hookOpenA(true)
{
	InitializeCriticalSection(&cs);

	//
	//parents.InitHashTable(257);

	_InternetOpenW = hook.createHookByName("wininet.dll", "InternetOpenW", InternetOpenW_Hook);
	_InternetOpenA = hook.createHookByName("wininet.dll", "InternetOpenA", InternetOpenA_Hook);

}

CWinInetHook::~CWinInetHook(void)
{
	if(pHook == this)
		pHook = NULL;

	DeleteCriticalSection(&cs);
}

HINTERNET CWinInetHook::InternetOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
	HINTERNET ret = NULL;
	
	if ( _InternetOpenW )
	{
		ret = _InternetOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}

	return ret;
}

HINTERNET CWinInetHook::InternetOpenA(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags)
{
	HINTERNET ret = NULL;

	if (_InternetOpenA)
	{
		ret = _InternetOpenA(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
	}

	return ret;
}
