#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <algorithm>
using namespace std;

//void func1(int a, int b)
//{
//	cout << "func1(): " << a << " " << b << endl;
//}
//
//
//int main()
//{
//	int a = 1, b = 2;
//	thread t1;	//创建空的线程对象，由于没有关联任何线程函数，所以不会启动该线程
//	thread t2(func1, a, b);	//线程t2执行func1(), a和b作为参数传了过去
//	//使用lambda表达式作为线程的启动函数
//	thread t3([&] {
//		cout << "t3: " << a << " " << b << endl;
//	});
//
//	//t1.join();	//t1线程没有启动，因此无法join
//	t2.join();
//	t3.join();
//	return 0;
//}


//int main()
//{
//	thread t1([] {
//		cout << "This is t1 thread\n";
//		this_thread::sleep_for(std::chrono::seconds(3));
//	});
//
//	thread t2([] {
//		cout << "This is t2 thread\n";
//		this_thread::sleep_for(std::chrono::seconds(5));
//	});
//
//	t2.detach();
//
//	if (t1.joinable())
//	{
//		cout << "t1 is joinable!" << endl;
//		t1.join();
//	}
//	else
//	{
//		cout << "t1 is not joinable!" << endl;
//	}
//
//	if (t2.joinable())
//	{
//		cout << "t2 is joinable" << endl;
//		t2.join();
//	}
//	else
//	{
//		cout << "t2 is not joinable!" << endl;
//	}
//	return 0;
//}


//void Start_t1()
//{
//	cout << "std::this_thread::get_id()" << std::this_thread::get_id() << '\n';
//}
//
//int main()
//{
//	thread t1(Start_t1);
//	cout << "对象.get_id(): " << t1.get_id() << endl;
//	t1.join();
//	return 0;
//}


//测试 sleep_for 的耗时
//void Start_Routine()
//{
//	using namespace std::chrono;
//	int cnt = 10;
//	while (cnt--)
//	{
//		high_resolution_clock::time_point t1 = high_resolution_clock::now();
//		this_thread::sleep_for(milliseconds(500));
//		high_resolution_clock::time_point t2 = high_resolution_clock::now();
//
//		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
//		cout << "The time for sleep_for is: " << time_span.count() << endl;
//	}
//}
//
//int main()
//{
//	thread t(Start_Routine);
//	t.join();
//	return 0;
//}



//ref <functional>
//void func(int& a)
//{
//	++a;
//}
//
//int main()
//{
//	int a = 0;
//	//thread t([&] {
//	//	++a;
//	//});
//
//	//t.join();
//	//cout << a << endl;
//
//	thread t1(func, ref(a));
//	t1.join();
//	cout << a << endl;
//	return 0;
//}

/****************	mutex	*********************/
//mutex mtx;
//int tickets = 1000;
//
//void Get_Tickets()
//{
//	while (1)
//	{
//		this_thread::sleep_for(chrono::milliseconds(1));
//		mtx.lock();
//		if (tickets > 0)
//		{
//			--tickets;
//			cout << this_thread::get_id() << ": get a ticket, Tickets: " << tickets << endl;
//			mtx.unlock();
//		}
//		else
//		{
//			cout << "NO ticket!!!" << endl;
//			mtx.unlock();
//			break;
//		}
//	}
//	cout << this_thread::get_id() << ": Exit!!!!" << endl;
//}

//int main()
//{
//	//vector<thread> vt(5, thread(Get_Tickets)); //不能这么写!!! 这里是先构造了thread对象，然后再把对象拷贝构造到vt数组中(thread不支持拷贝)
//
//	vector<thread> vt;
//	for (int i = 0; i < 5; ++i)
//		vt.push_back(thread(Get_Tickets));
//
//	//for (thread& i : vt)	//必须加&，因为线程不可以被拷贝
//	//	i.join();
//
//	//for (size_t i = 0; i < vt.size(); ++i)
//	//	vt[i].join();
//
//	for_each(vt.begin(), vt.end(), mem_fn(&std::thread::join));
//	return 0;
//}

/*************	lock_guard & unique_lock	*******/
//mutex mtx;
//
//void Print(int i)
//{
//	lock_guard<mutex> lg(mtx);
//	cout << "thread# " << i << endl;
//}
//
//int main()
//{
//	vector<thread> vt;
//	for (int i = 0; i < 20; ++i)
//		vt.push_back(thread(Print, i));
//
//	for (auto& i : vt)
//		i.join();
//
//	return 0;
//}

int count = 0;

void Start_ul()
{
	

}

//int main()
//{
//	mutex mtx;
//	lock_guard<mutex> lg1(mtx);	//✔
//	//lock_guard<mutex> lg2(lg1);	//error
//	//lock_guard<mutex> lg3(move(lg2));	//error
//
//	unique_lock<mutex> ulock1(mtx);	//✔
//	//unique_lock<mutex> ulock2 = ulock1;	//error
//	unique_lock<mutex> ulock3 = move(ulock1);	//✔
//
//
//	return 0;
//}


//
//mutex mtx;
//
//void Print(int i)
//{
//	unique_lock<mutex> ulock(mtx, defer_lock);
//
//	if (i % 2 == 0)
//	{
//		ulock.lock();
//		cout << "Even thread# " << i << endl;
//		ulock.unlock();
//	}
//}
//
//int main()
//{
//	vector<thread> vt;
//	for (int i = 0; i < 20; ++i)
//		vt.push_back(thread(Print, i));
//
//	for (auto& i : vt)
//		i.join();
//
//	return 0;
//}

/********	atomic	******/

//atomic_long ato_cnt = 0;
//long cnt = 0;
//
//void func()
//{
//	for (int i = 0; i < 100000; ++i)
//	{
//		++cnt;
//		++ato_cnt;
//	}
//}
//
//int main()
//{
//	thread t1(func);
//	thread t2(func);
//
//	t1.join();
//	t2.join();
//	cout << "普通操作" << cnt << endl;
//	cout << "原子操作" << ato_cnt << endl;
//	return 0;
//}


//
//创建10个线程竞速，看谁先加到1000000，一共测试5轮
//atomic_bool ready = false;
//atomic_flag winner = ATOMIC_FLAG_INIT;
//
//void CountToNumber(int id)
//{
//	while (!ready)
//		this_thread::yield();
//
//	for (int i = 0; i < 1000000; ++i);
//	while (!winner.test_and_set())
//	{
//		cout << "thread#" << id << " is the winner!" << endl;
//	}
//}
//
//int main()
//{
//	for (int cnt = 0; cnt < 5; ++cnt)
//	{
//		//重置状态
//		ready = false;
//		winner.clear();
//		vector<thread> vt;
//		for (int i = 0; i < 10; ++i)
//			vt.push_back(thread(CountToNumber, i + 1));
//		//开始竞速!
//		ready = true;
//
//		for (auto& e : vt)
//			e.join();
//	}
//	return 0;
//}

//#include "My_Spinlock.h"
//
//My_Spinlock spl;
//long cnt = 0;
//
//void func()
//{
//	for (int i = 0; i < 1000000; ++i)
//	{
//		spl.lock();
//		++cnt;
//		spl.unlock();
//	}
//}
//
//int main()
//{
//	thread t1(func);
//	thread t2(func);
//
//	t1.join();
//	t2.join();
//
//	cout << cnt << endl;
//	return 0;
//}