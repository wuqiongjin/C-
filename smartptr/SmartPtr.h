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


	//auto_ptr��ģ��ʵ��
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


	//unique_ptr��ģ��ʵ��
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


	//C++11 shared_ptr��ģ��ʵ�� (���ü���)
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
	//			//���ü�������ԴҲҪ�ͷ�!
	//			delete _pcount;
	//			_pcount = nullptr;
	//		}
	//	}

	//	T& operator*() { return *_ptr; }
	//	T* operator->() { return _ptr; }

	//	//���ص�ǰ���ü�����ֵ
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
	//			//�Ƚ�_pcount�����ü���--��Ȼ���ж��Ƿ���Ҫ�ͷ���Դ
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

	//	//static����������⣬�������˶�������ʱ�򣬶����ͬ�Ķ��󶼹���ͬһ��count��������
	//	//static int _count;
	//};
	//
	////template <class T>
	////int shared_ptr<T>::_count = 1;


	template <class T>
	class weak_ptr;
	//�̰߳�ȫ�汾 --- shared_ptr
	template <class T>
	class shared_ptr
	{
	public:
		//shared_ptr()
		//{
			
		//}
		//�����_prev��_next�ṩĬ�Ϲ��캯��(�����������ȱʡֵ)
		//����!!!!���Ҫ�ṩĬ�Ϲ��캯����������Ҫ�������_pcount���г�ʼ��!
		//��Ȼ�� sp1->_next = sp2;�������оͻ������Ϊsp1->_next����ʹ�õ���shared_ptr<ListNode> _next����
		//Ȼ��_next�����е�_pcount��û�г�ʼ����ֵΪ���ֵ���� "_next = sp2;"����У�����п�����ֵoperator=��
		//������ֵ�����л�ȥ����Release��������Release�����л�Խ�_pcount����--�������ж��Ƿ���Ҫ�ͷ���Դ��
		//Ȼ�����_pcount��û�г�ʼ������--(*_pcount)������ʱ�ͻ����!!!!
		/************************************************************/
		//��������ṩĬ�Ϲ��캯��ʱ��Ҳ����Ҫ��ʼ�����еĳ�Ա����_pcount����������Ϊ�˷��㣬��ʹ����"T* ptr = nullptr"�ķ�ʽ
		//�ṩȱʡֵ����_next��_prev�����е�_pcount�������� _pcount(new int(1))�н��г�ʼ��!!! (˳���ʼ��һ��������Ա)
		shared_ptr(T* ptr = nullptr)	//���ȱʡֵ���̫̫̫�ؼ���!!!
			:_ptr(ptr),
			 _pcount(new int(1)),	//��ʼ��!
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
				//�õ�ǰptr�����ü���--�����ж��Ƿ���Ҫ�ͷ���Դ
				Release();

				//��ֵ
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;

				//�������ü���
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
				std::cout << "�ͷŵ�ǰ��Դ!" << std::endl;
			}
			_pmtx->unlock();

			//����ԴҲҪ�ͷ�
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
	
	//weak_ptr����������ָ�룬��û��RAII˼�룬��ֻ����"��ָ��һ��"
	template <class T>
	class weak_ptr
	{
	public:
		//��������һ��Ĭ�Ϲ��캯��!!!
		//��ListNode���У����Զ�������weak_ptr<ListNode> _prev���ڣ�
		//�ö������ListNode�Ĺ��캯���еĳ�ʼ���б�׶ν��г�ʼ��������ʼ���ͻ�ȥ����weak_ptr�Ĺ��캯��
		//���û�к��ʵĹ��캯���ͻᱨ����! �����������Ĭ�Ϲ��캯��, ��������Ͳ�������(��Ϊ��������д�˿�������, ���Ͳ����Զ����ɹ�����)
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

		//ʹ������Ԫ���﷨(��Ҫǰ������+��Ԫ��Ķ����﷨)
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
		Lock& _lk;	//��������������
	};

}
