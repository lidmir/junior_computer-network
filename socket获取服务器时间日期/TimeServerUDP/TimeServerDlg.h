
// TimeServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "UDPServer.h"
class CUDPServer;
// CTimeServerDlg �Ի���
class CTimeServerDlg : public CDialogEx
{
// ����
public:
	CTimeServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_TIMESERVER_DIALOG };
	CUDPServer *listenSocket; // ���ڴ򿪷�����
	void UpdateEvent(CString str);
	void RecvData(CUDPServer* pSocket); 
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
//	afx_msg void OnEnChangeEdit1();
	CEdit EDIT1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
