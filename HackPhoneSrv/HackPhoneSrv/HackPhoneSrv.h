
// HackPhoneSrv.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

class CSocketSrv;

class CHackPhoneSrvApp : public CWinApp
{
public:
	CHackPhoneSrvApp();
	CSocketSrv* m_ss;

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CHackPhoneSrvApp theApp;