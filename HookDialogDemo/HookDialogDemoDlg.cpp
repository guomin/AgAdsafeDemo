
// HookDialogDemoDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CHookDialogDemoDlg �Ի���




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


// CHookDialogDemoDlg ��Ϣ�������

BOOL CHookDialogDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHookDialogDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHookDialogDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CHookDialogDemoDlg::KBLock(BOOL sign)
{
	hDLL = ::LoadLibrary(_T("agnetfilter.dll"));//hDLL=::LoadLibrary(_T("HookDll.dll"));       //����DLL
	if (hDLL!=NULL)
	{
		loadhook=(LOADHOOK)::GetProcAddress (hDLL,"EnableKeyboardCapture");
		unloadhook=(UNLOADHOOK)::GetProcAddress (hDLL,"DisableKeyboardCapture");

		if(loadhook==NULL||unloadhook==NULL)
		{
			::MessageBox(0,_T("�Բ��𣬱����ܲ���ʹ�ã�����"), _T("Somthing Wrong"),MB_OK);
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
	::MessageBox(0,_T("��̬�����ʧ�ܣ�����"), _T("Somthing Wrong"),MB_OK);
	return 0;
}

void CHookDialogDemoDlg::OnBnClickedBtnHook()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KBLock(TRUE);
}

void CHookDialogDemoDlg::OnBnClickedBtnUnHook()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KBLock(FALSE);
}

void CHookDialogDemoDlg::OnBnClickedBtnOpenSite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_test.Navigate(_T("http://www.baidu.com"), NULL, NULL, NULL, NULL);
}

void CHookDialogDemoDlg::OnBnClickedBtnOpenHttpByWinsock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SOCKET      sSocket      = INVALID_SOCKET;
	SOCKADDR_IN stSvrAddrIn = {0}; /* �������˵�ַ */
	char sndBuf[10240] = {0};
	char rcvBuf[20480] = {0};
	char       *pRcv  = rcvBuf;
	int  num   = 0;
	int  nRet  = SOCKET_ERROR;

	WSADATA     wsaData;

	/* HTTP ��Ϣ���쿪ʼ�����ǳ���Ĺؼ�֮�� */
	//CONNECT XXX.XXX.XXX:80 HTTP/1.1\r\n\r\n
	sprintf(sndBuf,"");
	strcat(sndBuf,"GET / HTTP/1.1\r\n HOST:www.baidu.com\r\n\r\n");
	strcat(sndBuf,"\r\n");
	/* HTTP ��Ϣ������� */

	/* socket DLL��ʼ�� */
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	stSvrAddrIn.sin_family      = AF_INET;
	stSvrAddrIn.sin_port = htons(9999);
	stSvrAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");

	sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	/* ���� */
	nRet = connect(sSocket, (SOCKADDR*)&stSvrAddrIn, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("connect fail!/n");
		return;
	}
	printf("connnect ok\r\n");
	/* ����HTTP������Ϣ */
	send(sSocket, (char*)sndBuf, sizeof(sndBuf), 0);

	/* ����HTTP��Ӧ��Ϣ */
	while(1)
	{
		num = recv(sSocket, pRcv, sizeof(rcvBuf), 0);

		pRcv += num;

		if((0 == num) || (-1 == num))
		{
			break ;
		}
	}

	/* ��ӡ��Ӧ��Ϣ */
	printf("%s/n", rcvBuf);

}
