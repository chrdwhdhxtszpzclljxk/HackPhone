// SocketClient.cpp : 实现文件
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "SocketClient.h"


// CSocketClient

CSocketClient::CSocketClient()
{
}

CSocketClient::~CSocketClient()
{
}


// CSocketClient 成员函数


void CSocketClient::OnReceive(int nErrorCode){
	CSocket::OnReceive(nErrorCode);
}


void CSocketClient::OnSend(int nErrorCode){
	TRACE("OnSend\r\n");
	CSocket::OnSend(nErrorCode);
}
