#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<cstring>
#include<climits>
#include <windows.h>
using namespace std;
#define MAXV 100
// 边结点
struct ArcNode {
    int adjvex;            // 指向的顶点下标
    ArcNode* next;         // 下一条边
};

// 顶点（课程）
struct VNode {
    char id[10];           // 课程编号，如 c01
    char name[30];         // 课程名称
    int hours;             // 学时
    int term;              // 指定学期（0 表示不指定）
    int finalTerm;         // 实际安排学期（1-8）
    ArcNode* first;        // 邻接表头指针
};
struct Slot {
    char cname[30];
};

Slot table[9][5][10];
// table[学期][星期][节次]，学期 1-8

// 图结构
struct ALGraph {
    VNode vertices[MAXV];
    int indegree[MAXV];    // 入度数组
    int vexnum;            // 顶点数
    int arcnum;            // 边数
};
//初始化图
void InitGraph(ALGraph& G) {
    G.vexnum = 0;
    G.arcnum = 0;
    for (int i = 0; i < MAXV; i++) {
        G.indegree[i] = 0;
        G.vertices[i].first = NULL;
    }
}
//加边
void AddArc(ALGraph& G, int from, int to) {
    ArcNode* p = new ArcNode;
    p->adjvex = to;
    p->next = G.vertices[from].first;
    G.vertices[from].first = p;

    G.indegree[to]++;
    G.arcnum++;
}

//拓扑排序
bool TopologicalSort(ALGraph& G, int topo[]) {
    int stack[MAXV];       // 独立的栈数组
    int top = -1;          // 栈顶指针
    int count = 0;         // 拓扑序列中已处理的顶点数
    int indeg[MAXV];

    // 复制入度数组
    for (int i = 0; i < G.vexnum; i++)
        indeg[i] = G.indegree[i];

    // 把所有入度为 0 的顶点入栈
    for (int i = 0; i < G.vexnum; i++) {
        if (indeg[i] == 0) {
            stack[++top] = i;
        }
    }

    // 处理栈中的顶点
    while (top != -1) {
        int v = stack[top--];     // 从栈中取出顶点
        topo[count++] = v;        // 存入拓扑序列结果数组

        // 遍历 v 的所有后继顶点
        ArcNode* p = G.vertices[v].first;
        while (p) {
            int k = p->adjvex;
            if (--indeg[k] == 0) {
                stack[++top] = k;  // 入度变为 0，入栈
            }
            p = p->next;
        }
    }

    // 如果处理的顶点数小于总数，说明有环
    return count == G.vexnum;
}

//初始化课表
void InitAllTables() {
    for (int t = 1; t <= 8; t++)
        for (int d = 0; d < 5; d++)
            for (int p = 0; p < 10; p++)
                strcpy(table[t][d][p].cname, "");
}

