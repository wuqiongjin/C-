#pragma once

namespace wqj
{
	template <class T, class Container>
	class stack
	{
	public:
		void push(T val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_back();
		}

		bool empty()
		{
			return _con.empty();
		}

		size_t size()
		{
			return _con.size();
		}

		T& top()
		{
			return _con.back();
		}

	private:
		Container _con;
	};

	void teststack()
	{
		//stack<int, vector<int>> st;	//stack选用vector和list作为适配器都可以
		stack<int, list<int>> st;
		st.push(1);
		st.push(2);
		st.push(3);
		st.push(4);

		while (!st.empty())
		{
			cout << st.top() << " ";
			st.pop();
		}
		cout << endl;
	}
}