#include <afxwin.h>   //��дMFC���򣬱��������ͷ�ļ�
HHOOK hk;    //���ڱ��氲װ���Ӻ�Ĺ��Ӿ����

LRESULT CALLBACK f(HWND h, UINT u, WPARAM w, LPARAM l)  /*���̺��������ڼ�����Ϣ���β�w������Ǽ��̰��µİ���ASCII�롣*/
{
	switch (u) {
	case WM_KEYDOWN: {//�����¼����ϵİ���ʱִ��������Ϣ��������F���⣬���������ᱻ�������ء�
		if (w == 0x41) { 
			::MessageBox(NULL, "AAA", "", 0); } //���°���Aʱ�����Ի���
		if (w == 0x42) { 
			::MessageBox(NULL, "BBB", "", 0); }//���°���Bʱ�����Ի���
		if (w == 0x43) { 
			::MessageBox(NULL, "CCC", "", 0); }
		if (w == 0x44) { 
			::MessageBox(NULL, "DDD", "", 0); }
		if (w == 0x45) { 
			::MessageBox(NULL, "EEE", "", 0); }
		if (w == 0x46) { 
			::MessageBox(NULL, "FFF", "", 0); }//���°���F
		break;	
	}
	case WM_DESTROY: {	
		PostQuitMessage(0);		
		break; 
	}
	default:
		return ::DefWindowProc(h, u, w, l);
	}	
	return 0;
}   //f����

//���Ӻ���g
LRESULT CALLBACK g(int code, WPARAM w, LPARAM l) 
{ 
	//���Ӻ����ķ�������CALLBACK����ʡ�ԡ�
	if (w == 0x41) {					//���ذ���A����Ϣ
		::MessageBox(NULL, "A--", "", 0);  //������Ϣ��
		return 1;
	}     //���ط���ֵ��ʾ��������Ϣ���ݵ�Ŀ�괰��
	if (w == 0x42) {
		::MessageBox(NULL, "B--", "", 0);//���ذ���B����Ϣ��
		return 0;
	}    //����0����ʾ����������Ϣ���ݵ�Ŀ�괰��
	if (w == 0x43) {
		::MessageBox(NULL, "C--", "", 0);//���ذ���C����Ϣ
		UnhookWindowsHookEx(hk); //�Ƴ�(ж��)���������а�װ�Ĺ��Ӻ���g(�������Ӻ���)��
		return 0;
	}    //��������Ϣ
	if (w == 0x44) {			//���ذ���D����Ϣ
		CallNextHookEx(hk, code, w, l);/*�����ص�����Ϣ���ݸ����������е���һ�����Ӻ���(����Ϊgg����)���д���*/
		return 0;
	}
	return 0;
}   //����������������Ϣ���ݵ�Ŀ�괰��

//���Ӻ���gg
LRESULT CALLBACK gg(int code, WPARAM w, LPARAM l) 
{
	if (w == 0x44) { 
		::MessageBox(NULL, "D--", "", 0); return 1; 
	}  /*���ذ���D����Ϣ������������Ϣ���ݵ�Ŀ�괰��*/
	if (w == 0x45) {
		::MessageBox(NULL, "E--", "", 0); return 1; 
	}
	return 1;
} //��������������Ϣ���ݵ�Ŀ�괰�ڣ�gg����

//��������
class B :public CFrameWnd
{
public:
	B()	{
		Create("HH", "H", WS_OVERLAPPEDWINDOW);
	}

	BOOL CreateEx(       //�ض���CWnd::CreateEx�����Զ���Ĵ���
		DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, int x, int y, int nWidth, int nHeight,
		HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
	{
		HINSTANCE hs = AfxGetModuleState()->m_hCurrentInstanceHandle;
		WNDCLASSEX w;
		memset(&w, 0, sizeof(w)); 	 //�ѽṹ��w�����г�Ա��ֵ��ʼ��Ϊ��
		w.hInstance = hs;  	
		w.cbSize = sizeof(w);  
		w.lpszClassName = "HH";
		w.lpfnWndProc = f;  //���ù��̺���Ϊf����ʾ����Ҫ�ù��̺���������ʾ
		::RegisterClassEx(&w);
		HWND h = ::CreateWindow("HH", "H", WS_OVERLAPPEDWINDOW, 0, 0, 350, 280, 0, 0, hs, 0);
		::ShowWindow(h, 1);  
		::UpdateWindow(h);    //����CreateEx�����Ĵ���Ӧ�ڴ˴���ʾ
		return 1;
	}
};  //��B����

class A :public CWinApp 
{
public:
	BOOL InitInstance() {
		m_pMainWnd = new B();
		//��װ�������ؼ�����Ϣ����װ�Ĺ��Ӻ�����ִ�У������Ӻ���g����ggִ�С�
		hk = ::SetWindowsHookEx(WH_KEYBOARD, gg, 0, ::GetCurrentThreadId());
		hk = ::SetWindowsHookEx(WH_KEYBOARD, g, 0, ::GetCurrentThreadId());
		return 1;
	}
};   //��A����

A ma;