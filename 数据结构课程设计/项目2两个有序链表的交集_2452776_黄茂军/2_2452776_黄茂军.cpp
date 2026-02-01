#include<iostream>
#include"2_2452776_黄茂军.h"//自定义链表
using namespace std;
template<class T>
//两个非降序链表求交集
bool interset(const List<T>& l1, const List<T>& l2, List<T>& l3) {
	ListNode<T>* p = l1.getFirst();
	ListNode<T>* q = l2.getFirst();
	while (p != nullptr && q != nullptr) {
		if (p->data < q->data) {
			p = p->next;
		}
		else if (p->data > q->data) {
			q = q->next;
		}
		else {
			l3.insert(l3.length(), p->data);
			p = p->next;
			q = q->next;
		}
	}
	return true;
}
template<class T>
//打印链表
void printList(const List<T>& l) {
	if(l.isEmpty()){
		cout<<"NULL"<<endl;
		return;
	}
	ListNode<T>* p = l.getFirst();
	while (p != nullptr) {
		if(p->next==nullptr)
			cout << p->data;//最后一个元素后不加空格
		else
			cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
//输入处理并检查非降序
void inputList(List<int>& l,int tag) {
	while (1) {
		int n;
		cin >> n;
		if (n == tag)//输入结束标志
			break;
		if (cin.fail()) {
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		if (!l.isEmpty()) {
			if (n < l.search(l.length())->data) {//非降序输入检查
				cout << "输入数据不符合非降序要求，请重新输入！" << endl;
				l.makeEmpty();//清空链表重新输入
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
		}
		
		l.insert(l.length(),n);
	}
	return;
}
int main() {
	List<int> l1, l2, l3;
	inputList(l1, -1);
	inputList(l2, -1);
	interset(l1, l2, l3);
	cout << endl;
	printList(l3);
	return 0;
}