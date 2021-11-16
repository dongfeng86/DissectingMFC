//CHaveStaticDataMemember.h
//

#pragma once

extern int s_iFirst;		//请注意这两个变量的“声明”顺序（定义是在cpp文件中）
extern int s_iSeond;

class CHaveStaticDataMemember
{
public:
	CHaveStaticDataMemember() {};
	~CHaveStaticDataMemember() {};

private:
	static int m_iStaticInitial;
	static int m_iDynInitial;
};