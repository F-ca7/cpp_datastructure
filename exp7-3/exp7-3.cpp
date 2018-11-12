#include "../data structure/btree.cpp"
#include <iostream>
using namespace std;
class TreeUtil {
private:
	static BTNode<char>* CreateHelp1(const char* pre, const char* in, int n) {
		if (n <= 0)
			return nullptr;
		BTNode<char>* root = new BTNode<char>(pre[0]);
		int i = 0;
		while (i < n)
		{
			if (in[i] == pre[0])
				break;
			i++;
		}
		root->lchild = CreateHelp1(pre + 1, in, i);
		root->rchild = CreateHelp1(pre + i + 1, in + i + 1, n - i - 1);
		return root;
	}

	static BTNode<char>* CreateHelp2(const char* post, const char* in, int n) {
		if (n <= 0)
			return nullptr;
		BTNode<char>* root = new BTNode<char>(post[n-1]);
		int i = 0;
		while (i < n)
		{
			if (in[i] == post[n-1])
				break;
			i++;
		}
		root->lchild = CreateHelp2(post, in, i);
		root->rchild = CreateHelp2(post + i, in + i + 1, n - i - 1);
		return root;
	}
public:

	//用先序和中序构造树
	static BTree<char> CreateBT1(const char* pre, const char* in) {
		BTree<char> b;
		b.root = CreateHelp1(pre, in, strlen(pre));
		return b;
	}

	//用后序和中序构造树
	static BTree<char> CreateBT2(const char* post, const char* in) {
		BTree<char> b;
		b.root = CreateHelp2(post, in, strlen(post));
		return b;
	}

	//用凹入法输出
	static void Disp2(BTree<char> &b) {
		if (b.root == nullptr) {
			cout << "Empty tree!" << endl;
			return;
		}
		struct MarkedNode
		{
			BTNode<char>* node;
			int type;		//记录左右结点，0左，1右
			int level;		//记录层数
		};
		MarkedNode mNode;		//保存临时带标记结点
		BTNode<char>* p = nullptr;	//保存临时结点
		char type;				//输出结点类型
		Sqstack<MarkedNode> st;
		cout.setf(ios::left);	//设置输出格式
		st.Push({ b.root,-1,0 });			//入栈
		while (!st.IsEmpty())
		{
			mNode = st.Pop();
			p = mNode.node;
			switch (mNode.type)
			{
				case -1:
					type = 'B';
					break;
				case 0:
					type = 'L';
					break;			
				case 1:
					type = 'R';
					break;
				default:
					break;
			}
			for (int i = 0; i < mNode.level; i++) {
				cout << "    ";
			}
			cout << p->data << "(" << type;
			cout.width(50 - 4 * (mNode.level + 1));							//格式化输出
			cout.fill('-');
			cout << ")" << endl;
			if (p->rchild != nullptr) {	//先右后左
				st.Push({ p->rchild, 1, mNode.level + 1 });
			}
			if (p->lchild != nullptr) {	//先右后左
				st.Push({ p->lchild, 0, mNode.level + 1 });
			}
		}
	}
};


int main()
{
	const char* strPre  = "ABDEHJKLMNCFGI";
	const char* strIn   = "DBJHLKMNEAFCGI";
	const char* strPost = "DJLNMKHEBFIGCA";
	cout << "先序序列: " << strPre << endl;
	cout << "中序序列: " << strIn << endl;
	cout << "二叉树的括号表示: " << endl;
	BTree<char> t1 = TreeUtil::CreateBT1(strPre, strIn);
	t1.Disp();
	cout << "二叉树的凹入表示: " << endl;
	TreeUtil::Disp2(t1);
	cout << "后序序列: " << strPost << endl;
	cout << "中序序列: " << strIn << endl;
	cout << "二叉树的括号表示: " << endl;
	BTree<char> t2 = TreeUtil::CreateBT2(strPost, strIn);
	t2.Disp();


}
