//函数的强制类型转换
/*
本文的总体结论：
1.强制类型转换type(expr)和static_cast并不完全相同，后者会检查参数类型和目标类型是否一致。
将某个函数指针赋给另一函数指针时，如果两者签名不同，type(expr)可以赋值，但是static_cast却无法赋值的。
2.在单继承类中，可以通过强制类型转换type(expr)将类成员函数赋给继承链中的任意成员函数指针，甚至
可以赋给其他类函数指针；而static_cast因为会进行函数签名检查，类型不同的无法转换。
3.在多继承中，若子类方法参数与返回值和父类相同，且没有二义性，则可将子类函数地址赋给相应父类方法指针；
同一类层次中，如果两个函数签名相同，则可以相互转换。不可将多继承中的类成员函数直接赋值给一个不相关的类函数指针
*/

#include <iostream>
#include <tchar.h>
using namespace std;

class CBase
{
public:
	virtual void PrintMsg() { cout << "\nPrint in CBase class!\n"; }
	int GetInteger(int i) { return i; }
};

class CA :public CBase
{
public:
	virtual void PrintMsg() { cout << "\nPrint in CADerive class!\n"; }
	int GetInteger(int i) { return i + 1; }
};

class CB :public CBase
{
public:
	virtual void PrintMsg() { cout << "\nPrint in CBDerive class!\n"; }
};

class CSI :public CA
{
public:
	virtual void PrintMsg() { cout << "\nPrint in CSIDerive class!\n"; }
	int GetInteger(int i) { return i + 1; }
};

class CMI :public CA, public CB
{
public:
	void PrintMsg() { cout << "\nPrint in CSIDerive class!\n"; }
	int GetInteger(int i) { return 8; }
	double GetDouble(int i, double m) { return i * m; }
	void Hello() { cout << "\nPrint in CSIDerive class!\n"; }
};

class COther
{
public:
	virtual void PrintMsg() { cout << "\nPrint in CSIDerive class!\n"; }
};

class CMI2 :public COther, public CA
{
public:
	void NewPrint() { cout << "\nPrint in CSIDerive class!\n"; }
};

void GlobalFunVoid() { cout << "hello"; }

int GlobalFunInt(int i) { return i; }

