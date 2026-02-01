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
	String res(newData);
	delete[] newData;
	return res;
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

ostream& operator<<(ostream& out, const String& str) {
	out << str.c_str();
	return out;
}
void String::getline(istream& in) {
	char buffer[1024];
	in.getline(buffer, 1024);
	*this = String(buffer);
}

template <typename T>
class Vector {
private:
	T* data;
	int length;//当前长度
	int capacity;//当前容量
	//动态调整容量
	void resize(int new_capacity);
public:
	Vector() : capacity(4), length(0) {
		data = new T[capacity];
	}
	~Vector() {
		delete[] data;
	}
	void push_back(const T& value);//在末尾添加元素
	void pop_back();//在末尾删除元素
	int size() const { return length; }//返回当前长度
	T& operator[](int index) {
		return data[index];
	}//重载下标运算符
	const T& operator[](int index) const {
		return data[index];
	}//重载下标运算符（常量版本）
	void make_empty() {
		length = 0;
	}//清空动态数组
	bool is_empty() const {
		return length == 0;
	}//判断动态数组是否为空
};
template<class T>
void Vector<T>::resize(int new_capacity) {
	T* new_data = new T[new_capacity];
	for (int i = 0; i < length; ++i) {
		new_data[i] = data[i];
	}
	delete[] data;
	data = new_data;
	capacity = new_capacity;
}
template<class T>
void Vector<T>::push_back(const T& value) {
	if (length == capacity) {
		resize(capacity * 2);
	}
	data[length] = value;
	++length;
}
template<class T>
void Vector<T>::pop_back() {
	if (length > 0) {
		--length;
		if (length <= capacity / 4 && capacity > 4) {
			resize(capacity / 2);
		}
	}
}


