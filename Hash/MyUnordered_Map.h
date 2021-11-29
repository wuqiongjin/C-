#pragma once
#include "HashTable.h"

//using namespace OPEN_HASH;	//�������չ��������Щ�ط�Ҳ��Ҫָ�������ռ䡣����

namespace wqj_umap
{
	//��MapKeyOfValue���unordered_map���ڲ���Ҳ�ǿ��Ե�
	template <class K, class Value>
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, Value>& kv)
		{
			return kv.first;
		}
	};

	//����Hash����: �������²���Ĭ�ϵĴ��������������ϲ�����Ҳ����֧���Զ��崦���������������������һ��Hash�Ҵ�ȱʡ
	template <class K, class Value, class Hash = OPEN_HASH::_Hash<K>>
	class unordered_map
	{
	public:
		typedef MapKeyOfValue<K, Value> MapKeyOfValue;

		//��MapKeyOfValue������ڲ���Ƚϼ�
		//struct MapKeyOfValue
		//{
		//	const K& operator()(const pair<K, Value>& kv)
		//	{
		//		return kv.first;
		//	}
		//};

		//typedef typename OPEN_HASH::__HashIterator<K, pair<K, Value>, MapKeyOfValue> iterator;
		typedef typename OPEN_HASH::HashTable<K, pair<K, Value>, MapKeyOfValue, Hash>::iterator iterator;	//�����䶼����!
		

		pair<iterator, bool> Insert(const pair<K, Value>& kv)
		{
			return _ht.Insert(kv);
		}

		iterator begin()
		{
			return _ht.begin();
		}
		
		iterator end()
		{
			return _ht.end();
		}


		Value& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, Value()));
			return ret.first->second;
		}

	private:
		OPEN_HASH::HashTable<K, pair<K, Value>, MapKeyOfValue, Hash> _ht;
	};

	void test_MyUnordered_Map()
	{
		unordered_map<string, string> um;
		um.Insert(make_pair("sort", "����"));
		um.Insert(make_pair("fly", "����"));
		um.Insert(make_pair("down", "�½�"));
		um.Insert(make_pair("sleep", "˯��"));

		um["sort"] = "������";
		um["bed"] = "��";

		auto it = um.begin();
		while (it != um.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
	}
}
