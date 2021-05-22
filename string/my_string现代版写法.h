#pragma once

//ֻ�����Դ���� ����+����+��������+operator=

////�ɰ�
//namespace wqj
//{
//	class string
//	{
//	public:
//		//���캯��
//		string(const char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//
//		//�������캯��
//		string(const string& s)
//			:_str(new char[strlen(s._str) + 1])
//		{
//			strcpy(_str, s._str);
//		}
//
//		//operator=
//		string& operator=(const string& s)
//		{
//			if (this != &s)
//			{
//				char* tmp = new char[strlen(s._str) + 1];
//				strcpy(tmp, s._str);
//				delete[] _str;
//				_str = tmp;
//			}
//			return *this;
//		}
//
//		//��������
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//	private:
//		char* _str;
//	};
//
//
//	void test_string1()
//	{
//		string s1("Hello");
//		string s2 = "world";
//		string s3 = s2;
//
//	}
//}



//�ִ���д��
namespace wqj
{
	class string
	{
	public:
		//���캯��
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
		}

		//string s2(s1) ��������
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
		}

		////operator=
		//string& operator=(const string& s)
		//{
		//	string tmp(s);
		//	swap(_str, tmp._str);
		//	return *this;
		//}

		//operator=			--->������
		string& operator=(string s)
		{
			swap(_str, s._str);
			return *this;
		}

		//��������
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
	private:
		char* _str;
	};


	void test_string1()
	{
		string s1("Hello");
		string s2 = "world";
		string s3 = s2;

		
	}
}