#pragma once
#include <vector>
#include <string>

////闭散列 - 线性探测/二次探测
//namespace CLOSE_HASH
//{
//	enum State
//	{
//		EMPTY,
//		EXITS,
//		DELETE
//	};
//
//	template <class V>
//	struct HashData
//	{
//		V _data = V();
//		State _state = EMPTY;
//	};
//
//	template <class K, class Value, class KeyOfValue>
//	class HashTable
//	{
//		typedef HashData<Value> HashData;
//	public:
//		bool Insert(const Value& data)
//		{
//			//扩容
//			//负载因子大于等于0.7的时候进行扩容
//			if (_tables.size() == 0 || _nums * 10 / _tables.size() >= 7)
//			{
//				//HashTable* newht = new HashTable;
//				HashTable<K, Value, KeyOfValue> newht;
//				size_t newSize = _tables.size() == 0 ? 10 : 2 * _tables.size();
//				newht._tables.resize(newSize);
//
//				for (size_t i = 0; i < _tables.size(); ++i)
//				{
//					if (_tables[i]._state != EMPTY)
//						newht.Insert(_tables[i]._data);
//				}
//				_tables.swap(newht._tables);
//			}
//
//			//除留余数法
//			KeyOfValue kofv;
//			size_t index = kofv(data) % _tables.size();
//			while (_tables[index]._state == EXITS)
//			{
//				if (kofv(_tables[index]._data) == kofv(data))	//重复元素插入失败
//					return false;
//
//				++index;
//				if (index >= _tables.size())
//					index = 0;
//			}
//
//			_tables[index]._state = EXITS;
//			_tables[index]._data = data;
//			++_nums;
//			return true;
//		}
//
//		HashData* Find(const K& key)
//		{
//			KeyOfValue kofv;
//			size_t index = key % _tables.size();
//			while (_tables[index]._state != EMPTY)
//			{
//				if (kofv(_tables[index]._data) == key)
//				{
//					if (_tables[index]._state == EXITS)
//						return &_tables[index];
//					else if (_tables[index]._state == DELETE)
//						return nullptr;
//				}
//
//				++index;
//				if (index >= _tables.size())
//					index = 0;
//			}
//			return nullptr;
//		}
//
//	private:
//		//vector<int> _data1(10, 0);			//✖
//		//vector<int> _data2 = (10, 0);		//✖
//
//		vector<HashData> _tables;	//初始值给10个
//		size_t			 _nums = 0;
//	};
//
//	template<class K>
//	struct SetKeyOfValue
//	{
//		const K& operator()(const K& key)
//		{
//			return key;
//		}
//	};
//
//	void test_HashTable()
//	{
//		HashTable<int, int, SetKeyOfValue<int>> ht;
//		ht.Insert(5);
//		ht.Insert(15);
//		ht.Insert(25);
//		ht.Insert(6);
//		ht.Insert(16);
//		ht.Insert(26);
//		ht.Insert(7);
//		ht.Insert(17);
//	}
//}


//开散列 (链地址法)
namespace OPEN_HASH
{
	template <class Value>
	struct HashNode
	{
		Value _data;
		HashNode<Value>* _next;

		HashNode(const Value& data)
			:_data(data),
			 _next(nullptr)
		{}
	};


	//为了解决传string类型、自定义类型时，无法计算kofv(data)这个值的问题， 
	//我们可以通过仿函数，让使用者自己传计算"映射值"的方法
	//##kofv(data) % _tables.size()，必须保证kofv(data)是整形才能算。如果是string，kofv(data)就是string类型了。
	template <class K>
	struct _Hash
	{
		const K& operator()(const K& k)
		{
			return k;
		}
	};
	//模板的特化，将string类型也设置为默认处理类型，
	//下次传string时，就会优先调用这里的计算"映射值"的方法了
	template<>
	struct _Hash<string>
	{
		size_t operator()(const string& k)
		{
			size_t hash = 0;
			for (size_t i = 0; i < k.size(); ++i)
			{
				hash = hash * 131 + k[i];
			}
			return hash;
		}
	};


	//这里需要"前置声明"一下，因为下面的迭代器中的成员变量有HashTable
	template <class K, class Value, class KeyOfValue, class Hash = _Hash<K>> //声明写了缺省，定义就可以不用写了。声明不写，定义不能写!
	class HashTable;															
	//哈希表迭代器
	template <class K, class Value, class KeyOfValue, class Hash = _Hash<K>>
	struct __HashIterator
	{
		typedef HashNode<Value> Node;
		typedef __HashIterator<K, Value, KeyOfValue, Hash> Self;

		typedef HashTable<K, Value, KeyOfValue> HT;

		Node* _node;
		//为了访问到里面的vector，这样就不用传参了。
		HT* _pht;	//vector还是私有成员，因此需要在HashTable中设置友元关系

		__HashIterator(Node* node, HT* pht)
			:_node(node),
			 _pht(pht)
		{}
		
		Value& operator*()
		{
			//>>>理解一下，防止混淆
			//这里返回的是value不是key，所以不用KeyOfValue。set访问到的就是key值，map访问到的是pair<Key, Value>
			return _node->_data;
		}

		Value* operator->()
		{
			return &(_node->_data);
		}
		
