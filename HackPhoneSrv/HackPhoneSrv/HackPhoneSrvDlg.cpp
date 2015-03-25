
// HackPhoneSrvDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "HackPhoneSrvDlg.h"
#include "afxdialogex.h"
#include "SocketSrv.h"
#include "SocketTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable:4996)

#define ID_TIMER_GETPRICE 1
#define ID_TIMER_GETSERVERINFO 2

const CString TNoPasteEdit = _T("TEdit");// _T("TNoPasteEdit");

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHackPhoneSrvDlg �Ի���



CHackPhoneSrvDlg::CHackPhoneSrvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHackPhoneSrvDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHackPhoneSrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DP_GO, m_dpGo);
	//DDX_Control(pDX, IDC_STATIC_PRICE, m_staPrice);
	DDX_Control(pDX, IDC_STATIC_SERVERINFO, m_staServerInfo);
	DDX_Control(pDX, IDC_CHECK_AUTOCLOSE, m_chkAutoClose);
	DDX_Control(pDX, IDC_LIST_INFO, m_listInfo);
	DDX_Control(pDX, IDC_DP_P1, m_timePrice1);
	DDX_Control(pDX, IDC_DP_P2, m_timePrice2);
}

BEGIN_MESSAGE_MAP(CHackPhoneSrvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CHackPhoneSrvDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BN_FINDPRICE, &CHackPhoneSrvDlg::OnBnClickedBnFindprice)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DP_GO, &CHackPhoneSrvDlg::OnDtnDatetimechangeDpGo)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BN_MAINWND, &CHackPhoneSrvDlg::OnBnClickedBnMainwnd)
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_BN_SCRIPT, &CHackPhoneSrvDlg::OnBnClickedBnScript)
	ON_BN_CLICKED(IDC_BN_RESET, &CHackPhoneSrvDlg::OnBnClickedBnReset)
	ON_BN_CLICKED(IDC_BN_PWD, &CHackPhoneSrvDlg::OnBnClickedBnPwd)
END_MESSAGE_MAP()


// CHackPhoneSrvDlg ��Ϣ�������

