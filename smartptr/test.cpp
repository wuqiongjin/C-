#include "SmartPtr.h"
#include <thread>
//using namespace wqj;

//int Div(int a, int b)
//{
//	if (b == 0)
//	{
//		throw invalid_argument("除0错误");
//	}
//	return a / b;
//}
//
//int main()
//{
//	try
//	{
//		int* ptr = new int[10];
//		int a, b;
//		cin >> a >> b;
//		cout << Div(a, b) << endl;
//		delete ptr;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "Unknown exception!" << endl;
//	}
//	return 0;
//}



//int *p = new int;
//wqj::shared_ptr<int> sp1(new int);
//wqj::shared_ptr<int> sp2(sp1);

//int main()
//{
//	smart_ptr<int> sp1(new int);
//	smart_ptr<std::pair<int, int>> sp2(new std::pair<int, int>);
//
//	*sp1 = 1;
//
//	sp2->first = 5;
//	sp2->second = 10;
//
//	std::cout << "sp1: " << *sp1 << std::endl;
//	std::cout << "sp2: " << sp2->first << ":" << sp2->second << std::endl;
//	return 0;
//}

//int main()
//{
//	smart_ptr<int> sp1(new int);
//	smart_ptr<int> sp2(sp1);
//	return 0;
//}

//using namespace std;
////库auto_ptr使用
//int main()
//{
//	auto_ptr<int> ap1(new int(1));
//	auto_ptr<int> ap2(ap1);
//	return 0;
//}

//int main()
//{
//	//wqj::auto_ptr<int> ap1(new int(1));
//	//wqj::auto_ptr<int> ap2(ap1);
//	
//
//	//wqj::unique_ptr<int> up1(new int);
//	//wqj::unique_ptr<int> up2(up1);
//	//wqj::unique_ptr<int> up3 = up1;
//	
//	wqj::shared_ptr<int> sp1(new int(1));
//	wqj::shared_ptr<int> sp2(sp1);
//	wqj::shared_ptr<int> sp3(sp1);
//
//	wqj::shared_ptr<int> spp1(new int(5));
//	wqj::shared_ptr<int> spp2(spp1);
//
//	wqj::shared_ptr<int> spp3(new int(3));
//	wqj::shared_ptr<int> spp4(spp3);
//	wqj::shared_ptr<int> spp5(spp3);
//	spp3 = spp1;
//	
//	//std::cout << sp1.use_count() << std::endl;
//	//std::cout << spp1.use_count() << std::endl;
//	std::cout << spp1.use_count() << std::endl;
//	std::cout << spp4.use_count() << std::endl;
//
//	return 0;
//}


//int main()
//{
//	shared_ptr<int> sp1(new int(5));
//	shared_ptr<int> sp2(sp1);
//	shared_ptr<int> sp3(sp1);
//	
//
//	shared_ptr<int> sh1(new int(23));
//	shared_ptr<int> sh2 = sh1;
//	shared_ptr<int> sh3 = sh1;
//
//	std::cout << sp1.use_count() << std::endl;
//	std::cout << sh1.use_count() << std::endl;
//
//	sh3 = sp1;
//	sh2 = sp1;
//
//	std::cout << sp1.use_count() << std::endl;
//	std::cout << sh1.use_count() << std::endl;
//
//	sh1 = sp1;
//	std::cout << sp1.use_count() << std::endl;
//	std::cout << sh1.use_count() << std::endl;
//	return 0;
//}

//#include <thread>

//int main()
//{
//	int n = 10000;
//	int cnt = 0;
//	wqj::shared_ptr<int> sp(new int);
//
//	std::cout << sp.use_count() << std::endl;
//
//	std::thread t1([&]() {
//		for (int i = 0; i < n; ++i)
//		{
//			wqj::shared_ptr<int> copy(sp);
//		}
//	});
//
//	std::thread t2([&]() {
//		for (int i = 0; i < n; ++i)
//		{
//			wqj::shared_ptr<int> copy(sp);
//		}
//	});
//
//
//	t1.join();
//	t2.join();
//
//	std::cout << sp.use_count() << std::endl;
//
//	//int a = 1;
//	//std::thread t([&]() 
//	//{
//	//	std::cout << "lambda" << std::endl;
//	//	a = 2;
//	//});
//
//	//std::cout << a << std::endl;
//	//t.join();
//
//	//int a = 1;
//	//auto Routine = [&]()
//	//{
//	//	a = 2;
//	//	std::cout << "lambda" << std::endl;
//	//};
//
//	//std::thread t(Routine);
//	//
//	//std::cout << a << std::endl;
//	//t.join();
//	//return 0;
//	return 0;
//}

