#include "stdafx.h"
#include "SocketTools.h"

#include "Iphlpapi.h"
#include <malloc.h>
#include "Winsock2.h"
#include <stdlib.h>
#pragma warning(disable:4996)

#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

static char TcpState[][32] ={
	"???",
	"CLOSED",
	"LISTENING",
	"SYN_SENT",
	"SEN_RECEIVED",
	"ESTABLISHED",
	"FIN_WAIT",
	"FIN_WAIT2",
	"CLOSE_WAIT",
	"CLOSING",
	"LAST_ACK",
	"TIME_WAIT"
};

DWORD local;
DWORD localpt;
DWORD remote;
DWORD remotept;


DWORD DelTCPConnect(){
	DWORD dwRetVal = ERROR_NOT_FOUND; MIB_TCPROW srtTcpRow;
	srtTcpRow.dwLocalAddr = local;
	srtTcpRow.dwRemoteAddr = remote;
	srtTcpRow.dwLocalPort = localpt;
	srtTcpRow.dwRemotePort = remotept;
	srtTcpRow.dwState = MIB_TCP_STATE_DELETE_TCB; //目前为止，settcpEntry只支持该参数
	dwRetVal = SetTcpEntry(&srtTcpRow);
	if (dwRetVal != ERROR_SUCCESS)
	{
		LPVOID lpMsgBuf;
		if (FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwRetVal,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPSTR)&lpMsgBuf,
			0,
			NULL))
		{
			TRACE("\tError(%d): %s", GetLastError(), lpMsgBuf);
		}
		LocalFree(lpMsgBuf);
	}
	return dwRetVal;
}

CString BreakNetbidclient(){
	PMIB_TCPTABLE pTcpTable = NULL; DWORD dwSize = 0, dwRetVal = ERROR_SUCCESS; char* premoteip;
	struct   in_addr rip, lip; char  szrip[32] = { 0 }, szlip[32] = { 0 }; CString strRet;
	
	if (GetTcpTable(pTcpTable, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)	{//获得pTcpTable所需要的真实长度,dwSize
		pTcpTable = (MIB_TCPTABLE*)malloc((UINT)dwSize);
	}
	else return strRet;

	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR){
		for (int i = 0; i < (int)pTcpTable->dwNumEntries; i++){
			rip.S_un.S_addr = pTcpTable->table[i].dwRemoteAddr; lip.S_un.S_addr = pTcpTable->table[i].dwLocalAddr;
			premoteip = inet_ntoa(rip);
			if (strcmp(premoteip, "222.73.114.22") == 0 || strcmp(premoteip, "222.73.114.3") == 0){ // 找到国服务器。
				local = pTcpTable->table[i].dwLocalAddr;
				localpt = pTcpTable->table[i].dwLocalPort;
				remote = pTcpTable->table[i].dwRemoteAddr;
				remotept = pTcpTable->table[i].dwRemotePort;
				DelTCPConnect();
				strRet = premoteip;
				break;
			}
			//if (pTcpTable->table[i].dwState == MIB_TCP_STATE_LISTEN) pTcpTable->table[i].dwRemotePort = 0;//监听端口，远程主机端口为0，但函数返回是有值的，不知道它是怎么考虑的
			//_snprintf(szlip, sizeof(szlip), "%s:%d", inet_ntoa(lip), htons((u_short)pTcpTable->table[i].dwLocalPort));			//dwLocalPort，dwRemotePort 是网络字节
			//_snprintf(szrip, sizeof(szrip), "%s:%d", inet_ntoa(rip), htons((u_short)pTcpTable->table[i].dwRemotePort));
			//TRACE("  TCP\t%-24s%-24s%s\r\n", szlip, szrip, TcpState[pTcpTable->table[i].dwState]);
		}
	} else {
		//TRACE("\tCall to GetTcpTable failed.%d\r\n",GetLastError());
		LPVOID lpMsgBuf;
		if (FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwRetVal,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPSTR)&lpMsgBuf,
			0,
			NULL)){
			TRACE("\tError: %s", lpMsgBuf);
		}
		LocalFree(lpMsgBuf);
	}
	free(pTcpTable);
	return strRet;
}

CStringA GetCurServer(){
	PMIB_TCPTABLE pTcpTable = NULL; DWORD dwSize = 0, dwRetVal = ERROR_SUCCESS; char* premoteip; CStringA strRet;
	struct   in_addr rip, lip; char  szrip[32] = { 0 }, szlip[32] = { 0 };

	if (GetTcpTable(pTcpTable, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)	{//获得pTcpTable所需要的真实长度,dwSize
		pTcpTable = (MIB_TCPTABLE*)malloc((UINT)dwSize);
	}
	else return "";

	CTime t = CTime::GetCurrentTime();
	strRet.Format(("%02d:%02d:%02d "), t.GetHour(), t.GetMinute(), t.GetSecond());
	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR){
		for (int i = 0; i < (int)pTcpTable->dwNumEntries; i++){
			rip.S_un.S_addr = pTcpTable->table[i].dwRemoteAddr; lip.S_un.S_addr = pTcpTable->table[i].dwLocalAddr;
			premoteip = inet_ntoa(rip);
			if (strcmp(premoteip, "222.73.114.22") == 0 || strcmp(premoteip, "222.73.114.3") == 0){ // 找到国服务器。
				strRet.Append(premoteip);
				return strRet;
				break;
			}
			//if (pTcpTable->table[i].dwState == MIB_TCP_STATE_LISTEN) pTcpTable->table[i].dwRemotePort = 0;//监听端口，远程主机端口为0，但函数返回是有值的，不知道它是怎么考虑的
			//_snprintf(szlip, sizeof(szlip), "%s:%d", inet_ntoa(lip), htons((u_short)pTcpTable->table[i].dwLocalPort));			//dwLocalPort，dwRemotePort 是网络字节
			//_snprintf(szrip, sizeof(szrip), "%s:%d", inet_ntoa(rip), htons((u_short)pTcpTable->table[i].dwRemotePort));
			//TRACE("  TCP\t%-24s%-24s%s\r\n", szlip, szrip, TcpState[pTcpTable->table[i].dwState]);
		}
	}
	else {
		//TRACE("\tCall to GetTcpTable failed.%d\r\n",GetLastError());
		LPVOID lpMsgBuf;
		if (FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwRetVal,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPSTR)&lpMsgBuf,
			0,
			NULL)){
			TRACE("\tError: %s", lpMsgBuf);
		}
		LocalFree(lpMsgBuf);
	}
	free(pTcpTable);
	return strRet;
}