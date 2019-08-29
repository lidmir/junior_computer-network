#include "stdafx.h"
#include "TCPClient.h"
#include "TimeClientTCPDlg.h"


CTCPClient::CTCPClient(void)
{
}


CTCPClient::~CTCPClient(void)
{
}


void CTCPClient::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDlg->RecvData(this);
	CAsyncSocket::OnReceive(nErrorCode);
}


void CTCPClient::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDlg->EDIT4.SetWindowTextW(_T("连接成功"));
	CAsyncSocket::OnConnect(nErrorCode);
}
