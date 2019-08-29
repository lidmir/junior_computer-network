
// SMTPDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "SMTPSocket.h"

// CSMTPDlg 对话框
class CSMTPDlg : public CDialogEx
{
// 构造
public:
	CSMTPDlg(CWnd* pParent = NULL);	// 标准构造函数
	SMTPSocket MySock;
// 对话框数据
	enum { IDD = IDD_SMTP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
