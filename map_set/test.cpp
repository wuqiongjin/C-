#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

void test_set1()
{
	//set: ÅÅĞò + È¥ÖØ
	set<int> s;
	s.insert(4);
	s.insert(3);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(3);
	s.insert(3);

	/*set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;*/

	set<int>::iterator it = s.find(3);
	if (it != s.end())
	{
		cout << *it << endl;
	}

	//for (auto& e : s)
	//{
	//	cout << e << " ";
	//}
	cout << endl;
}

void test_map1()
{
	//map<int, string> m;
	//m.insert(make_pair(3, "Sort"));
	//m.insert(make_pair(5, "Map"));
	//m.insert(make_pair(2, "Set"));
	//m.insert(make_pair(1, "RBTree"));

	//for (auto& e : m)
	//{
	//	cout << e.first << ":" << e.second.c_str() << endl;;
	//}

	map<string, string> m;
	m.insert(make_pair("sort", "ÅÅĞò"));
	m.insert(make_pair("string", "×Ö·û´®"));
	m.insert(make_pair("apple", "Æ»¹û"));
	m.insert(make_pair("sky", "Ìì¿Õ"));

	map<string, string>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;

	cout << (m["sort"] = "paixu") << endl;
	m["string"] = "zifuchuan";
	cout << (m["nm"] = "YourMom") << endl;;
	//m.at("orange") = "éÙ×Ó";
	cout << endl;

	for (auto& e : m)
	{
		cout << e.first << ":" << e.second << endl;
	}
	cout << endl;
}


void test_map2()
{
	map<string, int> countMap;
	//string strs[] = { "Æ»¹û","Æ»¹û", "éÙ×Ó", "Î÷¹Ï", "Æ»¹û", "éÙ×Ó", "Î÷¹Ï", "²¤ÂÜ", "Ïã½¶" };
	vector<string> v = { "Æ»¹û","Æ»¹û", "éÙ×Ó", "Î÷¹Ï", "Æ»¹û", "éÙ×Ó", "Î÷¹Ï", "²¤ÂÜ", "Ïã½¶" };

	vector<string>::iterator it = v.begin();
	while (it != v.end())
	{
		countMap[*it]++;
		++it;
	}


	for (auto& e : countMap)
	{
		cout << e.first << ":" << e.second << endl;
	}
	cout << endl;
}


void test_multiset()
{
	multiset<int> ms;
	ms.insert(3);
	ms.insert(3);
	ms.insert(2);
	ms.insert(5);
	ms.insert(7);
	ms.insert(4);
	ms.insert(5);
	ms.insert(6);

	multiset<int>::iterator it = ms.begin();
	while (it != ms.end())
	{
		cout << *it << endl;
		++it;
	}
	cout << endl;
}

void test_multimap()
{
	multimap<int, int> mm;
	mm.insert(make_pair(1, 5));
	mm.insert(make_pair(1, 3));
	mm.insert(make_pair(2, 2));
	mm.insert(make_pair(4, 3));
	mm.insert(make_pair(3, 5));

	multimap<int, int>::iterator it = mm.begin();
	while (it != mm.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;
}

#include "MyMap.h"
#include "MySet.h"

int main()
{
	//test_set1();
	//test_map1();
	//test_map2();
	//test_multiset();
	//test_multimap();

	//wqj_set::test_set1();
	//wqj_map::test_map1();
	wqj_map::test_map2();
	return 0;
}