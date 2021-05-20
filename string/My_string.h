#pragma once

//string类的模拟实现

//无增删查改的string类
//namespace wqj
//{
//	class string
//	{
//	public:
//		/*string()
//			:_str(new char[1])
//		{
//			_str[0] = '\0';
//		}
//
//		string(const char* str)
//			:_str(new char[strlen(str) + 1])	//注意：strlen遇到空string时，他会出错。因为停止条件是\0
//		{
//			strcpy(_str, str);
//		}*/
//
//		//构造函数
//		//同时完成了对空串string的构造 和 根据一个字符串构造string
//		string(const char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//
//		//拷贝构造函数
//		string(const string& s)
//			//:_str(new char[strlen(s._str) + 1])
//			:_str(new char[s.size()])
//		{
//			//s.size();  为什么不让访问？ 如果你的size函数的参数不是const类型，这里就无法去访问s的s.size()，因为s是const
//			//如果你要去访问就属于权限的放大
//			strcpy(_str, s._str);
//		}
//
//		//operator=的模拟实现		赋值运算符重载
//		string& operator=(const string& s)//this -> string* this 注意类型！！！
//		{
//			if (this != &s)		
//			{
//				char* tmp = new char[s.size()];
//				strcpy(tmp, s._str);//char*, char*
//				delete[] _str;
//				_str = tmp;
//			}
//			return *this;
//		}
//
//		size_t size() const//后加了const，上面的s.size()就可以访问了
//		{
//			return strlen(_str) + 1;
//		}
//
//		char& operator[](size_t i)
//		{
//			return _str[i];
//		}
//
//		char* c_str()
//		{
//			return _str;
//		}
//
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//
//	private:
//		char* _str;
//	};
//
//	void test_string1()
//	{
//		//string s1;
//		string s2("Hello");
//		//string s3(s2);
//		//string s4 = s2;
//
//		//for (size_t i = 0; i < s2.size(); ++i)
//		//{
//		//	cout << s2[i] << " ";
//		//}
//
//		//cout << endl;
//
//		//for (size_t i = 0; i < s3.size(); ++i)
//		//{
//		//	cout << s3[i] << " ";
//		//}
//
//		//cout << endl;
//
//		//for (size_t i = 0; i < s4.size(); ++i)
//		//{
//		//	cout << s4[i] << " ";
//		//}
//		//std::cout << s2.c_str() << std::endl;
//	
//		string s5 = s2;	//调用拷贝构造函数
//
//		s2 = s5;		//调用operator=赋值重载运算符
//		for (size_t i = 0; i < s5.size(); ++i)
//		{
//			cout << s5[i] << " ";
//		}
//	}
//}




//增删查改 版本的string
namespace wqj
{
	class string
	{
	public:
		typedef char* iterator;

		//构造函数
		string(const char* str = "")
		{
			_size = strlen(str);	//size是表示目前str中有多少个有效字符
			_capacity = _size;		//capacity表示string中最多能存储多少个有效字符
			char* tmp = new char[_capacity + 1];	//'\0'不属于有效字符，因此计算capacity时不能包括他，所以开辟空间时需要多开辟1个
			_str = tmp;
			strcpy(_str, str);
		}

		//拷贝构造函数
		string(const string& s)
		{
			_size = strlen(s._str);
			_capacity = _size;
			char* tmp = new char[_capacity + 1];
			_str = tmp;
			strcpy(_str, s._str);
		}

		//赋值运算符重载
		string& operator=(const string& s)// string* this, const string& s
		{
			if (this != &s)//这里不能写为	*this != s   因为*this != s属于string类型的!=的运算，因为我们没有string类型的这种运算 (自己还没写)
			{
				char* tmp = new char[s.size() + 1];//char* tmp = new char[strlen(s._str) + 1]
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_size = s._size;
				_capacity = s._capacity;
			}				//而this != &s就是可以的。因为这是属于地址之间的比较
			return *this;	//this的类型是string*
		}

		//operator[]
		char operator[](size_t i)//operator[]需要给定下标才能去访问
		{
			return _str[i];
		}

		//const属性operator[]
		const char operator[](size_t i)const
		{
			return _str[i];
		}
		
		//size
		size_t size() const
		{
			return _size;
		}

		//c_str
		char* c_str()
		{
			return _str;
		}

		//析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//增删查改

		//增
		//增容函数reserve	对容量进行扩大的函数（传要扩大到多少的大小）
		void reserve(size_t newcapacity)
		{
			//判断一下，防止有人直接调用reserve (不是通过push_back和append调用的)
			if (newcapacity > _capacity)
			{
				char* tmp = new char[newcapacity + 1];	//憨批，这里的new并不会调用什么构造函数(不会进行初始化)。因为char是内置类型！！！！！！！！
				//memset(tmp, 0, sizeof(char)*(newcapacity + 1));
				strcpy(tmp, _str);

				// 释放原来旧空间,然后使用新空间
				delete[] _str;
				_str = tmp;
				_capacity = newcapacity;
			}
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 1 : 2 * _capacity;
				reserve(newcapacity);	//代码的复用

				//char* tmp = new char[newcapacity + 1];
				//_capacity = newcapacity;

				//strcpy(tmp, _str);
				//delete[] _str;
				//_str = tmp;
			}

			//不管是否需要增容，都要进行添加字符的操作
			_str[_size] = ch;
			++_size;
	//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
			_str[_size] = '\0';		//这里的\0必须要添加。否则上面的字符在添加后就会将之前的最后1个位置的字符覆盖（如果该位置是\0的话，那么字符串中的\0就没了。。）
	//※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
		}