BOOL CHackPhoneSrvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	LPCTSTR className = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW);
	m_wndNumpad.Create(className, _T("NumPad01"), WS_CHILD | WS_VISIBLE , CRect(0, 0, 0, 0), this, 0);
	m_fontPrice.CreatePointFont(660,_T("����"));
	//m_staPrice.SetFont(&m_fontPrice);
	theApp.m_ss = new CSocketSrv();
	theApp.m_ss->Create(1996);
	theApp.m_ss->Listen();
	PostMessage(WM_SIZE);

	CTime tNow = CTime::GetCurrentTime();
	CTime t1(tNow.GetYear(), tNow.GetMonth(), tNow.GetDay(), 10, 58, 0);
	m_timePrice1.SetTime(&t1);
	CTime t2(tNow.GetYear(), tNow.GetMonth(), tNow.GetDay(), 11, 29, 46);
	m_timePrice2.SetTime(&t2);
	
	SetTimer(ID_TIMER_GETPRICE, 20, NULL);
	SetTimer(ID_TIMER_GETSERVERINFO, 1000, NULL);
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE);
	RegisterHotKey(GetSafeHwnd(), 1000, 0, VK_ESCAPE);
	if (!RegisterHotKey(GetSafeHwnd(), 1001, MOD_CONTROL, VK_F12)){
		DWORD err = GetLastError();
		AfxMessageBox(_T("F12 ʧ�ܣ�"));
	}
	m_chkAutoClose.SetCheck(TRUE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHackPhoneSrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHackPhoneSrvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHackPhoneSrvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHackPhoneSrvDlg::OnDestroy(){
	CDialogEx::OnDestroy();
	theApp.m_ss->Close();
	delete theApp.m_ss;
	UnregisterHotKey(GetSafeHwnd(), 1000);
	UnregisterHotKey(GetSafeHwnd(), 1001);
}


void CHackPhoneSrvDlg::OnBnClickedOk(){
}


void CHackPhoneSrvDlg::OnSize(UINT nType, int cx, int cy){
	CDialogEx::OnSize(nType, cx, cy);
	CRect rc; GetClientRect(rc);
	rc.DeflateRect(0,80,0,0);
	if (IsWindow(m_wndNumpad.GetSafeHwnd())) m_wndNumpad.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
}

BOOL CALLBACK GetImageFormChild(_In_  HWND hwnd, _In_  LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam; static time_t tLast = 0;
	::GetClassName(hwnd, szClass, _countof(szClass));
	//if ((_tcsicmp(szClass, _T("TNoPasteEdit")) == 0)){
	//::ShowWindow(hwnd, SW_SHOW);
	//::EnableWindow(hwnd, TRUE);

	if ((_tcsicmp(szClass, _T("TEdit")) == 0)){
		if (hwnd != NULL){
			TCHAR tcPrice[1024] = { 0 };
			::SendMessage(hwnd, WM_GETTEXT, _countof(tcPrice), (LPARAM)tcPrice);
			if (_tcslen(tcPrice) == 6 && ::IsWindowVisible(hwnd)){
				time_t tNow = time(NULL);
				TRACE("Last %s\r\n", tcPrice);

				::PostMessage(pThis->m_hWndImage, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(130, 230));
				::PostMessage(pThis->m_hWndImage, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(130, 230));
				pThis->m_hWndImage = NULL;
				//AfxMessageBox(_T("ok")); 
			}
			return FALSE;
		}
		return TRUE;
	}
	return TRUE;
}

//TErrorBoxForm
BOOL CALLBACK CloseImageForm(HWND hwnd, LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass)); // TImageForm
	if ((_tcsicmp(szClass, _T("TImageCodeForm")) == 0) || (_tcsicmp(szClass, _T("TImageForm")) == 0)){
		if (hwnd != NULL && ::IsWindowVisible(hwnd)){
			pThis->m_hWndImage = hwnd;
			EnumChildWindows(hwnd, GetImageFormChild, lParam);
		}
		return FALSE;
	}
	return TRUE;
}


BOOL CALLBACK GetErrorBoxFormChild(_In_  HWND hwnd, _In_  LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass));
	//if ((_tcsicmp(szClass, _T("TNoPasteEdit")) == 0)){
	::ShowWindow(hwnd, SW_SHOW);
	::EnableWindow(hwnd, TRUE);

	if ((_tcsicmp(szClass, _T("TMemo")) == 0)){
		if (hwnd != NULL ){
			TCHAR tcPrice[1024] = { 0 };
			::SendMessage(hwnd, WM_GETTEXT, _countof(tcPrice), (LPARAM)tcPrice);
			CTime t = CTime::GetCurrentTime();
			CString strInfo; strInfo.Format(_T("%02d:%02d:%02d - �Զ��ر���ʾ[%s]"), t.GetHour(),t.GetMinute(),t.GetSecond(),tcPrice);
			pThis->m_listInfo.InsertString(0,strInfo);
			return FALSE;
		}
		return TRUE;
	}
	return TRUE;
}

//TErrorBoxForm
BOOL CALLBACK CloseErrorBoxForm(HWND hwnd, LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass)); // TMainform
	if ((_tcsicmp(szClass, _T("TErrorBoxForm")) == 0)){
		if (hwnd != NULL){
			EnumChildWindows(hwnd, GetErrorBoxFormChild, lParam);
			::PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(230, 230));
			::PostMessage(hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(230, 230));
		}
		return FALSE;
	}
	return TRUE;
}

