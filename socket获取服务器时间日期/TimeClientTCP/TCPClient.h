#pragma once
#include "afxsock.h"
#include "TimeClientTCPDlg.h"
class CTimeClientTCPDlg;
class CTCPClient :
	public CAsyncSocket
{
public:
	CTimeClientTCPDlg *m_pDlg;
	CTCPClient(void);
	~CTCPClient(void);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
};

