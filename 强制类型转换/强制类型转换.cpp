//强制类型转换

#include <iostream>
#include <tchar.h>
using namespace std;

class CBase
{
public:
	virtual void PrintMsg() {
		cout << "\nPrint in CBase class!\n";
	}
	int GetInteger(int i) {
		return i;
	}
};

class CA :public CBase
{
public:
	virtual void PrintMsg() {
		cout << "\nPrint in CADerive class!\n";
	}

	int GetInteger(int i){
		return i + 1;
	}
};

class CB :public CBase
{
public:
	virtual void PrintMsg() {
		cout << "\nPrint in CBDerive class!\n";
	}
};

class CSI :public CA
{
public:
	virtual void PrintMsg() {
		cout << "\nPrint in CSIDerive class!\n";
	}

	int GetInteger(int i){
		return i+1;
	}
};

class CMI :public CA, public CB
{
public:
	void PrintMsg() {
		cout << "\nPrint in CSIDerive class!\n";
	}
	int GetInteger(int i){
		return 8;
	}

	int GetIntegerDouble(int i, double m)
	{
		return i * m;
	}

	void Hello()	{
		cout << "\nPrint in CSIDerive class!\n";
	}
};

class COther
{
public:
	virtual void PrintMsg() {
		cout << "\nPrint in CSIDerive class!\n";
	}
};

class CMI2 :public COther, public CA
{
public:
	void NewPrint() {
		cout << "\nPrint in CSIDerive class!\n";
	}
};

void GlobalFunVoid(){
	cout << "hello";
}

int GlobalFunInt(int i) {
	return i;
}

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

	//****************************************************************
	//情况1：单继承，将子类某个成员函数指针强制转为祖父类某个成员函数指针
	//1.1 在单继承中，可以将子类的成员函数强制转换为祖父类某个函数指针，函数参数或者返回值相同
	pFunbaseVoid = (PFunBaseVoid)&CSI::PrintMsg;			//单继承这个写法没有问题
	pFunbaseVoid = (PFunBaseVoid)(PFunAVoid)&CSI::PrintMsg;	//这种写法更严格
	//1.2 在单继承中，可以将子类的成员函数强制转换为祖父类某个函数指针，哪怕函数参数或者返回值不同
	pFunbaseVoid = (PFunBaseVoid)&CSI::GetInteger;	//这种是可以转换的

	//****************************************************************
	//情况2：多重继承
	//2.1 多重继承中，将具有相同函数参数和返回值的子类函数指针强制转换为父类函数指针
	//下面的转换涉及到一个非常隐蔽的知识点，在多重继承中，可能会有两个直接父类
	//从同一基类派生出来，例如CBase→CA、CB→CMI,因此，当采用强制类型转换(BaseFun)miDeriveFun时
	//编译器不知道是该转为CA这个类对应的BaseFun还是CB这个类对应的BaseFun，因此需要指定
	PFunMIVoid pFunMIVoidFun = &CMI::Hello;
	//pFunbaseVoid = (PFunBaseVoid)pFunMIVoidFun;	//编译出错，出现二义性
	pFunbaseVoid = (PFunBaseVoid)(PFunAVoid)pFunMIVoidFun;	//编译正确

	//这是一个反例，如果说多重继承里面没有两个BaseFun指针对象，一切ok
	typedef void(CMI2::*PCMI2Fun)();
	PCMI2Fun pCmi2Fun = &CMI2::NewPrint;
	pFunbaseVoid = (PFunBaseVoid)pCmi2Fun;

	//2.2 多重继承中，如果子类函数参数和返回值与父类不同，无法强制转换
	PFunMIInt pFunMIInt = &CMI::GetInteger;
	//PFunMIVoid pFunMIVoid = (pFunMIVoid)pFunMIInt;//多重继承的类，当函数签名不同时，无法将一个函数指针强制转为另一个
	//pFunbaseVoid = (PFunBaseVoid)pFunMIInt;		//多重继承的类，如果子类函数参数和父类不同，无法强制转换
	//pFunbaseVoid = static_cast<PFunBaseVoid>(pFunMIInt);	//上面代码的另一种写法，static_cast可以进行函数参数匹配检查
	PFunAInt pFunAInt = (PFunAInt)pFunMIInt;		//多重继承的类，如果子类函数参数和父类相同，可以转为父类函数指针
	PFunAInt aaaaInt = static_cast<PFunAInt>(pFunMIInt);//另一种写法

	//PFunBaseInt pFunBaseInt = (PFunBaseInt)(pFunMIInt);	//出现二义性
	//PFunBaseInt pFunBaseInt = static_cast<PFunBaseInt>(pFunMIInt);	//出现二义性


	//PFunAInt bInt = static_cast<PFunAInt>(&CMI::GetIntegerDouble);//报错
	//PFunAInt bInt = (PFunAInt)(&CMI::GetIntegerDouble);//报错,做了函数签名检查

	pFunbaseVoid = (PFunBaseVoid)(PFunAInt)pFunMIInt;	//由于CA为单继承，pFunMIInt和pFunAInt参数返回值相同，因此编译通过
	PFunBaseVoid bbbb = (PFunBaseVoid)(static_cast<PFunAInt>(pFunMIInt));	//static_cast可以进行函数参数检查

	//****************************************************************
	//情况3：将一个类的成员函数付给另外一个类的成员函数指针,哪怕函数参数不同也可以
	PFunOther otherFun1 = (PFunOther)&CBase::PrintMsg;
	PFunOther otherFun2 = (PFunOther)&CSI::GetInteger;
	PFunSIInt pSIGetIntFun= (PFunSIInt)&CBase::PrintMsg;

	//情况4：全局函数指针可以互转（即便函数参数不同）
	PGlobalFunVoid pFunVOid = (PGlobalFunVoid)&GlobalFunInt;	//参数不同的全局函数指针可以互相赋值
	PGlobalFunInt pFunInt = (PGlobalFunInt)&GlobalFunVoid;

	//情况5：一些胡乱转换
	//这种是没有办法转换的，自己一直以为强制类型转换，仅仅是直接赋值，实际上，
	//这种想法是错误的，编译器进行了类型检查，会对一些无效的转换进行报错。
	//PGlobalFunVoid pFun = (PGlobalFunVoid)&CBase::PrintMsg;	//这个出错的原因是：成员函数拥有一个隐藏的参数this指针
	CSI siDerive;
	//double mm = (double)siDerive;//这是不会成功的，因为CSI没有定义到double的转换函数
}