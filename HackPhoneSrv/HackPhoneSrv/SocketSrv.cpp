// SocketSrv.cpp : 实现文件
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "SocketSrv.h"
#include "SocketClient.h"

CSocketSrv::CSocketSrv(){

}

CSocketSrv::~CSocketSrv(){
	MAPCLIENT::iterator it;
	for (it = m_cc.begin(); it != m_cc.end(); it++){
		delete it->second; 
	}
	m_cc.clear();
}

void CSocketSrv::SendCmd(uint16_t* cmd, int len){
	MAPCLIENT::iterator it; char szutf8[2048] = { 0 };
	for (it = m_cc.begin(); it != m_cc.end(); it++){
		it->second->Send(cmd, len);
	}
}

void CSocketSrv::SendCmd(uint16_t cmd){
	MAPCLIENT::iterator it;
	for (it = m_cc.begin(); it != m_cc.end(); it++){
		it->second->Send(&cmd, 2);
	}
}

void CSocketSrv::SendCmd(const CString& cmd){
	MAPCLIENT::iterator it; char szutf8[2048] = {0};
	::WideCharToMultiByte(CP_UTF8, 0, cmd, -1, szutf8, _countof(szutf8), NULL, NULL);
	for (it = m_cc.begin(); it != m_cc.end(); it++){
		it->second->Send(szutf8, strlen(szutf8));
	}
}

CSocketClient* CSocketSrv::AllocClient(){
	CSocketClient* s = new CSocketClient(m_ccid++);
	return s;
}

void CSocketSrv::FreeClient(uint64_t ccid){
	MAPCLIENT::iterator it = m_cc.find(ccid);
	if (it != m_cc.end()){ it->second->Close(); delete it->second; m_cc.erase(it); }
}

void CSocketSrv::OnAccept(int nErrorCode){
	CSocketClient* s = AllocClient();
	if (s != NULL && Accept(*s)){
		m_cc[s->GetCCID()] = s;
	}
	CSocket::OnAccept(nErrorCode);
}
