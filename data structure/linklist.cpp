#include <iostream>
using namespace std;

template <typename T>
class LinkList;

template <typename T>
class Node {
	friend class LinkList<T>;
private:
	T data;
	Node* next;
	//默认node构造时next域为空
	Node(T d, Node* n = NULL) {
		data = d;
		next = n;
	}

	Node(Node* n = NULL) {
		next = n;
	}
};


template <typename T>
class LinkList {

private:
	Node<T>* head;


public:
	LinkList() {
		head = new Node<T>();
	}

	~LinkList() {
		//cout << "deleting!" << endl;
		Node<T> * n, *temp = head;
		while (temp != NULL) {
			n = temp->next;
			delete temp;
			temp = n;
		}
		delete head;
	}

	//从已有数组中用尾插法创建链表
	LinkList(T a[], int size) {
		head = new Node<T>();
		Node<T>* temp = head;
		for (int i = 0; i < size; i++) {
			temp->next = new Node<T>(a[i]);
			temp = temp->next;
		}
	}

	bool IsEmpty() {
		return head->next == NULL;
	}



	int Length() {
		int count = 0;
		Node<T>* temp = head->next;
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}

	//i从1开始，除开头结点
	bool GetElem(int i, T& e) {
		if (i < 1)
			return false;
		//temp指向第一个节点
		Node<T>* temp = head;
		for (int j = 0; j < i; j++) {
			if (temp->next == NULL)
				return false;
			temp = temp->next;
		}
		e = temp->data;
		return true;
	}

	//未找到返回0
	int LocateElem(T e) {
		int index = 0;
		Node<T>* temp = head;
		for (int j = 0; temp->next != NULL; j++) {
			index++;
			temp = temp->next;
			if (temp->data == e)
				return index;
		}
		return 0;
	}

	//插入的元素在第i个位置
	bool ListInsert(int i, T e) {
		if (i < 1)
			return false;
		Node<T>* temp = head;
		//j也从1开始
		for (int j = 1; temp->next != NULL; j++) {
			//找到了第i个位置
			if (j == i) {
				temp->next = new Node<T>(e, temp->next);
				return true;
			}
			temp = temp->next;
		}
		//未找到第i个位置
		return false;
	}

	bool ListDelete(int i, T& e) {
		if (i < 1)
			return false;
		Node<T>* temp = head;
		Node<T>* p;
		//temp是要删除结点的前一个结点
		for (int j = 1; temp->next != NULL; j++) {
			if (j == i) {
				p = temp->next->next;
				delete temp->next;
				temp->next = p;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void DispList() {
		Node<T>* temp = head->next;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	//排序，将无序链表转为有序单链表
	void Sort() {
		Node<T>* temp = head->next, *n;
		for (; temp != NULL; temp = temp->next) {
			for (n = temp->next; n != NULL; n = n->next) {
				if (n->data < temp->data) {
					T t = temp->data;
					temp->data = n->data;
					n->data = t;
				}
			}
		}
	}

	//只针对有序链表的并集
	//不能返回引用!
	//要返回局部对象的话，需要写拷贝构造函数，这里传参进去方便
	static void Union(const LinkList<T> &a,const LinkList<T> &b, LinkList<T> &list) {
		//LinkList<T> list;
		Node<T>* temp = list.head, *t1 = a.head->next, *t2 = b.head->next;
		while (t1 != NULL && t2 != NULL) {
			if (t1->data < t2->data) {
				temp->next = new Node<T>(t1->data);
				temp = temp->next;
				t1 = t1->next;
			}
			else if(t1->data == t2->data){
				temp->next = new Node<T>(t1->data);
				temp = temp->next;
				t1 = t1->next;
				t2 = t2->next;
			}
			else{
				temp->next = new Node<T>(t2->data);
				temp = temp->next;
				t2 = t2->next;
			}
		}

		while (t1 != NULL) {
			temp->next = new Node<T>(t1->data);
			temp = temp->next;
			t1 = t1->next;
		}
		while (t2 != NULL) {
			temp->next = new Node<T>(t2->data);
			temp = temp->next;
			t2 = t2->next;
		}
		temp->next = NULL;
		//return list;
	}

	static void Intersect(const LinkList<T> &a, const LinkList<T> &b, LinkList<T> &list) {
		Node<T>* temp = list.head, *t1 = a.head->next, *t2 = b.head->next;
		while (t1 != NULL && t2 != NULL) {
			if (t1->data < t2->data) {
				t1 = t1->next;
			}
			else if (t1->data == t2->data) {
				temp->next = new Node<T>(t1->data);
				temp = temp->next;
				t1 = t1->next;
				t2 = t2->next;
			}
			else {
				t2 = t2->next;
			}
		}
		temp->next = NULL;

	}

	//有先后顺序，是a-b
	static void Subtract(const LinkList<T> &a, const LinkList<T> &b, LinkList<T> &list) {
		Node<T>* temp = list.head, *t1 = a.head->next, *t2 = b.head->next;
		while (t1 != NULL && t2 != NULL) {
			//如果小于，直接加入，后面不可能重复
			if (t1->data < t2->data) {
				temp->next = new Node<T>(t1->data);
				temp = temp->next;
				t1 = t1->next;
			}
			//等于的话，两边一起跳过
			else if (t1->data == t2->data) {
				t1 = t1->next;
				t2 = t2->next;
			}
			//大于的话，只跳过2
			else  {
				t2 = t2->next;				
			}
		}

		while (t1 != NULL) {
			temp->next = new Node<T>(t1->data);
			temp = temp->next;
			t1 = t1->next;
		}
		temp->next = NULL;
	}
};
