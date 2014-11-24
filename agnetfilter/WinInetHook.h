#pragma once

#include <WinInet.h>
#include "ncodehook/NCodeHookInstantiation.h"

typedef HINTERNET(__stdcall * LPINTERNETOPNW)(LPCWSTR lpszAgent, DWORD dwAccessType, LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags);
typedef HINTERNET(__stdcall * LPINTERNETOPNA)(LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags);

void WinInetInstallHooks(void);
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

private:
	CRITICAL_SECTION	cs;
	bool				hookOpenA;
	NCodeHookIA32		hook;

	LPINTERNETOPNW	_InternetOpenW;
	LPINTERNETOPNA	_InternetOpenA;
};