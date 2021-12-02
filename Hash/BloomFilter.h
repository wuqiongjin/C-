#pragma once
#include "bitset.h"
#include <string>

//布隆过滤器:不支持删除!

namespace wqj_bloomf
{
	template <class K>
	struct HashStr1
	{
		size_t operator()(const K& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i)
			{
				hash = hash * 131 + key[i];
			}
			return hash;
		}
	};

	template <class K>
	struct HashStr2
	{
		size_t operator()(const K& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i)
			{
				hash = 65599 * hash + key[i];
			}
			return hash;
		}
	};

	template <class K>
	struct HashStr3
	{
		size_t operator()(const K& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i)
			{
				hash += (hash << 5) + key[i];
			}
			return hash;
		}
	};

	template <class K = string, class Hash1 = HashStr1<K>, class Hash2 = HashStr2<K>, class Hash3 = HashStr3<K>>
	class bloomfilter
	{
	public:
		bloomfilter(size_t num)
			:_bs(num * 5),
			 _N(num * 5)
		{}

		void set(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;	//index计算的是%过布隆过滤器长度的位置
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;

			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}

		bool test(const K& key)
		{
			size_t index1 = Hash1()(key) % _N;
			size_t index2 = Hash2()(key) % _N;
			size_t index3 = Hash3()(key) % _N;


			//返回true"不代表一定在"! 但是返回false代表"一定不在"!!!
			//布隆过滤器的目的就是: 推荐给用户"一定不在"的信息! 所以它这样的设计是可以的!
			if (_bs.test(index1) == false)
				return false;
			if (_bs.test(index2) == false)
				return false;
			if (_bs.test(index3) == false)
				return false;
			return true;
		}

	private:
		wqj_bitset::bitset _bs;
		size_t _N;
	};

	void test_bloomf()
	{
		bloomfilter<std::string> bf(100);
		bf.set("123124141");
		bf.set("1231212");
		bf.set("413413");
		
		cout << bf.test("123124141") << endl;
		cout << bf.test("1231212") << endl;
		cout << bf.test("413413") << endl;
		cout << bf.test("1234") << endl;
	}
}
