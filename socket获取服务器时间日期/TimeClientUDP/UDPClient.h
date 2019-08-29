#pragma once
#include "afxsock.h"
#include "TimeClientDlg.h"
class CTimeClientDlg;
class CUDPClient :
	public CAsyncSocket
{
public:
	CTimeClientDlg *m_pDlg;
	CUDPClient(void);
	~CUDPClient(void);
	virtual void OnReceive(int nErrorCode);
};

