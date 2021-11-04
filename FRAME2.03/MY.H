
#include <iostream>
#include "mfc.h"

class CMyWinApp : public CWinApp
{
public:
	CMyWinApp() {}
	~CMyWinApp() {}

	virtual BOOL InitInstance();
};

class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd();
	~CMyFrameWnd() {}
};


