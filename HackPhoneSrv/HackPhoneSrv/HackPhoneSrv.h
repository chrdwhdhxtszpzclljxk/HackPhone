
// HackPhoneSrv.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

class CSocketSrv;

class CHackPhoneSrvApp : public CWinApp
{
public:
	CHackPhoneSrvApp();
	CSocketSrv* m_ss;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHackPhoneSrvApp theApp;