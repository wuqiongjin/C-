#pragma once
#include <iostream>
#include <utility>
using namespace std;

enum Color
{
	RED,
	BLACK
};

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	pair<K, V> _kv;
	
	Color _c;

	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr),
		 _right(nullptr),
		 _parent(nullptr),
		 _kv(kv),
		 _c(RED)
	{}
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		//������
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_c = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first > cur->_kv.first)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

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
		return true;
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

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
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