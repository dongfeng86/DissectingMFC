#pragma once

// ClockPropPage.h: CClockPropPage 属性页类的声明。


// CClockPropPage : 请参阅 ClockPropPage.cpp 了解实现。

class CClockPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CClockPropPage)
	DECLARE_OLECREATE_EX(CClockPropPage)

// 构造函数
public:
	CClockPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_CLOCK };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

