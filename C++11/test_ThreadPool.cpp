#include "ThreadPool.h"
#include <Windows.h>

class Task
{
public:
	Task(int base = 10)
		:_base(base)
	{}
	void Run()
	{
		std::cout << "ThreadID:[" << this_thread::get_id() << "]";
		std::cout << " Run Task --- Base: " << _base * _base << std::endl;
	}
	~Task() {}
private:
	int _base;
};

int main()
{
	ThreadPool<Task>* tp = new ThreadPool<Task>();
	tp->PoolInit();

	while (true)
	{
		int base = rand() % 10 + 1;
		Task t(base);
		tp->Push(t);
		Sleep(1);
	}
	return 0;
}

//void rt()
//{
//	cout << "create" << endl;
//}
//
//int main()
//{
//	vector<thread> vt;
//	for (int i = 0; i < 10; ++i)
//	{
//		vt.emplace_back(thread(rt));
//		vt[i].detach();
//	}
//	return 0;
//}