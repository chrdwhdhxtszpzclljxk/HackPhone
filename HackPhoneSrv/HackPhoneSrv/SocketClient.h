#pragma once

// CSocketClient ����Ŀ��

class CSocketClient : public CSocket
{
public:
	CSocketClient();
	virtual ~CSocketClient();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};


