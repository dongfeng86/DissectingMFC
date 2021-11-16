//���ַ����ֽ��� Meyers' SingletonMeyer's�ĵ���,���Ƽ��ķ�ʽ
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
		static Singleton instance;		//��ע�⣬�ھ�̬��Ա�����е����˷Ǿ�̬��Ա�������������������Թ��캯������
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