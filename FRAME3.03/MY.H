#include <iostream>
#include "mfc.h"

class CMyWinApp : public CWinApp
{
public:
	CMyWinApp() {
	}
	~CMyWinApp() {
	}

	virtual BOOL InitInstance();
};

class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd();
	~CMyFrameWnd() {
	}
};


class CMyDoc : public CDocument
{
public:
	CMyDoc() {
	}
	~CMyDoc() {
	}
};

class CMyView : public CView
{
public:
	CMyView() {
	}
	~CMyView() {
	}
};

// global function
void PrintAllClasses();
