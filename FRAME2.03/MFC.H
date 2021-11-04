#define BOOL int
#define TRUE 1
#define FALSE 0

#include <iostream>

using std::cout;

class CObject
{
public:
	CObject() {}
	~CObject() {}
};

class CCmdTarget : public CObject
{
public:
	CCmdTarget() {}
	~CCmdTarget() {}
};

class CWinThread : public CCmdTarget
{
public:
	CWinThread() {}
	~CWinThread() {}

	virtual BOOL InitInstance() {
		cout << "CWinThread::InitInstance \n";
		return TRUE;
	}
	virtual int Run() {
		cout << "CWinThread::Run \n";
		return 1;
	}
};

class CWnd;

class CWinApp : public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;

public:
	CWinApp() {
		m_pCurrentWinApp = this;
	}
	~CWinApp() {
	}

	virtual BOOL InitApplication() {
		cout << "CWinApp::InitApplication \n";
		return TRUE;
	}
	virtual BOOL InitInstance() {
		cout << "CWinApp::InitInstance \n";
		return TRUE;
	}
	virtual int Run() {
		cout << "CWinApp::Run \n";
		return CWinThread::Run();
	}
};


class CDocument : public CCmdTarget
{
public:
	CDocument() {}
	~CDocument() {}
};


class CWnd : public CCmdTarget
{
public:
	CWnd() {}
	~CWnd() {}

	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd() {}
	~CFrameWnd() {}
	BOOL Create();
	virtual BOOL PreCreateWindow();
};

class CView : public CWnd
{
public:
	CView() {}
	~CView() {}
};


// global function

CWinApp* AfxGetApp();

