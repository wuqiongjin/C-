#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

#include <Windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

//int main()
//{
//	short a = 32670;
//	short b = 32670;
//
//	decltype(a + b) c;
//	c = 10;
//	//cout << typeid(c).name() << endl;
//	cout << c << endl;
//	return 0;
//}

//void* GetMemory(size_t size)
//{
//	return malloc(size);
//}
//int main()
//{
//
//	decltype(GetMemory) a;
//	// 如果没有带参数，推导函数的类型
//	cout << typeid(decltype(GetMemory)).name() << endl;
//
//	// 如果带参数列表，推导的是函数返回值的类型,注意：此处只是推演，不会执行函数
//	cout << typeid(decltype(GetMemory(0))).name() << endl;
//
//	return 0;
//}
//
//int main()
//{
//	//int a = 10;
//
//	//int&& b = move(a);
//	//int& c = a;
//	//cout << a << endl;
//	//cout << b << endl;
//	//cout << c << endl;
//	
//	return 0;
//}

//class String
//{
//public:
//	String(const char* str = ""):
//		_str(new char[strlen(str) + 1])
//	{
//		strcpy(_str, str);
//	}
//
//	//默认版本 - 拷贝构造
//	String(const String& s)
//	{
//		cout << "String(const String& s) - 深拷贝 - 效率低" << endl;
//		//char* tmp = new char[strlen(s._str) + 1];
//		//_str = tmp;
//		_str = new char[strlen(s._str) + 1];	//与注释部分没什么区别
//		strcpy(_str, s._str);
//	}
//
//	//右值引用 - 拷贝构造
//	String(String&& s)
//		:_str(nullptr)
//	{
//		cout << "String(String&& s) - 移动拷贝构造 - 效率高" << endl;
//		swap(s._str, _str);
//	}
//	//默认版本
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			cout << "String& operator=(const String& s) - 赋值拷贝 - 效率低" << endl;
//			char* tmp = new char[strlen(s._str) + 1];
//			strcpy(tmp, s._str);
//			delete[] _str;
//			_str = tmp;
//		}
//		return *this;
//	}
//	//右值引用
//	String& operator=(String&& s)
//	{
//		if (this != &s)
//		{
//			cout << "String& operator=(String&& s) - 移动赋值 - 效率高" << endl;
//			delete[] _str;
//			_str = nullptr;
//			swap(_str, s._str);
//		}
//		return *this;
//	}
//
//	String operator+(const String& s)
//	{
//		String tmp(*this);
//		return tmp;		//返回的是右值(将亡值)，因为传值返回，返回的是临时对象
//	}
//
//	String& operator+=(const String& s)
//	{
//		return *this;	//返回的是左值，因为是引用返回
//	}
//private:
//	char* _str;
//};
//
//String func(String s)
//{
//	return s;
//}
//
//int main()
//{
//	//String s1 = "hello";
//	//String s2(s1);
//	//String s3(func("右值"));
//	//s3 = s2;
//	//s3 = "右值";
//
//	String s1 = "s1";
//	String s2 = "s2";
//	
//	String s3 = s1 + s2;
//	String s4 = s1 += s2;
//
//
//	return 0;
//}


//int main()
//{
//	vector<string> v;
//	string s1 = "100";
//	int val = 110;
//	v.push_back(s1);
//
//	v.push_back("右值");
//	v.push_back(to_string(val));
//
//
//	return 0;
//}

//int main()
//{
//	//vector<pair<string, string>> vp;
//	//vp.push_back(make_pair("fly", "飞"));
//
//
//	//vp.emplace_back(make_pair("sleep", "睡觉"));
//	//vp.emplace_back("decline", "减少");
//	//for (auto& e : vp)
//	//	cout << e.first << ":" << e.second << endl;
//
//	vector<int> v(5);
//
//	return 0;
//}


//仿函数、lamdba表达式
class Goods
{
public:
	string name;
	int nums;
	double prices;
};

