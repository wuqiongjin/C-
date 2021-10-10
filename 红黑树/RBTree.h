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
		//插入结点
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

		//调整颜色
		cur->_c = RED;
		while (parent && parent->_c == RED)
		{
			Node* grandfather = parent->_parent;	//parent是红色，不可能是根结点。所以祖父一定存在
			//按照parent位于grandfather的左右来划分，两侧的处理类似，只是旋转的时候不同
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;		//一切取决于uncle
				if (uncle && uncle->_c == RED)	//情况1
				{
					parent->_c = uncle->_c = BLACK;
					grandfather->_c = RED;

					//继续向上 判断 / 调整
					cur = grandfather;
					parent = grandfather->_parent;	//parent可能不存在，所以在while循环里面要防止它为nullptr
				}
				else//uncle不存在 或 uncle为黑	//情况2/3
				{
					if (parent->_left == cur)	//情况2：左左，进行右单旋
					{
						RotateR(grandfather);
						parent->_c = BLACK;	//parent作子树的根节点
						grandfather->_c = RED;
					}
					else						//情况3：左右，进行左右双旋
					{
						RotateL(parent);		//双旋的2次旋转传入的对象结点不同！
						RotateR(grandfather);
						cur->_c = BLACK;  //cur作子树的根节点
						grandfather->_c = parent->_c = RED;
					}
					//结束调整
					break;	//旋转结束后，作为子树，它的根结点边黑色了，所以不管根结点是否有父亲，都不会破坏红黑树的规则
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
					if (parent->_right == cur)		//情况2：左单旋
					{
						RotateL(grandfather);
						parent->_c = BLACK;	//parent子树根结点
						grandfather->_c = RED;
					}
					else //parent->_left == cur		//情况3：右左双旋
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_c = BLACK;	//cur子树根结点
						parent->_c = grandfather->_c = RED;
					}
					break;
				}
			}
		}

		_root->_c = BLACK;	//在最外面暴力的给root赋成黑色，这样在里面就不用考虑root被变色的问题了!
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

		//判断红色结点的父亲是否为红石结点
		Node* cur = root;
		Node* parent = cur->_parent;
		if (cur->_c == RED && parent->_c == RED)
			return false;

		//统计每条路径的黑色结点的个数
		if(cur->_c == BLACK)
			++count;
		//递归统计左子树和右子树的黑色结点个数，并顺便判断红色结点的父亲是否为红色
		return _IsValidRBTree(root->_left, count, BlackNodes)
			&& _IsValidRBTree(root->_right, count, BlackNodes);
	}

	bool IsValidRBTree()
	{
		//检测是否有效分为3点：
		//1. 根结点是否为黑色
		//-----------------------------//下面的2点建议递归遍历的时候进行统计和判断
		//2. 每条路径的黑色结点数目是否相同
		//3. 判断红色结点的parent是否为红色
		if (_root == nullptr)
			return true;
		if (_root->_c == RED)
			return false;

		//先统计出任意一条路径的黑色结点的数目
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