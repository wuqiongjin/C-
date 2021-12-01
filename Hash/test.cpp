#include <iostream>
using namespace std;
#include "HashTable.h"
#include <vector>
//#include <string>
#include "MyUnordered_Map.h"
#include "MyUnordered_Set.h"
#include "bitset.h"
#include "BloomFilter.h"

//template <class T>
//class Vape
//{
//public:
//	Vape()
//	{
//		cout << "1" << endl;
//	}
//
//	void push_back(const T& x)
//	{
//		_v.push_back(x);
//	}
//private:
//	vector<int> _v = vector<int>(10, 1);
//};

int main()
{
	//vector<int> v1(10, 0);		//✔
	//vector<int> v2 = (10, 1);		//✖
	
	//Vape<int>().func(1);
	//Vape<int> v;
	//v.push_back(1);

	//CLOSE_HASH::test_HashTable();
	//OPEN_HASH::test_OPHashTable();
	//OPEN_HASH::test_OPHashTable2();
	//wqj_umap::test_MyUnordered_Map();
	//wqj_uset::test_MyUnordered_Set();
	//wqj_bitset::test_bitset();
	wqj_bloomf::test_bloomf();
	return 0;
}