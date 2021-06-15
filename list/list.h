#pragma once

//list的结构：带头双向循环链表		-	list是由1个1个结点组成的
//			 1. 所以需要先定义1个node类  -   node类中的成员变量有 _data, _prev, _next; 成员函数
//			 2. 其次定义list类，list类中的成员变量是 头结点_head，接下来只要向_head后面添加结点就可以了
//			 3. 迭代器类需要单独定义


namespace wqj
{
	//定义list中的每个结点的内容
	template <class T>
	struct __list_node
	{
		__list_node(const T& x = T())	//这里需要给全缺省，不然list中的head头结点初始化时不知道给什么值
			:_prev(nullptr),
			 _next(nullptr),
			 _data(x)
		{}
		
		__list_node<T>* _prev;
		__list_node<T>* _next;
		T _data;
	};

	//iterator类
	template <class T>
	struct __list_iterator
	{
		typedef __list_node<T> Node;


		Node* _node;
	};



	//list类
	template <class T>
	class list
	{
	public:
		typedef __list_node<T> Node;

		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		void push_back(const T& x)
		{
			Node* tail = _head->_prev;
			Node* newNode = new Node(x);

			tail->_next = newNode;
			newNode->_prev = tail;
			newNode->_next = _head;
			_head->_prev = newNode;
		}




	private:
		Node* _head;
	};


}