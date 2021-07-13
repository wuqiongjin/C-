#include <iostream>
using namespace std;

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
	Add<int, int>(1, 3);
	return 0;
}