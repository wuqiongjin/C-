#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
#define NUM 5

template <class T>
class ThreadPool
{
public:

public:
	ThreadPool(int num = NUM)
		:thread_num(num)
	{}

	void PoolInit()
	{
		vector<thread> vt;
		for (size_t i = 0; i < thread_num; ++i)
		{
			vt.emplace_back(thread(Routine));
			vt[i].detach();
		}
	}

	static void Routine(ThreadPoool* const t)
	{
		_mtx.lock();
		while (taskQueue.empty())
		{
			unique_lock<mutex> ulock(_mtx);
			_cv.wait(ulock);
		}

		T task;
		Get(task);
		_mtx.unlock();
		task.Run();
	}

	void Get(T& task)
	{
		T* tmp = taskQueue.front();
		taskQueue.pop();
		task = *tmp;
	}

	void Push(T& task)
	{
		_mtx.lock();
		taskQueue.emplace(&task);
		_mtx.unlock();
		_cv.notify_one();
	}

	~ThreadPool(){}
private:
	queue<T*> taskQueue;
	mutex _mtx;
	condition_variable _cv;
	size_t thread_num;
};