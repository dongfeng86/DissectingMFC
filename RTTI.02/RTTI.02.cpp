// RTTI.cpp - a demonstration of RTTI in C++
#include <typeinfo>
#include <iostream>
#include <string>

using namespace std;

class graphicImage
{
protected:
	char name[80];

public:
	graphicImage()
	{
		strcpy_s(name, "graphicImage");
	}

	virtual void display()
	{
		cout << "Display a generic image." << endl;
	}

	char* getName()
	{
		return name;
	}
};
//----------------------------------------------------------------
class GIFimage : public graphicImage
{
public:
	GIFimage()
	{
		strcpy_s(name, "GIFimage");
	}

	void display()
	{
		cout << "Display a GIF file." << endl;
	}
};

class PICTimage : public graphicImage
{
public:
	PICTimage()
	{
		strcpy_s(name, "PICTimage");
	}

	void display()
	{
		cout << "Display a PICT file." << endl;
	}
};
//----------------------------------------------------------------
void processFile(graphicImage *type)
{
	if (typeid(GIFimage) == typeid(*type))
	{
		((GIFimage *)type)->display();
	}
	else if (typeid(PICTimage) == typeid(*type))
	{
		((PICTimage *)type)->display();
	}
	else
		cout << "Unknown type! " << (typeid(*type)).name() << endl;
}

class CNoPolymorphic
{
public:
	CNoPolymorphic(const char* psz)
	{
		strcpy_s(name, psz);
	}
	void Display()
	{
		cout << "this is NoPolymorphic type\n";
	}
private:
	char name[80];
};

class CDerFromNoPolymorphic:public CNoPolymorphic
{
public:
	CDerFromNoPolymorphic(const char* psz)
		:CNoPolymorphic(psz)
	{}
	void Display()
	{
		cout << "this is DerFromNoPolymorphic type\n";
	}
};

void ShowStaticClassType(CNoPolymorphic* pType)
{
	if (typeid(*pType) == typeid(CNoPolymorphic))
	{
		cout << "this is a class CNoPolymorphicBase\n";
	}
	else if (typeid(*pType) == typeid(CDerFromNoPolymorphic))
	{
		cout << "this is a class CDerPolymorphicBase\n";
	}
}

void main()
{
	//如果typeid的参数是多态类，那么返回的是指针指向的实际对象的类型信息
	graphicImage *gImage = new GIFimage();
	graphicImage *pImage = new PICTimage();
	processFile(gImage);
	processFile(pImage);
	delete gImage;
	delete pImage;

	//如果typeid的参数不是多态类，则返回指针指向对象的静态类型
	//（The static type of an expression refers to the type of an expression as it is known at compile time）
	CNoPolymorphic* pNoPolymorphicBase = new CNoPolymorphic("helel");
	CDerFromNoPolymorphic* pNoPolyDer = new CDerFromNoPolymorphic("non");
	ShowStaticClassType(pNoPolymorphicBase);
	ShowStaticClassType(pNoPolyDer);
	delete pNoPolymorphicBase;
	delete pNoPolyDer;

	return;

}
