#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

//int func1(int a, int b)
//{
//	//if (b == 0)
//	//	throw - 1;
//
//	//if (b == 0)
//	//	throw string("除零错误!");
//
//	if (b == 0)
//		throw 3.1415;
//
//	return a / b;
//}
//
//void test1()
//{
//	try
//	{
//		int a, b;
//		cin >> a >> b;
//		cout << func1(a, b) << endl;
//	}
//	catch (int& err)
//	{
//		cout << "除零错误:" << err << endl;
//	}
//	catch(string& err)
//	{
//		cout << err << endl;
//	}
//	catch (...)
//	{
//		cout << "未知异常!!!" << endl;
//	}
//}
//
//void f3()
//{
//	throw 111;
//}
//
//void f2()
//{
//	f3();
//}
//
//void f1()
//{
//	try
//	{
//		f2();
//	}
//	catch (int& err)
//	{
//		cout << "f1()-" <<"err:" << err << endl;
//	}
//}
//
//void test2()
//{
//	try
//	{
//		f1();
//	}
//	catch (int& err)
//	{
//		cout << "test2()-err:" << err << endl;
//	}
//}
//
//int Div(int a, int b)
//{
//	if (b == 0)
//		throw "Division by zero condition!";
//	
//	return a / b;
//}
//
//void reThrow()
//{
//	int* arr = new int[10];
//	//try
//	{
//		int a, b;
//		cin >> a >> b;
//		int ret = Div(a, b);
//		cout << "Result:" << ret << endl;
//	}
//	//catch (...)	//我这里的目的在于重新抛出，所以捕获的时候可以使用...去捕获任意类型的异常
//	//{
//		cout << "Delete[] arr success!" << endl;
//		delete[] arr;
//	//	throw;
//	//}
//}
//
//void test3()
//{
//	try
//	{
//		reThrow();
//	}
//	catch (const char* errmsg)
//	{
//		cout << errmsg << endl;
//	}
//}
//
//void test4()
//{
//
//}
//
//int main()
//{
//	//test1();
//	//test2();
//	//test3();
//	test4();
//	
//	return 0;
//}



//blog - code3
//class MyException
//{
//public:
//	MyException(string errmsg, int id)
//		:_errmsg(errmsg),
//		 _id(id)
//	{}
//	
//	virtual string what() const = 0;	//必须放到public下才能让类外定义的成员访问到
//
//protected:
//	string _errmsg;	//存放错误信息
//	int _id;		//错误码
//	//vector<stack<string>> _st;	//存放调用链的信息
//};
//
//class CacheException : public MyException
//{
//public:
//	CacheException(string errmsg, int id)
//		:MyException(errmsg, id)
//	{}
//
//	virtual string what() const
//	{
//		return "CacheException!: " + _errmsg;
//	}
//};
//
//class NetworkException : public MyException
//{
//public:
//	NetworkException(string errmsg, int id)
//		:MyException(errmsg, id)
//	{}
//
//	virtual string what() const
//	{
//		return "NetworkException!: " + _errmsg;
//	}
//};
//
//class SqlException : public MyException
//{
//public:
//	SqlException(string errmsg, int id)
//		:MyException(errmsg, id)
//	{}
//
//	virtual string what() const
//	{
//		return "SqlException!: " + _errmsg;
//	}
//};
//
//int main()
//{
//	try
//	{
//		//抛出任意派生类对象
//		throw SqlException("sql open failed", 10);
//	}catch (const MyException& e)	//使用基类去捕获
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)	//走到这里说明出现未知异常
//	{
//		cout << "Unknown Exception!" << endl;
//	}
//
//	return 0;
//}


//blog - code1
//void f3()
//{
//	throw 123;
//}
//void f2()
//{
//	f3();
//}
//void f1()
//{
//	try
//	{
//		f2();
//		cout << "f1() not catched Exception!" << endl;
//	}
//	catch (int& err)
//	{
//		cout << "f1()-err: " << err << endl;
//	}
//}
//
//int main()
//{
//	try
//	{
//		f1();
//		cout << "main not catched Exception!" << endl;
//	}
//	catch (int& err)
//	{
//		cout << "main-err: " << err << endl;
//	}
//	return 0;
//}

//blog - code2
//void FirstThrowException()
//{
//	throw "First throw a exception!";
//}
//
//void SecondThrowException()
//{
//	int* arr = new int[10];
//	try
//	{
//		FirstThrowException();
//	}
//	catch (...)
//	{
//		cout << "Delete[] arr Success!" << endl;
//		delete[] arr;
//		throw;
//	}
//}
//
//void SoluteException()
//{
//	try
//	{
//		SecondThrowException();
//	}
//	catch (const char* err)
//	{
//		cout << err << endl;
//	}
//}
//
//int main()
//{
//	SoluteException();
//	return 0;
//}


//void func() throw()
//{
//	//throw 1;
//}
//
//void func2() noexcept
//{
//
//}
//
//int main()
//{
//	func();
//	return 0;
//}


// C++标准库异常测试
//int main()
//{
//	try
//	{
//		vector<int> v(5);
//		v.at(5) = 0;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "Unknown Exception!" << endl;
//	}
//}