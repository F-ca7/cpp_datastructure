#include <iostream>
#include "../data structure/liqueue.cpp"
using namespace std;
int main()
{
	Liqueue<char> queue;
	char temp;
	cout << "队列是否为空：" << boolalpha << queue.IsEmpty() << endl;
	cout << "进队a,b,c:\n";
	queue.Enqueue('a');
	queue.Enqueue('b');
	queue.Enqueue('c');
	queue.Dequeue(temp);
	cout << "出队元素：" << temp << endl;
	cout << "进队d,e,f:\n";
	queue.Enqueue('d');
	queue.Enqueue('e');
	queue.Enqueue('f');
	cout << "出队序列：\n";
	while (queue.Dequeue(temp)) {
		cout << temp << " ";
	}
}