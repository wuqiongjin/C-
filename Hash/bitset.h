#pragma once
#include <vector>

namespace wqj_bitset
{
	class bitset
	{
	public:
		bitset(size_t N)
		{
			_bits.resize(N / 32 + 1, 0);
			_nums = 0;
		}

		//将第x位变成1
		void set(size_t x)
		{
			//index表示在第几个整形处
			//pos表示在整形中的第几个位
			size_t index = x / 32;
			size_t pos = x % 32;

			//"左移"代表向"高位"移动! (并不一定代表是向左移动, 大端机中左移就是向右移动...)
			_bits[index] |= (1 << pos);
			++_nums;
		}

		void reset(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;

			_bits[index] &= (~(1 << pos));
			--_nums;
		}
		
		//判断x在不在
		bool test(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;

			return _bits[index] & (1 << pos);
		}

	private:
		std::vector<int> _bits;
		size_t _nums;	//统计位图中存了多少个数
	};

	void test_bitset()
	{
		//bitset bs(100);
		//bs.set(3);
		//bs.set(99);
		//bs.set(98);
		//bs.set(97);

		//cout << bs.test(98) << endl;

		//bs.reset(98);
		//cout << bs.test(98) << endl;

		//想开42亿个数
		//bitset bs(-1);	//size_t的最大值
		//bitset bs(pow(2, 32));
		//bitset bs(0xFFFFFFFF);
	}
}