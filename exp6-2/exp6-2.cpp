#include <iostream>
#include "../data structure/generalList.cpp"
using namespace std;
int main()
{
	cout << "输出广义表g：" << endl;
	GeneralList<char> g("(b,(b,a,(#),d),((a,b),c,((#))))");
	g.Disp();

	cout << "g的长度：" << g.Length() << endl;
	cout << "g的深度：" << g.Depth() << endl;
	cout << "g的最大原子：" << g.MaxElem() << endl;

	cin.get();
}

