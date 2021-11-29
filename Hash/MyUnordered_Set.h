#pragma once
#include "HashTable.h"

namespace wqj_uset
{
	template <class K, class Hash = OPEN_HASH::_Hash<K>>
	class unordered_set
	{
	public:
		//�����ֱ�����ڲ����ˣ�unordered_map�а����ŵ����ⲿ�࣬���ǻ���Ҫ������typedefһ�£���Ȼ���鷳��<���Ƽ��ڲ���>
		struct SetKeyOfValue
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename OPEN_HASH::HashTable<K, K, SetKeyOfValue, Hash>::iterator iterator;	//�����typename���߱��������������Ǹ�������

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