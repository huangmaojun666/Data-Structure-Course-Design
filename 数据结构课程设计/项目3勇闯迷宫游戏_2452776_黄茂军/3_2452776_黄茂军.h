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
template <typename T>
class stack {
private:
	Vector<T> data;
	int top;
public:
	stack() :top(-1) {}
	//入栈
	void push(const T& value) {
		data.push_back(value);
		++top;
	}
	//出栈并返回栈顶元素
	T pop() {
		T value = data[top];
		data.pop_back();
		--top;
		return value;
	}
	//返回栈的大小
	int size() const {
		return top + 1;
	}
	bool is_empty() const {
		return size() == 0;
	}
	//返回栈顶索引
	const int& top_index()const {
		return top;
	}
	//返回栈顶元素
	const T& get_top() const {
		return data[top];
	}

};
