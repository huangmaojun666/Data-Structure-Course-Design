#pragma once
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
