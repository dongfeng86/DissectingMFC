//--------------------------------------------------------------------
//              MFC 4.0  Hello Sample Program
//        Copyright (c) 1996   Top Studio * J.J.Hou
//
// 檔名      : hello.h
// 作者      : 侯俊杰
// 编译联结  : 请参考 hello.mak
//
// 宣告 Hello 程序的两个类别 : CMyWinApp 和 CMyFrameWnd
//--------------------------------------------------------------------

class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();       // 每一个应用程序都应该改写此函式
	virtual BOOL OnIdle(LONG lCount);  // OnIdle 用来处理空闲时间（idle time）
};

//--------------------------------------------------------------------
class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd();            // constructor
	afx_msg void OnPaint();   // for WM_PAINT
	afx_msg void OnAbout();   // for WM_COMMAND (IDM_ABOUT)
	void IdleTimeHandler(LONG lCount);  // we want it call by CMyWinApp::OnIdle

private:
	DECLARE_MESSAGE_MAP()     // Declare Message Map
	static VOID CALLBACK LineDDACallback(int, int, LPARAM);
	// 注意: callback 函式必须是 "static"，才能去除隐藏的 'this' 指标。
};
//--------------------------------------------------------------------
