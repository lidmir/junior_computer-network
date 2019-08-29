
// TimeServerTCPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TimeServerTCP.h"
#include "TimeServerTCPDlg.h"
#include "afxdialogex.h"
#include "TCPServer.h"
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


// CTimeServerTCPDlg 对话框



CTimeServerTCPDlg::CTimeServerTCPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeServerTCPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeServerTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, EDIT1);
}

BEGIN_MESSAGE_MAP(CTimeServerTCPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTimeServerTCPDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTimeServerTCPDlg::OnBnClickedButton2)
//	ON_EN_CHANGE(IDC_EDIT1, &CTimeServerTCPDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CTimeServerTCPDlg 消息处理程序

BOOL CTimeServerTCPDlg::OnInitDialog()
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

void CTimeServerTCPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTimeServerTCPDlg::OnPaint()
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
HCURSOR CTimeServerTCPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CTimeServerTCPDlg::AcceptClient()
{
	CTCPServer *pSocket=new CTCPServer;
	pSocket->m_pDlg = this;
	BOOL aFlag=listenSocket->Accept(*pSocket);
	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	if(!aFlag)
		this->UpdateEvent(_T("建立连接失败"));
	else
	{
		CString ipadress;
		UINT port;
		pSocket->GetPeerName(ipadress,port);
		CString str6;
		str6.Format(_T("%d"),port);
		CString string=_T("IP=")+ipadress+_T(",Port=")+str6+_T(",建立连接成功");
		this->UpdateEvent(string);
	}
}

void CTimeServerTCPDlg::RecvData(CTCPServer* pSocket)
{
	char lpBuf[MAX_PATH];
    int nBufLen = strlen(lpBuf);
	int nRet=pSocket->Receive(lpBuf,nBufLen);
	//事件打印的处理
	//对接收到缓存区的数据处理
	CString str;     
	CString szText;
	for (int i = 0; i < nRet; i++)       
    {
		szText.Format(_T("%c"),lpBuf[i]);
        str += szText;
    }
	//对于请求命令的处理
	CString string1;
	if(str=="time"||str=="Time"||str=="TIME")
	{
		CTime tm=CTime::GetCurrentTime();
		string1 = tm.Format(_T("%H:%M:%S"));
		int a=pSocket->Send(string1,sizeof(string1)*4);
		if(a==SOCKET_ERROR) this->UpdateEvent(_T("响应命令失败"));
	}
	else if(str=="date"||str=="Date"||str=="DATE")
	{
		CTime tm=CTime::GetCurrentTime();
		string1 = tm.Format(_T("%Y/%m/%d"));
		int a=pSocket->Send(string1,sizeof(string1)*5);
		if(a==SOCKET_ERROR) this->UpdateEvent(_T("响应命令失败"));
	}
	else
	{
		string1=_T("FormatWrong!");
		int a=pSocket->Send(string1,sizeof(string1)*6);
		if(a==SOCKET_ERROR) this->UpdateEvent(_T("响应命令失败"));
	}
	CString string;
	string=_T("请求【")+str+_T("】，响应【")+string1+_T("】");
	this->UpdateEvent(string);
}
void CTimeServerTCPDlg::OnBnClickedButton1()
{
	listenSocket = new CTCPServer();
    listenSocket->m_pDlg = this;
	bFlag=listenSocket->Create(3000,SOCK_STREAM,FD_READ|FD_ACCEPT|FD_CLOSE);
	if(!bFlag)
		UpdateEvent(_T("服务器连接失败或已连接中"));		
	else
		UpdateEvent(_T("服务器已连接"));
	BOOL lFlag=listenSocket->Listen(1);
	if(lFlag)
		UpdateEvent(_T("侦听中"));
	else
		UpdateEvent(_T("侦听连接失败或已侦听中"));
}

void CTimeServerTCPDlg::OnBnClickedButton2()
{
	listenSocket->Close();
	UpdateEvent(_T("服务器已关闭"));
	bFlag=0;
}

void CTimeServerTCPDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();                  
	str += _T("\r\n");         	// 用于换行显示日志                                                    
	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;   
	//获取编辑框最后一行索引，并替换其内容
	int lastLine = EDIT1.LineIndex(EDIT1.GetLineCount() - 1);
	EDIT1.SetSel(lastLine+1,lastLine+2,0);                                     
	EDIT1.ReplaceSel(string);                                                             
}


