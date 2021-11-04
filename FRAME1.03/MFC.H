#include <iostream>

using std::cout;

class CObject
{
public:
	CObject() {
		cout << "CObject Constructor \n";
	}
	~CObject() {
		cout << "CObject Destructor \n";
	}
};

class CCmdTarget : public CObject
{
public:
	CCmdTarget() {
		cout << "CCmdTarget Constructor \n";
	}
	~CCmdTarget() {
		cout << "CCmdTarget Destructor \n";
	}
};

class CWinThread : public CCmdTarget
{
public:
	CWinThread() {
		cout << "CWinThread Constructor \n";
	}
	~CWinThread() {
		cout << "CWinThread Destructor \n";
	}
};

class CWinApp : public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;

public:
	CWinApp() {
		cout << "CWinApp Constructor \n";
		m_pCurrentWinApp = this;
	}
	~CWinApp() {
		cout << "CWinApp Destructor \n";
	}
};



class CDocument : public CCmdTarget
{
public:
	CDocument() {
		cout << "CDocument Constructor \n";
	}

	~CDocument() {
		cout << "CDocument Destructor \n";
	}
};


class CWnd : public CCmdTarget
{
public:
	CWnd() {
		cout << "CWnd Constructor \n";
	}
	~CWnd() {
		cout << "CWnd Destructor \n";
	}
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd() {
		cout << "CFrameWnd Constructor \n";
	}
	~CFrameWnd() {
		cout << "CFrameWnd Destructor \n";
	}
};

class CView : public CWnd
{
public:
	CView() {
		cout << "CView Constructor \n";
	}
	~CView() {
		cout << "CView Destructor \n";
	}
};


// global function

CWinApp* AfxGetApp();

