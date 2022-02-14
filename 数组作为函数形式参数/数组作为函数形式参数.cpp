// 数组作为函数形式参数.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

//形式1：非引用形式：参数传递时没有带上数组大小，这样会导致在编译时，只要传递的是相同类型的指针，那么编译都是可以通过的。
void print(int arr[10])
{
	for (size_t i = 0; i < 10; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//形式2：引用形式，必须传递相同大小的数组
void print2(int(&arr)[10])
{
	for (size_t i = 0; i < 10; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//形式3：采用模板引用形式
template<size_t nBufLen> void print3(int(&buf)[nBufLen])
{
	for (size_t i = 0; i < nBufLen; ++i)
	{
		cout << buf[i] << " ";
	}
	cout << endl;
}

int main()
{
	int i[2] = { 1,2 };
	int *p = 0;
	int pc[] = { 0,1,2,3,4,5,6,7,8,9 };

	//验证非引用形式，编译全部通过
	print(pc);
	//print(i);	//编译通过，运行错误，因为数组越界
	//print(p);	//编译通过，运行错误，因为数组越界

	//验证引用形式，如果数组数量不通，编译会出错
	print2(pc);
	//print2(i);	//编译错误，数组大小不一样：error C2664: “void print2(int (&)[10])”: 无法将参数 1 从“int [2]”转换为“int (&)[10]”
	//print2(p);	//编译错误，数组大小不一样：error C2664: “void print2(int (&)[10])”: 无法将参数 1 从“int *”转换为“int (&)[10]”

	//验证模板引用形式
	print3(pc);		//模板函数可以推导出数组元素数量
	print3(i);		//模板函数可以推导出数组元素数量
	//print3(p);	//编译错误，数组大小不一样：error C2784: “void print3(int (&)[nBufLen])”: 未能从“int *”为“int (&)[nBufLen]”推导 模板 参数

	return 0;
}