#pragma once

namespace wqj
{
	template <class T>
	struct __list_node
	{
		//这里typedef是也需要将<T>带着
		typedef __list_node<T> Node;
		Node* _prev;
		Node* _next;
		T _data;

		//构造函数
		__list_node(const T& x = T())//这里需要给全缺省，不然list中的head头结点初始化时不知道给什么值
			:_prev(nullptr),
			 _next(nullptr),
			 _data(x)	//这里给data的初始化值是需要通过参数传给它的。
		{}

		//这里不用写析构函数，list对象调用它的析构函数时，就已经把Node结点给delete[]了，
		//所以如果这里再去给_prev改成nullptr，就出现访问错误了。(访问已经释放的空间了)

		//~__list_node()
		//{
		//	_prev = nullptr;
		//	_next = nullptr;
		//}
	};

	template <class T, class Ref, class Ptr>
	struct __list_iterator
	{
		//迭代器中存储的成员变量是指针，因为只有指针才支持++，->prev,->next等操作
		typedef __list_node<T> Node;
		//typedef __list_iterator<T, T&, T*> iterator;
		//typedef __list_iterator<T, const T&, const T*> const_iterator;
		typedef __list_iterator<T, Ref, Ptr> Self;	
		Node* _node;

		//构造函数
		__list_iterator(Node* node)	//迭代器必须要进行初始化，所以这里不给缺省参数
			:_node(node)
		{}


		//++it 前置++
		//这里的返回值应该是个迭代器，而不是Node* 。。。 Node*是 __list_node<T>*是一个指向结点的指针。而我们需要的是迭代器，类型不一样的!
		//++it	--->	it.operator(&it);
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//it++ 后置++	这里的int实参不需要给参数，它的作用只是在于和前置++构成函数重载
		//it++ --->	it.operator(&it, 0);
		Self operator++(int)
		{
			Self tmp(*this);
			++(*this);	// _node = _node->_next;
			return tmp;	//这里返回的是 局部变量，所以不能用引用
		}

		//*it
		Ref operator*()
		{
			return _node->_data;
		}

		//重载->是为了方便自定义类型去直接访问_data中的内容 (因为data是T类型的，所以T可以使自定义类型)
		Ptr operator->()
		{
			return &(_node->_data);
		}


		//比较迭代器相不相等，就是比较迭代器中的 _node成员变量是否相等。而_node是指针类型，可以直接进行 ==和!=的比较
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}

		bool operator==(const Self& it)
		{
			return _node == it._node;
		}
	};

	//带头双向循环链表
	template <class T>
	class list
	{
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		//构造函数
		list()
		{
			_head = new Node;	//头结点处不存数据。Node在初始化时，_data部分没有传参，也就是默认初始化成了T()。
								//如果_data是int类型，int() = 0...以此类推
			_head->_prev = _head;
			_head->_next = _head;
		}

		//拷贝构造函数
		list(const list<T>& l)
		{
			//拷贝构造的时候，头结点需要自己处理
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			//然后遍历l，利用push_back接口去添加数据
			for (auto& e : l)
				push_back(e);
		}

		//赋值重载运算符operator=		l1 = l
		list<T>& operator=(const list<T>& l)
		{
			if (this != &l)
			{
				clear();	//clear的作用是将除了头结点的所有结点删除
				for (auto& e : l)
				{
					push_back(e);
				}
			}
			return *this;
		}

		////现代写法 --- 赋值重载运算符operator=
		//list<T>& operator=(list<T> l)	//形参l是调用深拷贝的，出了该函数就自动销毁了
		//{								
		//	swap(_head, l._head);		//这里交换只交换_head,因为对于链表就是通过_head去访问的
		//	return *this;
		//}


		void push_back(const T& x)
		{
			//Node* tail = _head->_prev;
			//Node* newNode = new Node(x);

			//_head->_prev = newNode;
			//newNode->_next = _head;
			//tail->_next = newNode;
			//newNode->_prev = tail;

			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		void pop_back()
		{
			//Node* tail = _head->_prev;
			//
			//_head->_prev = tail->_prev;
			//tail->_prev->_next = _head;
			//delete[] tail;

			//assert(_head->_prev != _head);
			erase(iterator(_head->_prev));			//erase(--end());
		}

		void pop_front()
		{
			//assert(_head->_next != _head);
			erase(begin());
		}

		//在pos位置插入元素x
		void insert(iterator pos, const T& x)
		{
			Node* prev = (pos._node)->_prev;
			Node* cur = pos._node;

			Node* newNode = new Node(x);
			prev->_next = newNode;
			newNode->_prev = prev;
			cur->_prev = newNode;
			newNode->_next = cur;
		}

		//删除pos位置的结点
		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			//delete[] cur;	//不要写[]
			delete cur;


			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}

		//删除链表中的所有结点 （除了头结点）
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);	//erase(it++);也可以
			}
		}


		//这里返回的可不能是_head->_next，_head->_next并不是迭代器！！！！！！
		//*****************************************************************************************
		//所以这里直接使用iterator()去构造迭代器，因为迭代器构造需要传结点的指针，所以我们传_head->_next
		iterator begin()  					//iterator
		{
			return iterator(_head->_next);
		}
		
		iterator end() 
		{
			return iterator(_head);
		}

		//const list<T>* this  这里加const只能保证this指针指向对象的值不能被修改。
		//所以如果不是const_iterator的话，是可以把返回值赋给非const迭代器的。
		//因此我们才需要定义3个模板参数去重新构建const_iterator   [还得看operator*()和operator->()是不是const属性]
		const_iterator begin() const		//const_iterator
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}


		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		
	private:
		typedef __list_node<T> Node;
		Node* _head;
	};

	struct Date
	{
		int _year = 0;
		int _month = 1;
		int _day = 1;
	};


	void test_list1()
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);

		//__list_iterator<int> it1 = l.begin();
		list<int>::iterator it = l.begin();

		while (it != l.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_list2()
	{
		list<Date> l;
		l.push_back(Date());
		l.push_back(Date());


		list<Date>::iterator it = l.begin();
		while (it != l.end())
		{
			//cout << *it << " ";	//这里因为没有重载自定义类型Date的operator<<，所以没法直接打印
			cout << it->_year << "-" << it->_month << "-" << it->_day << endl;  //这里重载iterator中的->，方便访问自定义类型的成员。编译器这里处理过了
																				//正常应该是 it->->_year的 。编译器处理了
			cout << (*it)._year << "-" << (*it)._month << "-" << (*it)._day << endl;//这样写也可以。但是更常用->
			++it;
		}
		cout << endl;
	}

	void test_list3()
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);

		list<int>::iterator it = l.begin();
		while (it != l.end())
		{
			cout << *(it++) << " ";
		}
		cout << endl;
	}

	//测试const迭代器
	void print_list(const list<int>& l)
	{
		list<int>::const_iterator it = l.begin();
		while (it != l.end())
		{
			//*it = 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_list4()
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_front(-1);
		l.push_front(-2);
	
		print_list(l);

		l.pop_back();
		l.pop_back();
		print_list(l);

		l.pop_front();
		l.pop_front();
		print_list(l);
	}

	void test_list5()
	{
		list<int> l1;
		l1.push_back(10);
		l1.push_back(20);
		l1.push_back(30);
		l1.push_back(40);

		list<int>l2(l1);
		print_list(l2);

		l1.push_back(5);
		l1.push_back(6);
		l1.push_back(7);


		l2 = l1;
		print_list(l2);

		//l1.clear();
		//print_list(l2);
	}
}