#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
//#include "My_string.h"
#include "my_string现代版写法.h"
//using namespace std;//这里std需要在My_string.h前面，不然在.h中还需要再包含using namespace std;


void testString1()
{
	string s1("Hello");
	s1 += " ";
	s1 += "world";

	size_t i = 0;
	while (i < s1.size())
	{
		s1[i] += 1;
		++i;
	}

	i = 0;
	while (i < s1.size())
	{
		cout << s1[i] << " ";
		++i;
	}
	cout << endl;



	string::iterator it = s1.begin();
	while (it != s1.end())
	{
		*it -= 1;
		++it;
	}

	it = s1.begin();
	while (it != s1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : s1)
	{
		cout << e << "";
	}
}


void testString2()
{
	string s("Hello");
	s.reserve(100);
	cout << s.capacity() << endl;
	s.reserve(10);
	cout << s.capacity() << endl;
}

void testString3()
{
	string s;
	s.push_back('x');
	s += "123";
	s.append("45");
	s.append(3, 'L');
	cout << s << endl;

	//for (auto ch : s)
	//{
	//	cout << ch << " ";
	//}
}

void testString4()
{
	string s;
	s += "12345";
	s.insert(0, "0");
	s.erase(0, 1);
	s.erase(0, 0);
	s.erase(3, string::npos);
	s.insert(2,"5555");

	cout << s << endl;
}

void testString5()
{
	string s("Test find, rfind and substr function!!");
	size_t pos = s.find("find");
	cout << "find pos is " << pos << endl;				// 5

	pos = s.find("find", pos + 1);
	cout << "second find pos is " << pos << endl;		// 12

	//从第0个位置开始进行find，然后匹配3个字符，如果匹配成功，返回当前匹配位置，失败返回npos
	pos = s.find("sub", 0, 3);
	cout << pos << endl;

	//下标是从0开始的！
	pos = s.find('T');
	cout << pos << endl;	// 0

	//rfind
	pos = s.rfind("find");
	cout << "last occurrence pos is " << pos << endl;	// 12


	//substr
	//从pos位置开始向后匹配6个字符，并将这6个字符作为子串进行输出
	pos = s.find("substr");
	cout << s.substr(pos, 6) << endl;



}

void split_url(const string& url)
{
	//https://space.bilibili.com/97719822
	//协议 + 域名 + 资源名称
	// https + space.bilibili.com + 97719822
	
	//协议
	size_t l1 = url.find(':');
	if (l1 != string::npos)
	{
		cout << url.substr(0, l1);
		cout << endl;
	}


	//域名
	size_t l2 = url.find('/', l1 + 3);
	if (l2 != string::npos)
	{
		cout << url.substr(l1 + 3, l2 - l1 - 3);//s p a c e /   
		cout << endl;							//1 2 3 4 5 6  // 6 - 1 = 5 (space = 5)    
	}

	//资源名称
	cout << url.substr(l2 + 1, string::npos);
	cout << endl;
}

void testString6()
{
	string l1("https://space.bilibili.com/97719822");
	string url = l1;

	split_url(url);
}

char testString7()
{
	string s1 = "12345";
	string s2 = "10000";
	return s1[0];
}

string& _s(string& s)
{
	return s;
}

void testString8()
{
	string s("12345");

//	_s(s[1]);  //s[1]的返回值是char / const char
}

void testString9()
{
	string s("hello world");
	//h e l l o
	//0 1 2 3 4 5
	reverse(s.begin(), s.begin() + 5);
	//		h			' '
	cout << s << endl;
}

void testString10()
{
	char* A = new char[1];
	char* B = new char;
	//等价的
	A[0] = 'a';
	B[0] = 'b';

	cout << *A << endl;
	cout << *B << endl;

	//delete[] A;
	delete A;
	//delete B;
	delete[] B;
}

int main()
{
	//testString1();
	//testString2();
	//testString3();
	//testString4();
	//testString5();
	//testString6();
	//testString7();
	//testString8();
	//testString9();
	//testString10();

	wqj::test_string1();
	//wqj::test_string2();

	return 0;
}
