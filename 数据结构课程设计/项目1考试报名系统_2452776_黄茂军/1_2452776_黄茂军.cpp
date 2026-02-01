#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include"1_2452776_黄茂军.h"//自定义链表
using namespace std;
//学生结构体
typedef struct {
	int id;
	String name;
	String gender;
	int age;
	String major;
}stu;
//学生信息类
class StudentInfo {
private:
	List<stu> students;//学生链表
public:
	//添加学生信息
	bool addStudent(const stu& s) {
		return students.insert(students.length(), s);
	}
	//插入学生信息
	bool insertStudent(int i, stu& s) {
		if(students.insert(i - 1, s)) return true;
		return false;
	}
	//删除学生信息
	bool removeStudent(int i) {
		if(students.remove(i)) return true;
		return false;
	}
	//查找第i个学生的信息
	ListNode<stu>* find(int i) const{
		return students.search(i);
	}
	//修改学生信息
	bool modifyStudent(int i, const stu& s) {
		ListNode<stu>* p = students.search(i);
		if (p != nullptr) {
			p->data = s;
			return true;
		}
		return false;
	}
	//统计学生人数
	int getStudentCount() const {
		return students.length();
	}
	//获取学生信息
	bool initStudent( String& str) {
		stu s;
		char name_buf[100] = { 0 };
		char gender_buf[100] = { 0 };
		char major_buf[100] = { 0 };
		sscanf(str.c_str(), "%d %s %s %d %s", &s.id, name_buf, gender_buf, &s.age, major_buf);
		s.name = name_buf;
		s.gender = gender_buf;
		s.major = major_buf;
		return addStudent(s);
	}
	//检查用户输入学生信息是否有效
	bool checkStudentInfo( String& line) const {
		int id, age; 
		char name_buf[100] = { 0 };
		char gender_buf[100] = { 0 };
		char major_buf[100] = { 0 };
		String gender;
		int ret = sscanf(line.c_str(), "%d %s %s %d %s", &id, name_buf, gender_buf, &age, major_buf);
		if (ret != 5) {
			return false;
		}
		if (id <= 0 || age <= 0) {
			return false;
		}
		gender = gender_buf;
		if (gender != "男" && gender != "女") {
			return false;
		}
		return true;
	}
	//根据选择的操作执行相应功能
	bool performOperation(int choice, StudentInfo& stuinfo) {
		switch (choice) {
		case 1: {
			//插入操作
			cout << "请输入你要插入的考生位置：";
			int pos;
			cin >> pos;
			cout << "请输入考生的考号，姓名，性别，年龄及报考类别（以空格分隔）：" << endl;
			String line;
			cin.ignore();//清除缓冲区的换行符
			line.getline(cin);//自定义字符串类的getline函数
			while(!checkStudentInfo(line)){
				cout << "输入的考生信息有误，请重新输入考生的考号，姓名，性别，年龄及报考类别（以空格分隔）：" << endl;
				line.getline(cin);
			}
			stu s;
			char name_buf[100] = { 0 };
			char gender_buf[100] = { 0 };
			char major_buf[100] = { 0 };
			sscanf(line.c_str(), "%d %s %s %d %s", &s.id, name_buf, gender_buf, &s.age, major_buf);
			s.name = name_buf;
			s.gender = gender_buf;
			s.major = major_buf;
			stuinfo.insertStudent(pos, s);
			break;
		}
		case 2: {
			//删除操作
			cout << "请输入你要删除的考生的考号：";
			int id;
			cin >> id;
			//查找考号对应的位置
			ListNode<stu>* p = nullptr;
			for (int i = 1; i <= stuinfo.getStudentCount(); i++) {
				 p = stuinfo.find(i);
				if (p != nullptr && p->data.id == id) {
					cout << "你删除的考生信息为:" << p->data.id << "   " << p->data.name << "   " << p->data.gender << "   " << p->data.age << "   " << p->data.major << endl;
					stuinfo.removeStudent(i);
					break;
				}
			}
			if(p->next==nullptr){
				cout << "未找到该考号对应的考生信息！" << endl;
			}
			break;
		}
		case 3: {
			//修改操作
			cout << "请输入你要修改的考生的考号：";
			int id;
			cin >> id;
			//查找考号对应的位置
			ListNode<stu>* p = nullptr;
			int tag = 0;//检查最后一个学生是否为被修改对象
			for (int i = 1; i <= stuinfo.getStudentCount(); i++) {
				p = stuinfo.find(i);
				if (p != nullptr && p->data.id == id) {
					tag = 1;
					cout << "请输入修改后的考生信息（考号，姓名，性别，年龄及报考类别，以空格分隔）：" << endl;
					String line;
					cin.ignore();//清除缓冲区的换行符
					line.getline(cin);//自定义字符串类的getline函数
					while (!stuinfo.checkStudentInfo(line)) {
						cout << "输入的考生信息有误，请重新输入修改后的考生信息（考号，姓名，性别，年龄及报考类别，以空格分隔）：" << endl;
						line.getline(cin);
					}
					stu s;
					char name_buf[100] = { 0 };
					char gender_buf[100] = { 0 };
					char major_buf[100] = { 0 };
					sscanf(line.c_str(), "%d %s %s %d %s", &s.id, name_buf, gender_buf, &s.age, major_buf);
					s.name = name_buf;
					s.gender = gender_buf;
					s.major = major_buf;
					stuinfo.modifyStudent(i,s);
					break;
				}
			}
			if (p->next == nullptr && !tag) {
				cout << "未找到该考号对应的考生信息！" << endl;
			}
			break;
		}
		case 4: {
			//查询操作
			cout << "请输入你要查询的考生的考号：";
			int id;
			cin >> id;
			//查找考号对应的位置
			ListNode<stu>* p = nullptr;
			int tag=0;//检查最后一个学生是否为被查找对象
			for (int i = 1; i <= stuinfo.getStudentCount(); i++) {
				p = stuinfo.find(i);
				if (p != nullptr && p->data.id == id) {
					tag = 1;
					cout << left<<setw(10)<<"考号"<<setw(10)<<"姓名"<<setw(10)<<"性别"<<setw(10)<<"年龄"<<setw(10)<<"报考类别"<<endl;
					cout << left<<setw(10)<<p->data.id<<setw(10)<<p->data.name<<setw(10)<<p->data.gender<<setw(10)<<p->data.age<<setw(10)<<p->data.major<<endl;
					break;
				}
			}
			if (p->next == nullptr&&!tag) {
				cout << "未找到该考号对应的考生信息！" << endl;
			}
			break;
		}
		case 5: {
			//统计操作
			int count = stuinfo.getStudentCount();
			cout << "当前考生总人数为：" << count << endl;
			break;
		}
		case 0:
			//取消操作
			return false;
		default:
			cout << "无效的选择，请重新选择！" << endl;
			return false;
		}
		return true;
	}
	//显示所有学生信息
	void displayAllStudents() const {
		if(students.isEmpty()){
			cout<<"当前无考生信息！"<<endl;
			return;
		}
		ListNode<stu>* p = students.search(1);
		cout << left << setw(10) << "考号" << setw(10) << "姓名" << setw(10) << "性别" << setw(10) << "年龄" << setw(10) << "报考类别" << endl;
		while (p != nullptr) {
			cout << left << setw(10) << p->data.id << setw(10) << p->data.name << setw(10) << p->data.gender << setw(10) << p->data.age << setw(10) << p->data.major << endl;
			p = p->next;
		}
		cout << endl;
	}
};
int main() {
	StudentInfo stuinfo;
	cout << "首先请建立考生信息系统！" << endl;
	int n;
	cout << "请输入考生人数：";
	cin >> n;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别（以空格分隔）：" << endl;
	cin.get();//清除缓冲区的换行符
	for (int i = 0; i < n; i++) {
		String line;
		line.getline(cin);//自定义字符串类的getline函数
		while (!stuinfo.checkStudentInfo(line)) {
			cout << "输入信息有误，请重新输入第" << i + 1 << "位考生的信息：" << endl;
			line.getline(cin);
		}
		stuinfo.initStudent(line);
	}
	stuinfo.displayAllStudents();
	cout << "请选择你要进行的操作（1为插入，2为删除，3为修改，4为查询，5为统计，0为取消操作）"<<endl;
	int choice;
	while (true) {
		cout << "请选择你要进行的操作：";
		cin >> choice;
		if (choice == 0) {
			cout << "操作已取消，退出系统！" << endl;
			return 0;
		}
		stuinfo.performOperation(choice, stuinfo);
		stuinfo.displayAllStudents();
	}
	return 0;
}