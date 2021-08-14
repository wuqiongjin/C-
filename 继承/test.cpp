#include <iostream>
#include <string>
using namespace std;

//class Person
//{
//public:
//  void Print()
//  {
//    cout << "name:" << _name << endl;
//    cout << "age:" << _age << endl;
//  }
//protected:  
// string _name;
// int _age;
//};
//
//class Student : public Person
//{
//protected:
//    int _stuid;
//};
//
//int main()
//{
//  Person p;
//  Student s;
//
//  return 0;
//}


//Test继承类的默认成员函数
//class Person
//{
//public:
//	//构造函数
//	Person(const string& name, int age)
//		:_name(name),
//		_age(age)
//	{}
//	//拷贝构造函数
//	Person(const Person& p)
//		:_name(p._name),
//		_age(p._age)
//	{}
//	//赋值重载运
//	Person& operator=(const Person& p)
//	{
//		if (this != &p)
//		{
//			_name = p._name;
//			_age = p._age;
//		}
//		return *this;
//	}
//	//析构函数
//	~Person()
//	{
//		_name = "";
//		_age = 0;
//	}
//
//protected:
//	string _name;
//	int    _age;
//};
//
////子类
//class Student : public Person
//{
//public:
//	Student(const string& name, int age, int stuid)
//		:Person(name, age),			//给基类中的多个成员变量进行赋值
//		_stuid(stuid)
//	{}
//
//	Student(const Student& s)
//		:Person(s),					//这里传的是Student类型的，Person中的拷贝构造的参数是const Person& p
//		_stuid(s._stuid)				//相当于 切片。将子类赋值给 父类的引用
//	{}
//
//	Student& operator=(const Student& s)
//	{
//		if (this != &s)
//		{
//			Person::operator=(s);		//调用父类的operator=的写法
//			_stuid = s._stuid;			//这里的operator=需要加上访问限定符Person::，因为在Student类里面也有operator=。
//		}
//		return *this;
//	}
//
//	~Student()	//析构函数不需要自己去调用父类的析构函数，当子类析构后，会自动调用父类的析构函数。
//	{
//		_stuid = 0;
//	}
//protected:
//	int _stuid;
//};
//
//int main()
//{
//	Person p("Tom", 20);
//	Student s("Jack", 20, 1055);
//
//	Student s2 = s;
//	Student s3("Mark", 45, 3766);
//
//	s2 = s3;
//
//	return 0;
//}



//菱形继承
//class Person
//{
//public:
//	string _name;
//};
//
//class Student : virtual public Person
//{
//protected:
//	int _stuid;
//};
//
//class Teacher : virtual public Person
//{
//protected:
//	int _id;
//};
//
//class Scholar : public Student, public Teacher
//{
//protected:
//	string _majorcourse;
//};
//
//int main()
//{
//	Scholar sch;
//
//	//sch._name = "Mark";	//二义性，
//						//因为同时从Student中和Teacher中继承了_name成员。所以不知道要给哪个_name赋值
//
//	return 0;
//}


class A
{
public:
	int _a;
};

class B : virtual public A
{
public:
	int _b;
};

class C : virtual public A
{
public:
	int _c;
};

class D : public B, public C
{
public:
	int _d;
};

int main()
{
	D d;

	d.B::_a = 111;
	d.C::_a = 11;
	d._a = 1;

	d._b = 2;
	d._c = 3;
	d._d = 4;

	return 0;
}