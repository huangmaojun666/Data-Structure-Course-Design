#pragma once

#include<iostream>
using namespace std;
class String {
private:
	char* data;
	int length;
public:
	String();
	String(const char* str);//从C风格字符串构造
	String(const String& str);//拷贝构造函数
	~String();
	int size() const;//返回字符串长度
	const char* c_str() const;//返回C风格字符串
	String& operator=(const String& str);//赋值运算符重载
	String operator+(const String& str) const;//字符串连接
	bool operator==(const String& str) const;//相等比较
	bool operator!=(const String& str) const;//不等比较
	bool operator<(const String& str) const;//小于比较
	bool operator<=(const String& str) const;//小于等于比较
	bool operator>(const String& str) const;//大于比较
	bool operator>=(const String& str) const;//大于等于比较
	char& operator[](int index);//下标运算符重载
	const char& operator[](int index) const;//下标运算符重载（常量版本）
	void getline(istream& in);//从输入流中读取一行字符串
	friend istream& operator>>(istream& in, String& str);//输入流运算符重载
	friend ostream& operator<<(ostream& out, const String& str);//输出流运算符重载
};
String::String() : data(nullptr), length(0) {}
String::String(const char* str) {
	if (str) {
		length = 0;
		while (str[length] != '\0') {
			length++;
		}
		data = new char[length + 1];
		for (int i = 0; i < length; i++) {
			data[i] = str[i];
		}
		data[length] = '\0';
	}
	else {
		data = nullptr;
		length = 0;
	}
}
String::String(const String& str) {
	length = str.length;
	if (length > 0) {
		data = new char[length + 1];
		for (int i = 0; i < length; i++) {
			data[i] = str.data[i];
		}
		data[length] = '\0';
	}
	else {
		data = nullptr;
	}
}
String::~String() {
	delete[] data;
}
int String::size() const {
	return length;
}
const char* String::c_str() const {
	return data ? data : "";
}
String& String::operator=(const String& str) {
	if (this != &str) {
		delete[] data;
		length = str.length;
		if (length > 0) {
			data = new char[length + 1];
			for (int i = 0; i < length; i++) {
				data[i] = str.data[i];
			}
			data[length] = '\0';
		}
		else {
			data = nullptr;
		}
	}
	return *this;
}
String String::operator+(const String& str) const {
	int newLength = length + str.length;
	char* newData = new char[newLength + 1];
	for (int i = 0; i < length; i++) {
		newData[i] = data[i];
	}
	for (int i = 0; i < str.length; i++) {
		newData[length + i] = str.data[i];
	}
	newData[newLength] = '\0';
	return String(newData);
}
bool String::operator==(const String& str) const {
	if (length != str.length) return false;
	for (int i = 0; i < length; i++) {
		if (data[i] != str.data[i]) return false;
	}
	return true;
}
bool String::operator!=(const String& str) const {
	return !(*this == str);
}
bool String::operator<(const String& str) const {
	int minLength = length < str.length ? length : str.length;
	for (int i = 0; i < minLength; i++) {
		if (data[i] < str.data[i]) return true;
		if (data[i] > str.data[i]) return false;
	}
	return length < str.length;
}
bool String::operator<=(const String& str) const {
	return *this < str || *this == str;
}
bool String::operator>(const String& str) const {
	return !(*this <= str);
}
bool String::operator>=(const String& str) const {
	return !(*this < str);
}
char& String::operator[](int index) {
	return data[index];
}
const char& String::operator[](int index) const {
	return data[index];
}
istream& operator>>(istream& in, String& str) {
	char buffer[1024];
	in >> buffer;
	str = String(buffer);
	return in;
}

ostream& operator<<(ostream& out, String& str) {
	out << str.c_str();
	return out;
}
void String::getline(istream& in) {
	char buffer[1024];
	in.getline(buffer, 1024);
	*this = String(buffer);
}

template<class T>
struct ListNode {
	T data;
	ListNode<T>* next;
	ListNode() : next(nullptr) {}
	ListNode(const T& d, ListNode<T>* n = nullptr) : data(d), next(n) {}
};
template<class T>
class List {
private:
	ListNode<T>* first;
	ListNode<T>* last;
public:
	List() { first = new ListNode<T>; last = first; last->next = nullptr; }
	List(const T& d) { first = new ListNode<T>; first->next = new ListNode<T>(d); last = first->next; last->next = nullptr; }
	List(const List<T>& l);
	~List() {
		makeEmpty();
	}
	void makeEmpty();
	bool isEmpty() const { return first == last; }
	ListNode<T>* find(const T& d) const;
	ListNode<T>* search(int i) const;
	bool insert(int i, const T& d);//在第i个元素后插入数据d
	bool remove(int i);//删除第i个元素
	bool remove(ListNode<T>* p);//删除节点p
	bool remove(const T& d);
	int length() const;
	ListNode<T>* getFirst() const { return first->next; }
};
template<class T>
List<T>::List(const List<T>& l) {
	first = new ListNode<T>;
	first->next = nullptr;
	last = first;
	ListNode<T>* p = first;
	ListNode<T>* q = l.first->next;
	while (q != nullptr) {
		p->next = new ListNode<T>(q->data);
		p = p->next;
		q = q->next;
	}
	last = p;
	last->next = nullptr;
}
template<class T>
void List<T>::makeEmpty() {
	ListNode<T>* p = first;
	while (p != nullptr) {
		ListNode<T>* q = p;
		p = p->next;
		delete q;
	}
	first = new ListNode<T>;
	last = first;
	last->next = nullptr;
}


template<class T>
ListNode<T>* List<T>::find(const T& d) const {
	ListNode<T>* p = first->next;
	while (p != nullptr) {
		if (p->data == d) {
			return p;
		}
		p = p->next;
	}
	return nullptr;
}
template<class T>
bool List<T>::insert(int i, const T& d) {
	if (i < 0 || i > length()) return false;
	ListNode<T>* newNode = new ListNode<T>(d);
	ListNode<T>* p = first;
	if (i == 0) {
		newNode->next = first->next;
		first->next = newNode;
		if (newNode->next == nullptr) {
			last = newNode;
		}
		return true;
	}
	for (int j = 0; j < i; j++) {
		p = p->next;
	}
	newNode->next = p->next;
	p->next = newNode;
	if (newNode->next == nullptr) {
		last = newNode;
	}
	return true;
}
template<class T>
bool List<T>::remove(int i) {
	if (i <= 0 || i >length()) return false;
	ListNode<T>* p = first;
	for (int j = 0; j < i - 1; j++) {
		p = p->next;
	}
	ListNode<T>* q = p->next;
	p->next = q->next;
	if (q == last) {
		last = p;
	}
	delete q;
	return true;
}
template<class T>
bool List<T>::remove(ListNode<T>* p) {
	if (p == nullptr) return false;
	ListNode<T>* q = first;
	while (q->next != nullptr && q->next != p) {
		q = q->next;
	}
	if (q->next == nullptr) return false;
	q->next = p->next;
	if (p == last) {
		last = q;
	}
	delete p;
	return true;
}
template<class T>
bool List<T>::remove(const T& d) {
	return remove(find(d));
}
template<class T>
int List<T>::length() const {
	int len = 0;
	ListNode<T>* p = first->next;
	while (p != nullptr) {
		len++;
		p = p->next;
	}
	return len;
}
template<class T>
ListNode<T>* List<T>::search(int i)const {
	if (i <= 0 || i > length()) {
		return nullptr;
	}
	ListNode<T>* p = first;
	for (int j = 0; j < i; j++) {
		p = p->next;
	}
	return p;
}
