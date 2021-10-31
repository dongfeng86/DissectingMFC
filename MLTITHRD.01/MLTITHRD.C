//--------------------------------------------------------------------
//           Mltithrd - 示范 threads 的产生与优先权的设定
//                      Top Studio * J.J.Hou
//
// 檔名     : mltithrd.c
// 作者     : 侯俊杰
// 编译联结 : 请参考 mltithrd.mak
// 创意来源 : "Multitask Windows NT" Chap6 (joel Powell/WAITE GROUP PRESS)
//
// 说明 : 本例产生 5 个 threads，各给予不同之优先权 (priority)；每个
//        threads 执行 1000 次回路，回路中不断绘四方形，代表执行进度。
//        以此观察 threads 之独立情况以及优先权不同所带来之影响。
//
//        你可以选择以 Sleep() 或单纯之 for loop 延迟 thread 的进行，
//        这也有助于你观察 thread 释放控制权。
//--------------------------------------------------------------------

#include <windows.h>
#include "mltithrd.h"

// 全局变量
HANDLE _hInst;
HANDLE _hWnd;
HANDLE _hThread[5];
UINT   _uDelayType = NODELAY;

//--------------------------------------------------------------------
// WinMain : 程序进入点
//--------------------------------------------------------------------
int APIENTRY WinMain(HANDLE hInstance, HANDLE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG  msg;
	WNDCLASS wndclass;

	UNREFERENCED_PARAMETER(lpCmdLine);      // 避免编译时的警告
	UNREFERENCED_PARAMETER(hPrevInstance);

	_hInst = hInstance;

	wndclass.style = 0;
	wndclass.lpfnWndProc = (WNDPROC)MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, "Multi1Icon");
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = "Multi1Menu";
	wndclass.lpszClassName = "Multi1Class";

	RegisterClass(&wndclass);

	_hWnd = CreateWindow("Multi1Class",
		"Thread Priority Example",
		WS_OVERLAPPED | WS_SYSMENU,
		0, 0, 400, 250,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}
