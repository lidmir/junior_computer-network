
// TimeClientTCPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TimeClientTCP.h"
#include "TimeClientTCPDlg.h"
#include "afxdialogex.h"
#include "TCPClient.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTimeClientTCPDlg �Ի���



CTimeClientTCPDlg::CTimeClientTCPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeClientTCPDlg::IDD, pParent)
{
	//ifcreate=false;  //�ж��Ƿ񴴽�socket
	MySock = new CTCPClient();
	MySock->m_pDlg = this;
	//create
	BOOL bFlag= MySock->Create(0,SOCK_STREAM,FD_READ|FD_CONNECT|FD_CLOSE);
	if(!bFlag)
		EDIT4.SetWindowTextW(_T("create wrong"));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeClientTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, EDIT1);
	DDX_Control(pDX, IDC_EDIT2, EDIT2);
	DDX_Control(pDX, IDC_EDIT3, EDIT3);
	DDX_Control(pDX, IDC_EDIT4, EDIT4);
}

BEGIN_MESSAGE_MAP(CTimeClientTCPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CTimeClientTCPDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTimeClientTCPDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTimeClientTCPDlg ��Ϣ�������

BOOL CTimeClientTCPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CTimeClientTCPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimeClientTCPDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTimeClientTCPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CString_to_UINT(const CString & value)       //CStringתUINT
{
UINT data=0;
if(value.Find(_T("0x"))==0)
_stscanf_s((LPCTSTR)value,_T("%x"),&data);
else
_stscanf_s((LPCTSTR)value,_T("%d"),&data);
return data;
}

void CTimeClientTCPDlg::OnBnClickedButton2()  //��������
{
	//if(!this->ifcreate)
	//	return;
	CString lpBuf1;
	GetDlgItem(IDC_EDIT3)->GetWindowText(lpBuf1);
	if(lpBuf1==_T("end")||lpBuf1==_T("End")||lpBuf1==_T("END"))
	{
		MySock->Close();
		EDIT4.SetWindowTextW(_T("�ͻ������ݷ��͹ر�"));
	}
	else
	{
		int test=MySock->Send(lpBuf1,sizeof(lpBuf1)*2);
		if(test==SOCKET_ERROR) 
			EDIT4.SetWindowTextW(_T("��������ʧ��"));
	}
}
void CTimeClientTCPDlg::RecvData(CTCPClient* pSocket)
{
	char lpBuf[MAX_PATH];
    int nBufLen = strlen(lpBuf);
	int nRet=pSocket->Receive(lpBuf,nBufLen);	
	//���ܷ�������Ӧת����CString����ҪΪ�˽����ַ��ĸ�ʽ��
	CString str;     
	CString szText;
	for (int i = 0; i < nRet; i++)       
    {
		szText.Format(_T("%c"),lpBuf[i]);
        str += szText;
    }
	EDIT4.SetWindowTextW((LPCTSTR)str);
}

void CTimeClientTCPDlg::OnBnClickedButton1()
{
	
	//this->ifcreate=true;
	//connect
	CString nHostPort;
	GetDlgItem(IDC_EDIT1)->GetWindowText(nHostPort);
	CString lpszHostAddress;
	GetDlgItem(IDC_EDIT2)->GetWindowText(lpszHostAddress);
	BOOL test=MySock->Connect((LPCTSTR)lpszHostAddress,CString_to_UINT(nHostPort));
	do{
	if(!test) 
	{		
		DWORD dwErrorID = GetLastError();
		if(GetLastError()==WSAEWOULDBLOCK)
			EDIT4.SetWindowTextW(_T("������.."));
		else 
			EDIT4.SetWindowTextW(_T("�ѽ������ӻ�������ʧ��"));	
	}
	else
		EDIT4.SetWindowTextW(_T("���ӳɹ�"));
	}while(GetLastError()==WSAEWOULDBLOCK);
}
