#pragma once

//string���ģ��ʵ��

//����ɾ��ĵ�string��
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
//			:_str(new char[strlen(str) + 1])	//ע�⣺strlen������stringʱ�����������Ϊֹͣ������\0
//		{
//			strcpy(_str, str);
//		}*/
//
//		//���캯��
//		//ͬʱ����˶Կմ�string�Ĺ��� �� ����һ���ַ�������string
//		string(const char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//
//		//�������캯��
//		string(const string& s)
//			//:_str(new char[strlen(s._str) + 1])
//			:_str(new char[s.size()])
//		{
//			//s.size();  Ϊʲô���÷��ʣ� ������size�����Ĳ�������const���ͣ�������޷�ȥ����s��s.size()����Ϊs��const
//			//�����Ҫȥ���ʾ�����Ȩ�޵ķŴ�
//			strcpy(_str, s._str);
//		}
//
//		//operator=��ģ��ʵ��		��ֵ���������
//		string& operator=(const string& s)//this -> string* this ע�����ͣ�����
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
//		size_t size() const//�����const�������s.size()�Ϳ��Է�����
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
//		string s5 = s2;	//���ÿ������캯��
//
//		s2 = s5;		//����operator=��ֵ���������
//		for (size_t i = 0; i < s5.size(); ++i)
//		{
//			cout << s5[i] << " ";
//		}
//	}
//}




//��ɾ��� �汾��string
namespace wqj
{
	class string
	{
	public:
		typedef char* iterator;

		//���캯��
		string(const char* str = "")
		{
			_size = strlen(str);	//size�Ǳ�ʾĿǰstr���ж��ٸ���Ч�ַ�
			_capacity = _size;		//capacity��ʾstring������ܴ洢���ٸ���Ч�ַ�
			char* tmp = new char[_capacity + 1];	//'\0'��������Ч�ַ�����˼���capacityʱ���ܰ����������Կ��ٿռ�ʱ��Ҫ�࿪��1��
			_str = tmp;
			strcpy(_str, str);
		}

		//�������캯��
		string(const string& s)
		{
			_size = strlen(s._str);
			_capacity = _size;
			char* tmp = new char[_capacity + 1];
			_str = tmp;
			strcpy(_str, s._str);
		}

		//��ֵ���������
		string& operator=(const string& s)// string* this, const string& s
		{
			if (this != &s)//���ﲻ��дΪ	*this != s   ��Ϊ*this != s����string���͵�!=�����㣬��Ϊ����û��string���͵��������� (�Լ���ûд)
			{
				char* tmp = new char[s.size() + 1];//char* tmp = new char[strlen(s._str) + 1]
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_size = s._size;
				_capacity = s._capacity;
			}				//��this != &s���ǿ��Եġ���Ϊ�������ڵ�ַ֮��ıȽ�
			return *this;	//this��������string*
		}

		//operator[]
		char operator[](size_t i)//operator[]��Ҫ�����±����ȥ����
		{
			return _str[i];
		}

		//const����operator[]
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

		//��������
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//��ɾ���

		//��
		//���ݺ���reserve	��������������ĺ�������Ҫ���󵽶��ٵĴ�С��
		void reserve(size_t newcapacity)
		{
			//�ж�һ�£���ֹ����ֱ�ӵ���reserve (����ͨ��push_back��append���õ�)
			if (newcapacity > _capacity)
			{
				char* tmp = new char[newcapacity + 1];	//�����������new���������ʲô���캯��(������г�ʼ��)����Ϊchar���������ͣ���������������
				//memset(tmp, 0, sizeof(char)*(newcapacity + 1));
				strcpy(tmp, _str);

				// �ͷ�ԭ���ɿռ�,Ȼ��ʹ���¿ռ�
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
				reserve(newcapacity);	//����ĸ���

				//char* tmp = new char[newcapacity + 1];
				//_capacity = newcapacity;

				//strcpy(tmp, _str);
				//delete[] _str;
				//_str = tmp;
			}

			//�����Ƿ���Ҫ���ݣ���Ҫ��������ַ��Ĳ���
			_str[_size] = ch;
			++_size;
	//����������������������������������������������������������������������������������������������������������������������������
			_str[_size] = '\0';		//�����\0����Ҫ��ӡ�����������ַ�����Ӻ�ͻὫ֮ǰ�����1��λ�õ��ַ����ǣ������λ����\0�Ļ�����ô�ַ����е�\0��û�ˡ�����
	//����������������������������������������������������������������������������������������������������������������������������
		}

