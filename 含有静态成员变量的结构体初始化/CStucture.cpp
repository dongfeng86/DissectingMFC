#include <string>
#include <iostream>

struct SStructHaveStaticMem
{
	int iId;
	static double dRate;
	int iSeries;
	std::string sName;
};

double SStructHaveStaticMem::dRate = 0.85;

int main()
{
	SStructHaveStaticMem cStructure1 = {103,5,"nihao"};
	std::cout << "cStructre1.iId=" << cStructure1.iId << std::endl;
	std::cout << "cStructre1.sName=" << cStructure1.sName << std::endl;

	return 0;
}