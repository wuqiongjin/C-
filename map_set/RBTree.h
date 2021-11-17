#pragma once
#include <iostream>
#include <utility>
using namespace std;

enum Color
{
	RED,
	BLACK
};

//这里改用T，T可以是任何类型。在这里set与map分别传过来的是 K 和 pair<K, V>
//所以对于set来说，这里就是 K _data;
//对于map来说，这里就是pair<K, V> _data;	//把T全部换成pair<K, V>
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
	Node* _node;				//封装一个结点的指针

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

	//前置++		---		采用中序遍历
	iterator& operator++()
	{
		Node* cur = _node;
		//从右孩子入手，分2种情况
		//1. 右孩子存在，那么去找以该孩子为根的子树的"最左"结点，并返回最左结点
		//2. 右孩子不存在，判断该结点是parent的左孩子还是右孩子。
		//如果是左孩子，那么说明该结点的parent还没被访问，去访问_parent。
		//如果是右孩子，说明以parent为根的子树访问完了，继续寻找下一个不是位于右孩子的结点的parent，或者遇到nullptr。
		if (cur->_right)
		{
			cur = cur->_right;
			while (cur && cur->_left)
				cur = cur->_left;

			_node = cur;	//最后需要修改_node，因为_node是this指针中的成员变量，只有_node变了，++it才会起效果
		}
		else//cur->_right == nullptr
		{
			Node* parent = cur->_parent;
			while (parent)
			{
				if (cur == parent->_left)
				{
					_node = parent;			//找到了还没被遍历的 父亲/祖先结点，可以直接return
					return *this;
				}
				else//cur == parent->_right		//cur在parent的右边说明，以parent为根的子树已经访问完了！
				{
					cur = parent;			//继续往上查找
					parent = parent->_parent;
				}
			}

			_node = parent;
		}

		return *this;
	}

	//前置--
	iterator& operator--()
	{
		//与++如出一辙，就是方向反了
		Node* cur = _node;
		//从左孩子入手
		//1. 左孩子不为空，去找它左孩子的"最右"子孙结点
		//2. 左孩子为空，判断它位于parent的左边还是右边
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
			//if (cur == parent->_right)	//说明以parent为根的子树的左路结点还没访问
			//{
			//	_node = parent;
			//	return *this;
			//}
			//else//cur == parent->_left	//说明以parent为根的子树全部访问了
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
		return _node != it._node;   //判断这两个迭代器相不相等就行了，相等的话就是指向同一结点
	}

	bool operator==(const iterator& it)
	{
		return _node == it._node;
	}
};

//参数K：键值；参数ValueType：数据(set是key值，map是pair<K,V>；KeyOfValue是仿函数所在类
template <class K, class ValueType, class KeyOfValue>
class RBTree
{
public:
	typedef RBTreeNode<ValueType> Node;				//这个可以是private
	typedef __RBTree_Iterator<ValueType, ValueType&, ValueType*> iterator;	//这个必须是public，不然Map类中无法使用iterator这个名字
	typedef __RBTree_Iterator<ValueType, const ValueType&, const ValueType*> const_iterator;	//这个必须是public，不然Map类中无法使用iterator这个名字

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
		//插入结点
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
			if (kofv(data) < kofv(cur->_data))		//凡是需要用到pair<K, V>.first值的地方都需要调用仿函数
			{										//让仿函数自己判断。map调用返回kv.first; set调用直接返回k
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
				//插入失败，返回已经存在的相同值结点的迭代器
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

		Node* newNode = cur;	//保存新插入结点的位置，因为在下面调整颜色时，cur所指对象可能会发生变化

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
		return make_pair(iterator(newNode), true);
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

	//这里传参传的就是键值K
	iterator Find(const K& k)
	{
		KeyOfValue kofv;
		Node* cur = _root;
		while (cur)
		{
			if (kofv(cur->_data) > k)	//map中访问 pair的first 与 k 进行比较
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
		//找不到返回nullptr迭代器
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