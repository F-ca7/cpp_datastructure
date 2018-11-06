#include "../data structure/btree.cpp"
#include <iostream>

using namespace std;

int main()
{
	BTree<char> b("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	b.Disp();
	cout << "先序遍历递归算法：" << endl;
	b.PreOrderRecur();
	cout << "先序遍历非递归算法：" << endl;
	b.PreOrder();
	cout << "后序遍历递归算法：" << endl;
	b.PostOrderRecur();
	cout << "后序遍历非递归算法：" << endl;
	b.PostOrder();
	cout << "中序遍历递归算法：" << endl;
	b.InOrderRecur();
	cout << "中序遍历非递归算法：" << endl;
	b.InOrder();

	cout << "层序遍历算法：" << endl;
	b.LevelOrder();
	cin.get();
    return 0;
}

