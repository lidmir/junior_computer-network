#include "stdafx.h"
#include "TCPServer.h"
#include "TimeServerTCPDlg.h"


CTCPServer::CTCPServer(void)
{
}


CTCPServer::~CTCPServer(void)
{
}


void CTCPServer::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDlg->AcceptClient(); 
	CAsyncSocket::OnAccept(nErrorCode);
}


void CTCPServer::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDlg->RecvData(this); 
	CAsyncSocket::OnReceive(nErrorCode);
}
