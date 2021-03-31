#include <iostream>
using namespace std;

//void Func1(int a = 10, int b = 20, int c = 30)//✔
//{
//	cout << a << " " << b << " " << c << endl;
//}
//
//void Func2(int a = 1 , int b , int c = 3 )// ✖ 这里给缺省参数的时候，必须是从左到右连续给出
//{
//	cout << a << " " << b << " " << c << endl;
//}
//
//void Func3(int a = 1, int b, int c )//✖ 而且前面一旦给出了缺省参数，后面必须全部都给
//{
//	cout << a << " " << b << " " << c << endl;
//}
//
//int main()
//{
//	Func1();
//	Func1(1);
//	Func1(1, 2);			//只允许后面缺省
//	Func1(1, 2, 3);				
//	//Func1(, 2, 3); //✖	--- 调用的时候，前面不能是空的
//	//Func1(, , 3);  //✖
//
//	return 0;
//}



//int main()
//{
//	int i = 0;
////	double a = i;
//
//	double& b = i;			//✖
//	const double& b = i;	//✔
//
//	return 0;
//}


//int main()
//{
//	int a = 0, b = 1, c = 2;
//	cout << a << endl << b << endl << c << endl;
//	return 0;
//}


void Func(int a, char b, double c)
{}

void Func(int a, char b)
{}

void Func(char a, char b, char c)
{}

void Func(int a, double c, char b)
{}

int main()
{
	Func(1, 'a', 1.1);
	Func(1, 'a');
	Func('a', 'b', 'c');
	Func(1, 1.1, 'a');
}