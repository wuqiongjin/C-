#include <iostream>
using namespace std;

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
template <class T1, class T2>
T1 Add(T1 x, T2 y)
{
	return x + y;
}

template <>
char Add<char, char>(char a, char b)
{
	return a + b;
}


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
	Add<int, int>(1, 3);
	return 0;
}