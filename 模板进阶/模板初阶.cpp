#include <iostream>
#include <string>
using namespace std;

void Swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
	cout << "��ģ�庯��" << endl;
}

template <class T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
	cout << "����ģ��" << endl;
}

int main()
{
	int a = 1;
	int b = 2;

	Swap(a, b);		//���õ��Ƿ�ģ�庯��
	Swap<int>(a, b);//���õ���ģ�庯��
	return 0;
}
//char _Tolower(char& ch)
//{
//	if (isupper(ch))
//		ch += 32;
//	return ch;
//}
//
//void Tolower()
//{
//	string s("A1CD");
//	//s[1] = tolower(s[1]);
//	s[1] = tolower(s[1]);
//	
//	cout << s << endl;
//
//}



//int main()
//{
//	int a = 1;
//	int b = 2;
//	double c = 1.1;
//	double d = 1.2;
//	//��ʽʵ����
//	Swap(a, b);
//	Swap(c, d);
//	//��ʽʵ����
//	Swap<int>(a, b);
//	Swap<double>(c, d);
//
//	return 0;
//}