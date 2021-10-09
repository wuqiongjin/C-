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

	pair<K, V> _kv;			//每个结点中存储的一个键值对
	int _bf;				//平衡因子

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
		cur->_parent = parent;	//别忘了让cur的_parent指回它的父结点

		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;

		//if (parent->_left == cur)		//吐了，不能拿地址比较呀！！！因为cur在new了之后，地址就变了    可别犯低级错误了。。。
		//	parent->_left = cur;
		//else
		//	parent->_right = cur;

		//开始更新平衡因子
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
				//以parent为根节点的子树的高度没发生变化，更新结束
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//以parent为根节点的子树的高度出现了变化，需要继续向上更新bf值
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//平衡因子出现问题。要进行旋转调平衡。
				//根据parent与cur的bf值进行判断是什么旋转
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)	//bf符号相同，单旋
					{
						RotateL(parent);
					}
					else	//cur->_bf == -1 双旋
					{
						RotateRL(parent);
					}
				}
				else	//parent->_bf == -2
				{
					if (cur->_bf == -1)	//bf符号相同，单旋
					{
						RotateR(parent);
					}
					else	//cur->_bf == 1 双旋
					{
						RotateLR(parent);
					}
				}
				
				break;	//※※※ 此处调完平衡，直接break；※※※
					//问题：为什么不继续向上调平衡？
					//因为调完平衡后，该子树的高度就"平衡"了，这样就不会影响该子树的祖先结点的bf值了
			}

		}
		return true;
	}

	//调平衡	---	左单旋	(右右出问题了
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;	//parent的父节点

		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)				//判断subR的左孩子是否为nullptr
			subRL->_parent = parent;

		parent->_parent = subR;
		//判断parent是否为根结点
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else	//如果parent的父节点是其它结点还要继续判断	
		{
			//判断parent位于父节点的哪一侧
			if (pparent->_left == parent)
				pparent->_left = subR;
			else
				pparent->_right = subR;

			subR->_parent = pparent;
		}

		subR->_bf = parent->_bf = 0;
	}

	//调平衡	---	右单旋	(左左出问题了
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

	//左右双旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		//更新平衡因子
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

	//右左双旋
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

	//判断该AVLTree是否平衡
	bool IsBalanced()
	{
		return _IsBalanced(_root);
	}

private:
	Node* _root = nullptr;
};
