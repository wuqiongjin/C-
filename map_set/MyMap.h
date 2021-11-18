#pragma once
#include "RBTree.h"
#include <vector>

namespace wqj_map
{
	template <class K, class V>
	class map
	{
		//�Լ�ʵ�ַº�����Ȼ����RBTree�оͿ���ͨ���º���ȥ���÷º����Ĺ�����
		//����map�У��º����Ĺ����Ƿ���first����set�зº�������ֱ�ӷ���kֵ��
		//������RBTree�У��Ϳ���ʵ�֣��㴫���ҵ���ʲô�º������Ҿͻ�����㴫���ҵķº�����ȥʵ�����Ĺ��ܣ�
		//����ĵ�����ģ����� ʵ�������Ǵ���ľ���һ��"��"������ֻ������operator()��һ�����ǳ���Ϊ�º�����
		struct MapKeyOfValue
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		//��map�ж�RBTree�е��Ѿ��������ĵ��������� �ٴ�������
		//��typename��ԭ����ΪRBTree<...>����໹û��ʵ����������û��ȥ�����ҵ�iterator������typename���߱��������Ǹ�������ƣ������ҹ�ȥ
		typedef typename RBTree<K, pair<K, V>, MapKeyOfValue>::iterator iterator;	//�������

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

		//operator[]����������Map���еģ�Setû��[]
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _t.Insert(make_pair(key, V()));
			return ret.first->second;	//ret.first��_insert����Ľ��ĵ�������->second �����Ǹ�����second������
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
		vector<string> v = { "ƻ��","ƻ��", "����", "����", "ƻ��", "����", "����", "����", "�㽶" };

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