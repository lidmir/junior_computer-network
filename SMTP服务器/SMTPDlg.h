
// SMTPDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "SMTPSocket.h"

// CSMTPDlg �Ի���
class CSMTPDlg : public CDialogEx
{
// ����
public:
	CSMTPDlg(CWnd* pParent = NULL);	// ��׼���캯��
	SMTPSocket MySock;
// �Ի�������
	enum { IDD = IDD_SMTP_DIALOG };

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
	CEdit m_log;
	CEdit m_info;
	CStatic m_pic;
	afx_msg void OnBnClickedButton1();
};
