#pragma once

namespace wqj
{
	//仿函数的本质就是重载了operator()，
	//然后利用模板类型去实例化less或者greater类的对象。然后借助对象去调用operator()
	template <class T>
	struct less
	{
		bool operator()(const T& x1, const T& x2)	//使用起来和函数类似。创建个对象cmp, 然后调用它的operator()
		{											//cmp(x1, x2)  <==> cmp.operator()(x1,x2)
			return x1 < x2;
		}
	};

	template <class T>
	struct greater
	{
		bool operator()(const T& x1, const T& x2)
		{
			return x1 > x2;
		}
	};

	//仿函数的本质就是重载了operator()，然后利用模板类型去实例化less或者greater类的对象。然后借助对象去调用operator()
	template <class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		//建大堆
		void AdjustUp(int child)
		{
			Compare cmp;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (cmp(_con[parent], _con[child]))		//cmp.operator()(_con[parent], _con[child])
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}
		}

		void AdjustDown(int root)
		{
			Compare cmp;
			int child = 2 * root + 1;

			while (child < _con.size())
			{
				//选左右孩子中大的那一个
				if (child + 1 < _con.size() && cmp(_con[child], _con[child + 1]))
					++child;

				if (cmp(_con[root], _con[child]))
					swap(_con[root], _con[child]);
				else
					break;

				root = child;
				child = 2 * root + 1;
			}
		}

		void push(T x)
		{
			_con.push_back(x);
			//O(logN)
			AdjustUp(_con.size() - 1);
		}
		
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			//O(logN)
			AdjustDown(0);
		}

		T& top()
		{
			assert(!_con.empty());
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};

	void test_priority_queue()
	{
		priority_queue<int> pq;								//建最大堆
		priority_queue<int, vector<int>, greater<int>> pq;	//建最小堆
		pq.push(1);
		pq.push(-10);
		pq.push(54);
		pq.push(32);
		pq.push(39);

		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
	}
}