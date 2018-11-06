#include <iostream>
using namespace std;

template <typename T>
class CLinkList;

template <typename T>
class Node {
	friend class CLinkList<T>;
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


//所有尾条件判断均要修改
template <typename T>
class CLinkList {
private:
	Node<T>* head;

public:
	CLinkList() {
		head = new Node<T>();
	}

	~CLinkList() {
		Node<T> * n, *temp = head;
		while (temp!=head){
			n = temp->next;
			delete temp;
			temp = n;
		}
		delete head;
	}

	//从已有数组中用尾插法创建循环单链表
	CLinkList(T a[],int size) {
		head = new Node<T>();
		Node<T>* temp = head;
		for (int i = 0; i < size; i++) {
			temp->next = new Node<T>(a[i]);
			temp = temp->next;
		}
		temp->next = head;
	}

	bool IsEmpty() {
		return head->next == NULL;
	}

	int Length(){
		int count = 0;
		Node<T>* temp = head->next;
		while (temp!=head)
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
			if (temp->next == head)
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
		for (int j = 0; temp->next != head; j++) {
			index++;
			temp = temp->next;
			if (temp->data == e)
				return index;
		}
		return 0;
	}

	//插入的元素在第i个位置
	bool ListInsert(int i,T e) {
		if (i < 1)
			return false;
		Node<T>* temp = head;
		//j也从1开始
		for (int j = 1; temp->next != head; j++) {
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
		for (int j = 1; temp->next != head; j++) {
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
		while (temp!=head)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

};

