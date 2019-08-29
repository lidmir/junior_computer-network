
// TimeClientTCPDlg.h : 头文件
//

#pragma once

#include "TCPClient.h"
#include "afxwin.h"
class CTCPClient;
// CTimeClientTCPDlg 对话框
class CTimeClientTCPDlg : public CDialogEx
{
// 构造
public:
	CTimeClientTCPDlg(CWnd* pParent = NULL);	// 标准构造函数
	//bool ifcreate;
// 对话框数据
	enum { IDD = IDD_TIMECLIENTTCP_DIALOG };
	CTCPClient *MySock;
	void RecvData(CTCPClient* pSocket); 
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
	CEdit EDIT1;
	CEdit EDIT2;
	CEdit EDIT3;
	CEdit EDIT4;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
