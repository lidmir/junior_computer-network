
// TimeServerTCPDlg.h : ͷ�ļ�
//

#pragma once

#include "TCPServer.h"
#include "afxwin.h"
class CTCPServer;
// CTimeServerTCPDlg �Ի���
class CTimeServerTCPDlg : public CDialogEx
{
// ����
public:
	CTimeServerTCPDlg(CWnd* pParent = NULL);	// ��׼���캯��
	BOOL bFlag;
// �Ի�������
	enum { IDD = IDD_TIMESERVERTCP_DIALOG };
	CTCPServer *listenSocket; // ���ڴ򿪷�����
	void UpdateEvent(CString str);
	void RecvData(CTCPServer* pSocket); 
	void AcceptClient(); 
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnEnChangeEdit1();
	CEdit EDIT1;
};
