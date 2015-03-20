
// HackPhoneSrvDlg.h : ͷ�ļ�
//

#pragma once
#include "WndNumpad.h"
#include "afxdtctl.h"
#include "afxwin.h"

// CHackPhoneSrvDlg �Ի���
class CHackPhoneSrvDlg : public CDialogEx
{
// ����
public:
	CHackPhoneSrvDlg(CWnd* pParent = NULL);	// ��׼���캯��
	HWND m_hWndPrice;

// �Ի�������
	enum { IDD = IDD_HACKPHONESRV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon; 
	CWndNumpad m_wndNumpad;
	CFont m_fontPrice;

	// ���ɵ���Ϣӳ�亯��
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
