#pragma once

// CSocketSrv ����Ŀ��

class CSocketSrv : public CSocket{
public:
	CSocketSrv();
	virtual ~CSocketSrv();
	virtual void OnAccept(int nErrorCode);
};


