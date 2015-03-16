#pragma once

// CSocketSrv ÃüÁîÄ¿±ê

class CSocketSrv : public CSocket{
public:
	CSocketSrv();
	virtual ~CSocketSrv();
	virtual void OnAccept(int nErrorCode);
};


