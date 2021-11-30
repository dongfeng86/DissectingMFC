//--------------------------------------------------------------------
// 檔名      : hello.cpp
// 作者      : 侯俊杰
// 本例示范最简单的 MFC应用程序，不含 Document/View 架构。程序每收到
// WM_PAINT 即利用 GDI 函式 LineDDA()让 "Hello, MFC" 字符串从天而降。
//--------------------------------------------------------------------
#include "Stdafx.h"
#include "Hello.h"
#include "Resource.h"

CMyWinApp theApp;   // application object

//--------------------------------------------------------------------
// CMyWinApp's member
//--------------------------------------------------------------------
BOOL CMyWinApp::InitInstance()
{
	m_pMainWnd = new CMyFrameWnd();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
//--------------------------------------------------------------------
// CMyWinApp's member
//--------------------------------------------------------------------
BOOL CMyWinApp::OnIdle(LONG lCount)
{
	CMyFrameWnd* pWnd = (CMyFrameWnd*)m_pMainWnd;
	pWnd->IdleTimeHandler(lCount);

	return TRUE;
}
//--------------------------------------------------------------------
// CMyFrameWnd's member
//--------------------------------------------------------------------
CMyFrameWnd::CMyFrameWnd()
{
	Create(NULL, "Hello MFC", WS_OVERLAPPEDWINDOW, rectDefault,
		NULL, "MainMenu");     // "MainMenu" 定义于 RC 档
}
//--------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_WM_PAINT()
END_MESSAGE_MAP()
//--------------------------------------------------------------------
void CMyFrameWnd::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;

	GetClientRect(rect);

	dc.SetTextAlign(TA_BOTTOM | TA_CENTER);

	::LineDDA(rect.right / 2, 0, rect.right / 2, rect.bottom / 2,
		(LINEDDAPROC)LineDDACallback, (LPARAM)(LPVOID)&dc);
}
//--------------------------------------------------------------------
VOID CALLBACK CMyFrameWnd::LineDDACallback(int x, int y, LPARAM lpdc)
{
	static char szText[] = "Hello, MFC";

	((CDC*)lpdc)->TextOut(x, y, szText, sizeof(szText) - 1);
	for (int i = 1; i < 50000; i++);  // ?粹是?了延?下降速度，以利?察
}
//--------------------------------------------------------------------
void CMyFrameWnd::OnAbout()
{
	CDialog about("AboutBox", this);  // "AboutBox" 定?于 RC 檔
	about.DoModal();
}
//--------------------------------------------------------------------
void CMyFrameWnd::IdleTimeHandler(LONG lCount)
{
	CString str;
	CRect rect(10, 10, 200, 30);
	CDC* pDC = new CClientDC(this);

	str.Format("%010d", lCount);
	pDC->DrawText(str, &rect, DT_LEFT | DT_TOP);
}
//--------------------------------------------------------------------

