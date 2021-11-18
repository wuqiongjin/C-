#pragma once
#include "RBTree.h"
#include <vector>

namespace wqj_map
{
	template <class K, class V>
	class map
	{
		//自己实现仿函数，然后在RBTree中就可以通过仿函数去调用仿函数的功能了
		//如在map中，仿函数的功能是返回first。在set中仿函数就是直接返回k值。
		//这样在RBTree中，就可以实现：你传给我的是什么仿函数？我就会调用你传给我的仿函数，去实现它的功能！
		//这里的第三个模板参数 实际上我们传入的就是一个"类"，类中只重载了operator()，一般我们称它为仿函数。
		struct MapKeyOfValue
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		//在map中对RBTree中的已经重命名的迭代器进行 再次重命名
		//加typename的原因：因为RBTree<...>这个类还没有实例化，所以没法去里面找到iterator，加上typename告诉编译器这是个类的名称，先让我过去
		typedef typename RBTree<K, pair<K, V>, MapKeyOfValue>::iterator iterator;	//必须加上

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		pair<iterator, bool> Insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		//operator[]的重载是在Map类中的，Set没有[]
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;	//ret.first是_insert插入的结点的迭代器。->second 访问那个结点的second的数据
		}

		iterator Find(const K& k)
		{
			return _t.Find(k);
		}

	private:
		RBTree<K, pair<K, V>, MapKeyOfValue> _t;
	};

	void test_map1()
	{
		map<int, int> m;
		m.Insert(make_pair(3, 9));
		m.Insert(make_pair(5, 5));
		m.Insert(make_pair(4, 4));
		m.Insert(make_pair(1, 1));
		m.Insert(make_pair(2, 2));

		map<int, int>::iterator it = m.begin();
		while (it != m.end())
		{
			cout << (*it).first << ":" << (*it).second << endl;
			++it;
		}

		//cout << m.Find(3)->second << endl;
	}

	void test_map2()
	{
		map<string, int> countMap;
		vector<string> v = { "苹果","苹果", "橘子", "西瓜", "苹果", "橘子", "西瓜", "菠萝", "香蕉" };

		for (auto& e : v)
		{
			countMap[e]++;
		}

		for (auto& e : countMap)
		{
			cout << e.first << ":" << e.second << endl;
		}
	}
}