		void append(const char* str)
		{
			int len = strlen(str);
			if (_size + len > _capacity)
			{
				//size_t newcapacity = _size + len;//��������_size + len �� ���ܸ����� 2 * _capacity���������֣���Ϊ�п���2*_capacityҲ��������
				//char* tmp = new char[newcapacity + 1];
				//_capacity = newcapacity;

				//strcpy(tmp, _str);
				//delete[] _str;
				//_str = tmp;

				reserve(_size + len);
			}

			//�����Ƿ���Ҫ���ݣ���Ҫ����׷���ַ����Ĳ���
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

		//��posλ�ò����ַ�ch/�ַ���str�������ظ��ַ���λ��
		string& insert(size_t pos, char ch)
		{
			assert(pos >= 0 && pos < _size);
			//���������
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 1 : _capacity * 2;
				//char* tmp = new char[newcapacity];
				//memmove(tmp, _str, _capacity * sizeof(char));
				//_capacity = newcapacity;
				//_str = tmp;
				reserve(newcapacity);	//ֱ�ӵ���reserve��������
			}
			//���в������
			int end = _size;
			while (end > (int)pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			++_size;
			//ע�ⲻҪ���ˣ�������������'\0'
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
				reserve(_size + len);	//ֱ�ӵ���reserve��������
			}
			//Ų������
			//H e l l o \0
			//0 1 2 3 4 5
			//H B C D E F e l l o \0
			//0 1 2 3 4 5 6 7 8 9 10
			int end = _size;	//ע�⣡Ҫ��\0Ҳ�����ߡ���Ȼ�Լ�Ҳ���ֶ����
			while ( end >= (int)pos)	//ҲҪ��pos��������Ų�� !!!!!!!!!!! posҪǿתΪint���ͣ���Ȼend����size_t������0λ�ò�������
			{
				_str[end + len] = _str[end];	
				--end;
			}
			//��������
			//memcpy(_str + pos, str, sizeof(char)*len);
			memmove(_str + pos, str, sizeof(char)* len);

			_size += len;
			return *this;
		}

		//�ı�string�Ĵ�Сsize���������n������chȥ����Ĳ��֣�����chĬ�����\0����С��n�Ļ������ǽض��ַ���
		void resize(size_t n, char ch = '\0')//������2����ʽ������ch�ĺʹ�ch��
		{
			assert(n >= 0);
			//2�����
			//Hello 5
			//resize(8) ����5
			//resize(3) С��5
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

		//ɾ��ָ��λ�õ�ֵ [ɾ����λ�õ�ֵ��  ��Ӧ���±�!!!]
		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			//���ɾ���ĳ��� > posλ�ú���ĳ���
			if (pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				//���С�� pos����ĳ��ȣ�����ɾ��
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
			char* pos = strstr(_str, str);	//����ƥ���λ�õ�ָ��
			if (pos)
			{
				return pos - _str;
			}
			else
				return npos;
		}

	private:
		//friend ostream& operator<<(ostream& out, const string& s); //û��Ҫʹ����Ԫ��������Ϊ��û�з���˽�г�Ա������
		friend istream& operator>>(istream& in, string& s);
	private:
		char*     _str;
		size_t	  _size;	//string���Ѿ��ж�����Ч�ַ�
		size_t    _capacity;//string������ܴ���ٸ���Ч�ַ� ������\0��\0������Ч�ַ���
		static size_t npos;
	};

	static size_t npos = -1;

	//��Ҫʹ����Ԫ����ʱ��ʹ��
	//����cout <<	<<û��ʹ��˽�г�Ա��������˿��Բ���д����Ԫ������
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			cout << s[i];
		}
		return out;
	}

	//����ʵ��cin >>
	istream& operator>>(istream& in, string& s)
	{
		while (1)
		{
			char ch;
			in.get(ch);	//istream���У�get�ǻ�ȡһ��
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
		string s1;		   //���캯��
		string s2("Hello");//���캯��
		string s3(s2);	//�������캯��
		string s4 = s2; //�������캯��
	
		//s1 = s2;		//��ֵ���������

		cout << s1 << endl;
		cout << s3 << endl;
		cout << s4.c_str() << endl;
		
		cin >> s2;	

		/*s2 += "World";
		s2 += '!';*/

		s1 += "Hello";	//׷��"Hello"ʱ��˳����Ҳ��Hello�е�\0׷�ӵ�������
		s1 += ' ';		//������ַ�ʱ���������\0��������Ҫ�Լ��ֶ���_str[_size]������\0������ͻ����û��\0��Խ�����
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