		void append(const char* str)
		{
			int len = strlen(str);
			if (_size + len > _capacity)
			{
				//size_t newcapacity = _size + len;//这里必须给_size + len 。 不能给比如 2 * _capacity这样的数字，因为有可能2*_capacity也不够。。
				//char* tmp = new char[newcapacity + 1];
				//_capacity = newcapacity;

				//strcpy(tmp, _str);
				//delete[] _str;
				//_str = tmp;

				reserve(_size + len);
			}

			//不管是否需要增容，都要进行追加字符串的操作
			strcpy(_str + _size, str);
			_size += len;
		}

		string& operator+=(char ch)
		{
			this->push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}

		//在pos位置插入字符ch/字符串str，并返回该字符的位置
		string& insert(size_t pos, char ch)
		{
			assert(pos >= 0 && pos < _size);
			//如果满容了
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 1 : _capacity * 2;
				//char* tmp = new char[newcapacity];
				//memmove(tmp, _str, _capacity * sizeof(char));
				//_capacity = newcapacity;
				//_str = tmp;
				reserve(newcapacity);	//直接调用reserve进行扩容
			}
			//进行插入操作
			int end = _size;
			while (end > (int)pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			++_size;
			//注意不要忘了！！！！！！！'\0'
			_str[_size] = '\0';
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos >= 0 && pos < _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				//size_t newcapacity = _size + len;
				//char* tmp = new char[newcapacity];
				//memmove(tmp, _str, _capacity * sizeof(char));
				//_capacity = newcapacity;
				//_str = tmp;
				reserve(_size + len);	//直接调用reserve进行扩容
			}
			//挪动数据
			//H e l l o \0
			//0 1 2 3 4 5
			//H B C D E F e l l o \0
			//0 1 2 3 4 5 6 7 8 9 10
			int end = _size;	//注意！要把\0也拷贝走。不然自己也得手动添加
			while ( end >= (int)pos)	//也要把pos处的数据挪走 !!!!!!!!!!! pos要强转为int类型，不然end会变成size_t，当在0位置插入会出错
			{
				_str[end + len] = _str[end];	
				--end;
			}
			//拷贝数据
			//memcpy(_str + pos, str, sizeof(char)*len);
			memmove(_str + pos, str, sizeof(char)* len);

			_size += len;
			return *this;
		}

		//改变string的大小size。如果大于n，则用ch去填充多的部分（不给ch默认填充\0）。小于n的话，就是截断字符串
		void resize(size_t n, char ch = '\0')//库中有2种形式，不带ch的和带ch的
		{
			assert(n >= 0);
			//2种情况
			//Hello 5
			//resize(8) 大于5
			//resize(3) 小于5
			if (n > _size)
			{
				reserve(n);
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
			}
				
			_size = n;
			_str[_size] = '\0';
		}

		//删除指定位置的值 [删除的位置的值是  对应的下标!!!]
		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			//如果删除的长度 > pos位置后面的长度
			if (pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				//如果小于 pos后面的长度，覆盖删除
				size_t end = pos + len;
				while (end <= _size)
				{
					_str[end - len] = _str[end];
					++end;
				}
				_size -= len;
			}
			return *this;
		}

		size_t find(char ch)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (_str[i] == ch)
					return i;
			}
			return npos;
		}

		size_t find(const char* str, size_t len = npos)
		{
			char* pos = strstr(_str, str);	//返回匹配的位置的指针
			if (pos)
			{
				return pos - _str;
			}
			else
				return npos;
		}

	private:
		//friend ostream& operator<<(ostream& out, const string& s); //没必要使用友元函数（因为并没有访问私有成员变量）
		friend istream& operator>>(istream& in, string& s);
	private:
		char*     _str;
		size_t	  _size;	//string中已经有多少有效字符
		size_t    _capacity;//string中最多能存多少个有效字符 （不算\0，\0不是有效字符）
		static size_t npos;
	};

	static size_t npos = -1;

	//需要使用友元函数时就使用
	//重载cout <<	<<没有使用私有成员变量，因此可以不用写如友元函数中
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			cout << s[i];
		}
		return out;
	}

	//重载实现cin >>
	istream& operator>>(istream& in, string& s)
	{
		while (1)
		{
			char ch;
			in.get(ch);	//istream流中，get是获取一行
			if (ch == ' ' || ch == '\n')
			{
				break;
			}
			else
			{
				s += ch;
			}
		}
		return in;
	}


	void test_string1()
	{
		string s1;		   //构造函数
		string s2("Hello");//构造函数
		string s3(s2);	//拷贝构造函数
		string s4 = s2; //拷贝构造函数
	
		//s1 = s2;		//赋值运算符重载

		cout << s1 << endl;
		cout << s3 << endl;
		cout << s4.c_str() << endl;
		
		cin >> s2;	

		/*s2 += "World";
		s2 += '!';*/

		s1 += "Hello";	//追加"Hello"时，顺带着也把Hello中的\0追加到里面了
		s1 += ' ';		//而添加字符时，并不会加\0。所以需要自己手动在_str[_size]处加上\0。否则就会出现没有\0的越界访问
		s1 += "world";

		cout << s1 << endl;

		//for (size_t i = 0; i < s1.size(); ++i)
		//{
		//	cout << s1[i] << " ";
		//}
		//cout << endl;

		for (size_t i = 0; i < s2.size(); ++i)
		{
			cout << s2[i] << " ";
		}
		cout << endl;
	
	}

	void test_string2()
	{
		string s("Hello");
		s.insert(1, 'A');
		s.insert(1, "BCDEF");

		s.resize(15, 'C');
		cout << s << endl;

		//s.resize(1, 'C');
		//cout << s << endl;

		s.erase(3, 2);
		cout << s << endl;
		
	}

}