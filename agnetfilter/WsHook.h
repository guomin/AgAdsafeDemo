#pragma once
#define INCL_WINSOCK_API_TYPEDEFS 1
//#include <windows.h>
#include <WinSock2.h>
//#include <ws2tcpip.h>
#include "ncodehook/NCodeHookInstantiation.h"

BOOL WinsockInstallHooks(void);
void WinsockRemoveHooks(void);

class CWsHook
{
public:
	CWsHook(void);
	virtual ~CWsHook(void);

	int		connect(IN SOCKET s, const struct sockaddr FAR * name, IN int namelen);

private:
	NCodeHookIA32		hook;
	CRITICAL_SECTION	cs;

	LPFN_CONNECT	_connect;
};