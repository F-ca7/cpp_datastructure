#include <iostream>
using namespace std;

template <typename T>
class Sqlist {

private:
	const int MaxSize = 30;
	//data 来指向存放数据的数组
	T* data;
	int length;

public:
	//默认无参初始化
	Sqlist() {
		data = new T[MaxSize];
		length = 0;
	}

	//通过数组初始化
	Sqlist(T a[],int size) {
		data = new T[MaxSize];
		length = size;
		for (int i = 0; i < length; i++) {
			data[i] = a[i];
		}
	}

	//析构函数，不用destroyList
	~Sqlist() {
		delete[] data;
	}

	bool IsEmpty() {
		return length == 0;
	}

	//输出线性表长度
	int Length() const {
		return length;
	}


	//打印线性表元素
	void DispList() {
		for (int i = 0; i < length; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
	}

	//取得某个位置的元素值
	//参数i从1开始
	bool GetElem(int i, T &e) {
		if (i<1 || i>length)
			return false;
		e = data[i - 1];
		return true;
	}

	//查找某一元素的位置，从1开始
	//未找到返回0
	int LocateElem(T e) {
		int pos = 0;
		for (; pos < length; pos++) {
			if (data[pos] == e)
				return pos + 1;
		}
		return 0;
	}


	//插入数据元素
	//在第i面插，位置i从1开始
	bool ListInsert(int i, T e) {
		//当length满时，无法插入
		if (i<1 || i>length + 1 || length == MaxSize)
			return false;
		for (int j = length; j > i - 1; j--) {
			data[j] = data[j - 1];
		}
		data[i - 1] = e;
		length++;
		return true;
	}

	//删除数据元素
	//位置i从1开始
	bool ListDelete(int i, T e) {
		if (i<1 || i>length)
			return false;
		e = data[i - 1];
		for (int j = i - 1; j < length - 1; j++) {
			data[j] = data[j + 1];
		}
		length--;
		return true;
	}

};