//按照数量，大的值放在最前面 --- 降序
struct CompareNumsGreater
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.nums > g2.nums;
	}
};

//按照价格，大的值放在最前面 --- 降序
struct ComparePricesGreater
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.prices > g2.prices;
	}
};

//按照数量，小的值放在最前面 --- 升序
struct CompareNumsLess
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.nums < g2.nums;
	}
};

//按照价格，小的值放在最前面 --- 升序
struct ComparePricesLess
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.prices < g2.prices;
	}
};

void test_Functor()
{
	Goods gd[] = { {"苹果", 10, 5.0}, {"西瓜", 8, 3.5}, {"香蕉", 9, 2.2} };
	
	//按照数量排序 降序
	sort(gd, gd + 3, CompareNumsGreater());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;

	//按照价格排序 降序
	sort(gd, gd + 3, ComparePricesGreater());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;


	//按照数量排序 升序
	sort(gd, gd + 3, CompareNumsLess());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;

	//按照价格排序 升序
	sort(gd, gd + 3, ComparePricesLess());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;

	//return 0;
}

void test_lambda1()
{

	int a = 0, b = 1;
	//auto add1 = [](int x, int y)->int{return x + y;};
	//cout << add1(a, b) << endl;
	//
	//auto add2 = [a, b]() {return a + b;};
	//cout << add2() << endl;

	////成功交换 - 参数列表使用左值引用
	//auto swap1 = [](int& x, int& y) {
	//	int tmp = x;
	//	x = y;
	//	y = tmp;
	//};
	//swap1(a, b);
	//cout << "a=" << a << " b=" << b << endl;

	////成功交换 - 参数列表使用取地址
	//auto swap2 = [](int* x, int* y) {
	//	int tmp = *x;
	//	*x = *y;
	//	*y = tmp;
	//};
	//swap2(&a, &b);
	//cout << "a=" << a << " b=" << b << endl;

	////失败交换 - 使用传值方式，无法交换实参的值
	//auto swap3 = [](int x, int y) {
	//	int tmp = x;
	//	x = y;
	//	y = tmp;
	//};
	//swap3(a, b);
	//cout << "a=" << a << " b=" << b << endl;


	////成功交换 - 捕获列表使用引用传值
	//auto swap4 = [&a, &b]() {
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//swap4();
	//cout << "a=" << a << " b=" << b << endl;

	////失败交换 - 捕获列表捕获的是值的拷贝，因此修改并不对原值造成影响
	//auto swap5 = [a, b]()mutable {	//mutable让捕获列表的值的属性变为非const
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//swap5();
	//cout << "a=" << a << " b=" << b << endl;

}

void test_lambda2()
{
	Goods gd[] = { {"苹果", 10, 5.0}, {"西瓜", 8, 3.5}, {"香蕉", 9, 2.2} };
	//auto NumGreater = [](const Goods& g1, const Goods& g2) {return g1.nums > g2.nums;};
	//sort(gd, gd + 3, NumGreater);

	sort(gd, gd + 3, [](const Goods& g1, const Goods& g2) {return g1.nums > g2.nums;});
	for(auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;


}

void test_lambda3()
{
	Goods gd[] = { {"苹果", 10, 5.0}, {"西瓜", 8, 3.5}, {"香蕉", 9, 2.2} };
	
	priority_queue<Goods, vector<Goods>, CompareNumsGreater> pq(gd, gd + 3);

	while (!pq.empty())
	{
		cout << pq.top().name << "-" << pq.top().nums << "-" << pq.top().prices << endl;
		pq.pop();
	}

//	priority_queue<Goods, vector<Goods>, ComparePricesGreater> pq;
}

void test_pq()
{
	vector<int> v{ 3,1,4,5,6,7,9,8,10,0,2 };
	priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.end());
	
	while (!pq.empty())
	{
		cout << pq.top() << endl;
		pq.pop();
	}
}

