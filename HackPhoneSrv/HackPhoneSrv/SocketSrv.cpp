// SocketSrv.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "SocketSrv.h"
#include "SocketClient.h"

CSocketSrv::CSocketSrv(){

}

CSocketSrv::~CSocketSrv(){
}

void CSocketSrv::OnAccept(int nErrorCode){
	CSocketClient* s = new CSocketClient();
	Accept(*s);
	CSocket::OnAccept(nErrorCode);
}
