#include <iostream>
using namespace std;

template <typename T>
class DLinkList;

template <typename T>
class Node {
	friend class DLinkList<T>;
private:
	T data;
	Node* next;
	Node* prior;
	//默认node构造时next域为空
	Node(T d,Node* p=NULL ,Node* n = NULL) {
		data = d;
		prior = p;
		next = n;
	}

	Node(Node* p = NULL,Node* n = NULL) {
		prior = p;
		next = n;
	}
};

//和单链表比，主要修改插入方式
template <typename T>
class DLinkList {
private:
	Node<T>* head;
public:
	DLinkList() {
		head = new Node<T>();
	}

	~DLinkList() {
		Node<T> * n, *temp = head;
		while (temp != NULL) {
			n = temp->next;
			delete temp;
			temp = n;
		}
	}

	DLinkList(T a[], int size) {
		head = new Node<T>();
		Node<T> *p=head, *n;
		for (int i = 0; i < size; i++) {
			n = p->next;
			//这里得想清楚
			p->next =new Node<T>(a[i], p, n);
			p = p->next;
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
				temp->next = new Node<T>(e,temp ,temp->next);
				temp->next->next->prior = temp->next;
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
				p->prior = temp;
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
};

