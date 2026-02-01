#include<iostream>
#include"5_2452776_黄茂军.h"
using namespace std;
//初始化A,B队列并进行输入处理
void initQueue(Queue<int>& a, Queue<int>& b,bool& inputerro) {
	int N;//顾客总人数
	cin >> N;
	if (cin.fail() || N < 1 || N>1000) {
		cout << "顾客人数输入错误，重新输入！" << endl;
		inputerro = 1;
		cin.clear();
		cin.ignore(1024, '\n');
		return;
	}
	int id;//顾客编号
	for (int i = 0; i < N; i++) {
		cin >> id;
		if (cin.fail() ) {
			cout << "顾客编号输入错误，重新输入！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			inputerro = 1;
			return;
		}
		//编号为偶数去B窗口
		if (id % 2 == 0) {
			b.enqueue(id);
		}
		//编号为奇数去A窗口
		else
			a.enqueue(id);
	}
	cin.ignore(1024, '\n');//清除输入的多余字符
}
//输出顾客处理顺序编号
void printid( Queue<int>& a,  Queue<int>& b) {
	int groupcount = a.size() / 2;
	//求A窗口2个人一组与B窗口1人1组的组数的较小者
	groupcount = groupcount < b.size() ? groupcount : b.size();
	for (int i = 0; i < groupcount; ++i) {
		int id1 = a.dequeue();
		int id2 = a.dequeue();
		int id3 = b.dequeue();
		if (a.isEmpty() && b.isEmpty()) {
			cout << id1 << " " << id2 << " " << id3 << endl;
		}
		else {
			cout << id1 << " " << id2 << " " << id3 << " ";
		}
	}
	int size;
	//如果A有剩余
	if (!a.isEmpty()) {
		//如果B没剩余,直接输出A剩余值
		if (b.isEmpty()) {
			size = a.size();
			for (int i = 0; i < size; ++i) {
				int id = a.dequeue();
				if (a.isEmpty()) {
					cout << id << endl;//末尾不加空格
				}
				else
					cout << id << " ";
			}
		}
		//如果B有剩余，A只剩一个，先输出A
		else {
			cout << a.dequeue() << " ";
			size = b.size();
			for (int i = 0; i < size; ++i) {
				int id = b.dequeue();
				if (b.isEmpty()) {
					cout << id << endl;//末尾无空格
				}
				else
					cout << id << " ";
			}
		}
	}
	//如果A没有剩余，B有剩余
	else {
		size = b.size();
		for (int i = 0; i < size; ++i) {
			int id = b.dequeue();
			if (b.isEmpty()) {
				cout << id << endl;//末尾无空格
			}
			else
				cout << id << " ";
		}
	}
}
int main() {
	Queue<int> a, b;
	//循环用于输入处理
	while (1) {
		a.makeEmpty();
		b.makeEmpty();//每次循环都清空队列
		bool inputerro = 0;//错误标记
		//初始化队列
		initQueue(a, b, inputerro);
		if (inputerro == 1)continue;
		printid(a, b);
		break;
	}
	return 0;
}