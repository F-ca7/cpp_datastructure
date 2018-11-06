#include <iostream>

template<typename T>
class GeneralList;


template<typename T>
class GLNode {
	friend class GeneralList<T>;
private:
	int tag;		//记录结点类型，0是原子结点，1是子表结点
	union
	{
		//两者取其一
		T data;			//原子结点的数据值
		GLNode<T>* sublist;	//指向子表
	}val;
	GLNode<T>* link;	//指向相邻的下一个元素(兄弟结点)

public:
	GLNode(int type, GLNode* next=nullptr) {
		tag = type;
		link = next;
	}
};

//用模板有点问题，在进行构造表的时候
template<typename T>
class GeneralList {
private:
	GLNode<T>* head;

	//str由括号表示
	GLNode<T>* CreateList(const char* &str) {
		char ch = *str;
		str++;						//str的指针后移
		GLNode<T>* g;
		if (ch!='\0'){				//递归构造；也可以用while循环
			g = new GLNode<T>(1);
			if (ch == '(') {		//括号说明是新的子表开始
				g->val.sublist = CreateList(str);
			}
			else if (ch == ')' || ch=='#') {	//子表的结束,或空表
				g = nullptr;	
			}
			else						//原子数据	
			{
				g->tag = 0;
				g->val.data = (T)ch;
			}
		}
		else
		{
			g = nullptr;
		}

		ch = *str;
		str++;			//str的指针后移
		if (g != nullptr) {	
			if (ch == ',') {	//递归构造兄弟结点
				g->link = CreateList(str);
			}
			else
			{
				g->link = nullptr;		//无兄弟结点了
			}
		}
		return g;
	}

	//销毁链表
	void DestroyGL(GLNode<T>* &g) {
		if (g != nullptr) {		//g为空指针则不操作			
			if (g->tag == 0) {		//如果g是原子结点，直接释放
				DestroyGL(g->link);
				//printf("deleting %c\n", g->val.data);
				delete g;
			}
			else {			//如果g是子表
				DestroyGL(g->val.sublist);	//先销毁子表
				DestroyGL(g->link);
				delete g;
			}
		}
	}

	void DispGLHelp(GLNode<T>* &g) {
		if (g != nullptr) {			//当g为空时，停止打印
			if (g->tag == 0) {		//若g是原子结点，直接输出数据
				printf("%c", g->val.data);
			}
			else {					//若g是子表(即 g->tag == 1)
				printf("(");
				if (g->val.sublist == nullptr) {	//若子表为空
					printf("#");
				}
				else {								//若子表不为空，视之为新的表，递归打印
					DispGLHelp(g->val.sublist);
				}
				printf(")");
			}
			if (g->link != nullptr) {	//若存在兄弟结点
				printf(",");
				DispGLHelp(g->link);
			}
		}
	}

	int DepthHelper(GLNode<T>* &g) {
		GLNode<T>* g1;
		int count = 0;
		if (g->tag == 0) {
			return 0;
		}
		else {		//else可以省略
			g1 = g->val.sublist;
			if (g1 == nullptr) {
				return 1;		//空表深度为1
			}
			while (g1 != nullptr) {
				if (g1->tag == 1) {		//这个判断也可以省略，加上这个判断可以节省一点时间
					int temp = DepthHelper(g1);
					count = temp > count ? temp : count;

				}
				g1 = g1->link;		//扫描所有兄弟结点，找到最深的深度
			}
		}

		return (count + 1);
	}

	T MaxElemHelp(GLNode<T>* &g) {
		T temp = (T)0, max = (T)0;
		if (g != nullptr) {
			if (g->tag == 0) {		//当g原子结点时，直接与兄弟节点的max作比较
				max = MaxElemHelp(g->link);
				return max > g->val.data ? max : g->val.data;
			}
			else {		//当g为子表结点时，返回g的兄弟结点和子表结点相对更大的max值
				temp = MaxElemHelp(g->val.sublist);
				max = MaxElemHelp(g->link);
				return temp > max ? temp : max;
			}
		}
		else {		//当为空时，返回0
			return (T)0;
		}
	}

public:
	GeneralList():head(nullptr) {}
	GeneralList(const char* str):head(nullptr) {
		head = CreateList(str);
	}
	~GeneralList(){
		DestroyGL(head);
	}

	void Disp() {
		DispGLHelp(head);
		printf("\n");
	}

	//求广义表长度
	int Length() {
		int count = 0;
		GLNode<T>* temp = head->val.sublist;
		while (temp != nullptr)
		{
			count++;
			temp = temp->link;
		}
		return count;
	}

	//求广义表深度
	int Depth() {
		return DepthHelper(head);
	}
	
	//求广义表中最大原子
	T MaxElem() {
		return MaxElemHelp(head);
	}
};