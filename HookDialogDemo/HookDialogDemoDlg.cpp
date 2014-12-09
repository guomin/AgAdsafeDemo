
// HookDialogDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HookDialogDemo.h"
#include "HookDialogDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef BOOL (CALLBACK *LOADHOOK)();
typedef BOOL (CALLBACK *UNLOADHOOK)();
HINSTANCE hDLL=NULL;
LOADHOOK loadhook;
UNLOADHOOK unloadhook;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHookDialogDemoDlg 对话框




CHookDialogDemoDlg::CHookDialogDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHookDialogDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHookDialogDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_test);
}

BEGIN_MESSAGE_MAP(CHookDialogDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CHookDialogDemoDlg::OnBnClickedBtnHook)
	ON_BN_CLICKED(IDC_BUTTON2, &CHookDialogDemoDlg::OnBnClickedBtnUnHook)
	ON_BN_CLICKED(IDC_BUTTON3, &CHookDialogDemoDlg::OnBnClickedBtnOpenSite)
	ON_BN_CLICKED(IDC_BUTTON4, &CHookDialogDemoDlg::OnBnClickedBtnOpenHttpByWinsock)
END_MESSAGE_MAP()


// CHookDialogDemoDlg 消息处理程序

BOOL CHookDialogDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHookDialogDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHookDialogDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHookDialogDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CHookDialogDemoDlg::KBLock(BOOL sign)
{
	hDLL = ::LoadLibrary(_T("agnetfilter.dll"));//hDLL=::LoadLibrary(_T("HookDll.dll"));       //加载DLL
	if (hDLL!=NULL)
	{
		loadhook=(LOADHOOK)::GetProcAddress (hDLL,"EnableKeyboardCapture");
		unloadhook=(UNLOADHOOK)::GetProcAddress (hDLL,"DisableKeyboardCapture");

		if(loadhook==NULL||unloadhook==NULL)
		{
			::MessageBox(0,_T("对不起，本功能不能使用！！！"), _T("Somthing Wrong"),MB_OK);
			return 0;
		}
		if(sign)
			loadhook();
		else
		{
			unloadhook();
			::FreeLibrary(hDLL);
		}
		return 1;
	}
	::MessageBox(0,_T("动态库加载失败！！！"), _T("Somthing Wrong"),MB_OK);
	return 0;
}

void CHookDialogDemoDlg::OnBnClickedBtnHook()
{
	// TODO: 在此添加控件通知处理程序代码
	KBLock(TRUE);
}

void CHookDialogDemoDlg::OnBnClickedBtnUnHook()
{
	// TODO: 在此添加控件通知处理程序代码
	KBLock(FALSE);
}

void CHookDialogDemoDlg::OnBnClickedBtnOpenSite()
{
	// TODO: 在此添加控件通知处理程序代码
	m_test.Navigate(_T("http://www.baidu.com"), NULL, NULL, NULL, NULL);
}

void CHookDialogDemoDlg::OnBnClickedBtnOpenHttpByWinsock()
{
	// TODO: 在此添加控件通知处理程序代码
	SOCKET      sSocket      = INVALID_SOCKET;
	SOCKADDR_IN stSvrAddrIn = {0}; /* 服务器端地址 */
	char sndBuf[10240] = {0};
	char rcvBuf[20480] = {0};
	char       *pRcv  = rcvBuf;
	int  num   = 0;
	int  nRet  = SOCKET_ERROR;

	WSADATA     wsaData;

	/* HTTP 消息构造开始，这是程序的关键之处 */
	//CONNECT XXX.XXX.XXX:80 HTTP/1.1\r\n\r\n
	sprintf(sndBuf,"");
	strcat(sndBuf,"GET / HTTP/1.1\r\n HOST:www.baidu.com\r\n\r\n");
	strcat(sndBuf,"\r\n");
	/* HTTP 消息构造结束 */

	/* socket DLL初始化 */
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	stSvrAddrIn.sin_family      = AF_INET;
	stSvrAddrIn.sin_port = htons(9999);
	stSvrAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");

	sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	/* 连接 */
	nRet = connect(sSocket, (SOCKADDR*)&stSvrAddrIn, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("connect fail!/n");
		return;
	}
	printf("connnect ok\r\n");
	/* 发送HTTP请求消息 */
	send(sSocket, (char*)sndBuf, sizeof(sndBuf), 0);

	/* 接收HTTP响应消息 */
	while(1)
	{
		num = recv(sSocket, pRcv, sizeof(rcvBuf), 0);

		pRcv += num;

		if((0 == num) || (-1 == num))
		{
			break ;
		}
	}

	/* 打印响应消息 */
	printf("%s/n", rcvBuf);

}
