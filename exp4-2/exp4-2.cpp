#include "../data structure/listring.cpp"
#include <iostream>
using namespace std;
int main()
{

	LiString s("abcdefghijklmn");
	LiString s1("xyz");
	s.DispStr();
	cout << "s的长度：" << s.StrLength() << endl;

	cout << "在串s的第9个字符位置插入串s1产生的s2：";
	LiString s2;
	s2 = s.InsStr(9, s1);
	s2.DispStr();

	cout << "删除串s的第2个字符位置开始的5个字符产生的s2：";
	s2 = s.DelStr(2, 5);
	s2.DispStr();

	cout << "将串s的第2个字符位置开始的5个字符替换成s1而产生的s2：";
	s2 = s.RepStr(2, 5, s1);
	s2.DispStr();

	cout << "提取串s的第2个字符位置开始的10个字符而产生的s3：";
	LiString s3 = s.SubStr(2, 10);
	s3.DispStr();

	cout << "将串s1和串s2连接起来而产生的串s4：";
	LiString s4 = LiString::Concat(s1,s2);
	s4.DispStr();
	cin.get();
	return 0;

}

