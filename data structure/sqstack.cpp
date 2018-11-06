
#include <cstring>
template <typename T>
class Sqstack {
private:
	const int Maxsize = 50;
	T* data;
	int top;

public:
	Sqstack() {
		data = new T[Maxsize];
		top = -1;
	}

	//需要写赋值函数函数(迷宫需要)
	Sqstack& operator=(const Sqstack& stack) {
		memcpy(data, stack.data, (stack.top + 1) * sizeof(T));
		top = stack.top;
		return *this;
	}

	~Sqstack() {

	}

	bool IsEmpty() {
		return top == -1;
	}

	bool Push(T const &e) {
		if (top == Maxsize - 1)
			return false;		
		top++;
		data[top] = e;
		return true;
	}

	bool Pop(T &e) {
		if (top == -1)
			return false;
		e = data[top];
		top--;
		return true;
	}

	 T Pop() {
		 if (top == -1)
			 throw "Stack is empty!";
		 T e = data[top];
		 top--;
		 return e;
	 }

	 bool GetTop(T &e) {
		 if (top == -1)
			 return false;
		 e = data[top];
		 return true;
	 }

	 T GetTop() {
		 if (top == -1)
			 throw "Stack is empty!";
		 T e = data[top];
		 return e;
	 }

	 int GetCount() {
		 return top;
	 }
};