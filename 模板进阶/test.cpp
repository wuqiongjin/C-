#include <iostream>
using namespace std;

//template <class T>
//class Stack
//{
//public:
//	Stack() {};
//	void push_back(const T& x);
//private:
//	T*	   _a;
//	size_t _capacity;
//	size_t _size;
//};
//
//template <class T>
//void Stack<T>::push_back(const T& x)
//{}




//非类型模板参数
template <class T, int N>
class Array
{
public:
	Array()
	{
		cout << "Array()" << endl;
	}

private:
	T _a[N];	//静态数组
};



//函数模板的特化
//template <class T>
//bool isEqual(T x1, T x2)
//{
//	return x1 == x2;
//}
//
//template <>
//bool isEqual<char*>(char* str1, char* str2)
//{
//	return !strcmp(str1, str2);
//}


//template <class T>
//bool isEqual(const T& x1, const T& x2)
//{
//	return x1 == x2;
//}
//
////错误，函数参数列表的类型 与 原模板的参数列表的基础类型不相同
//template <>
//bool isEqual<const char*>(const char* str1, const char* str2)
//{
//	return !strcmp(str1, str2);
//}
//
////正确
//template <>
//bool isEqual<const char*>(const char* const& str1, const char* const& str2)
//{
//	return !strcmp(str1, str2);
//}



//类模板的特化
template <class T1, class T2>
class A
{
public:
	A()
	{
		cout << "原模板类：A()<T1, T2>" << endl;
	}

private:
	T1 _a;
	T2 _b;
};


//全特化		
template <>
class A<int, char>
{
public:
	A()
	{
		cout << "全特化：A()<int, char>" << endl;
	}
private:
	int	 _a;
	char _b;
};


//偏特化		偏特化是指 只特化部分参数 / 或者是对参数进一步的限制(限制为 指针* 或者 引用&)
template <class T>
class A<int, T>
{
public:
	A()
	{
		cout << "偏特化：A()<int, T>" << endl;
	}
private:
	int	 _a;
	T _b;
};


template <class T1, class T2>
class A<T1*, T2*>
{
public:
	A()
	{
		cout << "偏特化：A()<T1*, T2*>" << endl;
	}
private:
	T1*	 _a;
	T2* _b;
};

int main()
{
	//Array<int, 10> a;

	//A<char, char>  a;
	//A<int, char> a1;
	//A<int, int>  a2;
	//A<int*, int*> a3;
	//A<char*, char*> a4;
	//Add<int, int>(1, 3);
	//Stack<int> st1;
	//Stack<double> st2;

	return 0;
}

//博客内容

////"A.h"
//template <class T>
//bool isEqual(const T& x1, const T& x2);
//
////A.cpp
//#include "A.h"
//template <class T>
//bool isEqual(const T& x1, const T& x2)
//{
//	return x1 == x2;
//}
//
//template
//bool isEqual<int>(const int& x1, const int& x2);
//
//template
//bool isEqual<double>(const double& x1, const double& x2);
//
////main.cpp
//int main()
//{
//	isEqual<int>(1, 2);
//
//	return 0;
//}