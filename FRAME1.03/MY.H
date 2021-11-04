
#include <iostream>
#include "mfc.h"

class CMyWinApp : public CWinApp
{
public:
	CMyWinApp() {
		cout << "CMyWinApp Constructor \n";
	}
	~CMyWinApp() {
		cout << "CMyWinApp Destructor \n";
	}
};

class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd() {
		cout << "CMyFrameWnd Constructor \n";
	}
	~CMyFrameWnd() {
		cout << "CMyFrameWnd Destructor \n";
	}
};

