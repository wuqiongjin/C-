//#include <iostream>
//using namespace std;
//
////class Date
////{
////public:
////	//���캯�����Ƽ�д��ȫȱʡ�Ĺ��캯����
////	Date(int year = 0, int month = 1, int day = 1)
////	{
////		_year = year;
////		_month = month;
////		_day = day;
////	}
////
////	void Print();
////
////private:
////	int _year;
////	int _month;
////	int _day;
////};
////
//////�����Ͷ��岻��һ��ʱ����Ҫ�� �������޶���::
////void Date::Print()
////{
////	cout << _year << "-";
////	cout << _month << "-";
////	cout << _day << endl;
////}
////
////int main()
////{
////	Date d1;
////	d1.Print();
////
////	Date d2(2021, 4, 3);
////	d2.Print();
////
////	return 0;
////}
//
//
//class Date
//{
//public:
//	//���캯�����Ƽ�д��ȫȱʡ�Ĺ��캯����
//	Date(int year = 0, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	//�������캯��
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//
//	//���������
//	bool operator>(const Date& d2)//operator>(Date* this, const Date& d2)
//	{
//		if (_year > d2._year)
//		{
//			return true;
//		}
//		else if(_year < d2._year)
//		{
//			return false;
//		}
//		else
//		{
//			if (_month > d2._month)
//			{
//				return true;
//			}
//			else if (_month < d2._month)
//			{
//				return false;
//			}
//			else
//			{
//				if (_day > d2._day)
//				{
//					return true;
//				}
//				else
//					return false;
//			}
//		}
//	}
//
//	void Print()
//	{
//		cout << _year << " " << _month << " " << _day << endl;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//
//int main()
//{
//	Date d1(2021, 4, 5);
//	Date d2(d1);
//	Date d3(2021, 4, 7);
//	if (d1 > d3)	//�ȼ���  d1.operator>d3
//		cout << "True" << endl;
//	else
//		cout << "False" << endl;
//
//	return 0;
//}