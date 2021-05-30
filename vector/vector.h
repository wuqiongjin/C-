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

		////�������캯��	д��1
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

		//�������캯��	д��2
		vector(const vector<T>& v)
			:_start(nullptr),
			 _finish(nullptr),
			 _endofstorage(nullptr)
		{
			//��ǰ���ݺã������ͼ��������������µ�������
			reserve(v.capacity());

			for (auto& e : v)
			{
				push_back(e);
			}
		}

		//operator=��ֵ���غ��� v1 = v3
		vector<T>& operator=(const vector<T>& v)
		{
			//���˵��Լ����Լ���ֵ
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

		//�ִ�д�� v1 = v3   ���ô�ֵ����ʱ�������β�v
		vector<T>& operator=(vector<T> v)
		{
			swap(v); //this->swap(v);
			return *this;
		}

		void swap(vector<T>& v)
		{
			//����Ϊ�˵��ÿ��е�swap�������Լ�ʵ�ֵ�swap������Ҫ���������������::
			//Ϊ�˵���ȫ�ֵ�swap����
			::swap(_start, v._start);
			::swap(_finish, v._finish);
			::swap(_endofstorage, v._endofstorage);
		}

		//���ݺ���
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				//*********************************************
				size_t sz = size();	//���������ǰ��һ��size()��
							//��Ȼ�¿��ٿռ���������_startָ�����¿ռ䡣Ȼ����ͨ��size()��������Ĵ�С���Ǵ����!!!
				//**********************************************
				T* tmp = new T[n];
				if (_start)	//���_startΪ�գ�memcpy�ͻ�����ˡ�
				{
					memcpy(tmp, _start, sizeof(T) * sz);
					delete[] _start;
				}
				//ÿ�θı�ռ�λ�õ�ʱ��������������Ҫ���иı�
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			//С�ڽض�
			if (n <= size())
			{
				_finish = _start + n;
			}
			else//n > size()
			{
				//���ж��Ƿ���Ҫ����
				if (n > capacity())
				{
					reserve(n);
				}
				
				//��_finish�� _start + nλ�ô�ȫ�����Ϊval�� ����_finish�ᵽ_start + nλ�ô�
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

			//���ж��Ƿ���Ҫ����
			if (_finish == _endofstorage)
			{
				//������ʧЧ���⣡���� ���������pos����������Ϊ���ݶ� ʧЧ ������
				size_t n = pos - _start;
				size_t newcapacity = capacity() == 0 ? 2 : 2 * capacity();
				reserve(newcapacity);
				
				//���µ�����λ��
				pos = _start + n;
			}

			//��posλ�ò��룬��pos��pos���������Ԫ���ƶ�1��
			iterator it = _finish;
			while (it != pos)
			{
				*it = *(it - 1);
				--it;
			}
			*pos = x;
			++_finish;
		}

		//erase����ɾ��λ�õ���һ��λ�õĵ�����
		iterator erase(iterator pos)
		{
			assert(pos < _finish);

			//ɾ��posλ�ã���posλ�õ�ֵ���ǳ�pos+1���Դ�����
			iterator it = pos;
			while (it != _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;

			//��ʱ��pos�Ѿ���ɾ��λ�õ���һ��λ�õ�Ԫ���ˡ�����ֱ�ӷ���pos�Ϳ�����
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


		//���Ǻ���������
		//~vector()
		//{
		//	delete[] _start;
		//	delete[] _finish;
		//	delete[] _endofstorage;
		//}
	
		~vector()
		{
			//ֻ��ɾ��1�δΰ������� �࿴������֪ʶ�ɡ�
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