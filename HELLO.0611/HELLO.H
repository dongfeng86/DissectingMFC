//--------------------------------------------------------------------
//              MFC 4.0  Hello Sample Program
//        Copyright (c) 1996   Top Studio * J.J.Hou
//
// �ɦW      : hello.h
// �@��      : �J�T��
// �sĶ�p��  : �аѦ� hello.mak
//
// �ŧi Hello �{����������O : CMyWinApp �M CMyFrameWnd
//--------------------------------------------------------------------

class CMyWinApp : public CWinApp
{
public:
   virtual BOOL InitInstance();       // �C�@�����ε{�������ӧ�g���禡
   virtual BOOL OnIdle(LONG lCount);  // OnIdle �ΨӳB�z���m�ɶ��]idle time�^
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
   static VOID CALLBACK LineDDACallback(int,int,LPARAM);
   // �`�N: callback �禡�����O "static"�A�~��h�����ê� 'this' ���СC
};
//--------------------------------------------------------------------