//--------------------------------------------------------------------
// MainWndProc - 主窗口函数
//--------------------------------------------------------------------
LONG APIENTRY MainWndProc(HWND hWnd, UINT message,
	UINT wParam, LONG lParam)
{
	int    i;
	DWORD  ThreadID[5];
	static HMENU  hMenu;
	static HANDLE hMasterThread;
	static DWORD  ThreadArg[5] = { HIGHEST_THREAD,    // 0x00
								  ABOVE_AVE_THREAD,  // 0x3F
								  NORMAL_THREAD,     // 0x7F
								  BELOW_AVE_THREAD,  // 0xBF
								  LOWEST_THREAD      // 0xFF
	};    // 用来调整四方形颜色

	switch (message) {
	case WM_CREATE:
		hMenu = GetMenu(hWnd);

		// 取得 primary thread handle 并设为最高 priority
		hMasterThread = GetCurrentThread();
		SetThreadPriority(hMasterThread, THREAD_PRIORITY_HIGHEST);

		for (i = 0; i < 5; i++)   // 产生 5 个 threads
			_hThread[i] = CreateThread(NULL,
				0,
				(LPTHREAD_START_ROUTINE)ThreadProc,
				&ThreadArg[i],
				CREATE_SUSPENDED,
				&ThreadID[i]);
		// 设定 thread priorities
		SetThreadPriority(_hThread[0], THREAD_PRIORITY_HIGHEST);
		SetThreadPriority(_hThread[1], THREAD_PRIORITY_ABOVE_NORMAL);
		SetThreadPriority(_hThread[2], THREAD_PRIORITY_NORMAL);
		SetThreadPriority(_hThread[3], THREAD_PRIORITY_BELOW_NORMAL);
		SetThreadPriority(_hThread[4], THREAD_PRIORITY_LOWEST);
		return (0);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_RESUME:       // 让 threads 开始执行
			EnableMenuItem(hMenu, IDM_RESUME, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_SUSPEND, MF_BYCOMMAND | MF_ENABLED);
			DrawMenuBar(hWnd);
			for (i = 0; i < 5; i++)
				ResumeThread(_hThread[i]);   // 启动 threads 的执行
			return (0);

		case IDM_SUSPEND:  // 暂停 threads 的执行
			for (i = 0; i < 5; i++)
				SuspendThread(_hThread[i]);   // 暂停 threads 的执行
			EnableMenuItem(hMenu, IDM_SUSPEND, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_RESUME, MF_BYCOMMAND | MF_ENABLED);
			DrawMenuBar(hWnd);
			return (0);

		case IDM_FOR:    // 以 for loop 延迟 thread 的执行
			_uDelayType = FORLOOPDELAY;
			EnableMenuItem(hMenu, IDM_FOR, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_SLEEP, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, IDM_NODELAY, MF_BYCOMMAND | MF_ENABLED);
			DrawMenuBar(hWnd);
			return (0);

		case IDM_SLEEP:  // 以 Sleep() 延迟 thread 的执行
			_uDelayType = SLEEPDELAY;
			EnableMenuItem(hMenu, IDM_SLEEP, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_FOR, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, IDM_NODELAY, MF_BYCOMMAND | MF_ENABLED);
			DrawMenuBar(hWnd);
			return (0);

		case IDM_NODELAY:  // 不延迟 thread 的执行
			_uDelayType = NODELAY;
			EnableMenuItem(hMenu, IDM_NODELAY, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_FOR, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(hMenu, IDM_SLEEP, MF_BYCOMMAND | MF_ENABLED);
			DrawMenuBar(hWnd);
			return (0);

		default:
			return (0);
		}

	case WM_DESTROY:
		for (i = 0; i < 5; i++)
			TerminateThread(_hThread[i], 0);   // 终止 threads
		PostQuitMessage(0);
		return (0);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return (0L);
}
//--------------------------------------------------------------------
// ThreadProc() - 本例之 5 个 threads 共享之 thread procedure
//--------------------------------------------------------------------
VOID ThreadProc(DWORD *ThreadArg)
{
	RECT rect;
	HDC  hDC;
	HANDLE hBrush, hOldBrush;
	DWORD dwThreadHits = 0;
	char  cBuf[80];
	int   iThreadNo, i;

	GetClientRect(_hWnd, &rect);
	hDC = GetDC(_hWnd);
	hBrush = CreateSolidBrush(RGB(*(ThreadArg), *(ThreadArg), *(ThreadArg)));  // 变化画刷颜色
	hOldBrush = SelectObject(hDC, hBrush);

	switch (*ThreadArg) {
	case HIGHEST_THREAD: iThreadNo = 0; break;
	case ABOVE_AVE_THREAD: iThreadNo = 1; break;
	case NORMAL_THREAD: iThreadNo = 2; break;
	case BELOW_AVE_THREAD: iThreadNo = 3; break;
	case LOWEST_THREAD: iThreadNo = 4; break;
	}

	// 显示 thread 号码及其优先权 (priority)
	wsprintf(cBuf, "T%d", iThreadNo);
	TextOut(hDC, *(ThreadArg), rect.bottom - 150, cBuf, lstrlen(cBuf));
	wsprintf(cBuf, "P=%d", GetThreadPriority(_hThread[iThreadNo]));
	TextOut(hDC, *(ThreadArg), rect.bottom - 130, cBuf, lstrlen(cBuf));

	do
	{
		dwThreadHits++;       // 计数器

		// 画出四方形，代表 thread 的进行
		Rectangle(hDC, *(ThreadArg), rect.bottom - (dwThreadHits / 10),
			*(ThreadArg)+0x40, rect.bottom);

		// 延迟...
		if (_uDelayType == SLEEPDELAY)
			Sleep(10);
		else if (_uDelayType == FORLOOPDELAY)
			for (i = 0; i < 3000000; i++);
		else // _uDelayType == NODELAY)
		{
		}
	} while (dwThreadHits < 10000000);      // 巡回  1000 次

	hBrush = SelectObject(hDC, hOldBrush);   // 恢复画刷颜色
	DeleteObject(hBrush);
	ReleaseDC(_hWnd, hDC);
}
//------------------------- end of file ------------------------------

