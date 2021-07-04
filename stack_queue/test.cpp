#include <iostream>
#include <assert.h>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <queue>		//priority_queue在里面
#include <functional>
#include "stack.h"
#include "queue.h"
#include "priority_queue.h"

//#include <stack>
//#include <queue>
//
//void test_stack()
//{
//	stack<int> st;
//	st.push(1);
//	st.push(2);
//	st.push(3);
//	st.push(4);
//
//	while (!st.empty())
//	{
//		cout << st.top() << " ";
//		st.pop();
//	}
//	cout << endl;
//}
//
//void test_queue()
//{
//	queue<int> q;
//	q.push(1);
//	q.push(2);
//	q.push(3);
//	q.push(4);
//
//	while (!q.empty())
//	{
//		cout << q.front() << " ";
//		q.pop();
//	}
//	cout << endl;
//}



void testdeque()
{
	deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	d.push_back(4);
	d.push_front(0);
	d.push_front(-1);

	
	//deque支持随机访问
	for (size_t i = 0; i < d.size(); ++i)
	{
		cout << d[i] << " ";
	}
	cout << endl;

	//for (auto& e : d)
	//{
	//	cout << e << " ";
	//}
	//cout << endl;
}

void test_priority_queue()
{
	vector<int> v{ 1,2,3,4,5 };
	int arr[] = { -1,-2,-3,-4,-5 };

	////cout << v << endl;				//v是个对象。。。
	//cout << &v << endl;			
	////cout << v.begin() << endl;		//cout没有重载vector迭代器的输出
	//cout << typeid(arr).name() << endl;

	//cout << (v.begin() + 5 == v.end()) << endl;

	
	//priority_queue<int> pq;
	priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.begin()+5);	//priority_queue可以给迭代器的范围以用来初始化

	//pq.push(1);
	//pq.push(-10);
	//pq.push(54);
	//pq.push(32);
	//pq.push(39);

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

void test_sort()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(22);
	v.push_back(9);
	v.push_back(4);
	v.push_back(8);

	//sort中传的是对象

	//默认排 升序	less <
	sort(v.begin(), v.end());

	//	  排 降序	greater >
	sort(v.begin(), v.end(), greater<int>());	//使用匿名对象

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}


int main()
{
	//test_stack();
	//test_queue();

	//wqj::teststack();
	//wqj::testqueue();
	//testdeque();
	//test_priority_queue();
	//wqj::test_priority_queue();

	test_sort();
}