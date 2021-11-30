//--------------------------------------------------------------------
//              MFC 4.0  Hello Sample Program
//        Copyright (c) 1996   Top Studio * J.J.Hou
//
// �n��      : hello.h
// ����      : ���
// ��������  : ��ο� hello.mak
//
// ���� Hello ������������ : CMyWinApp �� CMyFrameWnd
//--------------------------------------------------------------------

class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();       // ÿһ��Ӧ�ó���Ӧ�ø�д�˺�ʽ
	virtual BOOL OnIdle(LONG lCount);  // OnIdle ������������ʱ�䣨idle time��
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
	// ע��: callback ��ʽ������ "static"������ȥ�����ص� 'this' ָ�ꡣ
};
//--------------------------------------------------------------------