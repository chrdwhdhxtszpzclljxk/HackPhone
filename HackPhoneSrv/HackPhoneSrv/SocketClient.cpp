// SocketClient.cpp : ʵ���ļ�
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


// CSocketClient ��Ա����


void CSocketClient::OnReceive(int nErrorCode){
	CSocket::OnReceive(nErrorCode);
}


void CSocketClient::OnSend(int nErrorCode){
	TRACE("OnSend\r\n");
	CSocket::OnSend(nErrorCode);
}
