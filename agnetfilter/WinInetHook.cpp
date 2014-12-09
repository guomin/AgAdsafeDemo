#include "StdAfx.h"
#include "WinInetHook.h"
#include <WinInet.h>
#include "util.h"

static CWinInetHook * pHook = NULL;

BOOL WinInetInstallHooks(void)
{
	if(!pHook)
		pHook = new CWinInetHook();
	return pHook!=NULL;
}

void WinInetRemoveHooks(void)
{
	if(pHook)
	{
		delete pHook;
		pHook = NULL;
		WriteAGLog("WinInetRemoveHooks");
	}
}

HINTERNET __stdcall InternetOpenW_Hook(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
	WriteAGLog("InternetOpenW_Hook Begin");
	lpszProxy = _T("http://127.0.0.1:8888");
	dwAccessType = INTERNET_OPEN_TYPE_PROXY;

	HINTERNET ret = NULL;
	__try{
		if(pHook)
		{
			ret = pHook->InternetOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
		}
		else
		{
			WriteAGLog("InternetOpenW_Hook pHook == NULL");
		}
	}__except(1){
		WriteAGLog("InternetOpenW_Hook Failed");
	}
	WriteAGLog("InternetOpenW_Hook End");
	return ret;
}

HINTERNET __stdcall InternetOpenA_Hook(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags)
{
	//
	WriteAGLog("InternetOpenA_Hook Begin");
	lpszProxy = "http://127.0.0.1:8888";
	dwAccessType = INTERNET_OPEN_TYPE_PROXY;
	//
	HINTERNET ret = NULL;
	__try{
		if(pHook)
			ret = pHook->InternetOpenA(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
		else
		{
			WriteAGLog("InternetOpenA_Hook pHook == NULL");
		}
	}__except(1){
		WriteAGLog("InternetOpenA_Hook Failed");
	}
	WriteAGLog("InternetOpenA_Hook End");
	return ret;
}
HINTERNET __stdcall InternetConnectW_Hook(HINTERNET hInternet, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, LPCWSTR lpszUserName, LPCWSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext)
{
	WriteAGLog("InternetConnectW_Hook Begin");
	HINTERNET ret = NULL;
	__try{
		if(pHook)
		{
			hInternet = InternetOpenW(L"safe", 0, NULL, NULL, 0);
			ret = pHook->InternetConnectW(hInternet, lpszServerName, nServerPort, lpszUserName, lpszPassword, dwService, dwFlags, dwContext);
		}
	}__except(1){
		WriteAGLog("InternetConnectW_Hook Failed");
	}
	WriteAGLog("InternetConnectW_Hook End");
	return ret;
}

HINTERNET __stdcall InternetConnectA_Hook(HINTERNET hInternet, LPCSTR lpszServerName, INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext)
{
	WriteAGLog("InternetConnectA_Hook Begin");
	HINTERNET ret = NULL;
	__try{
		if(pHook)
		{
			hInternet = InternetOpenA("safe", 0, NULL, NULL, 0);
			ret = pHook->InternetConnectA(hInternet, lpszServerName, nServerPort, lpszUserName, lpszPassword, dwService, dwFlags, dwContext);
		}
	}__except(1){
		WriteAGLog("InternetConnectW_Hook Failed");
	}
	WriteAGLog("InternetConnectA_Hook End");
	return ret;
}


CWinInetHook::CWinInetHook(void):
hookOpenA(true)
{
	WriteAGLog("CWinInetHook");
	InitializeCriticalSection(&cs);

	//
	//parents.InitHashTable(257);

	_InternetOpenW = hook.createHookByName("wininet.dll", "InternetOpenW", InternetOpenW_Hook);
	_InternetOpenA = hook.createHookByName("wininet.dll", "InternetOpenA", InternetOpenA_Hook);
	if (_InternetOpenW==NULL && _InternetOpenA==NULL)
	{
		::MessageBox(0, _T("apihooked"), _T("CWinInetHook"), MB_OK);
	}

	_InternetConnectW = hook.createHookByName("wininet.dll", "InternetConnectW", InternetConnectW_Hook);
	_InternetConnectA = hook.createHookByName("wininet.dll", "InternetConnectA", InternetConnectA_Hook);
}

CWinInetHook::~CWinInetHook(void)
{
	if(pHook == this)
		pHook = NULL;

	DeleteCriticalSection(&cs);
	WriteAGLog("~CWinInetHook");
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

HINTERNET CWinInetHook::InternetConnectW(HINTERNET hInternet, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, LPCWSTR lpszUserName, LPCWSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext)
{
	HINTERNET ret = NULL;

	if( _InternetConnectW )
		ret = _InternetConnectW(hInternet, lpszServerName, nServerPort, lpszUserName, lpszPassword, dwService, dwFlags, dwContext);


	return ret;
}

/*-----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
HINTERNET CWinInetHook::InternetConnectA(HINTERNET hInternet, LPCSTR lpszServerName, INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext)
{
	HINTERNET ret = NULL;

	if( _InternetConnectA )
		ret = _InternetConnectA(hInternet, lpszServerName, nServerPort, lpszUserName, lpszPassword, dwService, dwFlags, dwContext);

	return ret;
}
