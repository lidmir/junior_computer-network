#include "stdafx.h"
#include "UDPServer.h"
#include "TimeServer.h"
#include "TimeServerDlg.h"


CUDPServer::CUDPServer(void)
{
}


CUDPServer::~CUDPServer(void)
{
}


void CUDPServer::OnReceive(int nErrorCode)
{
	m_pDlg->RecvData(this); 
	CAsyncSocket::OnReceive(nErrorCode);
}
