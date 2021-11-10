//CHaveStaticDataMemember.h
//

#pragma once

extern int s_iFirst;
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