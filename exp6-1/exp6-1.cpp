#include <iostream>
#include "../data structure/tsmatrix.cpp"
using namespace std;
int main()
{
	int a[4][4] = { {1,0,3,0},{0,1,0,0},{0,0,1,0},{0,0,1,1} };
	int b[4][4] = { {3,0,0,0},{0,4,0,0},{0,0,1,0},{0,0,0,2} };

	TSMatrix<int> tsm_a((int *)a, 4, 4);
	TSMatrix<int> tsm_b((int *)b, 4, 4);
	tsm_a.DispMat();
	//tsm1.SetElem(1, 3, 15);

	cout << "对a进行转置后:" << endl;
	tsm_a.Transpose().DispMat();

	cout << "输出a+b的三元组:" << endl;
	(tsm_a + tsm_b).DispMat();

	cout << "输出a*b的三元组:" << endl;
	(tsm_a * tsm_b).DispMat();
}