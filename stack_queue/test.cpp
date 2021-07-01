#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include "stack.h"
#include "queue.h"


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

int main()
{
	//test_stack();
	//test_queue();

	//wqj::teststack();
	//wqj::testqueue();
	testdeque();
}