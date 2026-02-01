#pragma once
#pragma once
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
	if(i==0){
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
	if (i <= 0 || i > length()) return false;
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
