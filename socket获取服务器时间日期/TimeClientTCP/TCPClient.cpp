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
	// TODO: �ڴ����ר�ô����/����û���
	m_pDlg->RecvData(this);
	CAsyncSocket::OnReceive(nErrorCode);
}


void CTCPClient::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pDlg->EDIT4.SetWindowTextW(_T("���ӳɹ�"));
	CAsyncSocket::OnConnect(nErrorCode);
}
