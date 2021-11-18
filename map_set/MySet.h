#pragma once

namespace wqj_set
{
	template <class K>
	class set
	{
		struct SetKeyOfValue
		{
			const K& operator()(const K& k)
			{
				return k;
			}
		};
	public:
		typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator, bool> Insert(const K& k)
		{
			return _t.Insert(k);
		}

		iterator Find(const K& k)
		{
			return _t.Find(k);
		}

	private:
		RBTree<K, K, SetKeyOfValue> _t;
	};

	void test_set1()
	{
		set<int> s;
		s.Insert(3);
		s.Insert(5);
		s.Insert(2);
		s.Insert(1);
		
		set<int>::iterator it = s.begin();
		
		while (it != s.end())
		{
			cout << *it << endl;
			++it;
		}

	/*	cout << *(s.Find(3)) << endl;*/
	}
}