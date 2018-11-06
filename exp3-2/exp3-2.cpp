#include <iostream>
#include "../data structure/listack.cpp"
using namespace std;

int main()
{
	Listack<char> stack;
	cout << "依次入栈a,b,c,d,e：\n";
	for (int i = 0; i < 5; i++) {
		stack.Push((char)('a' + i));
	}
	cout << "栈是否为空：" << boolalpha << stack.IsEmpty() << endl;
	cout << "出栈序列：\n";
	char temp;
	while (stack.Pop(temp)) {
		cout << temp << " ";
	}	
	//while (!stack.IsEmpty()) {
	//	temp = stack.Pop();
	//	cout << temp << " ";
	//}
	cout << "\n栈是否为空：" << boolalpha << stack.IsEmpty() << endl;
	return 0;
}