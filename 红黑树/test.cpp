#include "RBTree.h"

void TestRBTree()
{
	RBTree<int, int> t;
	//int a[] = { 16,3,7,11,9,26,18,14,15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	for (auto e : a)
		t.Insert(make_pair(e, e));


	t.InOrder();
	cout << t.IsValidRBTree() << endl;
}

int main()
{
	TestRBTree();
	return 0;
}