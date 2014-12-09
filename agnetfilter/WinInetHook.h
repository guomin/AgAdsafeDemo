#pragma once

#include <WinInet.h>
#include "ncodehook/NCodeHookInstantiation.h"

typedef HINTERNET(__stdcall * LPINTERNETOPNW)(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall * LPINTERNETOPNA)(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);
typedef INTERNET_STATUS_CALLBACK(__stdcall * LPINTERNETSETSTATUSCALLBACK)(HINTERNET hInternet, INTERNET_STATUS_CALLBACK lpfnInternetCallback);
typedef HINTERNET(__stdcall * LPINTERNETCONNECTW)(HINTERNET hInternet, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, LPCWSTR lpszUserName, LPCWSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext);
typedef HINTERNET(__stdcall * LPINTERNETCONNECTA)(HINTERNET hInternet, LPCSTR lpszServerName, INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext);
typedef HINTERNET(__stdcall * LPHTTPOPENREQUESTW)(HINTERNET hConnect, LPCWSTR lpszVerb, LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferrer, LPCWSTR FAR * lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext);
typedef HINTERNET(__stdcall * LPHTTPOPENREQUESTA)(HINTERNET hConnect, LPCSTR lpszVerb, LPCSTR lpszObjectName, LPCSTR lpszVersion, LPCSTR lpszReferrer, LPCSTR FAR * lplpszAcceptTypes, DWORD dwFlags, DWORD_PTR dwContext);


BOOL WinInetInstallHooks(void);
void WinInetRemoveHooks(void);

class CWinInetHook
{
public:
	CWinInetHook(void);
	virtual ~CWinInetHook(void);
	void InstallHooks(void);

	HINTERNET	InternetOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
	HINTERNET	InternetOpenA(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);
	BOOL		InternetCloseHandle(HINTERNET hInternet);
	HINTERNET	InternetConnectW(HINTERNET hInternet, LPCWSTR lpszServerName, INTERNET_PORT nServerPort, LPCWSTR lpszUserName, LPCWSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext);
	HINTERNET	InternetConnectA(HINTERNET hInternet, LPCSTR lpszServerName, INTERNET_PORT nServerPort, LPCSTR lpszUserName, LPCSTR lpszPassword, DWORD dwService, DWORD dwFlags, DWORD_PTR dwContext);


private:
	CRITICAL_SECTION	cs;
	bool				hookOpenA;
	NCodeHookIA32		hook;

	LPINTERNETOPNW	_InternetOpenW;
	LPINTERNETOPNA	_InternetOpenA;
	LPINTERNETCONNECTW			_InternetConnectW;
	LPINTERNETCONNECTA			_InternetConnectA;
};