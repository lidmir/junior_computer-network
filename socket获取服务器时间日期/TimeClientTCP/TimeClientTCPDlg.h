
// TimeClientTCPDlg.h : ͷ�ļ�
//

#pragma once

#include "TCPClient.h"
#include "afxwin.h"
class CTCPClient;
// CTimeClientTCPDlg �Ի���
class CTimeClientTCPDlg : public CDialogEx
{
// ����
public:
	CTimeClientTCPDlg(CWnd* pParent = NULL);	// ��׼���캯��
	//bool ifcreate;
// �Ի�������
	enum { IDD = IDD_TIMECLIENTTCP_DIALOG };
	CTCPClient *MySock;
	void RecvData(CTCPClient* pSocket); 
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
	CEdit EDIT1;
	CEdit EDIT2;
	CEdit EDIT3;
	CEdit EDIT4;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
