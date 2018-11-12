#include <iostream>
#include "sqstack.cpp"
#include "liqueue.cpp"

template <typename T>
class BTree;

template <typename T>
class BTNode {
	friend class BTree<T>;
	friend class TreeUtil;
public:
	T data;
	BTNode* lchild;
	BTNode* rchild;
	BTNode() {
		lchild = rchild = nullptr;
	}

	BTNode(T e, BTNode* l = nullptr, BTNode* r = nullptr) {
		data = e;
		lchild = l;
		rchild = r;
	}

	bool IsLeaf() {
		return (lchild == nullptr) && (rchild == nullptr);
	}
};

template <typename T>
class BTree {
	friend class TreeUtil;
protected:
	BTNode<T>* root;
	
	void CreateBTree(const char* str) {
		Sqstack<BTNode<T>*> st;
		BTNode<T>* p = nullptr, *top = nullptr;
		int k = 1;		//k为1时，是左孩子；k为2时，是右孩子
		int j = 0;
		char ch = str[j];
		while (ch != '\0')
		{
			switch (ch)
			{
			case '(':	//进入分支结点,从左孩子开始
				st.Push(p);
				k = 1;
				break;
			case ')':	//孩子结点结束
				st.Pop();
				break;
			case ',':
				k = 2;	//进入右孩子

			default:	//构造结点
				p = new BTNode<T>((T)ch);
				if (root == nullptr) {		//根节点为空就作为根结点
					root = p;
				}
				else {
					st.GetTop(top);
					switch (k)
					{
					case 1:
						top->lchild = p;
						break;
					case 2:
						top->rchild = p;
						break;
					}
				}
				break;
			}
			j++;
			ch = str[j];
		}
	}

	void DestroyBTree(BTNode<T>* n) {
		if (!n->IsLeaf()) {
			if (n->lchild != nullptr)
				DestroyBTree(n->lchild);
			if (n->rchild != nullptr)
				DestroyBTree(n->rchild);

		}
		//printf("deleting %c\n", n->data);
		delete n;
	}

	void DispHelp(BTNode<T>* n) {
		printf("%c", n->data);
		if (!n->IsLeaf()) {
			printf("(");
			if (n->lchild != nullptr)
				DispHelp(n->lchild);

			if (n->rchild != nullptr) {
				printf(",");
				DispHelp(n->rchild);
			}
			printf(")");
		}
	}

	BTNode<T>* FindNode(BTNode<T>* n, T t) {
		BTNode<T>* p;
		if (n == nullptr) {
			return nullptr;
		}
		else if (n->data == t) {
			return n;
		}
		else {
			p = FindNode(n->lchild, t);
			if (p != nullptr)		//找到第一个就立马返回
				return p;
			else
				return FindNode(n->rchild, t);
		}
	}

	int HeightHelp(BTNode<T>* n) {
		if (n == nullptr) {
			return 0;
		}
		else {
			int leftH = HeightHelp(n->lchild);
			int rightH = HeightHelp(n->rchild);
			return (leftH > rightH) ? (leftH + 1) : (rightH + 1);
		}
	}

	void PreOrderHelper(BTNode<T>* n) {
		printf("%c ", n->data);
		if (n->lchild != nullptr)
			PreOrderHelper(n->lchild);
		if (n->rchild != nullptr)
			PreOrderHelper(n->rchild);
	}

	void PostOrderHelper(BTNode<T>* n) {
		if (n->lchild != nullptr)
			PostOrderHelper(n->lchild);
		if (n->rchild != nullptr)
			PostOrderHelper(n->rchild);
		printf("%c ", n->data);
	}

	void InOrderHelper(BTNode<T>* n) {
		if (n->lchild != nullptr)
			InOrderHelper(n->lchild);
		printf("%c ", n->data);
		if (n->rchild != nullptr)
			InOrderHelper(n->rchild);
	}

