#pragma once
#include <iostream>
#include <utility>
using namespace std;

enum Color
{
	RED,
	BLACK
};

//�������T��T�������κ����͡�������set��map�ֱ𴫹������� K �� pair<K, V>
//���Զ���set��˵��������� K _data;
//����map��˵���������pair<K, V> _data;	//��Tȫ������pair<K, V>
template <class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	
	Color _c;

	RBTreeNode(const T& data)
		:_left(nullptr),
		 _right(nullptr),
		 _parent(nullptr),
		 _data(data),
		 _c(RED)
	{}
};

template <class T, class Ref, class Ptr>
struct __RBTree_Iterator
{
	typedef __RBTree_Iterator<T, Ref, Ptr> iterator;
	typedef RBTreeNode<T> Node;
	Node* _node;				//��װһ������ָ��

	__RBTree_Iterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	//ǰ��++		---		�����������
	iterator& operator++()
	{
		Node* cur = _node;
		//���Һ������֣���2�����
		//1. �Һ��Ӵ��ڣ���ôȥ���Ըú���Ϊ����������"����"��㣬������������
		//2. �Һ��Ӳ����ڣ��жϸý����parent�����ӻ����Һ��ӡ�
		//��������ӣ���ô˵���ý���parent��û�����ʣ�ȥ����_parent��
		//������Һ��ӣ�˵����parentΪ���������������ˣ�����Ѱ����һ������λ���Һ��ӵĽ���parent����������nullptr��
		if (cur->_right)
		{
			cur = cur->_right;
			while (cur && cur->_left)
				cur = cur->_left;

			_node = cur;	//�����Ҫ�޸�_node����Ϊ_node��thisָ���еĳ�Ա������ֻ��_node���ˣ�++it�Ż���Ч��
		}
		else//cur->_right == nullptr
		{
			Node* parent = cur->_parent;
			while (parent)
			{
				if (cur == parent->_left)
				{
					_node = parent;			//�ҵ��˻�û�������� ����/���Ƚ�㣬����ֱ��return
					return *this;
				}
				else//cur == parent->_right		//cur��parent���ұ�˵������parentΪ���������Ѿ��������ˣ�
				{
					cur = parent;			//�������ϲ���
					parent = parent->_parent;
				}
			}

			_node = parent;
		}

		return *this;
	}

	//ǰ��--
	iterator& operator--()
	{
		//��++���һ�ޣ����Ƿ�����
		Node* cur = _node;
		//����������
		//1. ���Ӳ�Ϊ�գ�ȥ�������ӵ�"����"������
		//2. ����Ϊ�գ��ж���λ��parent����߻����ұ�
		if (cur->_left)
		{
			cur = cur->_left;
			while (cur && cur->_right)
				cur = cur->_right;
			_node = cur;
		}
		else//cur->_left == nullptr
		{
			Node* parent = cur->_parent;
			//if (cur == parent->_right)	//˵����parentΪ������������·��㻹û����
			//{
			//	_node = parent;
			//	return *this;
			//}
			//else//cur == parent->_left	//˵����parentΪ��������ȫ��������
			//{
			//	while (parent && cur == parent->_left)
			//	{
			//		cur = parent;
			//		parent = parent->_parent;
			//	}
			//}

			while (parent)
			{
				if (cur == parent->_right)
				{
					_node = parent;
					return *this;
				}
				else//cur == parent->_left;
				{
					cur = parent;
					parent = parent->_parent;
				}
			}

			_node = parent;
		}
		return *this;
	}

	bool operator!=(const iterator& it)
	{
		return _node != it._node;   //�ж��������������಻��Ⱦ����ˣ���ȵĻ�����ָ��ͬһ���
	}

	bool operator==(const iterator& it)
	{
		return _node == it._node;
	}
};

//����K����ֵ������ValueType������(set��keyֵ��map��pair<K,V>��KeyOfValue�Ƿº���������
template <class K, class ValueType, class KeyOfValue>
class RBTree
{
public:
	typedef RBTreeNode<ValueType> Node;				//���������private
	typedef __RBTree_Iterator<ValueType, ValueType&, ValueType*> iterator;	//���������public����ȻMap�����޷�ʹ��iterator�������
	typedef __RBTree_Iterator<ValueType, const ValueType&, const ValueType*> const_iterator;	//���������public����ȻMap�����޷�ʹ��iterator�������

	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left)
			cur = cur->_left;
		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator begin() const
	{
		Node* cur = _root;
		while (cur && cur->_left)
			cur = cur->_left;
		return const_iterator(cur);
	}
	
	const_iterator end() const
	{
		return const_iterator(nullptr);
	}