int main()
{
	typedef void (CBase::*PFunBaseVoid)();
	typedef int (CBase::*PFunBaseInt)(int);
	typedef void (CA::*PFunAVoid)();
	typedef int (CA::*PFunAInt)(int);
	typedef void (CB::*PFunBVoid)();
	typedef void (CSI::*PFunSIVoid)();
	typedef int (CSI::*PFunSIInt)(int);
	typedef void (CMI::*PFunMIVoid)();
	typedef int (CMI::*PFunMIInt)(int);
	typedef void (COther::*PFunOther)();
	typedef void(*PGlobalFunVoid)();
	typedef int(*PGlobalFunInt)(int);

	PFunBaseVoid pFunbaseVoid = &CBase::PrintMsg;
	CBase base;
	(base.*pFunbaseVoid)();

	PFunAVoid aDeriveFun = &CA::PrintMsg;
	pFunbaseVoid = (PFunBaseVoid)aDeriveFun;
	(base.*pFunbaseVoid)();

	//第一部分****************************************************************
	//1：单继承
	//1.1 在单继承中，可以将子类的成员函数强制转换为祖父类某个函数指针，无论函数参数或者返回值是否相同
	pFunbaseVoid = (PFunBaseVoid)&CSI::PrintMsg;			//ok，函数参数一致
	pFunbaseVoid = (PFunBaseVoid)(PFunAVoid)&CSI::PrintMsg;	//ok,更严格
	pFunbaseVoid = (PFunBaseVoid)&CSI::GetInteger;			//ok，函数参数不同
	//pFunbaseVoid = static_cast<PFunBaseVoid>(&CSI::GetInteger);//编译错误。这是一个极为微妙的变化，static_cast会检查两个函数参数和返回类型是否相同

	//1.2 在单继承中，可以将类中某个成员函数赋给另一成员函数指针,哪怕函数参数或者返回类型不同
	PFunSIVoid pSIVoidFun = (PFunSIVoid)&CSI::GetInteger;	//ok，函数参数不同

	//第二部分****************************************************************
	//2：多重继承
	//2.1 多重继承中，若子类方法参数与返回值和直接父类相同，且没有二义性，则可将子类函数地址赋给相应父类方法指针
	PFunAInt pFunAInt = (PFunAInt)&CMI::GetInteger;		//多重继承的类，如果子类函数参数和直接父类相同，可以转为直接父类函数指针
	pFunAInt = static_cast<PFunAInt>(&CMI::GetInteger);	//另一种写法

	//2.2 多重继承中，若子类方法参数与返回值和直接父类不同，不可将子类函数地址赋给相应直接父类方法指针
	//PFunAInt = (PFunAInt)&CMI::PrintMsg;				//编译错误，如果方法参数不同，无法转换
	//PFunAInt = static_cast<PFunAInt>(&CMI::PrintMsg);	//编译错误，如果方法参数不同，无法转换

	//2.3 多重继承中，若子类方法参数与返回值和非直接父类相同，但有二义性，不可将子类函数地址赋给相应父类方法指针
	//在多重继承中，可能会有两个直接父类从同一基类派生出来，例如CBase→CA、CB→CMI,因此，
	//当采用强制类型转换(PFunBaseVoid)pFunMIVoidFun时,编译器不知道是该转为CA这个类对应的
	//PFunBaseVoid还是CB这个类对应的PFunBaseVoid，因此需要指定
	PFunMIVoid pFunMIVoidFun = &CMI::Hello;
	//pFunbaseVoid = (PFunBaseVoid)pFunMIVoidFun;				//编译出错，出现二义性
	//pFunbaseVoid =static_cast<PFunBaseVoid>(pFunMIVoidFun);	//编译出错，出现二义性
	pFunbaseVoid = (PFunBaseVoid)(PFunAVoid)pFunMIVoidFun;		//ok，两次转换避免二义性
	pFunbaseVoid = (PFunBaseVoid)&CMI2::NewPrint;		//ok，如果多重继承里面没有两个PFunBaseVoid类型函数

	//2.4 多重继承中，如果类内某两个函数参数或者返回类型不同，这两个函数无法相互转换
	//PFunMIVoid pFunMIVoid = (pFunMIVoid)&CMI::GetInteger;

	//2.5 在多重继承中，若子类函数参数与返回值和祖父类不同，一般需要经过两次转换
	//CMI::GetInteger和PFunAInt参数返回值相同，且CMI和CA为直接继承，所以(PFunAInt)&CMI::GetInteger成功转换，
	//而CA与CBase为单继承，因此PFunAInt指针可以直接转为PFunBaseVoid指针
	pFunbaseVoid = (PFunBaseVoid)(PFunAInt)&CMI::GetInteger;					//ok
	pFunbaseVoid = (PFunBaseVoid)(static_cast<PFunAInt>(&CMI::GetInteger));//另一种写法

	//第三部分****************************************************************
	//3：将一个类的成员函数赋给另外一个类的成员函数指针
	//3.1 单继承的类方法赋给另一个单继承的类方法指针，哪怕函数参数不同也可以
	PFunOther otherFun1 = (PFunOther)&CBase::PrintMsg;	//ok
	otherFun1 = (PFunOther)&CSI::GetInteger;			//ok
	PFunSIInt pSIGetIntFun = (PFunSIInt)&CBase::PrintMsg;	//ok

	otherFun1 = (PFunOther)&CSI::PrintMsg;//ok
	//otherFun1 = static_cast<PFunOther>(&CSI::PrintMsg);//编译错误。static_cast发现两个方法不属于同一类，且两个类没有继承关系

	//3.2 多继承中，哪怕方法参数一致，也无法将多继承类方法赋给不相关的令一个类方法指针
	//otherFun1 = (PFunOther)&CMI::PrintMsg;	//编译错误，在多重继承的类方法中，无法这样赋值
	//otherFun1 = (PFunOther)&CMI::GetInteger;				//编译错误
	//otherFun1 = static_cast<PFunOther>(&CMI::GetInteger);	//编译错误

	//第四部分****************************************************************
	//4：全局函数指针可以互转（即便函数参数不同）
	PGlobalFunVoid pFunVOid = (PGlobalFunVoid)&GlobalFunInt;	//参数不同的全局函数指针可以互相赋值
	//pFunVOid = static_cast<PGlobalFunVoid>(&GlobalFunInt);	//编译错误，static_cast会检查参数是否相同
	PGlobalFunInt pFunInt = (PGlobalFunInt)&GlobalFunVoid;
	//PGlobalFunVoid pFun = (PGlobalFunVoid)&CBase::PrintMsg;	//编译出错：成员函数拥有一个隐藏的参数this指针，强制类型转换会检查这个
}