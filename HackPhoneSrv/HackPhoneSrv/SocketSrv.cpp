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

void CSocketSrv::SenCmd(uint8_t cmd){
	MAPCLIENT::iterator it;
	for (it = m_cc.begin(); it != m_cc.end(); it++){
		it->second->Send(&cmd, 1);
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
