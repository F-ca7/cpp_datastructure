#include <stdio.h>

template <typename T>
class Listack;

template <typename T>
class Node {
	friend class Listack;
private:
	T data;
	Node* next;
	Node(T e,Node* n = NULL) {
		data = e;
		next = n;
	}
	
	Node(Node* n = NULL) {
		next = n;
	}
};

template <typename T>
class Listack {
private:
	Node<T>* head;

public:
	Listack() {
		head = new Node<T>();
	}
	~Listack(){
		Node<T>* temp;
		while (head->next!=NULL){
			temp = head->next;
			head->next = temp->next;
			delete temp;
		}
		delete head;
	}
	bool IsEmpty() {
		return head->next == NULL;
	}

	void Push(T const &e) {
		Node<T>* temp = new Node<T>(e,head->next);
		head->next = temp;
	}

	bool Pop(T &e) {
		if (head->next == NULL)
			return false;
		Node<T>* temp = head->next;
		e = temp->data;
		head->next = temp->next;
		delete temp;
		return true;
	}

	T Pop() {
		if (head->next == NULL)
			throw "Stack is empty!";
		Node<T>* temp = head->next;
		T e = temp->data;
		head->next = temp->next;
		delete temp;
		return e;
	}


};