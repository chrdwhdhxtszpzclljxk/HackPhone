// WndNumpad.cpp : 实现文件
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "WndNumpad.h"
#include "SocketSrv.h"


// CWndNumpad

IMPLEMENT_DYNAMIC(CWndNumpad, CWnd)

CWndNumpad::CWndNumpad()
{

}

CWndNumpad::~CWndNumpad()
{
}


BEGIN_MESSAGE_MAP(CWndNumpad, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CWndNumpad 消息处理程序




void CWndNumpad::OnPaint(){
	CPaintDC dc(this); // device context for painting
	CString strTxt;
	for (int i = 0; i <= 12; i++){
		dc.FillSolidRect(m_rc[i], RGB(255, 0, 0));
		if (i == 10) strTxt = _T("*"); 
		else if (i == 11) strTxt = _T("#");
		else if (i == 12) strTxt = _T("DIAL");
		else strTxt.Format(_T("%d"), i);
		dc.DrawText(strTxt, m_rc[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
}


BOOL CWndNumpad::OnEraseBkgnd(CDC* pDC){
	return TRUE;//return CWnd::OnEraseBkgnd(pDC);
}


void CWndNumpad::OnSize(UINT nType, int cx, int cy){
	CWnd::OnSize(nType, cx, cy);
	CRect rc; int top = 80,w,h;
	GetClientRect(rc);
	w = rc.Width() / 3;
	h = (rc.Height() - 80) / 5;
	m_rc[1].top = rc.top + top; m_rc[1].left = rc.left; m_rc[1].bottom = m_rc[1].top + h; m_rc[1].right = m_rc[1].left + w;
	m_rc[2].top = m_rc[1].top; m_rc[2].left = m_rc[1].right; m_rc[2].bottom = m_rc[1].bottom; m_rc[2].right = m_rc[2].left + w;
	m_rc[3].top = m_rc[1].top; m_rc[3].left = m_rc[2].right; m_rc[3].bottom = m_rc[1].bottom; m_rc[3].right = m_rc[3].left + w;
	m_rc[4].top = m_rc[1].bottom; m_rc[4].left = m_rc[1].left; m_rc[4].bottom = m_rc[4].top + h; m_rc[4].right = m_rc[4].left + w;
	m_rc[5].top = m_rc[4].top; m_rc[5].left = m_rc[4].right; m_rc[5].bottom = m_rc[4].bottom; m_rc[5].right = m_rc[5].left + w;
	m_rc[6].top = m_rc[4].top; m_rc[6].left = m_rc[5].right; m_rc[6].bottom = m_rc[4].bottom; m_rc[6].right = m_rc[6].left + w;
	m_rc[7].top = m_rc[4].bottom; m_rc[7].left = m_rc[4].left; m_rc[7].bottom = m_rc[7].top + h; m_rc[7].right = m_rc[7].left + w;
	m_rc[8].top = m_rc[4].bottom; m_rc[8].left = m_rc[7].right; m_rc[8].bottom = m_rc[7].bottom; m_rc[8].right = m_rc[8].left + w;
	m_rc[9].top = m_rc[4].bottom; m_rc[9].left = m_rc[8].right; m_rc[9].bottom = m_rc[7].bottom; m_rc[9].right = m_rc[9].left + w;
	m_rc[10].top = m_rc[7].bottom; m_rc[10].left = m_rc[7].left; m_rc[10].bottom = m_rc[10].top + h; m_rc[10].right = m_rc[10].left + w;
	m_rc[0].top = m_rc[10].top; m_rc[0].left = m_rc[10].right; m_rc[0].bottom = m_rc[10].bottom; m_rc[0].right = m_rc[0].left + w;
	m_rc[11].top = m_rc[10].top; m_rc[11].left = m_rc[0].right; m_rc[11].bottom = m_rc[10].bottom; m_rc[11].right = m_rc[11].left + w;
	m_rc[12].top = m_rc[10].bottom; m_rc[12].left = m_rc[10].left; m_rc[12].bottom = m_rc[12].top + h; m_rc[12].right = m_rc[12].left + w * 3;
}


void CWndNumpad::OnLButtonUp(UINT nFlags, CPoint point){
	CString strTxt;
	for (int i = 0; i <= 12; i++){
		if (m_rc[i].PtInRect(point)){
			if (i == 10) strTxt = _T("*");
			else if (i == 11) strTxt = _T("#");
			else if (i == 12) strTxt = _T("DIAL");
			else strTxt.Format(_T("%d"), i);
			strTxt.Format(_T("input tap %d %d\r\n"), m_pt[i].x, m_pt[i].y);
			//AfxMessageBox(strTxt);
			theApp.m_ss->SendCmd(strTxt);
			break;
		}
	}

	CWnd::OnLButtonUp(nFlags, point);
}


int CWndNumpad::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_cmd[0] = 7;
	m_cmd[1] = 8;
	m_cmd[2] = 9;
	m_cmd[3] = 10;
	m_cmd[4] = 11;
	m_cmd[5] = 12;
	m_cmd[6] = 13;
	m_cmd[7] = 14;
	m_cmd[8] = 15;
	m_cmd[9] = 16;
	m_cmd[10] = 17;
	m_cmd[11] = 18;
	m_cmd[12] = 5;
	m_pt[0].x = 420; m_pt[0].y = 1600;
	m_pt[1].x = 139; m_pt[1].y = 1000; //m_pt[1].x = 200; m_pt[1].y = 900; //
	m_pt[2].x = 420; m_pt[2].y = 1000; //m_pt[2].x = 400; m_pt[2].y = 900; //
	m_pt[3].x = 800; m_pt[3].y = 1000; //m_pt[3].x = 800; m_pt[3].y = 900; //
	m_pt[4].x = 139; m_pt[4].y = 1200;
	m_pt[5].x = 420; m_pt[5].y = 1200;
	m_pt[6].x = 800; m_pt[6].y = 1200;
	m_pt[7].x = 139; m_pt[7].y = 1450;
	m_pt[8].x = 420; m_pt[8].y = 1450;
	m_pt[9].x = 800; m_pt[9].y = 1450;
	m_pt[10].x = 139; m_pt[10].y = 1600; // *
	m_pt[11].x = 800; m_pt[11].y = 1600; // #
	m_pt[12].x = 139; m_pt[12].y = 1700; // DIAL

	return 0;
}
