#pragma once
#include <assert.h>

namespace wqj
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;

		vector()
			:_start(nullptr),
			 _finish(nullptr),
			 _endofstorage(nullptr)
		{}

		////拷贝构造函数	写法1
		//vector(const vector<T>& v)
		//	:_start(nullptr),
		//	 _finish(nullptr),
		//	 _endofstorage(nullptr)
		//{
		//	_start = new T[v.capacity()];

		//	memcpy(_start, v._start, sizeof(T)*(v.size()));
		//	_finish = _start + v.size();
		//	_endofstorage = _start + v.capacity();
		//}

		//拷贝构造函数	写法2
		vector(const vector<T>& v)
			:_start(nullptr),
			 _finish(nullptr),
			 _endofstorage(nullptr)
		{
			//提前扩容好，这样就减少了扩容所导致的消耗了
			reserve(v.capacity());

			for (auto& e : v)
			{
				push_back(e);
			}
		}

		//operator=赋值重载函数 v1 = v3
		vector<T>& operator=(const vector<T>& v)
		{
			//过滤掉自己给自己赋值
			if (this != &v)
			{
				delete[] _start;
				_start = new T[v.capacity()];
				memcpy(_start, v._start, v.capacity());

				_finish = _start + v.size();
				_endofstorage = _start + v.capacity();
			}
			return *this;
		}

		//现代写法 v1 = v3   借用传值传参时创建的形参v
		vector<T>& operator=(vector<T> v)
		{
			swap(v); //this->swap(v);
			return *this;
		}

		void swap(vector<T>& v)
		{
			//这里为了调用库中的swap而不是自己实现的swap函数。要加上作用域解析符::
			//为了调用全局的swap函数
			::swap(_start, v._start);
			::swap(_finish, v._finish);
			::swap(_endofstorage, v._endofstorage);
		}

		//扩容函数
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				//*********************************************
				size_t sz = size();	//这里必须提前存一下size()，
							//不然新开辟空间后，你的你让_start指向了新空间。然后再通过size()计算出来的大小就是错误的!!!
				//**********************************************
				T* tmp = new T[n];
				if (_start)	//如果_start为空，memcpy就会出错了。
				{
					memcpy(tmp, _start, sizeof(T) * sz);
					delete[] _start;
				}
				//每次改变空间位置的时候，这三个变量都要进行改变
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			//小于截断
			if (n <= size())
			{
				_finish = _start + n;
			}
			else//n > size()
			{
				//先判断是否需要增容
				if (n > capacity())
				{
					reserve(n);
				}
				
				//将_finish到 _start + n位置处全部填充为val。 最终_finish会到_start + n位置处
				while (_finish != _start + n)
				{
					_finish = val;
					++_finish;
				}
			}
		}

		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 2 : 2 * capacity();
				reserve(newcapacity);
			}
			*_finish = x;
			++_finish;
			
			insert(_finish, x);
		}

		void pop_back()
		{
			assert(_start < _finish);
			--_finish;
		}

		void insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);

			//先判断是否需要增容
			if (_finish == _endofstorage)
			{
				//迭代器失效问题！！！ 参数里面的pos迭代器会因为扩容而 失效 ！！！
				size_t n = pos - _start;
				size_t newcapacity = capacity() == 0 ? 2 : 2 * capacity();
				reserve(newcapacity);
				
				//更新迭代器位置
				pos = _start + n;
			}

			//在pos位置插入，将pos和pos后面的所有元素移动1格
			iterator it = _finish;
			while (it != pos)
			{
				*it = *(it - 1);
				--it;
			}
			*pos = x;
			++_finish;
		}

		//erase返回删除位置的下一个位置的迭代器
		iterator erase(iterator pos)
		{
			assert(pos < _finish);

			//删除pos位置，将pos位置的值覆盖成pos+1，以此类推
			iterator it = pos;
			while (it != _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;

			//此时的pos已经是删除位置的下一个位置的元素了。所以直接返回pos就可以了
			return pos;
		}


		T& operator[](size_t i)
		{
			assert(i < _finish);
			return *(_start + i);
		}

		const T& operator[](size_t i) const
		{
			assert(i < _finish);
			return *(_start + i);
		}

		iterator begin() const
		{
			return _start;
		}

		iterator end() const
		{
			return _finish;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}


		//我是憨批。。。
		//~vector()
		//{
		//	delete[] _start;
		//	delete[] _finish;
		//	delete[] _endofstorage;
		//}
	
		~vector()
		{
			//只能删除1次次啊。。。 多看看基础知识吧。
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};

	void print_vector(const vector<int>& v)
	{
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_vector1()
	{
		vector<int> v;

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		v.push_back(7);
		v.push_back(8);
		v.push_back(9);
		v.push_back(10);


		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_vector2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		print_vector(v);

		v.insert(v.begin() + 2, 233);

		v.erase(v.end() - 1);

		print_vector(v);
	}

	void test_vector3()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(6);

		vector<int> v2(v1);

		print_vector(v2);

		vector<int> v3;
		v3.push_back(10);
		v3.push_back(20);
		v3.push_back(30);
		v3.push_back(40);

		v1 = v3;
		print_vector(v1);
	}
	
}