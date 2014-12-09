#pragma once

#include <winhttp.h>
#include "ncodehook/NCodeHookInstantiation.h"

typedef HINTERNET(__stdcall * LPWINHTTPOPENW)(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall * LPWINHTTPOPENA)(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall * LPWINHTTPCONNECTW)(HINTERNET hSession, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, DWORD dwReserved);
typedef HINTERNET(__stdcall * LPWINHTTPCONNECTA)(HINTERNET hSession, LPCSTR lpszServerName, INTERNET_PORT nServerPort, DWORD dwReserved);

typedef HINTERNET(__stdcall * LPWINHTTPOPEN)(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall * LPWINHTTPCONNECT)(HINTERNET hSession, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, DWORD dwReserved);

typedef HINTERNET(__stdcall * LPWINHTTPOPENREQUEST)(HINTERNET hInternet, LPCWSTR lpszVerb, LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferrer, LPCWSTR FAR * plpszAcceptTypes, DWORD dwFlags);
typedef BOOL(__stdcall * LPWINHTTPGETPROXYFORURL)(HINTERNET hInternet, LPCWSTR lpszUrl, WINHTTP_AUTOPROXY_OPTIONS *pAutoProxyOptions, OUT WINHTTP_PROXY_INFO * pProxyInfo);

BOOL WinHttpInstallHooks(void);
void WinHttpRemoveHooks(void);

class CWinHttpHook
{
public:
	CWinHttpHook(void);
	virtual ~CWinHttpHook(void);
	void InstallHooks(void);

	HINTERNET WinHttpOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
	HINTERNET WinHttpOpenA(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);
	HINTERNET WinHttpConnectW(HINTERNET hSession, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, DWORD dwReserved);
	HINTERNET WinHttpConnectA(HINTERNET hSession, LPCSTR lpszServerName, INTERNET_PORT nServerPort, DWORD dwReserved);

	HINTERNET WinHttpOpen(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
	HINTERNET WinHttpConnect(HINTERNET hSession, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, DWORD dwReserved);
	HINTERNET WinHttpOpenRequest(HINTERNET hInternet, LPCWSTR lpszVerb, LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferrer, LPCWSTR FAR * plpszAcceptTypes, DWORD dwFlags);
	BOOL		WinHttpGetProxyForUrl(HINTERNET hInternet, LPCWSTR lpszUrl, WINHTTP_AUTOPROXY_OPTIONS *pAutoProxyOptions, OUT WINHTTP_PROXY_INFO * pProxyInfo);

private:
	bool				hookOpenA;
	CRITICAL_SECTION	cs;
	NCodeHookIA32		hook;


	LPWINHTTPOPENW	_WinHttpOpenW;
	LPWINHTTPOPENA	_WinHttpOpenA;
	LPWINHTTPCONNECTW _WinHttpConnectW;
	LPWINHTTPCONNECTA _WinHttpConnectA;

	LPWINHTTPOPEN		_WinHttpOpen;
	LPWINHTTPCONNECT	_WinHttpConnect;
	LPWINHTTPOPENREQUEST	_WinHttpOpenRequest;
	LPWINHTTPGETPROXYFORURL	_WinHttpGetProxyForUrl;
};