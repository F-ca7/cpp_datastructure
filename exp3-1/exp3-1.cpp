#include "../data structure/sqstack.cpp"
#include <iostream>
using namespace std;
int main() {
	Sqstack<char> stack;
	cout << "依次入栈a,b,c,d,e：\n";
	for (int i = 0; i < 5; i++) {
		stack.Push((char)('a' + i));
	}
	cout << "栈是否为空：" << boolalpha << stack.IsEmpty() << endl;
	cout << "出栈序列：\n";
	char temp;
	while (stack.Pop(temp)){
		cout << temp << " ";
	}
	cout << "\n栈是否为空：" << boolalpha << stack.IsEmpty() << endl;
	//while (!stack.IsEmpty()) {
	//	temp = stack.Pop();
	//	cout << temp << " ";
	//}
	return 0;
}