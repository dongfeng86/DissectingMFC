//CHaveStaticDataMemember.h
//

#pragma once

class CHaveStaticDataMemember
{
public:
	CHaveStaticDataMemember() {};
	~CHaveStaticDataMemember() {};

private:
	static int m_iStaticInitial;
	static int m_iDynInitial;
};