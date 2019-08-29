
// TimeClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TimeClient.h"
#include "TimeClientDlg.h"
#include "afxdialogex.h"
#include "UDPClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif





// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimeClientDlg 对话框



CTimeClientDlg::CTimeClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	MySock = new CUDPClient();
	MySock->m_pDlg = this;
	BOOL bFlag= MySock->Create(0,SOCK_DGRAM,FD_READ);
	if(!bFlag)
		EDIT4.SetWindowTextW(_T("create wrong"));
}

void CTimeClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, EDIT2);
	DDX_Control(pDX, IDC_EDIT1, EDIT1);
	DDX_Control(pDX, IDC_EDIT3, EDIT3);
	DDX_Control(pDX, IDC_EDIT4, EDIT4);
}

BEGIN_MESSAGE_MAP(CTimeClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_EN_CHANGE(IDC_EDIT1, &CTimeClientDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTimeClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTimeClientDlg 消息处理程序

BOOL CTimeClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CTimeClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimeClientDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTimeClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CString_to_UINT(const CString & value)
{
UINT data=0;
if(value.Find(_T("0x"))==0)
_stscanf_s((LPCTSTR)value,_T("%x"),&data);
else
_stscanf_s((LPCTSTR)value,_T("%d"),&data);
return data;
}


void CTimeClientDlg::OnBnClickedButton1()
{
	CString lpBuf1;
	GetDlgItem(IDC_EDIT3)->GetWindowText(lpBuf1);
	CString nHostPort;
	GetDlgItem(IDC_EDIT1)->GetWindowText(nHostPort);
	CString lpszHostAddress;
	GetDlgItem(IDC_EDIT2)->GetWindowText(lpszHostAddress);
	if(lpBuf1==_T("end")||lpBuf1==_T("End")||lpBuf1==_T("END"))
	{
		MySock->Close();
		EDIT4.SetWindowTextW(_T("客户端数据发送关闭"));
	}
	else
	{
		int test=MySock->SendTo(lpBuf1,sizeof(lpBuf1)*2,CString_to_UINT(nHostPort), (LPCTSTR)lpszHostAddress);
		if(test==SOCKET_ERROR) 
			EDIT4.SetWindowTextW(_T("send wrong"));
	}
}
void CTimeClientDlg::RecvData(CUDPClient* pSocket)
{
	// TODO: 在此添加专用代码和/或调用基类
	char lpBuf[MAX_PATH];
    int nBufLen = strlen(lpBuf);
	CString rSocketAddress;
	UINT rSocketPort; 
	int nRet=pSocket->ReceiveFrom(lpBuf,nBufLen,rSocketAddress,rSocketPort);	
	CString str;     
	CString szText;
	for (int i = 0; i < nRet; i++)       
    {
		szText.Format(_T("%c"),lpBuf[i]);
        str += szText;
    }
	EDIT4.SetWindowTextW((LPCTSTR)str);
}
