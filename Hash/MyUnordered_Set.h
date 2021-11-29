#pragma once
#include "HashTable.h"

namespace wqj_uset
{
	template <class K, class Hash = OPEN_HASH::_Hash<K>>
	class unordered_set
	{
	public:
		//这里就直接用内部类了，unordered_map中把它放到了外部类，但是还需要在里面typedef一下，不然很麻烦。<更推荐内部类>
		struct SetKeyOfValue
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename OPEN_HASH::HashTable<K, K, SetKeyOfValue, Hash>::iterator iterator;	//必须加typename告诉编译器，它后面那个是类型

		pair<iterator, bool> Insert(const K& key)
		{
			return _ht.Insert(key);
		}

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

	private:
		OPEN_HASH::HashTable<K, K, SetKeyOfValue, Hash> _ht;
	};

	void test_MyUnordered_Set()
	{
		unordered_set<int> s;
		s.Insert(1);
		s.Insert(4);
		s.Insert(5);
		s.Insert(2);

		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << endl;
			++it;
		}
	}
}