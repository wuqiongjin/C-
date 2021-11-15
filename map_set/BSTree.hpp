#pragma once

template <class K>
struct BSTreeNode
{
  BSTreeNode<K>* _left;
  BSTreeNode<K>* _right;
  K _key;
  
  BSTreeNode(const K& key = K())  //缺省参数给类型()
    :_left(nullptr),
     _right(nullptr),
     _key(key)
  {}
};

template <class K>
class BSTree 
{
  typedef BSTreeNode<K> Node;
  public:
    BSTree()
      :_root(nullptr)
    {}

    bool insert(const K& key)
    {
      if(_root == nullptr)
      {
        _root = new Node(key);
        return true;
      }
      
      Node* cur = _root;
      Node* parent = _root;
      while(cur)
      {
        if(cur->_key > key)
        {
          parent = cur;
          cur = cur->_left; 
        }
        else if(cur->_key < key)
        {
          parent = cur;
          cur = cur->_right;
        }
        else  //这里不对重复元素进行插入
        {
          return false;    
        }
      }
      
      cur = new Node(key);
      //这里千万别忘了，要链接parent结点和子结点，否则无法通过parent访问到子结点
      if(parent->_key > key)
        parent->_left = cur;
      else
        parent->_right = cur;

      return true;
    }
    
    void _InOrder(Node* root)
    {
      if(root == nullptr)
        return;
      _InOrder(root->_left);
      cout << root->_key << " ";
      _InOrder(root->_right);
    }

    void InOrder()
    {
      //这里使用子函数的目的：为了传_root这个成员变量。因为类外面无法传_root，所以只能通过调用Inorder，Inorder再向子函数传_root
      _InOrder(_root);
      cout << endl;
    }

    bool Find(const K& key)
    {
      Node* cur = _root;
      while(cur)
      {
        if(key < cur->_key)
          cur = cur->_left;
        else if(key > cur->_key)
          cur = cur->_right;
        else
          return true;
      }
      return false;
    }

    bool Erase(const K& key)
    {
      if(_root == nullptr)
          return false;
      //先查找，再删除
      Node* cur = _root;
      Node* parent = cur;
      while(cur)
      {
        if(key < cur->_key)
        {
          parent = cur;
          cur = cur->_left;
        }
        else if(key > cur->_key)
        {
          parent = cur;
          cur = cur->_right;
        }
        else
        {
          break;
        }
      }
      //没找到
      if(cur == nullptr)
        return false;
      
      //开始删除
      if(cur->_left == nullptr)
      {
        //判断要删除的结点是否为根节点
        if(_root == cur)
          _root = cur->_right;
     
        //判断 cur结点在 父节点 的左边还是右边
        if(parent->_left == cur)
          parent->_left = cur->_right;
        else 
          parent->_right = cur->_right;
      }
      else if(cur->_right == nullptr)
      {
        if(_root == cur)
          _root = cur->_left;
      
        if(parent->_left == cur)
          parent->_left = cur->_left;
        else 
          parent->_right = cur->_left;
      }
      else //左右均不为nullptr
      {
        //从右子树总找最小的值进行替换，然后删除掉该值
        parent = cur;
        Node* subParent = cur;
        cur = cur->_right;
        while(cur->_left)
        {
          subParent = cur;
          cur = cur->_left; //右子树中的最小值，不断地访问_left即可。
        }
      
        parent->_key = cur->_key;
        if(parent->_right == cur)
          parent->_right = cur->_right;
        else 
          subParent->_left = cur->_right;
      }
      delete cur;
    }

  private:
    BSTreeNode<K>* _root;
};
