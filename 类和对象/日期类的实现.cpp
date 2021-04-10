#include <iostream>
using namespace std;

class Date
{
public:
	//获取某个月的天数
	int GetMonthDay(int year, int month)const
	{
		//由于这个数组不会进行任何修改，还将多次调用，我们可以将它放入静态区
		static int Monthdays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			return 29;
		return Monthdays[month];
	}

	//构造函数(初始化)
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
			cout << "非法输入！" << endl;
		}
	}

	//拷贝构造函数【将别名为d的对象的值分别 拷贝给 this指针所指向的对象】
	Date(const Date& d)//这里必须是传引用，否则会陷入无限递归当中
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//运算符重载
	//>
	//inline bool operator>(Date d2)
	inline bool operator>(const Date& d2)const//使用引用效率高一些 --->参数 Date* this, const Date& d2
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
		//函数的复用
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
		//这里因为不是赋值运算符，因此不能修改原数据，所以需要拷贝构造另一个ret作为临时变量
		Date ret = *this;//Date ret(*this); 都可以
		
		ret._day += day;
		while (ret._day > GetMonthDay(ret._year, ret._month))
		{
			//这里必须先将day -=
			//再将month++，否则GetMonthDay获取的天数就是下一个月的了。。错开了
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

	//++前置
	Date& operator++()
	{
		*this += 1;
		return *this;
	}

	//后置++
	Date operator++(int)
	{
		Date tmp(*this);
		*this += 1;
		return tmp;//这里返回的是局部变量，因此不能用引用返回
	}

	//前置--
	Date& operator--()
	{
		*this -= 1;
		return *this;
	}

	//后置--
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
		//让小的日期不断++，看需要加多少次才等于大的
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

	////前置++
	//++d2;
	//d2.Print();
	//++d2;
	//d2.Print();

	//--d2;
	//d2.Print();

	////后置++
	//(d2++).Print();
	//d2.Print();
	////前置++
	//(++d2).Print();
	//d2.Print();

	d2 += 20;
	cout << d1 - d2 << endl;

	return 0;
}