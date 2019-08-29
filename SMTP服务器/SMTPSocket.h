
#if !defined(AFX_NEWSOCKCLASS_H__8EB4225C_953E_4C9D_B82B_735228DD045A__INCLUDED_)
#define AFX_NEWSOCKCLASS_H__8EB4225C_953E_4C9D_B82B_735228DD045A__INCLUDED_
#define BufferLen 4096
#endif
// SMTPSocket 命令目标
#if _MSC_VER > 1000
#pragma once
#endif



class SMTPSocket : public CAsyncSocket
{
public:
	SMTPSocket();
	virtual ~SMTPSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	bool IsData;    //判断服务器接收到的是否是命令
	bool Quit;     //判断客户端是否退出
	bool IsBmp;
	CString pic;
	char data[BufferLen];
};