//根据课程编号定位顶点下标
int LocateVex(ALGraph& G, const char* id) {
    for (int i = 0; i < G.vexnum; i++) {
        if (strcmp(G.vertices[i].id, id) == 0)
            return i;
    }
    return -1;
}
// 在指定一天 day 上，按给定大节优先表 prefers 安放 len 连节
bool TryPlaceBlockInDay(int term, int day, const char* cname,
    const int prefers[][2], int preferCount, int len)
{
    for (int i = 0; i < preferCount; ++i) {
        int start = prefers[i][0];
        int segLen = prefers[i][1];
        if (segLen < len) {
            continue;
        }
        int end = start + segLen; // [start, end)

        for (int s = start; s + len <= end && s + len <= 10; ++s) {
            bool ok = true;
            for (int k = 0; k < len; ++k) {
                if (strcmp(table[term][day][s + k].cname, "") != 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                for (int k = 0; k < len; ++k) {
                    strcpy(table[term][day][s + k].cname, cname);
                }
                return true;
            }
        }
    }
    return false;
}

// 在指定一天 day 上，从早到晚随便找 len 连节
bool TryPlaceAnywhereInDay(int term, int day, const char* cname, int len)
{
    for (int p = 0; p + len <= 10; ++p) {
        bool ok = true;
        for (int k = 0; k < len; ++k) {
            if (strcmp(table[term][day][p + k].cname, "") != 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int k = 0; k < len; ++k) {
                strcpy(table[term][day][p + k].cname, cname);
            }
            return true;
        }
    }
    return false;
}

// 在指定学期安排课程
bool PlaceCourseInTerm(int term, const char* cname, int hours)
{
    if (hours <= 0) {
        return true;
    }

    // 按 4=2+2、5=3+2、6=3+3 拆块，其它 3>2>1
    int blocks[16];
    int blockCount = 0;
    int left = hours;

    while (left > 0) {
        if (left == 4) {
            blocks[blockCount++] = 2;
            blocks[blockCount++] = 2;
            left -= 4;
        }
        else if (left == 5) {
            blocks[blockCount++] = 3;
            blocks[blockCount++] = 2;
            left -= 5;
        }
        else if (left == 6) {
            blocks[blockCount++] = 3;
            blocks[blockCount++] = 3;
            left -= 6;
        }
        else if (left >= 3) {
            blocks[blockCount++] = 3;
            left -= 3;
        }
        else if (left == 2) {
            blocks[blockCount++] = 2;
            left -= 2;
        }
        else { // left == 1
            blocks[blockCount++] = 1;
            left -= 1;
        }
    }

   
    const int threePrefers[2][2] = {
        { 2, 3 }, // 第 2 大节 3-5 节 
        { 7, 3 }  // 第 4 大节 8-10 节 
    };
    const int threePrefCount = 2;

    const int twoPrefers[2][2] = {
        { 0, 2 }, // 第 1 大节 1-2 节 
        { 5, 2 }  // 第 3 大节 6-7 节 
    };
    const int twoPrefCount = 2;

    int weekday = 0; // 最近一次排课的工作日 

    //  依次排每一块
    for (int b = 0; b < blockCount; ++b) {
        int len = blocks[b];
        bool placed = false;

        // 按“隔一天”规则，最多尝试 5 次
        int tryDayCount = 0;
        int curDay = weekday;

        while (tryDayCount < 5 && !placed) {
            if (len == 3) {
                if (TryPlaceBlockInDay(term, curDay, cname,
                    threePrefers, threePrefCount, 3) ) {
                    placed = true;
                    weekday = curDay;
                    break;
                }
            }
            else if (len == 2) {
                if (TryPlaceBlockInDay(term, curDay, cname,
                    twoPrefers, twoPrefCount, 2) ) {
                    placed = true;
                    weekday = curDay;
                    break;
                }
            }
            else { // len == 1
                if (TryPlaceAnywhereInDay(term, curDay, cname, 1)) {
                    placed = true;
                    weekday = curDay;
                    break;
                }
            }

            // 当前 day 不行，按“隔一天”换天
            curDay = (curDay > 2) ? (curDay + 2 - 5) : (curDay + 2);
            ++tryDayCount;
        }

        // 如果按“隔一天”仍排不上，就放宽成任意天
        if (!placed) {
            if (len == 3) {
                for (int day = 0; day < 5 && !placed; ++day) {
                    if (TryPlaceBlockInDay(term, day, cname,
                        threePrefers, threePrefCount, 3)) {
                        placed = true;
                        weekday = day;
                        break;
                    }
                }
            }
            else if (len == 2) {
                for (int day = 0; day < 5 && !placed; ++day) {
                    if (TryPlaceBlockInDay(term, day, cname,
                        twoPrefers, twoPrefCount, 2)) {
                        placed = true;
                        weekday = day;
                        break;
                    }
                }
            }
            else { // len == 1
                for (int day = 0; day < 5 && !placed; ++day) {
                    if (TryPlaceAnywhereInDay(term, day, cname, 1)) {
                        placed = true;
                        weekday = day;
                        break;
                    }
                }
            }
        }

        // 排不下，本门课失败
        if (!placed) {
            return false;
        }

        // 尽量隔一天
        weekday = (weekday > 2) ? (weekday + 2 - 5) : (weekday + 2);
    }

    return true;
}

//安排所有学期课程
bool ScheduleAll(ALGraph& G) {
    InitAllTables();

    for (int t = 1; t <= 8; t++) {
        for (int i = 0; i < G.vexnum; i++) {
            if (G.vertices[i].finalTerm == t) {
                if (!PlaceCourseInTerm(t, G.vertices[i].name, G.vertices[i].hours))
                    return false;
            }
        }
    }
    return true;
}


//输出所有学期课表
void OutputAll() {
    ofstream out("all_semesters.txt");
    if (!out.is_open()) {
        cout << "无法打开输出文件！" << endl;
        return;
    }

    const char* weekNames[5] = { "周一", "周二", "周三", "周四", "周五" };

    
    const int colPeriodWidth = 8;   // "节次"列宽
    const int colDayWidth = 18;  // 每个星期列宽

    for (int t = 1; t <= 8; t++) {
        out << "============================================================" << endl;
        out << "                         第 " << t << " 学期课表" << endl;
        out << "============================================================" << endl;

        // 统一填充和对齐方式
        out.setf(ios::left);
        out.fill(' ');

        // 表头：节次 + 星期
        out << setw(colPeriodWidth) << "节次";
        for (int d = 0; d < 5; d++) {
            out << setw(colDayWidth) << weekNames[d];
        }
        out << endl;

        // 每一节（1-10 节）为一行
        for (int p = 0; p < 10; p++) {
            // 第几节
            out << setw(colPeriodWidth) << (p + 1);

            // 周一到周五
            for (int d = 0; d < 5; d++) {
                if (strcmp(table[t][d][p].cname, "") == 0) {
                    out << setw(colDayWidth) << "空";
                }
                else {
                    out << setw(colDayWidth) << table[t][d][p].cname;
                }
            }
            out << endl;
        }

        out << endl << endl;
    }

    out.close();
}
// 根据文件读入图
void ReadFromFile(ALGraph& G, string filename)
{
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "无法打开输入文件：" << filename << endl;
        exit(1);
    }

    InitGraph(G);

    string line;
    bool firstDataLineFound = false;

    while (getline(in, line)) {
        // 去掉空行 
        if (line.empty()) {
            continue;
        }
        //
        bool allSpace = true;
        for (size_t i = 0; i < line.size(); ++i) {
            if (!isspace((unsigned char)line[i])) {
                allSpace = false;
                break;
            }
        }
        if (allSpace) {
            continue;
        }

		// 跳过表头行
        if (!firstDataLineFound) {
            size_t pos0 = 0;
            while (pos0 < line.size() &&
                isspace((unsigned char)line[pos0])) {
                ++pos0;
            }
            if (pos0 >= line.size()) {
                continue;
            }
            if (line[pos0] != 'c') {
                // 表头行
                continue;
            }
            firstDataLineFound = true;
        }

        
        char id[10] = { 0 };
        int pos = 0;
        // 跳过前导空白
        while (pos < (int)line.size() && isspace((unsigned char)line[pos])) {
            ++pos;
        }
        int idStart = pos;
        while (pos < (int)line.size() && !isspace((unsigned char)line[pos])) {
            ++pos;
        }
		int idLen = pos - idStart;// 课程编号长度
        if (idLen <= 0 || idLen >= (int)sizeof(id)) {
            // 行格式不对
            continue;
        }
        memcpy(id, line.c_str() + idStart, idLen);
        id[idLen] = '\0';

        // 剩余部分（去掉前面的 id）
        while (pos < (int)line.size() && isspace((unsigned char)line[pos])) {
            ++pos;
        }
        if (pos >= (int)line.size()) {
            continue; // 后面什么都没有
        }
        string rest = line.substr(pos);

		// 处理课程名称中间有空格的情况
        string tokens[128];
        int tokenCount = 0;
        int i = 0;
        int n = (int)rest.size();

        while (i < n) {
            // 跳过空白
            while (i < n && isspace((unsigned char)rest[i])) {
                ++i;
            }
            if (i >= n) {
                break;
            }
            int start = i;
            while (i < n && !isspace((unsigned char)rest[i])) {
                ++i;
            }
            int lenTok = i - start;
            if (lenTok > 0 && tokenCount < 128) {
                tokens[tokenCount++] = rest.substr(start, lenTok);
            }
        }

        if (tokenCount < 2) {
            // 至少要有 学时 和 term
            continue;
        }

        //找到两个整数 token：hours 和 term 
        int hours = 0;
        int term = 0;
        int hoursIndex = -1;
        int termIndex = -1;

        for (int iTok = 0; iTok < tokenCount; ++iTok) {
            const string& cur = tokens[iTok];
            const char* cstr = cur.c_str();
			char* endp = NULL;// 用于 strtol 的结束指针
            long val = strtol(cstr, &endp, 10);
            if (*endp == '\0') { // 完整的整数
                if (hoursIndex == -1) {
                    hoursIndex = iTok;
                    hours = (int)val;
                }
                else if (termIndex == -1) {
                    termIndex = iTok;
                    term = (int)val;
                    break;
                }
            }
        }

        if (hoursIndex == -1 || termIndex == -1 || hoursIndex == 0) {
            // 找不到两个整数，或者课程名为空
            continue;
        }

        // 合并课程名（tokens[0 .. hoursIndex-1]） 
        string nameStr;
        for (int iTok = 0; iTok < hoursIndex; ++iTok) {
            if (iTok > 0) {
                nameStr += ' ';
            }
            nameStr += tokens[iTok];
        }

        // ---------- 在图中创建这个课程顶点 ----------
        if (G.vexnum >= MAXV) {
            cerr << "顶点数超过 MAXV，忽略后续课程。" << endl;
            break;
        }

        int idx = G.vexnum++;
        strncpy(G.vertices[idx].id, id, sizeof(G.vertices[idx].id) - 1);
        G.vertices[idx].id[sizeof(G.vertices[idx].id) - 1] = '\0';

        strncpy(G.vertices[idx].name, nameStr.c_str(),
            sizeof(G.vertices[idx].name) - 1);
        G.vertices[idx].name[sizeof(G.vertices[idx].name) - 1] = '\0';

        G.vertices[idx].hours = hours;
        G.vertices[idx].term = term;
        G.vertices[idx].finalTerm = 0;
        G.vertices[idx].first = NULL;

        // 先修课程：tokens[termIndex+1 .. tokenCount-1] 
        for (int iTok = termIndex + 1; iTok < tokenCount; ++iTok) {
            const string& preId = tokens[iTok];
            int preIndex = LocateVex(G, preId.c_str());
            if (preIndex != -1) {
                AddArc(G, preIndex, idx);
            }
        }
    }

    in.close();
}
//给课程分配学期
void AssignTerms(ALGraph& G, int topo[],
    int n1, int n2, int n3, int n4,
    int n5, int n6, int n7, int n8)
{
    const int MAX_TERM = 8;

    int need[MAX_TERM + 1] = { 0 };
    need[1] = n1; need[2] = n2; need[3] = n3; need[4] = n4;
    need[5] = n5; need[6] = n6; need[7] = n7; need[8] = n8;

    int assigned[MAX_TERM + 1] = { 0 }; // 每学期已分配课程数

    //  先把指定学期的课程固定下来
    for (int i = 0; i < G.vexnum; ++i) {
        int v = topo[i];
        if (G.vertices[v].term != 0) {
            int t = G.vertices[v].term;
            if (t < 1) t = 1;
            if (t > MAX_TERM) t = MAX_TERM;
            G.vertices[v].finalTerm = t;
            assigned[t]++;
        }
        else {
            G.vertices[v].finalTerm = 0; 
        }
    }

    // 查找顶点 u 是否为 v 的先修
    auto HasEdge = [&](int u, int v)->bool {
        ArcNode* p = G.vertices[u].first;
        while (p) {
            if (p->adjvex == v) return true;
            p = p->next;
        }
        return false;
        };

    //  按拓扑序遍历，给未指定学期的课程分配学期
    for (int i = 0; i < G.vexnum; ++i) {
        int v = topo[i];
        if (G.vertices[v].finalTerm != 0) {
            // 已经指定或已分配
            continue;
        }

        // 计算所有先修的最大学期
        int maxPreTerm = 0;
        for (int u = 0; u < G.vexnum; ++u) {
            if (HasEdge(u, v)) {
                int preTerm = G.vertices[u].finalTerm;
                if (preTerm == 0) preTerm = 1;
                if (preTerm > maxPreTerm) maxPreTerm = preTerm;
            }
        }

        int earliest = maxPreTerm + 1; // 要求至少放在先修后的一学期
        if (earliest < 1) earliest = 1;
        if (earliest > MAX_TERM) earliest = MAX_TERM; // 超出则只能放最后学期

        // 在 earliest..MAX_TERM 中找第一个还有名额的位置
        int chosen = -1;
        for (int t = earliest; t <= MAX_TERM; ++t) {
            if (assigned[t] < need[t]) {
                chosen = t;
                break;
            }
        }

        // 如果从 earliest..MAX_TERM 都满了，尝试把它放在比 earliest 更早但还有名额的学期
        if (chosen == -1) {
            for (int t = 1; t <= MAX_TERM; ++t) {
                if (assigned[t] < need[t]) {
                    chosen = t;
                    break;
                }
            }
        }
        if (chosen == -1) chosen = MAX_TERM;

        G.vertices[v].finalTerm = chosen;
        assigned[chosen]++;
    }
}
int main() {
    SetConsoleOutputCP(65001); // 控制台输出 UTF-8
    ALGraph G;
    int topo[MAXV];

    InitGraph(G);
   string filename;
	cout << "请输入课程数据文件名：";
    cin >> filename;
    ReadFromFile(G, filename);

    if (G.vexnum == 0) {
        cout << "没有读到任何课程数据！" << endl;
        return 0;
    }

    if (!TopologicalSort(G, topo)) {
        cout << "存在先修冲突（有环），排课失败！" << endl;
        return 0;
    }
    cout << "请输入每学期的所设课程数" << endl;
	int n1, n2, n3, n4, n5, n6, n7, n8;
    while (1) {
        cin >> n1 >> n2 >> n3 >> n4 >> n5 >> n6 >> n7 >> n8;
        if(cin.fail() || n1<=0 || n2<=0 || n3<=0 || n4<=0 || n5<=0 || n6<=0 || n7<=0 || n8<=0) {
            cout << "输入无效，请输入正整数！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
		}
        if(n1+n2+n3+n4+n5+n6+n7+n8!=G.vexnum) {
            cout << "课程总数与所设课程数之和不符，请重新输入！" << endl;
            continue;
		}
		break;
    }
    AssignTerms(G, topo,n1,n2,n3,n4,n5,n6,n7,n8);

    if (ScheduleAll(G)) {
        OutputAll();
        cout << "8 个学期排课成功，结果已生成到 all_semesters.txt。" << endl;
    }
    else {
        cout << "课时冲突，排课失败！" << endl;
    }
    return 0;
}