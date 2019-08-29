#include "stdafx.h"
#include "UDPClient.h"
#include "TimeClientDlg.h"


CUDPClient::CUDPClient(void)
{	
}


CUDPClient::~CUDPClient(void)
{
}



void CUDPClient::OnReceive(int nErrorCode)
{
	m_pDlg->RecvData(this);
	CAsyncSocket::OnReceive(nErrorCode);
}
