template <typename T>
class Sqqueue {
private:
	const int MaxSize = 10;
	T* data;
	int front, rear;

public:
	Sqqueue() {
		data = new T[MaxSize];
		front = rear = 0;
	}
	~Sqqueue() {
		delete[] data;
	}

	bool IsEmpty() {
		return front == rear;
	}

	bool Enqueue(T const &e) {
		if ((rear + 1) % MaxSize == front)
			return false;
		rear = (rear + 1) % MaxSize;
		data[rear] = e;
		return true;
	}

	bool Dequeue(T &e) {
		//队空则无法出队
		if (front==rear)
			return false;
		e = data[front + 1];
		front = (front + 1) % MaxSize;
		return true;
	}


};