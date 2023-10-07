// Clock.cpp: CClockApp 和 DLL 注册的实现。

#include "pch.h"
#include "framework.h"
#include "Clock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CClockApp theApp;

const GUID CDECL _tlid = {0x54202a5e,0x9ac4,0x4fbb,{0xbd,0x32,0xd6,0xcc,0x7f,0x05,0xef,0xb0}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CClockApp::InitInstance - DLL 初始化

BOOL CClockApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CClockApp::ExitInstance - DLL 终止

int CClockApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
