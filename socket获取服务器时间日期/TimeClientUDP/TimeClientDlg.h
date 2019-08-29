
// TimeClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "UDPClient.h"
class CUDPClient;
// CTimeClientDlg 对话框
class CTimeClientDlg : public CDialogEx
{
// 构造
public:
	CTimeClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TIMECLIENT_DIALOG };
	CUDPClient *MySock; 
	void RecvData(CUDPClient* pSocket); 
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
	afx_msg void OnBnClickedButton1();
	CEdit EDIT2;
	CEdit EDIT1;
	CEdit EDIT3;
	CEdit EDIT4;
};
