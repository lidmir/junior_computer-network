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
	// TODO: �ڴ����ר�ô����/����û���
	m_pDlg->AcceptClient(); 
	CAsyncSocket::OnAccept(nErrorCode);
}


void CTCPServer::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pDlg->RecvData(this); 
	CAsyncSocket::OnReceive(nErrorCode);
}