	BTNode<T>* CopyHelp(BTNode<T>* n) {
		if (n == nullptr)
			return nullptr;
		BTNode<T>* node = new BTNode<T>(n->data);
		node->lchild = CopyHelp(n->lchild);
		node->rchild = CopyHelp(n->rchild);
		return node;
	}
public:
	BTree() :root(nullptr) {
	}

	BTree(const char* str) :root(nullptr) {
		CreateBTree(str);
	}

	//拷贝构造函数，有必要
	BTree(const BTree<T>& t) {
		root = CopyHelp(t.root);
	}



	~BTree() {
		DestroyBTree(root);
	}

	void Disp() {
		if (root == nullptr) {
			printf("Empty tree!");
			return;
		}
		DispHelp(root);
		printf("\n");
	}

	void PrintChildren(T t) {
		BTNode<T>* n = FindNode(root, t);
		printf("left child: %c, right child: %c\n", n->lchild->data, n->rchild->data);
	}

	int Height() {
		return HeightHelp(root);
	}

	void PreOrderRecur() {
		PreOrderHelper(root);
		printf("\n");
	}

	void PostOrderRecur() {
		PostOrderHelper(root);
		printf("\n");
	}

	void InOrderRecur() {
		InOrderHelper(root);
		printf("\n");
	}

	void PreOrder() {
		Sqstack<BTNode<T>*> st;
		BTNode<T>* p = nullptr;
		if (root != nullptr) {	//空二叉树就不用管了
			st.Push(root);
			while (!st.IsEmpty())
			{
				p = st.Pop();		//出栈
				printf("%c ", p->data);
				if (p->rchild != nullptr) {		//先进后出
					st.Push(p->rchild);
				}
				if (p->lchild != nullptr) {		//后进先出
					st.Push(p->lchild);
				}
			}
		}
		else {
			printf("Empty tree!");
		}
		printf("\n");
	}

	//这里把后序看成 根-右-左 的倒置 用前序思想和两个栈即可
	//复杂度是一样的
	void PostOrder() {
		Sqstack<BTNode<T>*> st, st_rev;
		BTNode<T>* p = root;
		if (root != nullptr) {	//空二叉树就不用管了
			st.Push(root);
			while (!st.IsEmpty())
			{
				//根-右-左
				p = st.Pop();		//出栈
				st_rev.Push(p);		//进入倒序栈
				if (p->lchild != nullptr) {		//后进先出
					st.Push(p->lchild);
				}
				if (p->rchild != nullptr) {		//先进后出
					st.Push(p->rchild);
				}
			}
			while (!st.IsEmpty())
			{
				st_rev.Push(st.Pop());		//进入倒序栈
			}
			while (!st_rev.IsEmpty())
			{
				p = st_rev.Pop();
				printf("%c ", p->data);
			}
		}
		else {
			printf("Empty tree!");
		}
		printf("\n");
	}

	void InOrder() {
		Sqstack<BTNode<T>*> st;
		BTNode<T>* p = root->lchild;
		if (root != nullptr) {	//空二叉树就不用管了
			st.Push(root);
			while (!st.IsEmpty() || p != nullptr)
			{
				while (p != nullptr)		//将左孩子结点全部进栈
				{
					st.Push(p);
					p = p->lchild;
				}
				p = st.Pop();
				printf("%c ", p->data);
				p = p->rchild;

			}
		}
		else {
			printf("Empty tree!");
		}
		printf("\n");
	}

	//用链队
	void LevelOrder() {
		Liqueue<BTNode<T>*> qu;
		BTNode<T>* p = nullptr;
		qu.Enqueue(root);
		while (!qu.IsEmpty())
		{
			qu.Dequeue(p);
			printf("%c ", p->data);
			if (p->lchild != nullptr)
				qu.Enqueue(p->lchild);
			if (p->rchild != nullptr)
				qu.Enqueue(p->rchild);
		}
	}
};