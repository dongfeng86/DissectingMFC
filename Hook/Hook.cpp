#include <afxwin.h>   //编写MFC程序，必须包含此头文件
HHOOK hk;    //用于保存安装钩子后的钩子句柄。

LRESULT CALLBACK f(HWND h, UINT u, WPARAM w, LPARAM l)  /*过程函数，对于键盘消息，形参w保存的是键盘按下的按键ASCII码。*/
{
	switch (u) {
	case WM_KEYDOWN: {//当按下键盘上的按键时执行以下消息，除按下F键外，其他按键会被钩子拦截。
		if (w == 0x41) { 
			::MessageBox(NULL, "AAA", "", 0); } //按下按键A时弹出对话框
		if (w == 0x42) { 
			::MessageBox(NULL, "BBB", "", 0); }//按下按键B时弹出对话框
		if (w == 0x43) { 
			::MessageBox(NULL, "CCC", "", 0); }
		if (w == 0x44) { 
			::MessageBox(NULL, "DDD", "", 0); }
		if (w == 0x45) { 
			::MessageBox(NULL, "EEE", "", 0); }
		if (w == 0x46) { 
			::MessageBox(NULL, "FFF", "", 0); }//按下按键F
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
}   //f结束

//钩子函数g
LRESULT CALLBACK g(int code, WPARAM w, LPARAM l) 
{ 
	//钩子函数的返回类型CALLBACK不能省略。
	if (w == 0x41) {					//拦截按键A的消息
		::MessageBox(NULL, "A--", "", 0);  //弹出消息框
		return 1;
	}     //返回非零值表示阻塞该消息传递到目标窗口
	if (w == 0x42) {
		::MessageBox(NULL, "B--", "", 0);//拦截按键B的消息，
		return 0;
	}    //返回0，表示不阻塞该消息传递到目标窗口
	if (w == 0x43) {
		::MessageBox(NULL, "C--", "", 0);//拦截按键C的消息
		UnhookWindowsHookEx(hk); //移除(卸载)钩子链表中安装的钩子函数g(即本钩子函数)。
		return 0;
	}    //不阻塞消息
	if (w == 0x44) {			//拦截按键D的消息
		CallNextHookEx(hk, code, w, l);/*把拦截到的消息传递给钩子链表中的下一个钩子函数(本例为gg函数)进行处理*/
		return 0;
	}
	return 0;
}   //不阻塞其他按键消息传递到目标窗口

//钩子函数gg
LRESULT CALLBACK gg(int code, WPARAM w, LPARAM l) 
{
	if (w == 0x44) { 
		::MessageBox(NULL, "D--", "", 0); return 1; 
	}  /*拦截按键D的消息，并阻塞该消息传递到目标窗口*/
	if (w == 0x45) {
		::MessageBox(NULL, "E--", "", 0); return 1; 
	}
	return 1;
} //阻塞其他按键消息传递到目标窗口，gg结束

//创建窗口
class B :public CFrameWnd
{
public:
	B()	{
		Create("HH", "H", WS_OVERLAPPEDWINDOW);
	}

	BOOL CreateEx(       //重定义CWnd::CreateEx创建自定义的窗口
		DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
		DWORD dwStyle, int x, int y, int nWidth, int nHeight,
		HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
	{
		HINSTANCE hs = AfxGetModuleState()->m_hCurrentInstanceHandle;
		WNDCLASSEX w;
		memset(&w, 0, sizeof(w)); 	 //把结构体w的所有成员的值初始化为。
		w.hInstance = hs;  	
		w.cbSize = sizeof(w);  
		w.lpszClassName = "HH";
		w.lpfnWndProc = f;  //设置过程函数为f，本示例需要该过程函数进行演示
		::RegisterClassEx(&w);
		HWND h = ::CreateWindow("HH", "H", WS_OVERLAPPEDWINDOW, 0, 0, 350, 280, 0, 0, hs, 0);
		::ShowWindow(h, 1);  
		::UpdateWindow(h);    //重载CreateEx创建的窗口应在此处显示
		return 1;
	}
};  //类B结束

class A :public CWinApp 
{
public:
	BOOL InitInstance() {
		m_pMainWnd = new B();
		//安装钩子拦截键盘消息，后安装的钩子函数先执行，即钩子函数g先于gg执行。
		hk = ::SetWindowsHookEx(WH_KEYBOARD, gg, 0, ::GetCurrentThreadId());
		hk = ::SetWindowsHookEx(WH_KEYBOARD, g, 0, ::GetCurrentThreadId());
		return 1;
	}
};   //类A结束

A ma;