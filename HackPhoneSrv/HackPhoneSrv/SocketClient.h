#pragma once
#include <stdint.h>

class CSocketClient : public CSocket
{
public:
	CSocketClient(uint64_t ccid);
	virtual ~CSocketClient();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	const uint64_t GetCCID(){ return m_ccid; };
private:
	uint64_t m_ccid;
};


