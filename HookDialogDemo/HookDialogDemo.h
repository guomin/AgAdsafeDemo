
// HookDialogDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHookDialogDemoApp:
// �йش����ʵ�֣������ HookDialogDemo.cpp
//

class CHookDialogDemoApp : public CWinAppEx
{
public:
	CHookDialogDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHookDialogDemoApp theApp;