// SocketClient.cpp : 实现文件
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "SocketClient.h"
#include "SocketSrv.h"

CSocketClient::CSocketClient(uint64_t ccid) : m_ccid(ccid){
}

CSocketClient::~CSocketClient(){
	TRACE("client free(%d)\r\n",(uint32_t)m_ccid);
}

void CSocketClient::OnReceive(int nErrorCode){
	CSocket::OnReceive(nErrorCode);
}


void CSocketClient::OnSend(int nErrorCode){
	TRACE("OnSend\r\n");
	CSocket::OnSend(nErrorCode);
}


void CSocketClient::OnClose(int nErrorCode){
	TRACE("OnClose\r\n");
	CSocket::OnClose(nErrorCode);
	theApp.m_ss->FreeClient(m_ccid);
}
