#include "stdafx.h"
#include "OnScreenKeyboard.h"
#include "OnScreenKeyboardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COnScreenKeyboardDlg::COnScreenKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COnScreenKeyboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hForegroundWnd = NULL;
	kb = new keyboard(this);
}

void COnScreenKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL COnScreenKeyboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	kb->create_keys(1280,480);

	int maxX = 1280, maxY = 480;
	MoveWindow(0, 0, maxX, maxY);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COnScreenKeyboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void COnScreenKeyboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		RECT client;
		GetClientRect(&client);
		//COLORREF color=pDC->GetBkColor();
		COLORREF color = ::GetSysColor(COLOR_WINDOW);
		//FillRect(pDC->m_hDC,&client,::GetStockObject(GRAY_BRUSH));
		//pDC->FillSolidRect(&client,color);

		dc.FillSolidRect(&client, RGB(0, 0, 0));
		kb->show();
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COnScreenKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COnScreenKeyboardDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (!m_hForegroundWnd)
	{
		m_hForegroundWnd = ::GetForegroundWindow();
		ModifyStyleEx(WS_EX_NOACTIVATE,0);
		SetForegroundWindow();
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}

void COnScreenKeyboardDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_hForegroundWnd)
	{
		::SetForegroundWindow(m_hForegroundWnd);
		ModifyStyleEx(0,WS_EX_NOACTIVATE);
		m_hForegroundWnd = NULL;
	}

	CDialog::OnMouseMove(nFlags, point);
}

void COnScreenKeyboardDlg::OnBnClickedSendX()
{
	INPUT keyInput;
	keyInput.type = INPUT_KEYBOARD;
	
	KEYBDINPUT key;
	key.wVk = 88;
	key.wScan = ::VkKeyScan(88);
		
	key.dwFlags = 0;
	keyInput.ki = key;
	::SendInput(1,&keyInput,sizeof(INPUT));
	
	key.dwFlags = KEYEVENTF_KEYUP;
	keyInput.ki = key;
	::SendInput(1,&keyInput,sizeof(INPUT));
}

BEGIN_MESSAGE_MAP(COnScreenKeyboardDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_SEND_X, &COnScreenKeyboardDlg::OnBnClickedSendX)
	ON_MESSAGE(WM_SHIFT_PRESSED, OnMessageShiftChanged)
	ON_MESSAGE(WM_CAPS_PRESSED, OnMessageCapsChanged)
	ON_MESSAGE(WM_HIDE_APP, OnMessageHideApp)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

COnScreenKeyboardDlg::CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void COnScreenKeyboardDlg::CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COnScreenKeyboardDlg::CAboutDlg, CDialog)
END_MESSAGE_MAP()


void COnScreenKeyboardDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	int maxX = 1280, maxY = 480;
	if (nType == SIZE_MAXIMIZED) {
		MoveWindow(0, 0, maxX, maxY);
	}
	if (kb->keyboard_created()) {
		kb->arrange_keys(cx, cy);
		kb->show();
	}
}
LRESULT COnScreenKeyboardDlg::OnMessageShiftChanged(WPARAM wParam, LPARAM lParam) {
	kb->notify_shift_change(wParam);
	Invalidate();
	return 0;
}

LRESULT COnScreenKeyboardDlg::OnMessageCapsChanged(WPARAM wParam, LPARAM lParam) {
	kb->notify_caps_change(wParam);
	Invalidate();
	return 0;
}

LRESULT COnScreenKeyboardDlg::OnMessageHideApp(WPARAM wParam, LPARAM lParam) {
	ShowWindow(0);
	return 0;
}

void COnScreenKeyboardDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	HWND sonoquestHwnd = ::FindWindowA("SonoquestDlg", NULL);
	if (sonoquestHwnd != 0)
	{
		char* lpszString = (char*)"MouseMove";
		COPYDATASTRUCT cds;
		cds.dwData = 1;
		cds.cbData = strlen(lpszString) + 1;
		cds.lpData = lpszString;
		::SendMessage(sonoquestHwnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)(LPVOID)&cds);
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void COnScreenKeyboardDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	kb->release();
	CDialog::OnClose();
}


void COnScreenKeyboardDlg::OnDestroy()
{
	CDialog::OnDestroy();
	kb->release();
	// TODO: Add your message handler code here
}
