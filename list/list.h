#pragma once

//list�Ľṹ����ͷ˫��ѭ������		-	list����1��1�������ɵ�
//			 1. ������Ҫ�ȶ���1��node��  -   node���еĳ�Ա������ _data, _prev, _next; ��Ա����
//			 2. ��ζ���list�࣬list���еĳ�Ա������ ͷ���_head��������ֻҪ��_head������ӽ��Ϳ�����
//			 3. ����������Ҫ��������


namespace wqj
{
	//����list�е�ÿ����������
	template <class T>
	struct __list_node
	{
		__list_node(const T& x = T())	//������Ҫ��ȫȱʡ����Ȼlist�е�headͷ����ʼ��ʱ��֪����ʲôֵ
			:_prev(nullptr),
			 _next(nullptr),
			 _data(x)
		{}
		
		__list_node<T>* _prev;
		__list_node<T>* _next;
		T _data;
	};

	//iterator��
	template <class T>
	struct __list_iterator
	{
		typedef __list_node<T> Node;


		Node* _node;
	};



	//list��
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