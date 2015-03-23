#pragma once
#include <stdint.h>

class CWndNumpad : public CWnd{
	DECLARE_DYNAMIC(CWndNumpad)
public:
	CWndNumpad();
	virtual ~CWndNumpad();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CRect m_rc[15];
	TCHAR m_cmd[15];
	CPoint m_pt[15];
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


