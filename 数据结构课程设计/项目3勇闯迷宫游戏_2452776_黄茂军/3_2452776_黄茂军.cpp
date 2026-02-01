#include<iostream>
#include"3_2452776_黄茂军.h"
using namespace std;
//迷宫初始化函数
void initMaze(int** maze, int row, int col) {
	cout << "请输入迷宫地图（0表示通路，1表示墙壁）：" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> maze[i][j];
			//输入错误处理
			if (cin.fail() || (maze[i][j] != 0 && maze[i][j] != 1)) {
				cout << "输入错误，请重新输入迷宫地图！" << endl;
				cin.clear();
				cin.ignore(10000, '\n');
				i = -1; // 重置行索引以重新输入
				break;
			}
		}
	}
}
//路口结构体
struct Intersection {
	int x;
	int y;
};
//方向数组，表示上右下左四个方向的移动
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
//用于存储路径的栈
Vector<Intersection> path;

//寻找迷宫路径的函数（采用递归方式实现）
int findPath(int x, int y, int ex, int ey,int** maze, int row, int col) {
	if (x == ex && y == ey) {
		maze[x][y] = 2; // 标记终点为已走过
		path.push_back({ x, y }); // 将终点加入路径栈
		return 1; // 到达终点，找到路径
	}
	maze[x][y] = 2; // 标记当前位置为已走过
	path.push_back({ x, y }); // 将当前位置加入路径栈
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		// 检查新位置是否在迷宫范围内且未走过且不是墙
		if (nx >= 0 && nx < row && ny >= 0 && ny < col && maze[nx][ny] == 0) {
			if (findPath(nx, ny, ex, ey, maze, row, col)) {
				return 1; // 如果找到路径，返回成功
			}
		}
	}
	maze[x][y] = 0; // 回溯，取消标记
	path.pop_back(); // 回溯，弹出当前位置
	return 0; // 未找到路径
}
//迷宫显示函数
//#号表示墙，×号表示路径，0表示未走过的点
void printMaze(int** maze, int row, int col) {
	cout << "         ";
	for (int i = 0; i < col; i++) {
		cout << i << "列      ";
	}
	cout << endl;
	for (int i = 0; i < row; i++) {
		cout << i << "行      ";
		for (int j = 0; j < col; j++) {
			if(maze[i][j]==1)
				cout << "#        ";
			else if(maze[i][j]==2)
				cout << "×       ";
			else
				cout << "0        ";
		}
		cout << endl;
	}
}
int main() {
	int sx , sy ; // 起点坐标
	int ex , ey ; // 终点坐标
	int row, col; // 迷宫行列数
	while(1){
		cout << "请输入迷宫的行数和列数：";
		cin >> row >> col;
		if(cin.fail() || row <= 0 || col <= 0) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout<<"输入错误，请重新输入！"<<endl;
			continue;
		}
		break;
		
	}
	//定义二级指针表示迷宫
	int** maze = new int*[row];
	for (int i = 0; i < row; i++) {
		maze[i] = new int[col];
	}
	initMaze(maze, row, col);
	while(1){
		cout << "请输入起点坐标（行 列）：";
		cin >> sx >> sy;
		if(cin.fail() || sx < 0 || sx >= row || sy < 0 || sy >= col || maze[sx][sy]==1) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout<<"输入错误，请重新输入！"<<endl;
			continue;
		}
		cout << "请输入终点坐标（行 列）：";
		cin >> ex >> ey;
		if(cin.fail() || ex < 0 || ex >= row || ey < 0 || ey >= col || maze[ex][ey]==1) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout<<"输入错误，请重新输入！"<<endl;
			continue;
		}
		if(sx==ex && sy==ey){
			cout<<"起点不能与终点相同，请重新输入！"<<endl;
			continue;
		}
		break;
	}
	//如果找到路径则打印迷宫地图
	if (findPath(sx, sy, ex, ey, maze, row, col)) {
		cout << "迷宫地图：" << endl;
		printMaze(maze, row, col);
		cout << endl;
		cout << "迷宫路径：" << endl;
		for(int i = 0; i < path.size(); i++){
			if (i == path.size()-1) {
				cout << "<" << path[i].x << "," << path[i].y << ">";//最后一个元素后不加箭头
				return 0;
			}

			else {
				cout << "<" << path[i].x << "," << path[i].y << ">" << " ---> ";
			}

				
			
		}
	}
	else {
		cout << "无路径可达终点！" << endl;
	}
	return 0;
}