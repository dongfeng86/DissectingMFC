//这种方法又叫做 Meyers' SingletonMeyer's的单例,最推荐的方式
#include <iostream>

class Singleton
{
public:
	~Singleton() {
		std::cout << "destructor called!" << std::endl;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton& get_instance() {
		static Singleton instance;		//请注意，在静态成员函数中调用了非静态成员变量，这是特例，仅对构造函数有用
		return instance;
	}
private:
	Singleton() {
		std::cout << "constructor called!" << std::endl;
	}
};

int main(int argc, char *argv[])
{
	Singleton& instance_1 = Singleton::get_instance();
	Singleton& instance_2 = Singleton::get_instance();
	return 0;
}