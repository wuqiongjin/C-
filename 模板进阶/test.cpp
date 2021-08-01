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




//������ģ�����
template <class T, int N>
class Array
{
public:
	Array()
	{
		cout << "Array()" << endl;
	}

private:
	T _a[N];	//��̬����
};



//����ģ����ػ�
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
////���󣬺��������б������ �� ԭģ��Ĳ����б�Ļ������Ͳ���ͬ
//template <>
//bool isEqual<const char*>(const char* str1, const char* str2)
//{
//	return !strcmp(str1, str2);
//}
//
////��ȷ
//template <>
//bool isEqual<const char*>(const char* const& str1, const char* const& str2)
//{
//	return !strcmp(str1, str2);
//}



//��ģ����ػ�
template <class T1, class T2>
class A
{
public:
	A()
	{
		cout << "ԭģ���ࣺA()<T1, T2>" << endl;
	}

private:
	T1 _a;
	T2 _b;
};


//ȫ�ػ�		
template <>
class A<int, char>
{
public:
	A()
	{
		cout << "ȫ�ػ���A()<int, char>" << endl;
	}
private:
	int	 _a;
	char _b;
};


//ƫ�ػ�		ƫ�ػ���ָ ֻ�ػ����ֲ��� / �����ǶԲ�����һ��������(����Ϊ ָ��* ���� ����&)
template <class T>
class A<int, T>
{
public:
	A()
	{
		cout << "ƫ�ػ���A()<int, T>" << endl;
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
		cout << "ƫ�ػ���A()<T1*, T2*>" << endl;
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

//��������

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