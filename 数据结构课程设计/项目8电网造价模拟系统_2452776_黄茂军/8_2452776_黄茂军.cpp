#include<iostream>
#include<climits>
#include"8_2452776_黄茂军.h"
using namespace std;
#define MAX INT_MAX
//定义菜单选项
void menu() {
	cout << "**             电网造价模拟系统             **" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "**             A --- 创建电网的顶点         **" << endl;
	cout << "**             B --- 创建电网的边           **" << endl;
	cout << "**             C --- 构造最小生成树         **" << endl;
	cout << "**             D --- 显示最小生成树         **" << endl;
	cout << "**             E --- 退出系统               **" << endl;
	cout << "----------------------------------------------" << endl;

}
//定义最小生成树结点
struct MSTNode {
	char start; //起点
	char end;   //终点
	int weight; //权重
};
//定义最小生成树
class MST {
	private:
		Vector<MSTNode> edges; //存储最小生成树的边
public:
	void addEdge(char start, char end, int weight) {
			MSTNode edge = { start, end, weight };
			edges.push_back(edge);
		}
	void display() {
		if(this->size()==0){
			cout<<"最小生成树为空！"<<endl;
			return;
		}
		cout << "最小生成树的顶点及边为：" << endl;
		for (int i = 0; i < edges.size(); ++i) {
			cout << edges[i].start << "-<" << edges[i].weight<< ">-" << edges[i].end<< "    ";
		}
		cout << endl;
	}
	void clear() {
			edges.make_empty();
	}
	int size() const {
			return edges.size();
	}
};
//查找顶点在动态数组中的下标(便于后续操作)
int index(char c, Vector<char>& vertices) {
	for (int i = 0; i < vertices.size(); ++i) {
		if (vertices[i] == c) {
			return i;
		}
	}
	return -1;
}
//初始化邻接矩阵（包含输入判断）
void Matrix(int** matrix, Vector<char>& vertices,int size) {
	char start, end;
	int weight;
	for (int i = 0; i < size; i++) {
		cout << "请输入两个顶点及边: ";
		cin >> start >> end >> weight;
		int row = index(start, vertices);
		int col = index(end, vertices);
		if (row == -1 || col == -1) {
			cout << "输入的顶点不存在，请重新输入！" << endl;
			i--;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		if(row==col){
			cout << "不能创建自环边，请重新输入！" << endl;
			i--;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		if(cin.fail()||weight<=0) {
			cout << "输入的边权重不合法，请重新输入！" << endl;
			i--;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		if(matrix[row][col]!=MAX){
			cout << "该边已存在，请重新输入！" << endl;
			i--;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		matrix[row][col] =matrix[col][row]= weight;
	}
	return ;
}
void dfs(int v, int num, int** matrix, bool visited[]) {
	visited[v] = true;
	for (int j = 0; j < num; ++j) {
		// 有边且未访问过
		if (matrix[v][j] != MAX && !visited[j]) {
			dfs(j, num, matrix, visited);
		}
	}
}
int main() {
	menu();
	Vector<char> vertices; //存储顶点
	int num;//顶点数量
	int** matrix = nullptr; //邻接矩阵
	MST mst; //最小生成树对象
	int a_tag = 0; //标记是否已输入过顶点
	char choice;
	while (1) {
		cout << endl;
		cout << "请选择要进行的操作: ";
		cin >> choice;
		switch (choice) {
		case 'A':
		case 'a': {
			if (a_tag) {
				cout << "顶点已创建，不能重复创建！" << endl;
				break;
			}
			char vertex;
			while (1) {
				cout << "请输入顶点的数量:";
				cin >> num;
				if (cin.fail() || num <= 0) {
					cout << "输入的顶点数量不合法！" << endl;
					cin.clear();
					cin.ignore(10000, '\n');
					continue;
				}
				matrix = new int* [num];
				for (int i = 0; i < num; ++i) {
					matrix[i] = new int[num];
				}
				for (int i = 0; i < num; ++i) {
					for (int j = 0; j < num; ++j) {
						matrix[i][j] = MAX;
					}
				}
				cout << "依次输入各顶点名称: "<<endl;
				for (int i = 0; i < num; ++i) {
					cin >> vertex;
					if (index(vertex, vertices) != -1) {
						cout << "顶点重复，请重新输入！" << endl;
						cin.ignore(10000, '\n');
						vertices.make_empty();
						i = -1;
						continue;
					}
					vertices.push_back(vertex);
				}
				break;
			}
			a_tag = 1;
			break;
		}
		case 'B':
		case 'b': {
			if (vertices.is_empty()) {
				cout << "请先输入顶点！" << endl;
				break;
			}
			if (vertices.size() == 1) {
				cout << "顶点数量不足，无法创建边！" << endl;
				break;
			}
			int size;
			cout << "请输入要创建的边的数量: ";
			cin >> size;
			if (cin.fail() || size <= 0) {
				cout << "输入的边数量不合法！" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				break;
			}
			Matrix(matrix, vertices, size);
			break;
		}
		case 'C':
		case 'c': {
			if (vertices.is_empty()) {
				cout << "请先输入顶点！" << endl;
				break;
			}
			if (matrix == nullptr) {
				cout << "还未创建邻接矩阵，请先创建边！" << endl;
				break;
			}
			// 使用 DFS 检查是否连通
			bool* visited = new bool[num];
			for (int i = 0; i < num; ++i) {
				visited[i] = false;
			}

			// 从 0 号顶点开始（前提是图里至少有一个顶点）
			dfs(0, num, matrix, visited);

			// 检查是否所有顶点都被访问到
			bool connected = true;
			for (int i = 0; i < num; ++i) {
				if (!visited[i]) {
					connected = false;
					break;
				}
			}

			if (!connected) {
				cout << "图不连通，无法构造最小生成树！" << endl;
				delete[] visited; 
				break;
			}

			delete[] visited;
			char start;
			cout << "请输入起始顶点:";
			cin >> start;
			int start_index = index(start, vertices);
			if (start_index == -1) {
				cout << "输入的顶点不存在！" << endl;
				break;
			}
			mst.clear(); //清空之前的最小生成树
			// Prim算法构造最小生成树
			int* lowcost = new int[num];//记录各顶点到起始点的最小权值
			int* nearest = new int[num]; //记录各顶点到起始点的最近顶点
			for (int i = 0; i < num; ++i) {

				lowcost[i] = matrix[start_index][i];
				nearest[i] = start_index;
			}
			lowcost[start_index] = 0; //起始点权值设为0
			nearest[start_index] = -1; //起始点没有最近顶点
			//加n-1条边
			for (int i = 0; i < num - 1; i++) {
				int min = MAX;
				//找到权值最小的边
				int k;
				for (int j = 0; j < num; ++j) {
					if (nearest[j]!=-1 && lowcost[j] < min) {
						min = lowcost[j];
						k = j;
					}
				}
				//将找到的边加入最小生成树
				mst.addEdge(vertices[nearest[k]], vertices[k], min);
				for (int j = 0; j < num; ++j) {
					if (lowcost[j] != 0 && matrix[k][j] < lowcost[j]) {
						lowcost[j] = matrix[k][j];
						nearest[j] = k;

					}
				}
				nearest[k] = -1; //标记该顶点已加入最小生成树
				lowcost[k] = 0;//标记该顶点已加入最小生成树
			}
			delete[] lowcost;
			delete[] nearest;
			break;
		}
		case 'D':
		case 'd': {
			if (mst.size() == 0) {
				cout << "最小生成树为空，请先构造最小生成树！" << endl;
				break;
			}
			mst.display();
			break;
		}
		case 'E':
		case 'e': {
			cout << "退出系统！" << endl;
			//释放邻接矩阵内存
			if (matrix != nullptr) {
				for (int i = 0; i < num; ++i) {
					delete[] matrix[i];
				}
				delete[] matrix;
			}
			exit(1);
		}
		default: {
			cout << "输入选项不合法，请重新输入！" << endl;
			break;
		}
		}
	}
}
		