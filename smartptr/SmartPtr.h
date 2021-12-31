#pragma once
#include <iostream>
#include <mutex>

namespace wqj
{
	template <class T>
	class smart_ptr
	{
	public:
		smart_ptr(T* ptr)
			:_ptr(ptr)
		{}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		~smart_ptr()
		{
			if (_ptr)
			{
				std::cout << "delete _ptr: " << _ptr << std::endl;
				delete _ptr;
			}
		}
	private:
		T* _ptr;
	};


	//auto_ptr的模拟实现
	template <class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~auto_ptr()
		{
			if (_ptr)
			{
				std::cout << "delete _ptr: " << _ptr << std::endl;
				delete _ptr;
			}
		}

		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
					delete _ptr;
				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}
			return *this;
		}

		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }
	private:
		T* _ptr;
	};


	//unique_ptr的模拟实现
	template <class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
				delete _ptr;
		}

		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }
		
		unique_ptr(const unique_ptr<T>& up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;
	private:
		T* _ptr;
	};


	//C++11 shared_ptr的模拟实现 (引用计数)
	//template <class T>
	//class shared_ptr
	//{
	//	friend class weak_ptr<T>;
	//public:
	//	shared_ptr(T* ptr)
	//		:_ptr(ptr),
	//		 _pcount(new int(1))
	//	{}
	//	

	//	~shared_ptr()
	//	{
	//		if(--(*_pcount) == 0)
	//		{
	//			std::cout << "delete ptr: " << _ptr << std::endl;
	//			delete _ptr;
	//			_ptr = nullptr;
	//			//引用计数的资源也要释放!
	//			delete _pcount;
	//			_pcount = nullptr;
	//		}
	//	}

	//	T& operator*() { return *_ptr; }
	//	T* operator->() { return _ptr; }

	//	//返回当前引用计数的值
	//	int use_count()
	//	{
	//		return *_pcount;
	//	}

	//	shared_ptr(const shared_ptr<T>& sp)
	//		:_ptr(sp._ptr),
	//		 _pcount(sp._pcount)
	//	{
	//		++(*_pcount);
	//	}

	//	shared_ptr<T>& operator=(const shared_ptr<T>& sp)
	//	{
	//		if (this != &sp)
	//		{
	//			//先将_pcount的引用计数--，然后判断是否需要释放资源
	//			if (--(*_pcount) == 0)
	//			{
	//				delete _ptr;
	//				_ptr = nullptr;

	//				delete _pcount;
	//				_pcount = nullptr;
	//			}

	//			_ptr = sp._ptr;
	//			_pcount = sp._pcount;
	//			++(*_pcount);
	//		}
	//		return *this;
	//	}

	//private:
	//	T *_ptr;
	//	int* _pcount;

	//	//static解决不了问题，当定义了多个对象的时候，多个不同的对象都共享同一个count，会出错的
	//	//static int _count;
	//};
	//
	////template <class T>
	////int shared_ptr<T>::_count = 1;


	template <class T>
	class weak_ptr;
	//线程安全版本 --- shared_ptr
	template <class T>
	class shared_ptr
	{
	public:
		//shared_ptr()
		//{
			
		//}
		//必须给_prev和_next提供默认构造函数(所以这里给了缺省值)
		//并且!!!!如果要提供默认构造函数，还必须要在里面对_pcount进行初始化!
		//不然在 sp1->_next = sp2;这句代码中就会出错，因为sp1->_next就是使用到了shared_ptr<ListNode> _next对象
		//然而_next对象中的_pcount并没有初始化，值为随机值。在 "_next = sp2;"这句中，会进行拷贝赋值operator=，
		//拷贝赋值函数中会去调用Release函数，在Release函数中会对将_pcount进行--，并且判断是否需要释放资源，
		//然后你的_pcount并没有初始化，在--(*_pcount)这句代码时就会出错!!!!
		/************************************************************/
		//因此你在提供默认构造函数时，也必须要初始化其中的成员变量_pcount，所以这里为了方便，就使用了"T* ptr = nullptr"的方式
		//提供缺省值，让_next和_prev对象中的_pcount能在这里 _pcount(new int(1))中进行初始化!!! (顺便初始化一下其它成员)
		shared_ptr(T* ptr = nullptr)	//这个缺省值真的太太太关键了!!!
			:_ptr(ptr),
			 _pcount(new int(1)),	//初始化!
			 _pmtx(new std::mutex)
		{
			std::cout << this;
			std::cout << "shared_ptr()" << std::endl;
		}


		void Add_Ref_count()
		{
			_pmtx->lock();
			++(*_pcount);
			_pmtx->unlock();
		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr),
		 	 _pcount(sp._pcount),
			 _pmtx(sp._pmtx)
		{
			Add_Ref_count();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				//让当前ptr的引用计数--，并判断是否需要释放资源
				Release();

				//赋值
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;

				//增加引用计数
				Add_Ref_count();
			}
			return *this;
		}

		void Release()
		{
			bool flag = false;
			_pmtx->lock();

			if (--(*_pcount) == 0)
			{
				delete _ptr;
				_ptr = nullptr;

				delete _pcount;
				_pcount = nullptr;

				flag = true;
				std::cout << "释放当前资源!" << std::endl;
			}
			_pmtx->unlock();

			//锁资源也要释放
			if (flag)
				delete _pmtx;
		}

		~shared_ptr()
		{
			Release();
		}
		
		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }


		int use_count() 
		{
			return *_pcount; 
		}
		
		T* Get_Ptr() const
		{
			return _ptr;
		}

	private:
		T* _ptr;
		int* _pcount;
		std::mutex* _pmtx;
		
		//template <class T>
		friend class weak_ptr<T>;
	};
	
	//weak_ptr并不是智能指针，它没有RAII思想，它只是能"像指针一样"
	template <class T>
	class weak_ptr
	{
	public:
		//这里必须给一个默认构造函数!!!
		//在ListNode类中，有自定义类型weak_ptr<ListNode> _prev存在，
		//该对象会在ListNode的构造函数中的初始化列表阶段进行初始化，而初始化就会去调用weak_ptr的构造函数
		//如果没有合适的构造函数就会报错了! 所以这里给了默认构造函数, 如果不给就不会生成(因为后面我们写了拷贝构造, 它就不会自动生成构造了)
		weak_ptr() = default;
		//weak_ptr()
		//{
		//	std::cout << "weak_ptr()" << std::endl;
		//}


		//weak_ptr(const shared_ptr<T>& sp)
		//	:_ptr(sp.Get_Ptr())
		//{}

		//weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		//{
		//	_ptr = sp.Get_Ptr();
		//	return *this;
		//}

		//使用了友元类语法(需要前置声明+友元类的定义语法)
		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
		{}
		
		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp._ptr;
			return *this;
		}

		T& operator*() { return *_ptr; }
		T* operator->() { return _ptr; }

	private:
		T* _ptr;
	};


	template <class Lock>
	class Lock_Guard
	{
	public:
		Lock_Guard(Lock& lk)
			:_lk(lk)
		{
			std::cout << "Lock_Guard()" << std::endl;
			_lk.lock();
		}

		~Lock_Guard()
		{
			std::cout << "~Lock_Guard()" << std::endl;
			_lk.unlock();
		}

		Lock_Guard(const Lock_Guard<Lock>&) = delete;
	private:
		Lock& _lk;	//这里必须加上引用
	};

}
