
// TimeServerTCPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TimeServerTCP.h"
#include "TimeServerTCPDlg.h"
#include "afxdialogex.h"
#include "TCPServer.h"
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


// CTimeServerTCPDlg �Ի���



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


// CTimeServerTCPDlg ��Ϣ�������

BOOL CTimeServerTCPDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimeServerTCPDlg::OnPaint()
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
		this->UpdateEvent(_T("��������ʧ��"));
	else
	{
		CString ipadress;
		UINT port;
		pSocket->GetPeerName(ipadress,port);
		CString str6;
		str6.Format(_T("%d"),port);
		CString string=_T("IP=")+ipadress+_T(",Port=")+str6+_T(",�������ӳɹ�");
		this->UpdateEvent(string);
	}
}

void CTimeServerTCPDlg::RecvData(CTCPServer* pSocket)
{
	char lpBuf[MAX_PATH];
    int nBufLen = strlen(lpBuf);
	int nRet=pSocket->Receive(lpBuf,nBufLen);
	//�¼���ӡ�Ĵ���
	//�Խ��յ������������ݴ���
	CString str;     
	CString szText;
	for (int i = 0; i < nRet; i++)       
    {
		szText.Format(_T("%c"),lpBuf[i]);
        str += szText;
    }
	//������������Ĵ���
	CString string1;
	if(str=="time"||str=="Time"||str=="TIME")
	{
		CTime tm=CTime::GetCurrentTime();
		string1 = tm.Format(_T("%H:%M:%S"));
		int a=pSocket->Send(string1,sizeof(string1)*4);
		if(a==SOCKET_ERROR) this->UpdateEvent(_T("��Ӧ����ʧ��"));
	}
	else if(str=="date"||str=="Date"||str=="DATE")
	{
		CTime tm=CTime::GetCurrentTime();
		string1 = tm.Format(_T("%Y/%m/%d"));
		int a=pSocket->Send(string1,sizeof(string1)*5);
		if(a==SOCKET_ERROR) this->UpdateEvent(_T("��Ӧ����ʧ��"));
	}
	else
	{
		string1=_T("FormatWrong!");
		int a=pSocket->Send(string1,sizeof(string1)*6);
		if(a==SOCKET_ERROR) this->UpdateEvent(_T("��Ӧ����ʧ��"));
	}
	CString string;
	string=_T("����")+str+_T("������Ӧ��")+string1+_T("��");
	this->UpdateEvent(string);
}
void CTimeServerTCPDlg::OnBnClickedButton1()
{
	listenSocket = new CTCPServer();
    listenSocket->m_pDlg = this;
	bFlag=listenSocket->Create(3000,SOCK_STREAM,FD_READ|FD_ACCEPT|FD_CLOSE);
	if(!bFlag)
		UpdateEvent(_T("����������ʧ�ܻ���������"));		
	else
		UpdateEvent(_T("������������"));
	BOOL lFlag=listenSocket->Listen(1);
	if(lFlag)
		UpdateEvent(_T("������"));
	else
		UpdateEvent(_T("��������ʧ�ܻ���������"));
}

void CTimeServerTCPDlg::OnBnClickedButton2()
{
	listenSocket->Close();
	UpdateEvent(_T("�������ѹر�"));
	bFlag=0;
}

void CTimeServerTCPDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();                  
	str += _T("\r\n");         	// ���ڻ�����ʾ��־                                                    
	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;   
	//��ȡ�༭�����һ�����������滻������
	int lastLine = EDIT1.LineIndex(EDIT1.GetLineCount() - 1);
	EDIT1.SetSel(lastLine+1,lastLine+2,0);                                     
	EDIT1.ReplaceSel(string);                                                             
}


