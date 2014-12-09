
// HookDialogDemoDlg.h : 头文件
//

#pragma once
#include "explorer1.h"


// CHookDialogDemoDlg 对话框
class CHookDialogDemoDlg : public CDialog
{
// 构造
public:
	CHookDialogDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HOOKDIALOGDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL KBLock(BOOL sign);
	afx_msg void OnBnClickedBtnHook();
	afx_msg void OnBnClickedBtnUnHook();
	CExplorer1 m_test;
	afx_msg void OnBnClickedBtnOpenSite();
	afx_msg void OnBnClickedBtnOpenHttpByWinsock();
};
