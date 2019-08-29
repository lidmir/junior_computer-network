
// TimeServerTCPDlg.h : 头文件
//

#pragma once

#include "TCPServer.h"
#include "afxwin.h"
class CTCPServer;
// CTimeServerTCPDlg 对话框
class CTimeServerTCPDlg : public CDialogEx
{
// 构造
public:
	CTimeServerTCPDlg(CWnd* pParent = NULL);	// 标准构造函数
	BOOL bFlag;
// 对话框数据
	enum { IDD = IDD_TIMESERVERTCP_DIALOG };
	CTCPServer *listenSocket; // 用于打开服务器
	void UpdateEvent(CString str);
	void RecvData(CTCPServer* pSocket); 
	void AcceptClient(); 
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnEnChangeEdit1();
	CEdit EDIT1;
};
