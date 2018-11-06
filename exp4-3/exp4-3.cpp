#include <iostream>
#include "../data structure/sqstring.cpp"
using namespace std;


int main(){
	SqString s("abcabcdabcdeabcdefabcdefg");
	SqString t("abcdeabcdefab");
	cout << "字符串s: ";
	s.DispStr();
	cout << "字符串t: " ;
	t.DispStr();
	cout << "简单匹配算法：" << endl;
	cout << "t在s的位置：" << s.BFmatch(t)<<endl;
	cout << "KMP匹配算法：" << endl;
	cout << "t在s的位置：" << s.KMPIndex(t) << endl;
	cout << "改进后的KMP匹配算法：" << endl;
	cout << "t在s的位置：" << s.newKMPIndex(t) << endl;
	cin.get();
}