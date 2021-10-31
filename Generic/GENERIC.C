//---------------------------------------------------------------------
//           Generic - win32程序的基础写法
// 郎     : generic.c
//---------------------------------------------------------------------

#include <windows.h>   // 每一个Windows程序都需要载入此头文件
#include "resource.h"  // 资源的ID
#include "generic.h"   // 本程序的头文件

HINSTANCE _hInst;      // Instance handle
HWND      _hWnd;

char _szAppName[] = "Generic";    //程序名称
char _szTitle[] = "Generic Sample Application"; //窗口标题

//---------------------------------------------------------------------
// WinMain - 程序进入点
//---------------------------------------------------------------------
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	UNREFERENCED_PARAMETER(lpCmdLine);      // 避免编译时的警告

	if (!hPrevInstance)
		if (!InitApplication(hInstance))
			return (FALSE);

	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam); // 肚 PostQuitMessage 把计
}
//---------------------------------------------------------------------
// InitApplication - 注册窗口类
//---------------------------------------------------------------------
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;     // 窗口函数，窗口行为中枢
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, "jjhouricon");
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);  // 窗口后台颜色
	wc.lpszMenuName = "GenericMenu";                // .RC所定义的窗体
	wc.lpszClassName = _szAppName;

	return (RegisterClass(&wc));
}
//---------------------------------------------------------------------
// InitInstance - 产生窗口
//---------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	_hInst = hInstance; // 储存为全局变量，方便使用

	_hWnd = CreateWindow(
		_szAppName,
		_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!_hWnd)
		return (FALSE);

	ShowWindow(_hWnd, nCmdShow); // 显示窗口
	UpdateWindow(_hWnd);         // 送出WM_PAINT
	return (TRUE);
}
//---------------------------------------------------------------------
// WndProc - 窗口函数
//---------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message) {
	case WM_COMMAND:

		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId) {
		case IDM_ABOUT:
			DialogBox(_hInst,
				"AboutBox",     // 对话框资源名称
				hWnd,           // 父窗口
				(DLGPROC)About  // 对话框函数名称
			);
			break;

		case IDM_EXIT:
			// 使用者想要结束程序，处理方式与WM_CLOSE相同
			DestroyWindow(hWnd);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
		}
		break;

	case WM_DESTROY:  // 窗口已经被摧毁（程序即将结束）
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}
//---------------------------------------------------------------------
// About - 对话框函数
//---------------------------------------------------------------------
LRESULT CALLBACK About(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);      // 避免编译时警告

	switch (message) {
	case WM_INITDIALOG:
		return (TRUE);      // TRUE 表示我已处理过这个消息

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK
			|| LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, TRUE);
			return (TRUE);  // TRUE 表示我已处理过这个消息
		}
		break;
	}
	return (FALSE); // FALSE 表示我没有处理这个消息
}
//------------------------ end of file ------------------------------
