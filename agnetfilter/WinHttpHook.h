#pragma once

#include <winhttp.h>
#include "ncodehook/NCodeHookInstantiation.h"

typedef HINTERNET(__stdcall * LPWINHTTPOPENW)(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall * LPWINHTTPOPENA)(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);

void WinHttpInstallHooks(void);
void WinHttpRemoveHooks(void);

class CWinHttpHook
{
public:
	CWinHttpHook(void);
	virtual ~CWinHttpHook(void);
	void InstallHooks(void);

	HINTERNET WinHttpOpenW(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
	HINTERNET WinHttpOpenA(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);


private:
	bool				hookOpenA;
	CRITICAL_SECTION	cs;
	NCodeHookIA32		hook;


	LPWINHTTPOPENW	_WinHttpOpenW;
	LPWINHTTPOPENA	_WinHttpOpenA;
};