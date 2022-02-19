#include <iostream>
#include <mutex>
using namespace std;
//1. ֻ���ڶ��ϴ�������
//class HeapOnly
//{
//public:
//	static HeapOnly* CreateObj()
//	{
//		return new HeapOnly;
//	}
//private:
//	HeapOnly()
//	{}
//
//	HeapOnly(const HeapOnly&) = delete;	//��ֹ��������
//};
//
//int main()
//{
//	//HeapOnly ho;
//	//HeapOnly copy(ho);
//	HeapOnly* hop = HeapOnly::CreateObj();
//	return 0;
//}

//2. ֻ����ջ�ϴ�������
//����1
//class StackOnly
//{
//public:
//	static StackOnly CreateObj()
//	{
//		return StackOnly();
//	}
//private:
//	StackOnly(){}
//};

//����2
//class StackOnly
//{
//public:
//	StackOnly() {};
//private:
//	void* operator new(size_t size) = delete;
//	void operator delete(void* p) = delete;
//};
//
//int main()
//{
//	//StackOnly so1 = StackOnly::CreateObj();
//	StackOnly so2;
//	static StackOnly ss;
//	return 0;
//}

//4. ���ܼ̳�
//class A
//{
//private:
//	A()	{}
//};
//
//class B : public A
//{};
//
//int main()
//{
//	B b;
//	return 0;
//}

//class A final
//{
//private:
//	A() {}
//};
//
//class B : public A
//{};
//
//int main()
//{
//
//	return 0;
//}

/**************	����ģʽ		*******************/
//1. ����ģʽ
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		return &inst;
//	}
//
//	void Print()
//	{
//		cout << "Print(a):" << _a << endl;
//	}
//private:
//	Singleton(int a = 10) 
//		:_a(a)
//	{}
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	int _a;
//	static Singleton inst;
//};
//
//Singleton Singleton::inst;
//
//int main()
//{
//	Singleton::GetInstance()->Print();
//	return 0;
//}

//2. ����ģʽ
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		if (inst == nullptr)
//		{
//			inst = new Singleton;
//		}
//		return inst;
//	}
//
//	void Print()
//	{
//		cout << "Print(a):" << _a << endl;
//	}
//private:
//	Singleton(int a = 10)
//		:_a(a)
//	{}
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	int _a;
//	static Singleton* inst;
//};
//
//Singleton* Singleton::inst = nullptr;
//
//int main()
//{
//	Singleton::GetInstance()->Print();
//	return 0;
//}

//2. ����ģʽ --- �̰߳�ȫ�汾
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		if (inst == nullptr)
//		{
//			mtx.lock();
//			if (inst == nullptr)
//			{
//				inst = new Singleton;
//			}
//			mtx.unlock();
//		}
//		return inst;
//	}
//
//	void Print()
//	{
//		cout << "Print(a):" << _a << endl;
//	}
//private:
//	Singleton(int a = 10)
//		:_a(a)
//	{}
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	int _a;
//	static mutex mtx;	//��Ҳ�����Ǿ�̬�ģ���ȻGetInstance������ȡ����
//	static Singleton* inst;
//};
//mutex Singleton::mtx;
//Singleton* Singleton::inst = nullptr;
//
//int main()
//{
//	Singleton::GetInstance()->Print();
//	return 0;
//}


//2. ����ģʽ --- �̰߳�ȫ +���������ջ���
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		if (inst == nullptr)
//		{
//			mtx.lock();
//			if (inst == nullptr)
//			{
//				inst = new Singleton;
//			}
//			mtx.unlock();
//		}
//		return inst;
//	}
//
//	void Print()
//	{
//		cout << "Print(a):" << _a << endl;
//	}
//
//	~Singleton()
//	{
//		cout << "~Singleton()" << endl;
//	}
//
//	class GrabC
//	{
//	public:
//		~GrabC()
//		{
//			if (inst)
//			{
//				delete inst;
//				inst = nullptr;
//			}
//		}
//	};
//
//private:
//	Singleton(int a = 10)
//		:_a(a)
//	{}
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	int _a;
//	static mutex mtx;	//��Ҳ�����Ǿ�̬�ģ���ȻGetInstance������ȡ����
//	static Singleton* inst;
//	static GrabC _gc;
//};
//mutex Singleton::mtx;
//Singleton* Singleton::inst = nullptr;
//Singleton::GrabC _gc;
//
//int main()
//{
//	Singleton::GetInstance()->Print();
//	return 0;
//}