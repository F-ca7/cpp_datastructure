#include "../data structure/dlinklist.cpp"
#include <iostream>
using namespace std;
int main()
{
	char a[] = { 'a', 'b', 'c', 'd', 'e' };
	int size = sizeof(a) / sizeof(a[0]);
	DLinkList<char> list(a, size);
	char temp;
	list.DispList();
	cout << "双链表长度：" << list.Length() << endl;
	cout << "双链表是否为空：" << boolalpha << list.IsEmpty() << endl;
	list.GetElem(3, temp);
	cout << "双链表第3个元素：" << temp << endl;
	cout << "双链表中a的位置：" << list.LocateElem('a') << endl;
	cout << "在双链表第4个位置插入f：" << endl;
	list.ListInsert(4, 'f');
	list.DispList();
	cout << "删除双链表第3个元素：" << endl;
	list.ListDelete(3, temp);
	list.DispList();
	cin.get();
}