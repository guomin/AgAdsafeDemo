#include "WsHook.h"
#include "util.h"

#pragma comment(lib, "ws2_32.lib")

static CWsHook * pHook = NULL;

BOOL WinsockInstallHooks()
{
	if(!pHook)
		pHook = new CWsHook();
	return pHook!=NULL;
}

void WinsockRemoveHooks()
{
	if (pHook)
	{
		delete pHook;
		pHook = NULL;
	}
}

int WSAAPI connect_Hook(IN SOCKET s, const struct sockaddr FAR * name, IN int namelen)
{
	WriteAGLog("connect_Hook Begin");
	int ret = SOCKET_ERROR;
	__try{
		if(pHook)
		{
			WriteAGLog("...");
			BOOL bMark = FALSE;
			if (name!=NULL)
			{
				sockaddr_in sin;
				memcpy(&sin, &name, sizeof(sin));

				WriteAGLog("");
				if(sin.sin_port==htons(9222))
				{
					bMark = TRUE;
				}
			}
			SOCKADDR_IN stSvrAddrIn = {0};
			stSvrAddrIn.sin_family = AF_INET;
			stSvrAddrIn.sin_port = htons(8888);
			stSvrAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");
			if (bMark)
			{
				ret = pHook->connect(s, name, namelen);
			}
			else
			{
				ret = pHook->connect(s, name, namelen);
				//ret = pHook->connect(s, (SOCKADDR*)&stSvrAddrIn/*name*/, sizeof(SOCKADDR)/*namelen*/);
			}
			
			if (SOCKET_ERROR == ret)
			{
				WriteAGLog("ret==SOCKET_ERROR");
			}
		}
	}__except(1){
		WriteAGLog("connect_Hook Failed");
	}
	WriteAGLog("connect_Hook End");
	return ret;
}

CWsHook::CWsHook()
{
	InitializeCriticalSection(&cs);

	_connect = hook.createHookByName("ws2_32.dll", "connect", connect_Hook);

}

CWsHook::~CWsHook()
{
	if (pHook == this)
	{
		pHook = NULL;
	}

	DeleteCriticalSection(&cs);
}

int CWsHook::connect(IN SOCKET s, const struct sockaddr FAR * name, IN int namelen)
{
	int ret = SOCKET_ERROR;

	if (_connect)
	{
		ret = _connect(s, name, namelen);
	}

	return ret;
}