
// HackPhoneSrvDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HackPhoneSrv.h"
#include "HackPhoneSrvDlg.h"
#include "afxdialogex.h"
#include "SocketSrv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_TIMER_GETPRICE 1

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
	DDX_Control(pDX, IDC_DP_GO, m_dpGo);
	DDX_Control(pDX, IDC_STATIC_PRICE, m_staPrice);
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
	m_wndNumpad.Create(className, _T("NumPad01"), WS_CHILD  , CRect(0, 0, 0, 0), this, 0);
	m_fontPrice.CreatePointFont(680,_T("����"));
	m_staPrice.SetFont(&m_fontPrice);
	theApp.m_ss = new CSocketSrv();
	theApp.m_ss->Create(1996);
	theApp.m_ss->Listen();
	PostMessage(WM_SIZE);
	SetTimer(ID_TIMER_GETPRICE, 10, NULL);
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE);

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
}


void CHackPhoneSrvDlg::OnBnClickedOk(){
}


void CHackPhoneSrvDlg::OnSize(UINT nType, int cx, int cy){
	CDialogEx::OnSize(nType, cx, cy);
	CRect rc; GetClientRect(rc);
	rc.DeflateRect(0,80,0,0);
	if (IsWindow(m_wndNumpad.GetSafeHwnd())) m_wndNumpad.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
}


void CHackPhoneSrvDlg::OnTimer(UINT_PTR nIDEvent){
	TCHAR tcPrice[1024] = { 0 }; CTime timego; CString strCmd; int len = 0,i = 0,idx = 0;
	CDialogEx::OnTimer(nIDEvent);
	if (ID_TIMER_GETPRICE == nIDEvent && ::IsWindow(m_hWndPrice)){
		::SendMessage(m_hWndPrice, WM_GETTEXT, _countof(tcPrice), (LPARAM)tcPrice);
		len = _tcslen(tcPrice);
		if (len > 0){
			m_staPrice.SetWindowText(tcPrice);
			/*
			CTime t = CTime::GetCurrentTime();
			m_dpGo.GetTime(timego);
			//if ((t.GetHour() * 10000 + t.GetMinute() * 100 + t.GetSecond()) > 112945){
			if (t.GetHour() == timego.GetHour() && t.GetMinute() == timego.GetMinute() &&
				t.GetSecond() >= timego.GetSecond()){
				for (i = 0; i < len; i++){
					switch (tcPrice[i]){
					case _T('0'): idx = 0; break;
					case _T('1'): idx = 1; break;
					case _T('2'): idx = 2; break;
					case _T('3'): idx = 3; break;
					case _T('4'): idx = 4; break;
					case _T('5'): idx = 5; break;
					case _T('6'): idx = 6; break;
					case _T('7'): idx = 7; break;
					case _T('8'): idx = 8; break;
					case _T('9'): idx = 9; break;
					}
					strCmd.AppendFormat(_T("input tap %d %d\n"), m_wndNumpad.m_pt[idx].x, m_wndNumpad.m_pt[idx].y);
				}
				strCmd.AppendFormat(_T("input tap %d %d\n"), m_wndNumpad.m_pt[11].x, m_wndNumpad.m_pt[11].y);
				AfxMessageBox(strCmd);
				theApp.m_ss->SendCmd(strCmd);
				KillTimer(ID_TIMER_GETPRICE);
			}
			*/
		}
	}
}


BOOL CALLBACK EnumChildProc2(_In_  HWND hwnd, _In_  LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass));
	//if ((_tcsicmp(szClass, _T("TNoPasteEdit")) == 0)){
	if ((_tcsicmp(szClass, _T("TEdit")) == 0)){
		if (hwnd != NULL && IsWindowVisible(hwnd)){
				pThis->m_hWndPrice = hwnd;
				return FALSE;
			
		}
		return TRUE;
	}
	return TRUE;
}



BOOL CALLBACK EnumMainForm(HWND hwnd, LPARAM lParam){
	TCHAR szClass[1024] = { 0 }; RECT rc; CHackPhoneSrvDlg* pThis = (CHackPhoneSrvDlg*)lParam;
	::GetClassName(hwnd, szClass, _countof(szClass)); // TMainform
	if ((_tcsicmp(szClass, _T("TMainForm")) == 0)){
		if (hwnd != NULL){
			::ShowWindow(hwnd, SW_SHOW);
			::EnableWindow(hwnd, TRUE);
			EnumChildWindows(hwnd, EnumChildProc2, lParam);
		}
		return FALSE;
	}
	return TRUE;
}

void CHackPhoneSrvDlg::OnBnClickedBnFindprice(){
	TCHAR tcPrice[1024] = { 0 };
	EnumWindows(EnumMainForm, (LPARAM)this);
	::SendMessage(this->m_hWndPrice, WM_GETTEXT, _countof(tcPrice), (LPARAM)tcPrice);
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
