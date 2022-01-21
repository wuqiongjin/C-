#pragma once
#include <iostream>
#include <thread>
#include <atomic>

class My_Spinlock
{
public:
	My_Spinlock()
	{
		_spinlock.clear();
	}

	My_Spinlock(const My_Spinlock&) = delete;
	My_Spinlock& operator=(const My_Spinlock&) = delete;

	void lock()
	{
		while (_spinlock.test_and_set());
	}

	void unlock()
	{
		_spinlock.clear();
	}
private:
	std::atomic_flag _spinlock;
};