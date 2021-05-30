#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "vector.h"

void test_vector1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);

	vector<int> v2 = v1;

	//1. ��ͨ����  (�����޸�����) operator[] + size()
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	
	//2. ����������
	vector<int>::iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	//3. ��Χfor
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}

void print_vector(const vector<int>& vt)
{
	vector<int>::const_iterator it2 = vt.begin();
	while (it2 != vt.end())
	{
		cout << *it2 << " ";
		++it2;
	}
	cout << endl;
}

void test_vector2()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	vector<int>::iterator it1 = v.begin();
	print_vector(v);

	vector<int>::reverse_iterator it3 = v.rbegin();
	vector<int>::const_reverse_iterator it4 = v.rbegin();
}

void test_vector3()
{
	vector<int> v;
	v.reserve(100);
	v.resize(980);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = i;
		cout << v[i] << " ";
	}
	cout << endl;
}

void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//assert���Ա���
	//v[5] = 10;

	//at�������쳣
	v.at(5) = 10;
}

void test_vector5()
{
	vector<int> v(5);

	v.insert(v.begin(), 1);
	v.insert(v.begin() + 1, 2);
	v.insert(v.begin() + 2, 3);

	v.erase(v.begin());
	v.erase(v.end() - 1);
	v.erase(v.end() - 1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_vector6()
{
	vector<int> v;
	v.push_back(11);
	v.push_back(22);
	v.push_back(33);
	v.push_back(44);
	v.push_back(55);

	vector<int>::iterator pos = find(v.begin(), v.end(), 33);//���ķ�Χ�� [first, last)
	//Ҫ�������������β���������бȽϣ����Ƿ��ҵ��ˡ����û�ҵ��Ļ�pos����v.end()
	if (pos != v.end())
	{
		v.erase(pos);
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
}

void test_vector7()
{
	int a[] = { 1,2,3,4,5 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));	//���˵�����������ȥ�����ʼ��

	for (auto e : v)
	{
		cout << e << " ";
	}
}

void test_vector8()
{
	//1. ������ʧЧ�� ����1���������ݵ��µ�����ʧЧ
	vector<int> v{ 1,2,3,4,5 };
	//vector<int>::iterator it = v.begin();

	//v.push_back(6);//������������ݲ���������it������ʧЧ��

	//it = v.begin();	//������������µ�������λ��

	//while (it != v.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//}

	//2. ������ʧЧ���⣬ ����2:eraseɾ��ʹ��
	vector<int>::iterator ite = v.begin();

	while (ite != v.end())
	{
		if (*ite % 2 == 0)
		{
			ite = v.erase(ite);//��eraseɾ����������������Ԫ�ض�����ǰ�ƶ�������������ָ��λ��û�б�
		}				//�����ͻᵼ�µ�����ʧЧ��VS�»�ֱ�ӱ�����g++�в��ᣬ���ǽ��Ҳ�����Ǵ����
		else
		{
			++ite;
		}
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
}

int main()
{
	//test_vector1();
	//test_vector2();
	//test_vector3();
	//test_vector4();
	//test_vector5();
	//test_vector6();
	//test_vector7();
	//test_vector8();


	//wqj::test_vector1();
	//wqj::test_vector2();
	wqj::test_vector3();
	
	return 0;
}