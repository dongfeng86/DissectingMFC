// 这是神奇的一幕，我们知道，基类指针想要调用子类成员函数，一般需要将该函数定义
//为虚函数，通过在类中维护虚函数表，从而实现基类指针调用子类方法的效果。但是虚函数
//需要在每个类中维护一个虚函数表，大大增加了程序了空间复杂度。
//在MFC中，没有这么做，而是将子类的所有相应函数统一转为基类的某个响应函数指针，然后
//通过对比消息号来确定某个子类拥有合适的响应函数。这样做的关键是：通过成员解除引用
//运算符，可以将基类指针指向子类成员函数。
//这种处理方式的关键，是要理解成员解除引用运算符。基类指针使用成员解除引用运算符时，
//实际上流程会转到相应的子类函数中，基类指针（实际指向子类对象）把this指针压栈，
//子类成员函数根据这个地址可以正确找到相应的类成员。


#include<iostream>
using namespace std;

class CBase
{
public:
	void BasePrintMsg() {
		cout << "In Base class" << endl;
	}
};

class CDerive :public CBase
{
public:
	CDerive() :m_iDerive(3) {}
	int GetInt(int m) {
		return m_iDerive * m;
	}

	double GetDouble(int m, double d) {
		return m * d;
	}
private:
	int m_iDerive;
};

typedef void (CBase::* pBaseVoidFun)();

union UMapFuns
{
	//请注意，以下三个成员都是基类的成员函数的函数指针
	pBaseVoidFun pfn;
	double (CBase::*pfn_double)(int m, double d);
	int (CBase::*pfn_int)(int m);
};

int main()
{
	UMapFuns uMapFun;
	uMapFun.pfn = (pBaseVoidFun)&CDerive::GetInt;

	CDerive cDeriveObj;
	CBase* pBase = &cDeriveObj;
	//调用成功，关键要理解uMapFun.pfn_int的地址实际上是子类成员函数的地址，子类对象
	//调用解除引用运算符时，不过是将子类对象的地址压栈，让子类成员函数能够根据这个
	//地址找到类的其他成员。
	int i = (cDeriveObj.*(uMapFun.pfn_int))(3);	
	//调用成功，用基类指针调用子类函数。关键要理解uMapFun.pfn_int的地址实际上是子类
	//成员函数的地址，基类指针此时的地址就是子类对象的地址，该地址压栈后，
	//子类成员函数根据这个地址找到的类的其他成员都是正确的。
	int i2 = (pBase->*(uMapFun.pfn_int))(4);	

	uMapFun.pfn = (pBaseVoidFun)&CDerive::GetDouble;
	double d = (pBase->*(uMapFun.pfn_double))(3, 4.0);	//调用成功，用基类指针调用子类函数

	return 0;
}