//这是一个经典的例子，包含虚函数的类，隐藏着一个指向虚函数表的指针，
//当程序调用这个类对象的虚函数时，编译器通过动态绑定，也就是
//调用哪个虚函数，就在这个虚函数表上找到这个虚函数的地址，进行完成
//在运行时找到对象（而不是指针）的实际函数。
#include <iostream>
#include <stdio.h>

class ClassA
{
public:
	int m_data1;
	int m_data2;
	void func1() {   }
	void func2() {   }
	virtual void vfunc1() {     }
	virtual void vfunc2() {     }
};

class ClassB : public ClassA
{
public:
	int m_data3;
	void func2() {  }
	virtual void vfunc1() {   }
};

class ClassC : public ClassB
{
public:
	int m_data1;
	int m_data4;
	void func2() {  }
	virtual void vfunc1() {    }
};

void main()
{
	using namespace std;
	cout << sizeof(ClassA) << endl;
	cout << sizeof(ClassB) << endl;
	cout << sizeof(ClassC) << endl;

	ClassA a;
	ClassB b;
	ClassC c;

	b.m_data1 = 1;
	b.m_data2 = 2;
	b.m_data3 = 3;
	c.m_data1 = 11;
	c.m_data2 = 22;
	c.m_data3 = 33;
	c.m_data4 = 44;
	c.ClassA::m_data1 = 111;

	cout << b.m_data1 << endl;
	cout << b.m_data2 << endl;
	cout << b.m_data3 << endl;
	cout << c.m_data1 << endl;
	cout << c.m_data2 << endl;
	cout << c.m_data3 << endl;
	cout << c.m_data4 << endl;
	cout << c.ClassA::m_data1 << endl;

	cout << &b << endl;
	cout << &(b.m_data1) << endl;
	cout << &(b.m_data2) << endl;
	cout << &(b.m_data3) << endl;
	cout << &c << endl;
	cout << &(c.m_data1) << endl;
	cout << &(c.m_data2) << endl;
	cout << &(c.m_data3) << endl;
	cout << &(c.m_data4) << endl;
	cout << &(c.ClassA::m_data1) << endl;

	ClassB* pb = new ClassB;
	ClassC* pc = new ClassC;

	pb->m_data1 = 1111;
	pc->m_data3 = 3333;

	cout << (int)*((char*)pb + 4) << endl;
	cout << (int)*((char*)pc + 12) << endl;
}

