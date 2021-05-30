#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "vector.h"

void test_vector1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);

	vector<int> v2 = v1;

	//1. 普通遍历  (可以修改数据) operator[] + size()
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	
	//2. 迭代器遍历
	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//3. 范围for
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}

void print_vector(const vector<int>& vt)
{
	vector<int>::const_iterator it2 = vt.begin();
	while (it2 != vt.end())
	{
		cout << *it2 << " ";
		++it2;
	}
	cout << endl;
}

void test_vector2()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	vector<int>::iterator it1 = v.begin();
	print_vector(v);

	vector<int>::reverse_iterator it3 = v.rbegin();
	vector<int>::const_reverse_iterator it4 = v.rbegin();
}

void test_vector3()
{
	vector<int> v;
	v.reserve(100);
	v.resize(980);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = i;
		cout << v[i] << " ";
	}
	cout << endl;
}

void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//assert断言报错
	//v[5] = 10;

	//at进行抛异常
	v.at(5) = 10;
}

void test_vector5()
{
	vector<int> v(5);

	v.insert(v.begin(), 1);
	v.insert(v.begin() + 1, 2);
	v.insert(v.begin() + 2, 3);

	v.erase(v.begin());
	v.erase(v.end() - 1);
	v.erase(v.end() - 1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector6()
{
	vector<int> v;
	v.push_back(11);
	v.push_back(22);
	v.push_back(33);
	v.push_back(44);
	v.push_back(55);

	vector<int>::iterator pos = find(v.begin(), v.end(), 33);//传的范围是 [first, last)
	//要和所传的区间的尾迭代器进行比较，看是否找到了。如果没找到的话pos就是v.end()
	if (pos != v.end())
	{
		v.erase(pos);
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
}

void test_vector7()
{
	int a[] = { 1,2,3,4,5 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));	//传了迭代器的两端去构造初始化

	for (auto e : v)
	{
		cout << e << " ";
	}
}

void test_vector8()
{
	//1. 迭代器失效， 类型1：由于增容导致迭代器失效
	vector<int> v{ 1,2,3,4,5 };
	//vector<int>::iterator it = v.begin();

	//v.push_back(6);//这里进行了扩容操作，所以it迭代器失效了

	//it = v.begin();	//解决方法：更新迭代器的位置

	//while (it != v.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//}

	//2. 迭代器失效问题， 类型2:erase删除使得
	vector<int>::iterator ite = v.begin();

	while (ite != v.end())
	{
		if (*ite % 2 == 0)
		{
			ite = v.erase(ite);//用erase删除后，整个数组后面的元素都会向前移动。而迭代器所指的位置没有变
		}				//这样就会导致迭代器失效。VS下会直接报错，而g++中不会，但是结果也可能是错误的
		else
		{
			++ite;
		}
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
}

int main()
{
	//test_vector1();
	//test_vector2();
	//test_vector3();
	//test_vector4();
	//test_vector5();
	//test_vector6();
	//test_vector7();
	//test_vector8();


	//wqj::test_vector1();
	//wqj::test_vector2();
	wqj::test_vector3();
	
	return 0;
}