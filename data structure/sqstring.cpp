#include <iostream>
#include <string>
using namespace std;
class SqString {
private:
	const int MaxSize = 100;
	char* data;
	

public:
	int length;
	SqString() {
		data = new char[MaxSize];
		length = 0;
	}

	SqString(const char cstr[]) {
		data = new char[MaxSize];
		int i;
		for (i = 0; cstr[i] != '\0'; i++) {
			data[i] = cstr[i];
		}
		length = i;
	}

	~SqString() {
		//delete[] data;
	}


	//插在第index个数前，成为第index个数
	SqString InsStr(int index, const SqString& s) {
		SqString r;
		int i, j, k;
		for (i = 0; i < index-1; i++) {
			r.data[i] = this->data[i];
		}
		for (j = 0; j < s.length; j++, i++) {
			r.data[i] = s.data[j];
		}
		for (k=index-1; k < length; k++,i++) {
			r.data[i] = this->data[k];
		}
		r.length = length + s.length;
		return r;
	}
	
	bool StrEqual(const SqString& t) {
		bool same = true;
		if (length != t.length) {
			same = false;
		}
		else{
			for (int i = 0; i < length; i++) {
				if (data[i] != t.data[i]) {
					same = false;
					break;
				}
			}
		}
		return same;
	}

	void DispStr() {
		for (int i = 0; i < length; i++) {
			printf("%c",data[i]);
		}
		printf("\n");
	}

	//位置从1开始
	//删除从第i个字符起的j个字符
	SqString DelStr(int i, int j) {
		SqString r;
		int k, tmp;
		if (i>=1 && (i+j-1)<=length) {
			for (k = 0; k < i - 1; k++) {
				r.data[k] = data[k];
			}
			tmp = k;
			for (k = i+j-1; k < length; k++,tmp++) {
				r.data[tmp] = data[k];
			}
			r.length = length - j ;
			
		}
		return r;
	}

	SqString& operator= (const SqString &s) {
		//自赋值检查
		if (this == &s) {
			return *this;
		}
		//释放原来的data
		delete[] data;
		data = new char[MaxSize];
		for (int i = 0; i < s.length; i++) {
			data[i] = s.data[i];
		}
		length = s.length;
		return *this;
	}

	//替换从第i个字符起的j个字符为s
	SqString RepStr(int i, int j, SqString& s) {
		SqString t = DelStr(i, j).InsStr(i,s);
		return t;
	}

	//提取q从第i个字符起的j个字符
	SqString SubStr(int i, int j) {
		SqString r;
		int t = 0;
		//防止超出范围
		for (int k = i - 1; k < i + j-1 && k < length; k++) {
			r.data[t++] = data[k];
		}
		r.length = t;
		return r;
	}

	//把s连接在后面
	static SqString Concat(const SqString& s, const SqString& t) {
		SqString r = s;
		for (int i = 0; i < t.length; i++) {
			r.data[i + s.length] = t.data[i];
		}
		r.length += t.length;
		return r;
	}

	//作业题
	static SqString SameChars(const SqString& s, const SqString& t) {
		SqString r;
		int last=0,j;	
		for (int i = 0; i < s.length; i++) {
			char ch = s.data[i];
			for (j = 0; j < last; j++) {
				if (r.data[j] == ch) 
					break;
			}
			for (int k = 0; j==last && k < t.length; k++) {
				if (ch == t.data[k]) {
					r.data[last++] = ch;
				}
			}
		}
		r.length = last;
		return r;
	}

		int BFmatch(const SqString& s) {
		int i, j;
		for (i = 0; i < length - s.length + 1; i++) {
			for (j = 0; j < s.length; j++) {
				if (data[i + j] != s.data[j])
					break;
			}
			if (j == s.length)
				return i;
		}
		return -1;
	}
	
	void GetNext(int next[]) {
		int k = -1, j = 0;
		next[0] = -1;
		while (j<length-1) {
			if (k == -1 || data[k] == data[j]) {
				k++;
				j++;
				next[j] = k;
			}
			else{
				k = next[k];
			}
		}
	}

	int KMPIndex(SqString& s) {
		int* next= new int[MaxSize];
		s.GetNext(next);
		int i =0, j = 0;
		while (i<length && j<s.length){
			if (data[i] == s.data[j] || j == -1) {
				i++;
				j++;
			}
			else
			{
				j = next[j];
			}
		}
		delete[] next;
		if (j == s.length) {
			return (i - j);
		}
		//未找到
		return -1;
	}

	void GetNextVal(int nextval[]) {
		int k = -1, j = 0;
		nextval[0] = -1;
		while (j<length-1) {
			if (k == -1 || data[j] == data[k]) {
				j++;
				k++;
				if (data[j] == data[k]) {
					nextval[j] = nextval[k];
				}
				else{
					nextval[j] = k;
				}
			}
			else {
				k = nextval[k];
			}
		}
	}

	int newKMPIndex(SqString& s) {
		int *nextval = new int[MaxSize];
		GetNextVal(nextval);
		int i = 0, j = 0;
		while (i < length && j < s.length) {
			if (data[i] == s.data[j] || j==-1) {
				i++;
				j++;
			}
			else {
				j = nextval[j];
			}
		}
		if (j == s.length) {
			return i - j;
		}
		return -1;
	}

};