public:
	pair<iterator, bool> Insert(const ValueType& data)
	{
		KeyOfValue kofv;
		//������
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_c = BLACK;
			return make_pair(iterator(_root), true);
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kofv(data) < kofv(cur->_data))		//������Ҫ�õ�pair<K, V>.firstֵ�ĵط�����Ҫ���÷º���
			{										//�÷º����Լ��жϡ�map���÷���kv.first; set����ֱ�ӷ���k
				parent = cur;
				cur = cur->_left;
			}
			else if (kofv(data) > kofv(cur->_data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//����ʧ�ܣ������Ѿ����ڵ���ֵͬ���ĵ�����
				return make_pair(iterator(cur), false);
			}
		}

		cur = new Node(data);
		if (kofv(parent->_data) > kofv(cur->_data))
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		Node* newNode = cur;	//�����²������λ�ã���Ϊ�����������ɫʱ��cur��ָ������ܻᷢ���仯

		//������ɫ
		cur->_c = RED;
		while (parent && parent->_c == RED)
		{
			Node* grandfather = parent->_parent;	//parent�Ǻ�ɫ���������Ǹ���㡣�����游һ������
			//����parentλ��grandfather�����������֣�����Ĵ������ƣ�ֻ����ת��ʱ��ͬ
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;		//һ��ȡ����uncle
				if (uncle && uncle->_c == RED)	//���1
				{
					parent->_c = uncle->_c = BLACK;
					grandfather->_c = RED;

					//�������� �ж� / ����
					cur = grandfather;
					parent = grandfather->_parent;	//parent���ܲ����ڣ�������whileѭ������Ҫ��ֹ��Ϊnullptr
				}
				else//uncle������ �� uncleΪ��	//���2/3
				{
					if (parent->_left == cur)	//���2�����󣬽����ҵ���
					{
						RotateR(grandfather);
						parent->_c = BLACK;	//parent�������ĸ��ڵ�
						grandfather->_c = RED;
					}
					else						//���3�����ң���������˫��
					{
						RotateL(parent);		//˫����2����ת����Ķ����㲻ͬ��
						RotateR(grandfather);
						cur->_c = BLACK;  //cur�������ĸ��ڵ�
						grandfather->_c = parent->_c = RED;
					}
					//��������
					break;	//��ת��������Ϊ���������ĸ����ߺ�ɫ�ˣ����Բ��ܸ�����Ƿ��и��ף��������ƻ�������Ĺ���
				}
			}
			else //grandfather->_right = parent
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_c == RED)
				{
					parent->_c = uncle->_c = BLACK;
					grandfather->_c = RED;
				}
				else
				{
					if (parent->_right == cur)		//���2������
					{
						RotateL(grandfather);
						parent->_c = BLACK;	//parent���������
						grandfather->_c = RED;
					}
					else //parent->_left == cur		//���3������˫��
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_c = BLACK;	//cur���������
						parent->_c = grandfather->_c = RED;
					}
					break;
				}
			}
		}

		_root->_c = BLACK;	//�������汩���ĸ�root���ɺ�ɫ������������Ͳ��ÿ���root����ɫ��������!
		return make_pair(iterator(newNode), true);
	}

	//��ƽ��	---	����	(���ҳ�������
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;	//parent�ĸ��ڵ�

		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)				//�ж�subR�������Ƿ�Ϊnullptr
			subRL->_parent = parent;

		parent->_parent = subR;
		//�ж�parent�Ƿ�Ϊ�����
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else	//���parent�ĸ��ڵ���������㻹Ҫ�����ж�	
		{
			//�ж�parentλ�ڸ��ڵ����һ��
			if (pparent->_left == parent)
				pparent->_left = subR;
			else
				pparent->_right = subR;

			subR->_parent = pparent;
		}
	}

	//��ƽ��	---	�ҵ���	(�����������
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pparent = parent->_parent;

		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		parent->_parent = subL;
		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (pparent->_left == parent)
				pparent->_left = subL;
			else
				pparent->_right = subL;

			subL->_parent = pparent;
		}
	}

	//���ﴫ�δ��ľ��Ǽ�ֵK
	iterator Find(const K& k)
	{
		KeyOfValue kofv;
		Node* cur = _root;
		while (cur)
		{
			if (kofv(cur->_data) > k)	//map�з��� pair��first �� k ���бȽ�
			{
				cur = cur->_left;
			}
			else if(kofv(cur->_data) < k)
			{
				cur = cur->_right;
			}
			else
			{
				return iterator(cur);
			}
		}
		//�Ҳ�������nullptr������
		return iterator(nullptr);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		
		_InOrder(root->_left);
		//cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	void InOrder()
	{
		_InOrder(_root);
	}

	bool _IsValidRBTree(Node* root, size_t count, size_t BlackNodes)
	{
		if (root == nullptr && count == BlackNodes)
			return true;
		if (root == nullptr)
			return false;
		if (count > BlackNodes)
			return false;

		//�жϺ�ɫ���ĸ����Ƿ�Ϊ��ʯ���
		Node* cur = root;
		Node* parent = cur->_parent;
		if (cur->_c == RED && parent->_c == RED)
			return false;

		//ͳ��ÿ��·���ĺ�ɫ���ĸ���
		if(cur->_c == BLACK)
			++count;
		//�ݹ�ͳ�����������������ĺ�ɫ����������˳���жϺ�ɫ���ĸ����Ƿ�Ϊ��ɫ
		return _IsValidRBTree(root->_left, count, BlackNodes)
			&& _IsValidRBTree(root->_right, count, BlackNodes);
	}

	bool IsValidRBTree()
	{
		//����Ƿ���Ч��Ϊ3�㣺
		//1. ������Ƿ�Ϊ��ɫ
		//-----------------------------//�����2�㽨��ݹ������ʱ�����ͳ�ƺ��ж�
		//2. ÿ��·���ĺ�ɫ�����Ŀ�Ƿ���ͬ
		//3. �жϺ�ɫ����parent�Ƿ�Ϊ��ɫ
		if (_root == nullptr)
			return true;
		if (_root->_c == RED)
			return false;

		//��ͳ�Ƴ�����һ��·���ĺ�ɫ������Ŀ
		size_t BlackNodes = 0;
		Node* cur = _root;
		while (cur)
		{
			if(cur->_c == BLACK)
				++BlackNodes;
			cur = cur->_left;
		}

		return _IsValidRBTree(_root, 0, BlackNodes);
	}

private:
	Node* _root = nullptr;
};