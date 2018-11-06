#include <cstdio>

template <typename T>
class Liqueue;

template <typename T>
class Node {
	friend class Liqueue<T>;
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
class Liqueue {
private:
	//front相当于head
	Node<T>* front;
	Node<T>* rear;

public:
	Liqueue() {
		//这里不能写front=rear=new Node<T>();
		//会导致只初始化了一个对象
		front = new Node<T>();
		rear = new Node<T>();
	}

	~Liqueue(){
		Node<T>* temp;
		while (front->next!=NULL){
			temp = front->next;
			front->next = temp->next;
			delete temp;
		}
		delete front;
	}

	bool IsEmpty() {
		return rear->next == NULL;
	}

	//进队到队尾
	void Enqueue(T const &e) {
		Node<T>* temp=new Node<T>(e);
		if (rear->next == NULL) {
			front->next = rear->next = temp;
		}
		else{
			rear->next->next = temp;
			rear->next = temp;
		}
		
	}

	//从队头出队
	bool Dequeue(T &e) {
		//空队无法出
		if (rear->next == NULL)
			return false;
		Node<T>* temp = front->next;
		e = temp->data;
		//若只有一个节点
		if (front->next == rear->next) {
			front->next = rear->next = NULL;			
		}
		else {
			front->next = temp->next;
		}
		delete temp;
		return true;
	}
};