// ClockPropPage.cpp : CClockPropPage 属性页类的实现。

#include "pch.h"
#include "framework.h"
#include "Clock.h"
#include "ClockPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CClockPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CClockPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CClockPropPage, "MFCACTIVEXCONT.ClockPropPage.1",
	0x32e61744,0xb489,0x4e7c,0xb1,0xa9,0x92,0x16,0xfe,0xeb,0x13,0x1d)

// CClockPropPage::CClockPropPageFactory::UpdateRegistry -
// 添加或移除 CClockPropPage 的系统注册表项

BOOL CClockPropPage::CClockPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CLOCK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CClockPropPage::CClockPropPage - 构造函数

CClockPropPage::CClockPropPage() :
	COlePropertyPage(IDD, IDS_CLOCK_PPG_CAPTION)
{
}

// CClockPropPage::DoDataExchange - 在页和属性间移动数据

void CClockPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CClockPropPage 消息处理程序
