#define TRUE 1
#define FALSE 0

typedef char* LPSTR;
typedef const char* LPCSTR;

typedef unsigned long  DWORD;
typedef int            BOOL;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef int            INT;
typedef unsigned int   UINT;
typedef long           LONG;

#define WM_COMMAND             0x0111
#define CObjectid              0xffff
#define   CCmdTargetid         1
#define     CWinThreadid       11
#define       CWinAppid        111
#define         CMyWinAppid    1111
#define     CWndid             12
#define       CFrameWndid      121
#define         CMyFrameWndid  1211
#define       CViewid          122
#define         CMyViewid      1221
#define     CDocumentid        13
#define       CMyDocid         131

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

///////////////////////////////////////////////////////////////////////
// Window message map handling

struct AFX_MSGMAP_ENTRY;       // declared below after CWnd

struct AFX_MSGMAP
{
	AFX_MSGMAP* pBaseMessageMap;
	AFX_MSGMAP_ENTRY* lpEntries;
};

#define DECLARE_MESSAGE_MAP() \
        static AFX_MSGMAP_ENTRY _messageEntries[]; \
        static AFX_MSGMAP messageMap; \
        virtual AFX_MSGMAP* GetMessageMap() const;

#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
        AFX_MSGMAP* theClass::GetMessageMap() const \
                { return &theClass::messageMap; } \
        AFX_MSGMAP theClass::messageMap = \
        { &(baseClass::messageMap), \
                (AFX_MSGMAP_ENTRY*) &(theClass::_messageEntries) }; \
        AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
        {

#define END_MESSAGE_MAP() \
        { 0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } \
        };

// Message map signature values and macros in separate header
#include <afxmsg_.h>

class CObject
{
public:
	CObject() {	}
	~CObject() {	}
};

class CCmdTarget : public CObject
{
public:
	CCmdTarget() {	}
	~CCmdTarget() {	}
	DECLARE_MESSAGE_MAP()       // base class - no {{ }} macros
};

typedef void (CCmdTarget::*AFX_PMSG)(void);

struct AFX_MSGMAP_ENTRY  // MFC 4.0
{
	UINT nMessage; // windows message
	UINT nCode;    // control code or WM_NOTIFY code
	UINT nID;      // control ID (or 0 for windows messages)
	UINT nLastID;  // used for entries specifying a range of control id's
	UINT nSig;     // signature type (action) or pointer to message #
	AFX_PMSG pfn;  // routine to call (or special value)
};

class CWinThread : public CCmdTarget
{
public:
	CWinThread() {	}
	~CWinThread() {	}

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

	DECLARE_MESSAGE_MAP()
};

typedef void (CWnd::*AFX_PMSGW)(void);
// like 'AFX_PMSG' but for CWnd derived classes only

class CDocument : public CCmdTarget
{
public:
	CDocument() {
	}
	~CDocument() {
	}
	DECLARE_MESSAGE_MAP()
};

class CWnd : public CCmdTarget
{
public:
	CWnd() {
	}
	~CWnd() {
	}

	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();

	DECLARE_MESSAGE_MAP()
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd() {
	}
	~CFrameWnd() {
	}
	BOOL Create();
	virtual BOOL PreCreateWindow();

	DECLARE_MESSAGE_MAP()
};

class CView : public CWnd
{
public:
	CView() {
	}
	~CView() {
	}
	DECLARE_MESSAGE_MAP()
};

// global function
CWinApp* AfxGetApp();
