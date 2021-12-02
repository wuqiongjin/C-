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

		//����xλ���1
		void set(size_t x)
		{
			//index��ʾ�ڵڼ������δ�
			//pos��ʾ�������еĵڼ���λ
			size_t index = x / 32;
			size_t pos = x % 32;

			//"����"������"��λ"�ƶ�! (����һ�������������ƶ�, ��˻������ƾ��������ƶ�...)
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
		
		//�ж�x�ڲ���
		bool test(size_t x)
		{
			size_t index = x / 32;
			size_t pos = x % 32;

			return _bits[index] & (1 << pos);
		}

	private:
		std::vector<int> _bits;
		size_t _nums;	//ͳ��λͼ�д��˶��ٸ���
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

		//�뿪42�ڸ���
		//bitset bs(-1);	//size_t�����ֵ
		//bitset bs(pow(2, 32));
		//bitset bs(0xFFFFFFFF);
	}
}