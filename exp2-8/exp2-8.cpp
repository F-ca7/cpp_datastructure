#include "../data structure/linklist.cpp"
#include <iostream>
using namespace std;
int main() {
	char a[] = { 'c', 'a', 'e', 'b', 'd' };
	int size1 = sizeof(a) / sizeof(a[0]);
	LinkList<char> list1(a, size1);
	char b[] = {'a', 'g', 'd', 'f', 'h', 'c','e' };
	int size2 = sizeof(b) / sizeof(b[0]);
	LinkList<char> list2(b, size2);
	
	cout << "排序前：" << endl;
	cout << "list1：";
	list1.DispList();
	cout << "list2：";
	list2.DispList();
	
	cout << "排序后：" << endl;
	list1.Sort();
	list2.Sort();
	cout << "list1：";
	list1.DispList();
	cout << "list2：";
	list2.DispList();
	
	cout << "合并1和2：" << endl;
	LinkList<char> list3;
	LinkList<char>::Union(list1, list2,list3);
	list3.DispList();

	cout << "1和2的交集：" << endl;
	LinkList<char> list4;
	LinkList<char>::Intersect(list1, list2, list4);
	list4.DispList();
	
	cout << "1和2的减集：" << endl;
	LinkList<char> list5;
	LinkList<char>::Subtract(list1, list2, list5);
	list5.DispList();

	cout << "2和1的减集：" << endl;
	LinkList<char> list6;
	LinkList<char>::Subtract(list2, list1, list6);
	list6.DispList();

	cin.get();
	return 0;
}