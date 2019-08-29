#pragma once
#include "afxsock.h"
#include "TimeServerTCPDlg.h"
class CTimeServerTCPDlg;
class CTCPServer :
	public CAsyncSocket
{
public:
	CTimeServerTCPDlg *m_pDlg;
	CTCPServer(void);
	~CTCPServer(void);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

