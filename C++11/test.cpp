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
//	// ���û�д��������Ƶ�����������
//	cout << typeid(decltype(GetMemory)).name() << endl;
//
//	// ����������б��Ƶ����Ǻ�������ֵ������,ע�⣺�˴�ֻ�����ݣ�����ִ�к���
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
//	//Ĭ�ϰ汾 - ��������
//	String(const String& s)
//	{
//		cout << "String(const String& s) - ��� - Ч�ʵ�" << endl;
//		//char* tmp = new char[strlen(s._str) + 1];
//		//_str = tmp;
//		_str = new char[strlen(s._str) + 1];	//��ע�Ͳ���ûʲô����
//		strcpy(_str, s._str);
//	}
//
//	//��ֵ���� - ��������
//	String(String&& s)
//		:_str(nullptr)
//	{
//		cout << "String(String&& s) - �ƶ��������� - Ч�ʸ�" << endl;
//		swap(s._str, _str);
//	}
//	//Ĭ�ϰ汾
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			cout << "String& operator=(const String& s) - ��ֵ���� - Ч�ʵ�" << endl;
//			char* tmp = new char[strlen(s._str) + 1];
//			strcpy(tmp, s._str);
//			delete[] _str;
//			_str = tmp;
//		}
//		return *this;
//	}
//	//��ֵ����
//	String& operator=(String&& s)
//	{
//		if (this != &s)
//		{
//			cout << "String& operator=(String&& s) - �ƶ���ֵ - Ч�ʸ�" << endl;
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
//		return tmp;		//���ص�����ֵ(����ֵ)����Ϊ��ֵ���أ����ص�����ʱ����
//	}
//
//	String& operator+=(const String& s)
//	{
//		return *this;	//���ص�����ֵ����Ϊ�����÷���
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
//	//String s3(func("��ֵ"));
//	//s3 = s2;
//	//s3 = "��ֵ";
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
//	v.push_back("��ֵ");
//	v.push_back(to_string(val));
//
//
//	return 0;
//}

//int main()
//{
//	//vector<pair<string, string>> vp;
//	//vp.push_back(make_pair("fly", "��"));
//
//
//	//vp.emplace_back(make_pair("sleep", "˯��"));
//	//vp.emplace_back("decline", "����");
//	//for (auto& e : vp)
//	//	cout << e.first << ":" << e.second << endl;
//
//	vector<int> v(5);
//
//	return 0;
//}


//�º�����lamdba���ʽ
class Goods
{
public:
	string name;
	int nums;
	double prices;
};

//�������������ֵ������ǰ�� --- ����
struct CompareNumsGreater
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.nums > g2.nums;
	}
};

//���ռ۸񣬴��ֵ������ǰ�� --- ����
struct ComparePricesGreater
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.prices > g2.prices;
	}
};

//����������С��ֵ������ǰ�� --- ����
struct CompareNumsLess
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.nums < g2.nums;
	}
};

//���ռ۸�С��ֵ������ǰ�� --- ����
struct ComparePricesLess
{
	bool operator()(const Goods& g1, const Goods& g2)
	{
		return g1.prices < g2.prices;
	}
};

void test_Functor()
{
	Goods gd[] = { {"ƻ��", 10, 5.0}, {"����", 8, 3.5}, {"�㽶", 9, 2.2} };
	
	//������������ ����
	sort(gd, gd + 3, CompareNumsGreater());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;

	//���ռ۸����� ����
	sort(gd, gd + 3, ComparePricesGreater());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;


	//������������ ����
	sort(gd, gd + 3, CompareNumsLess());
	for (auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;
	cout << endl;

	//���ռ۸����� ����
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

	////�ɹ����� - �����б�ʹ����ֵ����
	//auto swap1 = [](int& x, int& y) {
	//	int tmp = x;
	//	x = y;
	//	y = tmp;
	//};
	//swap1(a, b);
	//cout << "a=" << a << " b=" << b << endl;

	////�ɹ����� - �����б�ʹ��ȡ��ַ
	//auto swap2 = [](int* x, int* y) {
	//	int tmp = *x;
	//	*x = *y;
	//	*y = tmp;
	//};
	//swap2(&a, &b);
	//cout << "a=" << a << " b=" << b << endl;

	////ʧ�ܽ��� - ʹ�ô�ֵ��ʽ���޷�����ʵ�ε�ֵ
	//auto swap3 = [](int x, int y) {
	//	int tmp = x;
	//	x = y;
	//	y = tmp;
	//};
	//swap3(a, b);
	//cout << "a=" << a << " b=" << b << endl;


	////�ɹ����� - �����б�ʹ�����ô�ֵ
	//auto swap4 = [&a, &b]() {
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//swap4();
	//cout << "a=" << a << " b=" << b << endl;

	////ʧ�ܽ��� - �����б������ֵ�Ŀ���������޸Ĳ�����ԭֵ���Ӱ��
	//auto swap5 = [a, b]()mutable {	//mutable�ò����б��ֵ�����Ա�Ϊ��const
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//swap5();
	//cout << "a=" << a << " b=" << b << endl;

}

void test_lambda2()
{
	Goods gd[] = { {"ƻ��", 10, 5.0}, {"����", 8, 3.5}, {"�㽶", 9, 2.2} };
	//auto NumGreater = [](const Goods& g1, const Goods& g2) {return g1.nums > g2.nums;};
	//sort(gd, gd + 3, NumGreater);

	sort(gd, gd + 3, [](const Goods& g1, const Goods& g2) {return g1.nums > g2.nums;});
	for(auto& e : gd)
		cout << e.name << "-" << e.nums << "-" << e.prices << endl;


}

void test_lambda3()
{
	Goods gd[] = { {"ƻ��", 10, 5.0}, {"����", 8, 3.5}, {"�㽶", 9, 2.2} };
	
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
//	//test_inher();	//���Զ�̳�
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
//C++11�߳̿�
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
//	//1. ����ָ�� --- �����ö���߳�ִ��ͬʱ���뵽һ��������
//	//thread t1(Routine);
//	//thread t2(Routine);
//	
//	//2. lambda���ʽ/�º���	---	�ò�ͬ���߳�ִ�в�ͬ�ĺ���
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
//	//ʹ��2���̣߳�ʵ��һ���߳�ֻ��ӡ��������һ���߳�ֻ��ӡż���������߳̽�����ӡ������֪ͨ�Է���
//	int n = 10;
//	mutex mtx1, mtx2;	//�����mutex����Ϊ����������������ζ����õ�
//	condition_variable cv1, cv2;
//
//	thread t1([&] {
//		for (int i = 0; i < n; i += 2)
//		{
//			unique_lock<mutex> ul1(mtx1);
//			if (i != 0)
//				cv1.wait(ul1);
//			//cv1.wait(unique_lock<mutex>(mtx1));	//wait�еĲ����Ǹ���ֵ����������ֱ�Ӵ�����������Ϊ���ﴫ������ֵ
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
