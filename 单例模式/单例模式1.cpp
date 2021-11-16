#include <iostream>

class Singleton {
private:
	Singleton() {
		std::cout << "constructor called!" << std::endl;
	}
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton* m_instance_ptr;
public:
	~Singleton() {
		std::cout << "destructor called!" << std::endl;
	}
	static Singleton* get_instance() {
		if (m_instance_ptr == nullptr) {
			m_instance_ptr = new Singleton;	//请注意，在静态成员函数中调用了非静态成员变量，这是特例，仅对构造函数有用
		}
		return m_instance_ptr;
	}
	void use() const { std::cout << "in use" << std::endl; }
};

Singleton* Singleton::m_instance_ptr = nullptr;

int main() 
{
	Singleton* instance = Singleton::get_instance();
	Singleton* instance_2 = Singleton::get_instance();
	return 0;
}
