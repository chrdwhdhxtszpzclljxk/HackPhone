// InJectFun.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "InJectFun.h"

void hackthread(void*);
BOOL bEnumChildProc2 = FALSE;
BOOL injectok = FALSE;
BOOL CALLBACK ClickHighestPrice(HWND hwnd, LPARAM lParam);
BOOL CALLBACK EnumChildProc2(_In_  HWND hwnd, _In_  LPARAM lParam);
BOOL CALLBACK ClickHighestPrice00(HWND hwnd, LPARAM lParam);
BOOL CALLBACK EnumChildProc200(_In_  HWND hwnd, _In_  LPARAM lParam);
void ClickButton(HWND hWnd,int x,int y);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
LONG oldproc = 0;
LONG mainoldproc = 0;
INJECTFUN_API void Initialize(void){ _beginthread(hackthread,0,0); }// 这是导出函数的一个示例。
int x = 10;

void hackthread(void*){
	HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,_T("Global\\event_hackthread_innectfun"));
	HANDLE hEvent00 = CreateEvent(NULL,FALSE,FALSE,_T("Global\\event_hackthread_innectfun00"));
	MessageBox(NULL,_T("wait cmd"),_T("hi"),MB_OK);
	while(true){
		//MessageBox(NULL,_T("wait cmd"),_T("hi"),MB_OK);
		if(::WaitForSingleObject(hEvent,500) == WAIT_OBJECT_0){
			//MessageBox(NULL,_T("cmd get"),_T("hi"),MB_OK);
			x = 10;
			if(!injectok){	EnumWindows(ClickHighestPrice, 0); injectok = TRUE;}
		}
		if(::WaitForSingleObject(hEvent00,500) == WAIT_OBJECT_0){
			MessageBox(NULL,_T("cmd get 00"),_T("hi"),MB_OK);
			EnumWindows(ClickHighestPrice00, 0); 
		}
		Sleep(1);
	}
	CloseHandle(hEvent);
}