void CHackPhoneSrvDlg::OnTimer(UINT_PTR nIDEvent){
	TCHAR tcPrice[1024] = { 0 }; CTime timego; CString strCmd; int len = 0, i = 0, idx = 0; CRect rc300; CPoint pt;
	CDialogEx::OnTimer(nIDEvent);
	if (ID_TIMER_GETSERVERINFO == nIDEvent){
		::SetWindowTextA(m_staServerInfo.GetSafeHwnd(), GetCurServer());
	}else if (ID_TIMER_GETPRICE == nIDEvent && ::IsWindow(m_hWndPrice)){
		rc300.left = 630; rc300.top = 348; rc300.right = 680; rc300.bottom = 375;
		GetCursorPos(&pt); 
		::ScreenToClient(m_hWndMain,&pt);
		if (rc300.PtInRect(pt)){
			::SendMessage(m_hWndMain, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(660, 366));
			::SendMessage(m_hWndMain, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(660, 366));
			::SendMessage(m_hWndPrice, WM_GETTEXT, _countof(tcPrice), (LPARAM)tcPrice);
			CTime tNow = CTime::GetCurrentTime();
			CTime t1(tNow.GetYear(), tNow.GetMonth(), tNow.GetDay(), 10, 58, 0);
			m_timePrice1.GetTime(t1);
			CTime t2(tNow.GetYear(), tNow.GetMonth(), tNow.GetDay(), 11, 29, 46);
			m_timePrice2.GetTime(t2);
			if (m_count == 0 && tNow >= t1){ // ��һ�γ���ʱ�䵽��
				TRACE(_T("%04d-%02d-%02d %02d:%02d:%02d\r\n"),t1.GetYear(),t1.GetMonth(),t1.GetDay(),t1.GetHour(),t1.GetMinute(),t1.GetSecond());
				TCHAR cmd[1024] = { 0 };
				cmd[0] = _T('#'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����#ȷ���ֻ���ʱ����ļ۸�
				Sleep(200);
				cmd[0] = _T('2'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����2ȡ���ո��ֶ���ʱ�ļ۸�
				Sleep(200);
				_tcscpy(cmd, tcPrice); cmd[_tcslen(cmd)] = _T('\n'); theApp.m_ss->SendCmd(cmd); // ���ͼ۸�
				//Sleep(200);
				cmd[0] = _T('#'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����#ȷ���ֻ���ʱ����ļ۸�
				Sleep(200);
				cmd[0] = _T('1'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����1ȷ���۸���Ч�ϱ���
				Sleep(200);
				cmd[0] = _T('1'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����1ȷ���۸���Ч�ϱ���
				Sleep(200);
				m_count += 1;
			}
			else if (m_count == 1 && tNow >= t2){  // �ڶ��γ���ʱ�䵽��
				TRACE(_T("%04d-%02d-%02d %02d:%02d:%02d\r\n"), t2.GetYear(), t2.GetMonth(), t2.GetDay(), t2.GetHour(), t2.GetMinute(), t2.GetSecond());
				TCHAR cmd[1024] = { 0 };
				cmd[0] = _T('#'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����#ȷ���ֻ���ʱ����ļ۸�
				Sleep(200);
				cmd[0] = _T('2'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����2ȡ���ո��ֶ���ʱ�ļ۸�
				Sleep(200);
				_tcscpy(cmd, tcPrice); cmd[_tcslen(cmd)] = _T('\n'); theApp.m_ss->SendCmd(cmd); // ���ͼ۸�
				//Sleep(200);
				cmd[0] = _T('#'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����#ȷ���ֻ���ʱ����ļ۸�
				Sleep(200);
				cmd[0] = _T('1'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����1ȷ���۸���Ч�ϱ���
				Sleep(200);
				cmd[0] = _T('1'); cmd[1] = _T('\n'); cmd[2] = 0; theApp.m_ss->SendCmd(cmd); // ����1ȷ���۸���Ч�ϱ���
				Sleep(200);
				m_count += 1;

			}
		}
	}
	if (m_chkAutoClose.GetCheck()){
		EnumWindows(CloseErrorBoxForm, (LPARAM)this);
		EnumWindows(CloseImageForm, (LPARAM)this);
	}
}


BOOL CALLBACK EnumChildProc2(_In_  HWND hwnd, _In_  LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass));
	//if ((_tcsicmp(szClass, _T("TNoPasteEdit")) == 0)){
	//::ShowWindow(hwnd, SW_SHOW);
	//::EnableWindow(hwnd, TRUE);
	if ((_tcsicmp(szClass, TNoPasteEdit) == 0)){
		if (hwnd != NULL && IsWindowVisible(hwnd)){
				pThis->m_hWndPrice = hwnd;
				return FALSE;
			
		}
		return TRUE;
	}
	return TRUE;
}



BOOL CALLBACK EnumMainForm(HWND hwnd, LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass)); // TMainform
	if ((_tcsicmp(szClass, _T("TMainForm")) == 0)){
		if (hwnd != NULL){
			//::ShowWindow(hwnd, SW_SHOW);
			//::EnableWindow(hwnd, TRUE);
			pThis->m_hWndMain = hwnd;
			EnumChildWindows(hwnd, EnumChildProc2, lParam);
		}
		return FALSE;
	}
	return TRUE;
}

void CHackPhoneSrvDlg::OnBnClickedBnFindprice(){
	TCHAR tcPrice[1024] = { 0 };
	EnumWindows(EnumMainForm, (LPARAM)this);
	//::SendMessage(this->m_hWndPrice, WM_GETTEXT, _countof(tcPrice), (LPARAM)tcPrice);
	//AfxMessageBox(tcPrice);
}


void CHackPhoneSrvDlg::OnDtnDatetimechangeDpGo(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
}


HBRUSH CHackPhoneSrvDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor){
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_PRICE){
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	
	return hbr;
}


void CHackPhoneSrvDlg::OnBnClickedBnMainwnd(){
	//634,366 // 682,395
	//::PostMessage(m_hWndMain, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(660,366));
	//::PostMessage(m_hWndMain, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(660, 366));

	BreakNetbidclient();

	//::PostMessage(m_hWndMain, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(366, 660));
	//::PostMessage(m_hWndMain, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(366, 660));
}


BOOL CHackPhoneSrvDlg::PreTranslateMessage(MSG* pMsg){
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_ESCAPE: return TRUE; //ESC
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CHackPhoneSrvDlg::OnCancel(){
	// TODO:  �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	//ShowWindow(SW_MINIMIZE);
}


void CHackPhoneSrvDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2){
	if (nHotKeyId == 1000){
		CString str = BreakNetbidclient();
		if (str.IsEmpty()) str = _T("�޿�������");
		CTime t = CTime::GetCurrentTime();
		CString strInfo; strInfo.Format(_T("%02d:%02d:%02d - �Ѿ��Ͽ� %s"), t.GetHour(), t.GetMinute(), t.GetSecond(), str);
		m_listInfo.InsertString(0, strInfo);
	}
	else if (nHotKeyId == 1001){
		::PostMessage(m_hWndMain, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(815, 415));
		::PostMessage(m_hWndMain, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(815, 415));
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CHackPhoneSrvDlg::OnBnClickedBnScript(){
	CString strPath;
	theApp.m_ss->SendCmd(_T("52775341#\n"));
	Sleep(1000);
	theApp.m_ss->SendCmd(_T("3678#\n"));
	return;
	CFileDialog fd(TRUE, _T("xbs"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR);
	if (fd.DoModal() == IDOK){
		strPath = fd.GetPathName();
		CStdioFile f; CString strCmd;
		if (f.Open(strPath, CFile::modeRead)){
			m_cmds.RemoveAll();
			while (f.ReadString(strCmd)){
				m_cmds.Add(strCmd);
			}
			f.Close();
		}
	}
}


void CHackPhoneSrvDlg::OnBnClickedBnReset(){
	m_count = 0;
}


void CHackPhoneSrvDlg::OnBnClickedBnPwd(){
	theApp.m_ss->SendCmd(_T("509921#\n"));
}
