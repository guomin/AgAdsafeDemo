
// HookDialogDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"


// CHookDialogDemoDlg �Ի���
class CHookDialogDemoDlg : public CDialog
{
// ����
public:
	CHookDialogDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HOOKDIALOGDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
