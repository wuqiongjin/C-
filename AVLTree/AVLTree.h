#pragma once
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;


template <class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	pair<K, V> _kv;			//ÿ������д洢��һ����ֵ��
	int _bf;				//ƽ������

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr),
		 _right(nullptr),
		 _parent(nullptr),
		 _kv(kv),
		 _bf(0)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
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
			else if (kv.first > cur->_kv.first)
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
		cur->_parent = parent;	//��������cur��_parentָ�����ĸ����

		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;

		//if (parent->_left == cur)		//���ˣ������õ�ַ�Ƚ�ѽ��������Ϊcur��new��֮�󣬵�ַ�ͱ���    �ɱ𷸵ͼ������ˡ�����
		//	parent->_left = cur;
		//else
		//	parent->_right = cur;

		//��ʼ����ƽ������
		parent = cur->_parent;
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}


			if (parent->_bf == 0)
			{
				//��parentΪ���ڵ�������ĸ߶�û�����仯�����½���
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//��parentΪ���ڵ�������ĸ߶ȳ����˱仯����Ҫ�������ϸ���bfֵ
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//ƽ�����ӳ������⡣Ҫ������ת��ƽ�⡣
				//����parent��cur��bfֵ�����ж���ʲô��ת
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)	//bf������ͬ������
					{
						RotateL(parent);
					}
					else	//cur->_bf == -1 ˫��
					{
						RotateRL(parent);
					}
				}
				else	//parent->_bf == -2
				{
					if (cur->_bf == -1)	//bf������ͬ������
					{
						RotateR(parent);
					}
					else	//cur->_bf == 1 ˫��
					{
						RotateLR(parent);
					}
				}
				
				break;	//������ �˴�����ƽ�⣬ֱ��break��������
					//���⣺Ϊʲô���������ϵ�ƽ�⣿
					//��Ϊ����ƽ��󣬸������ĸ߶Ⱦ�"ƽ��"�ˣ������Ͳ���Ӱ������������Ƚ���bfֵ��
			}

		}
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

		subR->_bf = parent->_bf = 0;
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

		subL->_bf = parent->_bf = 0;
	}

	//����˫��
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		//����ƽ������
		if (bf == 1)
		{
			subLR->_bf = 0;
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subLR->_bf = 0;
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else	//bf == 0
		{
			subLR->_bf = 0;
			subL->_bf = 0;
			parent->_bf = 0;
		}
	}

	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 1)
		{
			subRL->_bf = 0;
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subRL->_bf = 0;
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else	//bf == 0
		{
			subRL->_bf = 0;
			subR->_bf = 0;
			parent->_bf = 0;
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
		cout << endl;
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return max(leftHeight, rightHeight) + 1;
	}

	bool _IsBalanced(Node* root)
	{
		if (root == nullptr)
			return true;
		
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return abs(leftHeight - rightHeight) < 2
			&& _IsBalanced(root->_left)
			&& _IsBalanced(root->_right);
	}

	//�жϸ�AVLTree�Ƿ�ƽ��
	bool IsBalanced()
	{
		return _IsBalanced(_root);
	}

private:
	Node* _root = nullptr;
};