class base1
{
public:
	string name = "base1";
	int age;
	int num;
};

class base2
{
public:
	string name = "base2";
	int age;
	int num;
};

class Child : public base1, public base2
{
public:
	void func()
	{
		cout << base1::name << " " << base2::name << endl;
	}
};


void test_inher()
{
	Child c;
	//c.base1::name = "c";

	c.func();
}
//
//int main()
//{
//	//test_Functor();
//	//test_lambda1();
//	//test_lambda2();
//	//test_lambda3();
//	//test_pq();
//	//test_inher();	//测试多继承
//	return 0;
//}

//int main()
//{
//	vector<int> v{ 4,5,1,2,3 };
//	sort(v.begin(), v.end(), less<int>());
//	for (auto e : v)
//		cout << e << " ";
//	cout << endl;
//	
//	sort(v.begin(), v.end(), greater<int>());
//	for (auto e : v)
//		cout << e << " ";
//	
//	return 0;
//}

//*****************************************************************************************
//*****************************************************************************************
//*****************************************************************************************
//C++11线程库
//#include <thread>
//#include <mutex>
//#include <condition_variable>

//mutex mtx;
//
//void Routine()
//{
//	//mtx.lock();
//	for (int i = 10; i > 0; --i)
//	{
//		cout << this_thread::get_id() << ":" << i << endl;
//		Sleep(1);
//	}
//	//mtx.unlock();
//}
//
//void test_mutex()
//{
//	//1. 函数指针 --- 用来让多个线程执行同时进入到一个函数的
//	//thread t1(Routine);
//	//thread t2(Routine);
//	
//	//2. lambda表达式/仿函数	---	让不同的线程执行不同的函数
//	thread t1([] {
//		for (int i = 0; i < 10; ++i)
//		{
//			cout << i << endl;
//		}
//	});
//
//	thread t2([] {
//		for (int i = 0; i < 10; ++i)
//		{
//			cout << i << endl;
//		}
//	});
//
//	t1.join();
//	t2.join();
//}
//
//void test_cond()
//{
//	//使用2个线程，实现一个线程只打印奇数，另一个线程只打印偶数。两个线程交互打印，互相通知对方。
//	int n = 10;
//	mutex mtx1, mtx2;	//这里的mutex锁是为了配合条件变量传参而是用的
//	condition_variable cv1, cv2;
//
//	thread t1([&] {
//		for (int i = 0; i < n; i += 2)
//		{
//			unique_lock<mutex> ul1(mtx1);
//			if (i != 0)
//				cv1.wait(ul1);
//			//cv1.wait(unique_lock<mutex>(mtx1));	//wait中的参数是个左值，不能这样直接传匿名对象，因为这里传的是右值
//			cout << this_thread::get_id() << " " << i << endl;
//			cv2.notify_one();
//		}
//	});
//
//	thread t2([&] {
//		for (int i = 1; i < n; i += 2)
//		{
//			unique_lock<mutex> ul2(mtx2);
//			cv2.wait(ul2);
//			cout << this_thread::get_id() << " " << i << endl;
//			cv1.notify_one();
//		}
//	});
//
//	t1.join();
//	t2.join();
//}
//
//int main()
//{
//	//test_mutex();
//	//test_cond();
//
//	return 0;
//}


// for_each
//void printFunc(int i)
//{
//	cout << i << " ";
//}
//
//struct PrintFunctor
//{
//	void operator()(int i)
//	{
//		cout << i << " ";
//	}
//};
//
//int main()
//{
//	vector<int> v{ 1,3,5,7,9 };
//
//	for_each(v.begin(), v.end(), printFunc);
//	cout << endl;
//
//	for_each(v.begin(), v.end(), [] (int i) {
//		cout << i << " ";
//	});
//	cout << endl;
//
//	for_each(v.begin(), v.end(), PrintFunctor());
//	cout << endl;
//	return 0;
//}
