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


//Test�̳����Ĭ�ϳ�Ա����
//class Person
//{
//public:
//	//���캯��
//	Person(const string& name, int age)
//		:_name(name),
//		_age(age)
//	{}
//	//�������캯��
//	Person(const Person& p)
//		:_name(p._name),
//		_age(p._age)
//	{}
//	//��ֵ������
//	Person& operator=(const Person& p)
//	{
//		if (this != &p)
//		{
//			_name = p._name;
//			_age = p._age;
//		}
//		return *this;
//	}
//	//��������
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
////����
//class Student : public Person
//{
//public:
//	Student(const string& name, int age, int stuid)
//		:Person(name, age),			//�������еĶ����Ա�������и�ֵ
//		_stuid(stuid)
//	{}
//
//	Student(const Student& s)
//		:Person(s),					//���ﴫ����Student���͵ģ�Person�еĿ�������Ĳ�����const Person& p
//		_stuid(s._stuid)				//�൱�� ��Ƭ�������ำֵ�� ���������
//	{}
//
//	Student& operator=(const Student& s)
//	{
//		if (this != &s)
//		{
//			Person::operator=(s);		//���ø����operator=��д��
//			_stuid = s._stuid;			//�����operator=��Ҫ���Ϸ����޶���Person::����Ϊ��Student������Ҳ��operator=��
//		}
//		return *this;
//	}
//
//	~Student()	//������������Ҫ�Լ�ȥ���ø�������������������������󣬻��Զ����ø��������������
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



//���μ̳�
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
//	//sch._name = "Mark";	//�����ԣ�
//						//��Ϊͬʱ��Student�к�Teacher�м̳���_name��Ա�����Բ�֪��Ҫ���ĸ�_name��ֵ
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