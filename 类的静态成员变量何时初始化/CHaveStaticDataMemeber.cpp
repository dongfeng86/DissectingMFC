//CHaveStaticDataMemember.cpp
//

//请注意，这个程序在调试的时候，如果类的成员变量采用静态初始化，根本无法进入类的静态成员变量初始化的那个断点，这是因为
//若采用静态初始化方式，类的静态成员是在程序加载时完成的初始化。

//静态初始化：是指用常量对变量进行初始化。其中未赋初值及初值为0的放在bss段，其他放在data段。静态初始化在程序加载时完成。
//动态初始化：是指需要经过函数调用才能完成的初始化，比如说：int a=foo()，或者复杂类型的初始化（需要调用构造函数）等。
//			  对于全局或者类的静态成员变量，是在main()函数执行前由运行时调用相应的代码进行初始化的。而对于局部静态变量，
//			  是在函数执行至此初始化语句时才开始执行的初始化。

#include "CHaveStaticDataMemeber.h"
#include <iostream>

int DuplicateInt(int m)
{
	return 2 * m;
}

//情况1：若类的静态成员变量采用静态初始化，是在加载时完成的，调试时无法跟踪到
int CHaveStaticDataMemember::m_iStaticInitial = 3;				

//情况2：若类的静态成员变量采用动态初始化，是由运行时调用的，调试时可以跟踪到
int CHaveStaticDataMemember::m_iDynInitial = DuplicateInt(3);	

//情况3：全局变量和类的静态成员变量一样，如果采用静态初始化，是在加载的时候完成的初始化，调试时无法跟踪到
int s_iGlobalStatic = 8*2;

//情况4：全局变量和类的静态成员变量一样，如果采用动态初始化，是由运行时调用的，调试时可以跟踪到
int s_iGlobalDyn = DuplicateInt(8);

void GetSome()
{
	static int s_GlobalInfun = 7;
	std::cout << "now in GetSome fun" << s_GlobalInfun << std::endl;
}

int main()
{
	//情况5：局部静态变量和静态成员变量一样，如果采用静态初始化，是在加载的时候完成的初始化，调试时无法跟踪到
	static int iLocalStatic = 3;

	//情况6：局部静态变量和类的静态成员变量一样，如果采用动态初始化，是由运行时调用的，调试时可以跟踪到
	static int iLocalDyn = DuplicateInt(3);

	std::cout << "now in main fun" << std::endl;

	GetSome();
	return 0;
}
