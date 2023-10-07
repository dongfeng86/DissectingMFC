// ClockCtrl.cpp : CClockCtrl ActiveX 控件类的实现。

#include "pch.h"
#include "framework.h"
#include "Clock.h"
#include "ClockCtrl.h"
#include "ClockPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CClockCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CClockCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CClockCtrl, COleControl)
	DISP_FUNCTION_ID(CClockCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CClockCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CClockCtrl, 1)
	PROPPAGEID(CClockPropPage::guid)
END_PROPPAGEIDS(CClockCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CClockCtrl, "MFCACTIVEXCONTRO.ClockCtrl.1",
	0xbb34739a,0xedfe,0x46d0,0x94,0x83,0x36,0xcd,0x75,0x4d,0xbe,0xe0)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CClockCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DClock = {0x7eb2d774,0x3445,0x43b8,{0x84,0xe8,0xb6,0xed,0xcf,0x1c,0x87,0x38}};
const IID IID_DClockEvents = {0xa02e24c4,0x897b,0x43dc,{0x83,0x2b,0xec,0x01,0xd2,0x39,0xa7,0xdc}};

// 控件类型信息

static const DWORD _dwClockOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CClockCtrl, IDS_CLOCK, _dwClockOleMisc)

// CClockCtrl::CClockCtrlFactory::UpdateRegistry -
// 添加或移除 CClockCtrl 的系统注册表项

BOOL CClockCtrl::CClockCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CLOCK,
			IDB_CLOCK,
			afxRegApartmentThreading,
			_dwClockOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// 授权字符串

static const TCHAR _szLicFileName[] = _T("Clock.lic");
static const WCHAR _szLicString[] = L"Copyright (c) 2022 ";

// CClockCtrl::CClockCtrlFactory::VerifyUserLicense -
// 检查是否存在用户许可证

BOOL CClockCtrl::CClockCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}

// CClockCtrl::CClockCtrlFactory::GetLicenseKey -
// 返回运行时授权密钥

BOOL CClockCtrl::CClockCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR *pbstrKey)
{
	if (pbstrKey == nullptr)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != nullptr);
}


// CClockCtrl::CClockCtrl - 构造函数

CClockCtrl::CClockCtrl()
{
	InitializeIIDs(&IID_DClock, &IID_DClockEvents);
	// TODO:  在此初始化控件的实例数据。
}

// CClockCtrl::~CClockCtrl - 析构函数

CClockCtrl::~CClockCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CClockCtrl::OnDraw - 绘图函数

void CClockCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CClockCtrl::DoPropExchange - 持久性支持

void CClockCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CClockCtrl::OnResetState - 将控件重置为默认状态

void CClockCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CClockCtrl::AboutBox - 向用户显示“关于”框

void CClockCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_CLOCK);
	dlgAbout.DoModal();
}


// CClockCtrl 消息处理程序
