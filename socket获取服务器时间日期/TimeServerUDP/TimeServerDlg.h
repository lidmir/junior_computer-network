
// TimeServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "UDPServer.h"
class CUDPServer;
// CTimeServerDlg 对话框
class CTimeServerDlg : public CDialogEx
{
// 构造
public:
	CTimeServerDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_TIMESERVER_DIALOG };
	CUDPServer *listenSocket; // 用于打开服务器
	void UpdateEvent(CString str);
	void RecvData(CUDPServer* pSocket); 
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
//	afx_msg void OnEnChangeEdit1();
	CEdit EDIT1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
