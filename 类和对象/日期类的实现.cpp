#include <iostream>
using namespace std;

class Date
{
public:
	//��ȡĳ���µ�����
	int GetMonthDay(int year, int month)const
	{
		//����������鲻������κ��޸ģ�������ε��ã����ǿ��Խ������뾲̬��
		static int Monthdays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			return 29;
		return Monthdays[month];
	}

	//���캯��(��ʼ��)
	Date(int year = 0, int month = 1, int day = 1)
	{
		if (month > 0 && month <= 12
			&& day > 0 && day <= GetMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "�Ƿ����룡" << endl;
		}
	}

	//�������캯����������Ϊd�Ķ����ֵ�ֱ� ������ thisָ����ָ��Ķ���
	Date(const Date& d)//��������Ǵ����ã�������������޵ݹ鵱��
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//���������
	//>
	//inline bool operator>(Date d2)
	inline bool operator>(const Date& d2)const//ʹ������Ч�ʸ�һЩ --->���� Date* this, const Date& d2
	{
		if (_year > d2._year)
			return true;
		if (_year == d2._year && _month > d2._month)
			return true;
		if (_year == d2._year && _month == d2._month && _day > d2._day)
			return true;
		return false;
	}

	//==
	inline bool operator==(const Date& d2)const
	{
		return _year == d2._year &&
			_month == d2._month  &&
			_day == d2._day;
	}

	//<
	bool operator<(const Date& d2)const
	{
		//�����ĸ���
		return !(*this == d2 || *this > d2);
	}

	//>=
	bool operator>=(const Date& d2)const
	{
		return !(*this < d2);
	}

	//<=
	bool operator<=(const Date& d2)const
	{
		return !(*this > d2);
	}

	//!=
	bool operator!=(const Date& d2)const
	{
		return !(*this == d2);
	}


	//+
	Date operator+(int day)const
	{
		//������Ϊ���Ǹ�ֵ���������˲����޸�ԭ���ݣ�������Ҫ����������һ��ret��Ϊ��ʱ����
		Date ret = *this;//Date ret(*this); ������
		
		ret._day += day;
		while (ret._day > GetMonthDay(ret._year, ret._month))
		{
			//��������Ƚ�day -=
			//�ٽ�month++������GetMonthDay��ȡ������������һ���µ��ˡ�������
			ret._day -= GetMonthDay(ret._year, ret._month);
			ret._month++;

			if (ret._month > 12)
			{
				ret._month = 1;
				ret._year++;
			}
		}
		return ret;
	}

	//+=
	Date& operator+=(int day)
	{
		*this = *this + day;

		return *this;
	}

	//-
	Date operator-(int day)const
	{
		Date ret(*this);
		ret._day -= day;
		while (ret._day <= 0)
		{
			ret._month--;
			if (ret._month == 0)
			{
				ret._month = 12;
				ret._year--;
			}
			ret._day += GetMonthDay(ret._year, ret._month);


		}
		return ret;
	}

	//-=
	Date& operator-=(int day)
	{
		*this = *this - day;
		return *this;
	}

	//++ǰ��
	Date& operator++()
	{
		*this += 1;
		return *this;
	}

	//����++
	Date operator++(int)
	{
		Date tmp(*this);
		*this += 1;
		return tmp;//���ﷵ�ص��Ǿֲ���������˲��������÷���
	}

	//ǰ��--
	Date& operator--()
	{
		*this -= 1;
		return *this;
	}

	//����--
	Date operator--(int)
	{
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}

	//d1 - d2
	int operator-(const Date& d2)const
	{
		int count = 0;
		Date more = *this;
		Date less = d2;

		int flag = 1;
		if (more < less)
		{
			more = d2;
			less = *this;
			flag = -1;
		}
		//��С�����ڲ���++������Ҫ�Ӷ��ٴβŵ��ڴ��
		while (less != more)
		{
			++count;
			++less;
		}
		return flag * count;
	}

	void Print()const
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2021, 4, 5);

	Date d2(d1);//Date d2 = d1;

	d1.Print();
	d2.Print();


	//cout << (d1 > d2) << endl;
	//cout << (d1 < d2) << endl;
	//cout << (d1 == d2) << endl;
	//cout << (d1 >= d2) << endl;
	//cout << (d1 <= d2) << endl;
	//cout << (d1 != d2) << endl;



	//d2 + 10;
	//d2 - 10;

	//d2 += 10000;
	//d2 -= 10000;
	//
	//d2.Print();

	//d2 += 24;

	////ǰ��++
	//++d2;
	//d2.Print();
	//++d2;
	//d2.Print();

	//--d2;
	//d2.Print();

	////����++
	//(d2++).Print();
	//d2.Print();
	////ǰ��++
	//(++d2).Print();
	//d2.Print();

	d2 += 20;
	cout << d1 - d2 << endl;

	return 0;
}