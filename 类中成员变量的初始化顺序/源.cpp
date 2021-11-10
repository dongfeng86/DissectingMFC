#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/*
1、	成员变量在使用初始化列表初始化时，与构造函数中初始化成员列表的顺序无关，只与定义成员变量的顺序有关。
	因为成员变量的初始化次序是根据变量在内存中次序有关，而内存中的排列顺序早在编译期就根据变量的定义次序决定了。
2、	如果不使用初始化列表初始化，在构造函数内初始化时，此时与成员变量在构造函数中的位置有关。
3、	注意：类成员在定义时，是不能初始化的
4、	注意：类中const成员常量必须在构造函数初始化列表中初始化。
5、	注意：类中static成员变量，必须在类外初始化。
6、	静态变量进行初始化顺序是基类的静态变量先初始化，然后是它的派生类。直到所有的静态变量都被初始化。
	这里需要注意全局变量和静态变量的初始化是不分次序的。
*/


class CTest
{
private:
	int m_iLst1;
	int m_iLst2;

	int m_iInitialInCons1;
	int m_iInitialInCons2;

public:
	CTest();

	void Print() {
		cout << "n1:" << m_iLst1 << ", n2: " << m_iLst2 << endl;
	}
};

//如果采用初始化列表，成员变量的初始化顺序和声明顺序是一致的
CTest::CTest()
	:m_iLst2(2*m_iLst1)
	,m_iLst1(0)
{
	//如果采用构造函数，成员函数的初始化顺序和变量的函数中的位置有关。
	//其实，无论采用初始化列表还是构造函数内初始化，变量已经在栈上分配了内存（但是内容是垃圾值），
	//初始化列表或者构造函数内初始化仅仅是初始赋值而已。
	m_iInitialInCons2 = m_iInitialInCons1;
	m_iInitialInCons1 = 0;
}


int main()
{
	CTest a;
	a.Print();

	return 1;
}