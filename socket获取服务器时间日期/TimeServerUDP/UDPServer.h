#pragma once
#include "afxsock.h"
#include "TimeServerDlg.h"
class CTimeServerDlg;
class CUDPServer :
	public CAsyncSocket
{
public:
	CTimeServerDlg *m_pDlg;
	CUDPServer(void);
	~CUDPServer(void);
	virtual void OnReceive(int nErrorCode);
};

