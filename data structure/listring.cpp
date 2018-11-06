#include <iostream>

class LiString;

class SNode {
	friend class LiString;
private:
	char data;
	SNode* next;
	SNode(SNode* sn = nullptr) {
		next = sn;
	}

	SNode(char d,SNode* sn = nullptr) {
		data = d;
		next = sn;
	}
};

class LiString{
private:
	SNode* head;
	void DelStr() {
		SNode* tmp = head, *r = tmp->next;
		while (r != nullptr) {
			tmp = r->next;
			delete r;
			r = tmp;
		}
		delete head;
	}

public:
	LiString() {
		head = new SNode();
	}

	//把字符串常量赋值给链串
	LiString(const char* str) {
		head = new SNode();
		SNode* tmp = head;
		for (int i = 0; str[i] != '\0'; i++) {
			tmp->next = new SNode(str[i]);
			tmp = tmp->next;
		}
		tmp->next = nullptr;
	}

	LiString(const LiString& s) {
		head = new SNode();
		SNode* tmp = head, *smtp = s.head;
		while (smtp->next!=nullptr){
			smtp = smtp->next;
			tmp->next = new SNode(smtp->data);
			tmp = tmp->next;
		}
		tmp->next = nullptr;
	}

	~LiString() {
		DelStr();
	}

	int StrLength() {
		int i = 0;
		SNode* tmp = head;
		while (tmp->next != nullptr) {
			i++;
			tmp = tmp->next;
		}
		return i;
	}

	void DispStr() {
		SNode* tmp = head->next;
		while (tmp!=nullptr) {
			printf("%c", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
	}

	LiString& operator=(const LiString &s) {
		//自赋值检查
		if (this == &s) {
			return *this;
		}
		//释放原来的链串
		DelStr();
		head = new SNode();
		SNode* tmp = head, *stmp = s.head;
		while (stmp->next!=nullptr){
			stmp = stmp->next;
			tmp->next = new SNode(stmp->data);
			tmp = tmp->next;
		}
		tmp->next = nullptr;
		return *this;

	}


	//插在第index个数前，成为第index个数
	LiString InsStr(int index, const LiString &s) {
		LiString r;
		int i = 0;
		SNode *tmp=head, *rtmp = r.head, *stmp=s.head;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
			//找到了插入位置
			if (i == index - 1) {
				while (stmp->next!=nullptr){
					stmp = stmp->next;
					rtmp->next = new SNode(stmp->data);
					rtmp = rtmp->next;
				}
			}
			rtmp->next = new SNode(tmp->data);
			rtmp = rtmp->next;
			i++;
		}
		rtmp->next = nullptr;
		return r;
	}

	//位置从1开始
	//删除从第i个字符起的j个字符
	LiString DelStr(int i, int j) {
		LiString r;
		int index=0;
		SNode *tmp = head, *rtmp = r.head;
		for (; tmp->next != nullptr; index++) {	
			tmp = tmp->next;
			if (index<i - 1 || index>=i+j-1) {
				rtmp->next = new SNode(tmp->data);
				rtmp = rtmp->next;
			}
		}
		rtmp->next = nullptr;
		return r;
	}

	LiString RepStr(int i, int j, LiString& s) {
		LiString t = DelStr(i, j).InsStr(i, s);
		return t;
	}

	LiString SubStr(int i, int j) {
		LiString r;
		SNode *tmp = head, *rtmp = r.head;
		for (int k = 0; k < i + j - 1 && tmp->next != nullptr ; k++) {
			tmp = tmp->next;
			if (k >= i-1) {
				rtmp->next = new SNode(tmp->data);
				rtmp = rtmp->next;
			}
		}
		rtmp->next = nullptr;
		return r;
	}

	static LiString Concat(const LiString& s, const LiString& t) {
		LiString r;
		SNode *rtmp = r.head, *stmp = s.head, *ttmp = t.head;
		while (stmp->next!=nullptr){
			stmp = stmp->next;
			rtmp->next = new SNode(stmp->data);
			rtmp = rtmp->next;
		}
		while (ttmp->next!=nullptr){
			ttmp = ttmp->next;
			rtmp->next = new SNode(ttmp->data);
			rtmp = rtmp->next;
		}
		rtmp->next = nullptr;
		return r;
	}
};