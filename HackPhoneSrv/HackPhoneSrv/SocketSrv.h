#pragma once
#include <stdint.h>
#include <atomic>
#include <map>

class CSocketClient;
typedef std::map< uint64_t, CSocketClient* > MAPCLIENT;
class CSocketSrv : public CSocket{
public:
	CSocketSrv();
	virtual ~CSocketSrv();
	virtual void OnAccept(int nErrorCode);
	CSocketClient* AllocClient();
	void FreeClient(uint64_t);
	void SenCmd(uint8_t);
public:
	std::atomic<uint64_t> m_ccid;
	MAPCLIENT m_cc;
};


