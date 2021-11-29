#pragma once
#include "HashTable.h"

//using namespace OPEN_HASH;	//这里就算展开，在有些地方也需要指定命名空间。。。

namespace wqj_umap
{
	//把MapKeyOfValue搞成unordered_map的内部类也是可以的
	template <class K, class Value>
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, Value>& kv)
		{
			return kv.first;
		}
	};

	//关于Hash参数: 我们在下层有默认的处理方法，但是在上层这里也必须支持自定义处理方法，所以这里必须设置一个Hash且带缺省
	template <class K, class Value, class Hash = OPEN_HASH::_Hash<K>>
	class unordered_map
	{
	public:
		typedef MapKeyOfValue<K, Value> MapKeyOfValue;

		//把MapKeyOfValue定义成内部类比较简单
		//struct MapKeyOfValue
		//{
		//	const K& operator()(const pair<K, Value>& kv)
		//	{
		//		return kv.first;
		//	}
		//};

		//typedef typename OPEN_HASH::__HashIterator<K, pair<K, Value>, MapKeyOfValue> iterator;
		typedef typename OPEN_HASH::HashTable<K, pair<K, Value>, MapKeyOfValue, Hash>::iterator iterator;	//这两句都可以!
		

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
		um.Insert(make_pair("sort", "排序"));
		um.Insert(make_pair("fly", "飞翔"));
		um.Insert(make_pair("down", "下降"));
		um.Insert(make_pair("sleep", "睡觉"));

		um["sort"] = "不排序";
		um["bed"] = "床";

		auto it = um.begin();
		while (it != um.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
	}
}
