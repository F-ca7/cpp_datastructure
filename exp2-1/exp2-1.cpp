#include "../data structure/sqlist.cpp"
#include <iostream>
using namespace std;
int main() {
	char a[] = { 'a','b','c','d','e' };
	int size = sizeof(a) / sizeof(a[0]);
	Sqlist<char> list(a,size);
	char tp;
	list.DispList();
	cout << "数组长度：" << list.Length() << endl;
	cout << "数组是否为空：" << boolalpha <<list.IsEmpty() << endl;
	list.GetElem(3, tp);
	cout << "数组第三个元素：" << tp << endl;
	cout << "数组元素a的位置：" << list.LocateElem('a') << endl;
	cout << "在第四个位置插入f：" << endl;
	list.ListInsert(4, 'f');
	list.DispList();

	cout << "删除第三个元素" << endl;
	list.ListDelete(3, tp);
	list.DispList();
	cin.get();
	//释放顺序表交给析构函数
	return 0;
}