		Self& operator++()
		{
			Node* cur = _node;
			if (_node->_next)
			{
				_node = _node->_next;
				return *this;
			}
			else
			{
				//这里需要挪动到下一个指向不为nullptr的哈希桶中！
				KeyOfValue kofv;
				Hash hash;
				size_t index = hash(kofv(_node->_data)) % _pht->_tables.size();
				++index;
				for (; index < _pht->_tables.size(); ++index)
				{
					Node* cur = _pht->_tables[index];
					if (cur)
					{
						_node = cur;
						return *this;
					}
				}
				_node = nullptr;
			}	
			return *this;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}
	};

											//class Hash = _Hash<K>，我们在前面对HashTable的声明处给了缺省值了，这里就不用我们自己再写了
	template <class K, class Value, class KeyOfValue, class Hash>	//_Hash设置缺省
	class HashTable
	{
		friend struct __HashIterator<K, Value, KeyOfValue, Hash>;	//为了让迭代器的++中能访问到vector数组
		typedef HashNode<Value> Node;
	public:
		typedef __HashIterator<K, Value, KeyOfValue, Hash> iterator;
	public:
		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i] != nullptr)
				{
					return iterator(_tables[i], this);
				}
			}
			return iterator(nullptr, this);
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		size_t GetNextPrime(size_t sz)
		{
			//下面的素数表是给定的，每个相邻数据都是接近2倍关系的
			const int PRIMECOUNT = 28;
			const static size_t primeList[PRIMECOUNT] =
			{
			 53ul, 97ul, 193ul, 389ul, 769ul,
			 1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			 49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			 1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			 50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			 1610612741ul, 3221225473ul, 4294967291ul
			};
			
			for (int i = 0; i < PRIMECOUNT; ++i)
			{
				if (primeList[i] > sz)
					return primeList[i];
			}
			return primeList[PRIMECOUNT - 1];
		}

		pair<iterator, bool> Insert(const Value& data)
		{
			Hash hash;
			KeyOfValue kofv;
			//增容标准 - 负载因子大于等于1的时候进行增容
			if (_num >= _tables.size())
			{
				//HashTable<K, Value, KeyOfValue> newht;
				vector<Node*> newtables;
				//size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				size_t newSize = GetNextPrime(_tables.size());	//除留余数法，最好模上一个素数.
				newtables.resize(newSize);

				//遍历旧表，将旧表中的每个哈希桶的数据都放入新表中. #还需要计算新的放入位置
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;	//用next存一下cur的next，因为下面要修改cur的值
						size_t newIndex = hash(kofv(cur->_data)) % newSize;
						
						//直接进行头插，(这里就体现出了头插的方便，不用在新开的表中继续找到链表的尾部了
						cur->_next = newtables[newIndex];
						newtables[newIndex] = cur;

						cur = next;
					}
				}

				//新表的数据迁移完成后，交换两个表
				newtables.swap(_tables);
			}

			size_t index = hash(kofv(data)) % _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (kofv(cur->_data) == kofv(data))
				{
					return make_pair(iterator(cur, this), false);
				}
				else
				{
					cur = cur->_next;
				}
			}

			//采用头插法,使用_tables[index]这个指针
			Node* newNode = new Node(data);
			newNode->_next = _tables[index];
			_tables[index] = newNode;
			++_num;

			return make_pair(iterator(newNode, this), true);
		}

		Node* Find(const K& key)
		{
			Hash hash;
			KeyOfValue kofv;
			size_t index = hash(key) % _tables.size();

			Node* cur = _tables[index];
			while (cur)
			{
				if (kofv(cur->_data) == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		bool Erase(const K& key)
		{
			Hash hash;
			KeyOfValue kofv;
			size_t index = hash(key) % _tables.size();

			//这里需要定义一个prev指针，因为单链表的删除操作需要2个指针
			Node* cur = _tables[index];
			Node* prev = nullptr;	//prev赋值成nullptr最好，方便下面判断头结点的删除
			while (cur)
			{
				if (kofv(cur->_data) == key)
				{
					//说明删除的结点是头结点
					if (prev == nullptr)
					{
						delete cur;
						_tables[index] = nullptr;
						return true;
					}

					//删除结点
					prev->_next = cur->_next;
					delete cur;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

		~HashTable()
		{
			this->Clear();
		}

		void Clear()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

	private:
		vector<Node*> _tables;		//_tables是一个结构体指针数组
		size_t _num = 0;
	};

	//template <class K>
	//struct SetKeyOfValue
	//{
	//	const K& operator()(const K& key)
	//	{
	//		return key;
	//	}
	//};

	//void test_OPHashTable()
	//{
	//	HashTable<int, int, SetKeyOfValue<int>> ht;
	//	ht.Insert(3);
	//	ht.Insert(13);
	//	ht.Insert(23);
	//	ht.Insert(4);
	//	ht.Insert(14);
	//	ht.Insert(24);
	//	ht.Insert(5);
	//	ht.Insert(6);
	//	ht.Insert(16);
	//	ht.Insert(26);
	//	ht.Insert(36);

	//	ht.Erase(23);
	//	ht.Find(23);
	//}

	//void test_OPHashTable2()
	//{
	//	HashTable<string, string, SetKeyOfValue<string>> ht;

	//	ht.Insert("sort");
	//	ht.Insert("fly");
	//	ht.Insert("define");
	//	ht.Insert("false");
	//	ht.Insert("true");

	//	HashTable<string, string, SetKeyOfValue<string>>::iterator it = ht.begin();
	//	while (it != ht.end())
	//	{
	//		cout << *it << endl;;
	//		++it;
	//	}
	//}
}