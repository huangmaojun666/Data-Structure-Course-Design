#include<iostream>
#include"7_2452776_黄茂军.h"
using namespace std;
//最小堆类
class min_heap {
private:
    Vector<int> heap;
    //获得父节点索引
    int get_parent_index(int child_index) {
        if (child_index == 0) {
            return -1;
        }
        return (child_index - 1) / 2;
    }
    //获得左孩子索引
    int get_left_child_index(int parent_index) {
        return 2 * parent_index + 1;
    }
    //获得右孩子索引
    int get_right_child_index(int parent_index) {
        return 2 * parent_index + 2;
    }
    //向上筛选
    void sift_up(int index) {
        int parent_index = get_parent_index(index);
        if (parent_index == -1) {
            return;
        }
        if (heap[index] < heap[parent_index]) {
            int temp = heap[index];
            heap[index] = heap[parent_index];
            heap[parent_index] = temp;
            sift_up(parent_index);
        }
    }
    //向下筛选
    void sift_down(int index) {
        int left_child_index = get_left_child_index(index);
        int right_child_index = get_right_child_index(index);
        int smallest_index = index;
        if (left_child_index < heap.size() && heap[left_child_index] < heap[smallest_index]) {
            smallest_index = left_child_index;
        }
        if (right_child_index < heap.size() && heap[right_child_index] < heap[smallest_index]) {
            smallest_index = right_child_index;
        }
        if (smallest_index != index) {
            int temp = heap[index];
            heap[index] = heap[smallest_index];
            heap[smallest_index] = temp;
            sift_down(smallest_index);
        }
    }
public:
    void push(int value) {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }
    int pop() {
        if (heap.is_empty()) {
            return -1;
        }
        int root = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        sift_down(0);
        return root;
    }
    int size() {
        return heap.size();
    }
    int top()const {
        return heap[0];
    }
    bool is_empty()const {
        return heap.is_empty();
    }
};
//最小金额计算函数(用哈夫曼算法实现）
int min_cost(min_heap& woods) {
   int cost = 0;
   while (woods.size() > 1) {
       int a = woods.pop();
       int b = woods.pop();
       cost += a + b;
       woods.push(a + b);
   }
   return cost;
   
};
int main() {
    int N;//木头锯成的数量
    while (1) {
        cin >> N;
        if (cin.fail() || N <= 0 || N > 10000) {
            cout << "输入错误，请重新输入！" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        min_heap woods;//木头锯成的长度
        int error_flag = 0;//输入错误标记
        for (int i = 0; i < N; i++) {
            int temp;
            cin >> temp;
            if (cin.fail() || temp <= 0 || temp > 10000) {
                cout << "输入错误，请重新输入！" << endl;
                error_flag = 1;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }
            woods.push(temp);
        }
        //输入错误，跳过本次循环
        if (error_flag) {
            continue;
        }
        int cost = min_cost(woods);
        cout << "最小金额：" << cost << endl;
        break;
    }
    return 0;
}