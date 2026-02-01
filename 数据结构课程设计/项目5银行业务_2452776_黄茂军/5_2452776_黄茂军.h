#pragma once
#include<iostream>
#include <stdexcept> // 用于抛出 runtime_error 异常
// 定义节点结构体 
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    // 构造函数
    Node(T val) : data(val), next(nullptr) {}
};

//  定义队列类 
template <typename T>
class Queue {
private:
    Node<T>* head; // 队首指针 (Front of the queue)
    Node<T>* tail; // 队尾指针 (Rear of the queue)
    int count;     // 队列中元素的数量

public:
    // 构造函数
   Queue() : head(nullptr), tail(nullptr), count(0) {}

    // 析构函数 (释放所有动态分配的内存)
    ~Queue() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 判空操作
    bool isEmpty() const {
        return head == nullptr; // 或者 return count == 0;
    }

    // 获取队列大小
    int size() const {
        return count;
    }

    // 入队
    void enqueue(const T& value) {
        // 1. 创建新节点
        Node<T>* newNode = new Node<T>(value);

        // 2. 如果队列为空，head 和 tail 都指向新节点
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        }
        // 3. 如果队列不为空，新节点添加到队尾，并更新 tail
        else {
            tail->next = newNode;
            tail = newNode;
        }

        count++;
    }

    // 出队 
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("队列为空，无法出队！");
        }

        //  获取队首元素的数据
        T result = head->data;

        //  暂存当前队首节点 (用于稍后释放内存)
        Node<T>* temp = head;

        //  将 head 指针向后移动一位
        head = head->next;

        //  释放旧的队首节点内存
        delete temp;

        //  如果出队后队列变空了，需要将 tail 也设为 nullptr
        if (head == nullptr) {
            tail = nullptr;
        }

        count--;
        return result;
    }

    // 查看队首元素 
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("队列为空，无首元素");
        }
        return head->data;
    }
    // 清空队列并释放所有内存
    void makeEmpty() {
        Node<T>* current = head;

        // 遍历链表并逐个释放节点内存
        while (current != nullptr) {
            Node<T>* nextNode = current->next; // 暂存下一个节点的地址
            delete current;                   // 释放当前节点
            current = nextNode;               // 移动到下一个节点
        }

        // 重置控制变量到初始状态
        head = nullptr; // 队首指针置空
        tail = nullptr; // 队尾指针置空
        count = 0;      // 元素数量置零

   
    }
};