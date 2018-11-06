#include "../data structure/btree.cpp"
#include <iostream>
using namespace std;
int main()
{
	BTree<char> b("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	b.Disp();

	cout << "\nH结点的左、右孩子结点值:" << endl;
	b.PrintChildren('H');

	cout << "b的高度：" << b.Height() << endl;
	
	cin.get();
	//释放二叉树交给析构函数

}
