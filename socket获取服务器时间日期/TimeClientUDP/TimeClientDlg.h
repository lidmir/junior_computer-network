
// TimeClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "UDPClient.h"
class CUDPClient;
// CTimeClientDlg �Ի���
class CTimeClientDlg : public CDialogEx
{
// ����
public:
	CTimeClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TIMECLIENT_DIALOG };
	CUDPClient *MySock; 
	void RecvData(CUDPClient* pSocket); 
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
	afx_msg void OnBnClickedButton1();
	CEdit EDIT2;
	CEdit EDIT1;
	CEdit EDIT3;
	CEdit EDIT4;
};
