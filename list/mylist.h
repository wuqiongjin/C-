#pragma once

namespace wqj
{
	template <class T>
	struct __list_node
	{
		//����typedef��Ҳ��Ҫ��<T>����
		typedef __list_node<T> Node;
		Node* _prev;
		Node* _next;
		T _data;

		//���캯��
		__list_node(const T& x = T())//������Ҫ��ȫȱʡ����Ȼlist�е�headͷ����ʼ��ʱ��֪����ʲôֵ
			:_prev(nullptr),
			 _next(nullptr),
			 _data(x)	//�����data�ĳ�ʼ��ֵ����Ҫͨ�������������ġ�
		{}

		//���ﲻ��д����������list�������������������ʱ�����Ѿ���Node����delete[]�ˣ�
		//�������������ȥ��_prev�ĳ�nullptr���ͳ��ַ��ʴ����ˡ�(�����Ѿ��ͷŵĿռ���)

		//~__list_node()
		//{
		//	_prev = nullptr;
		//	_next = nullptr;
		//}
	};

	template <class T, class Ref, class Ptr>
	struct __list_iterator
	{
		//�������д洢�ĳ�Ա������ָ�룬��Ϊֻ��ָ���֧��++��->prev,->next�Ȳ���
		typedef __list_node<T> Node;
		//typedef __list_iterator<T, T&, T*> iterator;
		//typedef __list_iterator<T, const T&, const T*> const_iterator;
		typedef __list_iterator<T, Ref, Ptr> Self;	
		Node* _node;

		//���캯��
		__list_iterator(Node* node)	//����������Ҫ���г�ʼ�����������ﲻ��ȱʡ����
			:_node(node)
		{}


		//++it ǰ��++
		//����ķ���ֵӦ���Ǹ���������������Node* ������ Node*�� __list_node<T>*��һ��ָ�����ָ�롣��������Ҫ���ǵ����������Ͳ�һ����!
		//++it	--->	it.operator(&it);
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//it++ ����++	�����intʵ�β���Ҫ����������������ֻ�����ں�ǰ��++���ɺ�������
		//it++ --->	it.operator(&it, 0);
		Self operator++(int)
		{
			Self tmp(*this);
			++(*this);	// _node = _node->_next;
			return tmp;	//���ﷵ�ص��� �ֲ����������Բ���������
		}

		//*it
		Ref operator*()
		{
			return _node->_data;
		}

		//����->��Ϊ�˷����Զ�������ȥֱ�ӷ���_data�е����� (��Ϊdata��T���͵ģ�����T����ʹ�Զ�������)
		Ptr operator->()
		{
			return &(_node->_data);
		}


		//�Ƚϵ������಻��ȣ����ǱȽϵ������е� _node��Ա�����Ƿ���ȡ���_node��ָ�����ͣ�����ֱ�ӽ��� ==��!=�ıȽ�
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}

		bool operator==(const Self& it)
		{
			return _node == it._node;
		}
	};

	//��ͷ˫��ѭ������
	template <class T>
	class list
	{
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		//���캯��
		list()
		{
			_head = new Node;	//ͷ��㴦�������ݡ�Node�ڳ�ʼ��ʱ��_data����û�д��Σ�Ҳ����Ĭ�ϳ�ʼ������T()��
								//���_data��int���ͣ�int() = 0...�Դ�����
			_head->_prev = _head;
			_head->_next = _head;
		}

		//�������캯��
		list(const list<T>& l)
		{
			//���������ʱ��ͷ�����Ҫ�Լ�����
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;

			//Ȼ�����l������push_back�ӿ�ȥ�������
			for (auto& e : l)
				push_back(e);
		}

		//��ֵ���������operator=		l1 = l
		list<T>& operator=(const list<T>& l)
		{
			if (this != &l)
			{
				clear();	//clear�������ǽ�����ͷ�������н��ɾ��
				for (auto& e : l)
				{
					push_back(e);
				}
			}
			return *this;
		}

		////�ִ�д�� --- ��ֵ���������operator=
		//list<T>& operator=(list<T> l)	//�β�l�ǵ�������ģ����˸ú������Զ�������
		//{								
		//	swap(_head, l._head);		//���ｻ��ֻ����_head,��Ϊ�����������ͨ��_headȥ���ʵ�
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

		//��posλ�ò���Ԫ��x
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

		//ɾ��posλ�õĽ��
		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			//delete[] cur;	//��Ҫд[]
			delete cur;


			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}

		//ɾ�������е����н�� ������ͷ��㣩
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);	//erase(it++);Ҳ����
			}
		}


		//���ﷵ�صĿɲ�����_head->_next��_head->_next�����ǵ�����������������
		//*****************************************************************************************
		//��������ֱ��ʹ��iterator()ȥ�������������Ϊ������������Ҫ������ָ�룬�������Ǵ�_head->_next
		iterator begin()  					//iterator
		{
			return iterator(_head->_next);
		}
		
		iterator end() 
		{
			return iterator(_head);
		}

		//const list<T>* this  �����constֻ�ܱ�֤thisָ��ָ������ֵ���ܱ��޸ġ�
		//�����������const_iterator�Ļ����ǿ��԰ѷ���ֵ������const�������ġ�
		//������ǲ���Ҫ����3��ģ�����ȥ���¹���const_iterator   [���ÿ�operator*()��operator->()�ǲ���const����]
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
			//cout << *it << " ";	//������Ϊû�������Զ�������Date��operator<<������û��ֱ�Ӵ�ӡ
			cout << it->_year << "-" << it->_month << "-" << it->_day << endl;  //��������iterator�е�->����������Զ������͵ĳ�Ա�����������ﴦ�����
																				//����Ӧ���� it->->_year�� ��������������
			cout << (*it)._year << "-" << (*it)._month << "-" << (*it)._day << endl;//����дҲ���ԡ����Ǹ�����->
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

	//����const������
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