#include <iostream>
#include <mutex>
using namespace std;
//1. 只能在堆上创建对象
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
//	HeapOnly(const HeapOnly&) = delete;	//禁止拷贝构造
//};
//
//int main()
//{
//	//HeapOnly ho;
//	//HeapOnly copy(ho);
//	HeapOnly* hop = HeapOnly::CreateObj();
//	return 0;
//}

//2. 只能在栈上创建对象
//方法1
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

//方法2
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

//4. 不能继承
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

/**************	单例模式		*******************/
//1. 饿汉模式
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

//2. 懒汉模式
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

//2. 懒汉模式 --- 线程安全版本
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
//	static mutex mtx;	//锁也必须是静态的，不然GetInstance函数获取不到
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


//2. 懒汉模式 --- 线程安全 +　垃圾回收机制
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
//	static mutex mtx;	//锁也必须是静态的，不然GetInstance函数获取不到
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