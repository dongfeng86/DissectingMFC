//CHaveStaticDataMemember.h
//

#pragma once

extern int s_iFirst;		//��ע�������������ġ�������˳�򣨶�������cpp�ļ��У�
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