
// TimeServerTCP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTimeServerTCPApp:
// �йش����ʵ�֣������ TimeServerTCP.cpp
//

class CTimeServerTCPApp : public CWinApp
{
public:
	CTimeServerTCPApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTimeServerTCPApp theApp;