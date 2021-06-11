#include <iostream>
#include <assert.h>
#include <list>
using namespace std;

void print_list(const list<int>& lt)
{
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_list1()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);


	print_list(lt);
}

void test_list2()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	
	list<int>::iterator pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end())
	{
		lt.insert(pos, 999); // 1 2 999 3 4 5
	}

	print_list(lt);
}

void test_list3()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	list<int>::iterator pos = find(l.begin(), l.end(), 2);

	//list迭代器失效问题处理方法 
	list<int>::iterator it = l.begin();
	while (it != l.end())
	{
		if (*it % 2 == 0)
		{
			it = l.erase(it);// 尽量使用这种。（这里不能使用it++，因为这里是指定数据删除）
		}
		else
		{
			++it;
		}
	}
	print_list(l);
}

void test_list4()
{
	list<int> l;
	
	list<int>::iterator it = l.begin();
	list<int>::iterator ite = l.end();

}

//struct Date
//{
//	int _year = 0;
//	int _month = 1;
//	int _day = 1;
//};
//
//void test_list5()
//{
//	list<Date> l;
//	l.push_back(Date());
//	l.push_back(Date());
//
//	list<Date>::iterator it = l.begin();
//	while (it != l.begin())
//	{
//		//cout << *it << " ";		//没有重载自定义类型的输出
//		cout << it->_year << " " << it->_month << " " << it->_day << endl;	//需要使用->操作符去访问
//	}
//	cout << endl;
//}

//#include "list.h"
#include "mylist.h"

int main()
{
	//test_list1();
	//test_list2();
	//test_list3();
	//test_list4();
	//test_list5();

	//wqj::test_list1();
	//wqj::test_list2();
	//wqj::test_list3();
	wqj::test_list4();


	return 0;
}