//#include <Windows.h>
//int main()
//{
//	int a = 1;
//
//	auto Routine = [&]()
//	{
//		a = 2;
//		std::cout << "lambda" << std::endl;
//	};
//
//	std::thread t(Routine);
//	
//	std::cout << a << std::endl;
//	t.join();
//	return 0;
//}

/*************************************************/
//出现了循环引用的问题!!!
//struct ListNode
//{
//	//ListNode()
//	//	:_prev(nullptr),
//	//	 _next(nullptr)
//	//{}
//
//	~ListNode()
//	{
//		std::cout << "~ListNode()" << std::endl;
//	}
//
//	//在使用智能指针的时候，为了让智能指针能够使用_prev/_next指向某一个智能指针的对象，
//	//这里需要把它们定义为2个智能指针类型的对象
//	shared_ptr<ListNode> _prev;
//	shared_ptr<ListNode> _next;
//	int _data;
//};
//
//shared_ptr与循环引用
//int main()
//{
//	shared_ptr<ListNode> sp1(new ListNode);
//	shared_ptr<ListNode> sp2(new ListNode);
//
//	sp1->_next = sp2;	//sp2的引用计数++
//	sp2->_prev = sp1;	//sp1的引用计数++
//	
//	std::cout << "~~~开始调用析构函数~~~" << std::endl;
//	return 0;
//}


//struct ListNode
//{
//	//自定义类型的对象，必须在"初始化列表"阶段对其进行初始化!!!
//	//ListNode()
//	//{
//	//	std::cout << "ListNode()" << std::endl;
//	//}
//
//	~ListNode()
//	{
//		std::cout << "~ListNode()" << std::endl;
//	}
//
//	//在使用智能指针的时候，为了让智能指针能够使用_prev/_next指向某一个智能指针的对象，
//	//这里需要把它们定义为2个智能指针类型的对象
//	//shared_ptr<ListNode> _prev;
//	//shared_ptr<ListNode> _next;
//
//	weak_ptr<ListNode> _prev;
//	weak_ptr<ListNode> _next;
//	int _data = 0;
//};
//
//
////weak_ptr解决循环引用
//int main()
//{
//	shared_ptr<ListNode> sp1(new ListNode);
//	shared_ptr<ListNode> sp2(new ListNode);
//	
//	sp1->_next = sp2;
//	sp2->_prev = sp1;
//	std::cout << "~~~开始调用析构函数~~~" << std::endl;
//	return 0;
//}

class A
{
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}

	~A()
	{
		std::cout << "~A()" << std::endl;
	}
public:
	int _a;
};



//int main()
//{
//	shared_ptr<A> sp1(new A[10]);
//	shared_ptr<A> sp2((A*)malloc(sizeof(A)));
//	shared_ptr<FILE> sp3(fopen("test.txt", "w"));
//
//
//	//A* p = new A[10];
//	//delete p;
//	return 0;
//}



//C++11 智能指针 --- 定制删除器
//using namespace std;
//
//template <class T>
//struct DeleteAFunc
//{
//	void operator()(T* ptr)
//	{
//		cout << "delete[] ptr" << endl;
//		delete[] ptr;
//	}
//};
//
//template <class T>
//struct FreeAFunc
//{
//	void operator()(T* ptr)
//	{
//		cout << "free ptr" << endl;
//		free(ptr);
//	}
//};
//
//struct FcloseFunc
//{
//	void operator()(FILE* fp)
//	{
//		cout << "fclose fp" << endl;
//		fclose(fp);
//	}
//};
//
//int main()
//{
//	shared_ptr<A> sp1(new A[10], DeleteAFunc<A>());
//	shared_ptr<A> sp2((A*)malloc(sizeof(A)), FreeAFunc<A>());
//	shared_ptr<FILE> sp3(fopen("test.txt", "w"), FcloseFunc());
//	return 0;
//}

/**********lock与RAII********/
using namespace std;
using namespace wqj;

mutex mtx;

int main()
{
	int cnt = 0;
	thread t1([&] {
		Lock_Guard<mutex> lg(mtx);
		for (int i = 0; i < 100000; ++i)
		{
			++cnt;
		}
	});

	thread t2([&] {
		Lock_Guard<mutex> lg(mtx);
		for (int i = 0; i < 100000; ++i)
		{
			++cnt;
		}
	});

	t1.join();
	t2.join();
	
	std::cout << cnt << '\n';
	return 0;
}