BOOL CALLBACK ClickHighestPrice(HWND hwnd, LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; RECT rc;
	::GetClassName(hwnd, szClass, _countof(szClass)); // TMainform
	if ((_tcsicmp(szClass, _T("TMainForm")) == 0)){
		if (hwnd != NULL){
			::SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			::SetForegroundWindow(hwnd);
			::ShowWindow(hwnd,SW_SHOW);
			::EnableWindow(hwnd, TRUE);
			mainoldproc = GetWindowLong(hwnd,GWL_WNDPROC);
			SetWindowLong(hwnd,GWL_WNDPROC,(LONG)MainWndProc);

			//ClickButton(hwnd, 656, 363);
			//AfxMessageBox(_T("找到 TMainForm"));
			//MessageBox(NULL,_T("Find TMainForm"),_T("hi"),MB_OK);
			bEnumChildProc2 = FALSE;
			//for (;;){
				EnumChildWindows(hwnd, EnumChildProc2, lParam);
			//}
			//	if (bEnumChildProc2) break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EnumChildProc2(_In_  HWND hwnd, _In_  LPARAM lParam){
	TCHAR szClass[1024] = { 0 };
	::GetClassName(hwnd, szClass, _countof(szClass));
	if ((_tcsicmp(szClass, _T("TNoPasteEdit")) == 0)){
		if (hwnd != NULL){
			::EnableWindow(hwnd, TRUE);
			::ShowWindow(hwnd,SW_SHOW);
			::MoveWindow(hwnd,x,10,200,200,TRUE);
			//LONG style = GetWindowLong(hwnd,GWL_STYLE);
			//style = style &~ ES_LEFT;
			//style = style | ES_CENTER;
			//SetWindowLong(hwnd,GWL_STYLE,style);
			if(x == 10){
			oldproc = GetWindowLong(hwnd,GWL_WNDPROC);
			SetWindowLong(hwnd,GWL_WNDPROC,(LONG)WndProc);
			}

			x+=250;
			//::SetClassLong(hwnd,);
			//::SetForegroundWindow(hwnd);
			//::SetWindowText(hwnd, _T("200"));
			//::SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)_T("200"));
			//HWND hEdit1 = FindWindowEx(hwnd, NULL, _T("TEdit"), NULL);
			//#(781,377) (847,409)
			MessageBox(NULL,_T("innect ok"),_T("info"),MB_OK);
			bEnumChildProc2 = TRUE;
		}
		//return FALSE;
	}
	return TRUE;
}


BOOL CALLBACK ClickHighestPrice00(HWND hwnd, LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; RECT rc;
	::GetClassName(hwnd, szClass, _countof(szClass)); // TMainform
	if ((_tcsicmp(szClass, _T("TMainForm")) == 0)){
		if (hwnd != NULL){
			::SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			//::SetForegroundWindow(hwnd);
			::EnableWindow(hwnd, TRUE);
			//ClickButton(hwnd, 656, 363);
			//AfxMessageBox(_T("找到 TMainForm"));
			MessageBox(NULL,_T("Find TMainForm"),_T("hi"),MB_OK);
			bEnumChildProc2 = FALSE;
			for (;;){
				EnumChildWindows(hwnd, EnumChildProc200, lParam);
				if (bEnumChildProc2) break;
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EnumChildProc200(_In_  HWND hwnd, _In_  LPARAM lParam){
	TCHAR szClass[1024] = { 0 };
	::GetClassName(hwnd, szClass, _countof(szClass));
	if ((_tcsicmp(szClass, _T("TNoPasteEdit")) == 0)){
		if (hwnd != NULL){
			::EnableWindow(hwnd, TRUE);
			//::SetWindowText(hwnd,_T("888"));
			//SetWindowLong(hwnd,GWL_WNDPROC,(LONG)WndProc);

			//::SetClassLong(hwnd,);
			//::SetForegroundWindow(hwnd);
			//::SetWindowText(hwnd, _T("200"));
			//::SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)_T("200"));
			//HWND hEdit1 = FindWindowEx(hwnd, NULL, _T("TEdit"), NULL);
			//#(781,377) (847,409)
			MessageBox(NULL,_T("innect ok222"),_T("info"),MB_OK);
			bEnumChildProc2 = TRUE;
		}
		//return FALSE;
	}
	return TRUE;
}


void ClickButton(HWND hWnd,int x,int y){
	POINT p,oldp;
	::SetFocus(hWnd);
	p.x = x; p.y = y;
	::ClientToScreen(hWnd, &p);
	::GetCursorPos(&oldp);
	::SetCursorPos(p.x, p.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, p.x, p.y, 0, NULL);//鼠标down事件
	mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, p.x, p.y, 0, NULL);//鼠标up事件
	SetCursorPos(p.x, p.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, NULL);//鼠标down事件
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);//鼠标up事件

	::SetCursorPos(p.x, p.y);

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = p.x;
	Input.mi.dy = p.y;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE;
	UINT ret = SendInput(2, &Input, sizeof(INPUT));
	::SetCursorPos(oldp.x, oldp.y);
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
//return DefWindowProc (hwnd, message, wParam, lParam) ;
    // 必要时可以调用原来的窗口函数，使被子类化的窗口仍具有原来的很多特性
	//if(message == 0xBD00 || message == 0xBD01 || message == 0xBD02 ) return 0;
	//if(message == 0xBD33) return 0x741015c0;
	//if(message == 0x118) return 0;
	if(message == 0xB012){ OutputDebugString(_T("CM_TEXTCHANGEDCM_TEXTCHANGEDCM_TEXTCHANGED"));return TRUE;}

	if((message == WM_SETCURSOR) || (message == WM_NCHITTEST) || (message == WM_MOUSEFIRST)){
	}else{

		TCHAR tcOut[1024] = {0};
		_stprintf(tcOut,_T("Edit MESSAGE: 0x%08x"),message);
		OutputDebugString(tcOut);
		/*
		sprintf(tcOut,"message: 0x08X\r\n",message);

		FILE* fp = fopen("c:\\temp000.txt","ab+");
		if(fp != 0){
			fwrite(tcOut,1,strlen(tcOut),fp);
			fclose(fp);
		}
		//
		WM_PAINT;WM_SETCURSOR;WM_NCHITTEST;WM_MOUSEFIRST; //
		//#define WM_PAINT                        0x000F
		#define WM_NCPAINT                      0x0085
		#define WM_ERASEBKGND                   0x0014
#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
		#define WM_MOUSEACTIVATE                0x0021
		#define WM_LBUTTONDOWN                  0x0201
		#define WM_LBUTTONUP                    0x0202
		#define WM_IME_SETCONTEXT               0x0281
		#define WM_SETFOCUS                     0x0007
		#define WM_ERASEBKGND                   0x0014
		#define WM_LBUTTONUP                    0x0202
		#define WM_CAPTURECHANGED               0x0215
#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
		#define WM_KILLFOCUS                    0x0008
		#define WM_MOUSEACTIVATE                0x0021
		#define WM_SETTEXT                      0x000C
		#define WM_NCMOUSEMOVE                  0x00A0
		CM_BASE = $B000;
		CM_TEXTCHANGED = CM_BASE + 18;
		*/
		
		
	}


   LRESULT ret = CallWindowProc((WNDPROC)oldproc,hwnd,message,wParam,lParam);
  // 	if(message == WM_LBUTTONDOWN) {::SetWindowText(hwnd,_T("168800"));}
	return ret;
}

LRESULT CALLBACK MainWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
//return DefWindowProc (hwnd, message, wParam, lParam) ;
    // 必要时可以调用原来的窗口函数，使被子类化的窗口仍具有原来的很多特性
//	if(message == 0xBD00 || message == 0xBD01 || message == 0xBD02 ) return 0;
//		if(message == 0xBD33) return 0x741015c0;
	//if(message == WM_PAINT) return TRUE;

   LRESULT ret = CallWindowProc((WNDPROC)mainoldproc,hwnd,message,wParam,lParam);
   //if(message == WM_LBUTTONDOWN) {::SetWindowText(hwnd,_T("1688"));}
   return ret;
}