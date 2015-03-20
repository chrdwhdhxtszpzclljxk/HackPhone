
// HackPhoneSrvDlg.h : 头文件
//

#pragma once
#include "WndNumpad.h"
#include "afxdtctl.h"
#include "afxwin.h"

// CHackPhoneSrvDlg 对话框
class CHackPhoneSrvDlg : public CDialogEx
{
// 构造
public:
	CHackPhoneSrvDlg(CWnd* pParent = NULL);	// 标准构造函数
	HWND m_hWndPrice;

// 对话框数据
	enum { IDD = IDD_HACKPHONESRV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon; 
	CWndNumpad m_wndNumpad;
	CFont m_fontPrice;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBnFindprice();
	CDateTimeCtrl m_dpGo;
	afx_msg void OnDtnDatetimechangeDpGo(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_staPrice;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
