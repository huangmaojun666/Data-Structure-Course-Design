#include <iostream>
#include"6_2452776_黄茂军.h"
using namespace std;

//定义家庭成员结点
struct MemberNode{
	String name;
	MemberNode* parent;
	Vector<MemberNode*> children;
	//默认构造函数
	MemberNode() {
		name = "";
		parent = NULL;
		children.make_empty();
	}
	//节点构造函数(已知姓名）
	MemberNode(String name) {
		this->name = name;
		parent = NULL;
		children.make_empty();
	}
};
//定义家庭树
class FamilyTree {
private:
	MemberNode* root;//根结点指针
	//用递归方式清除家庭树
	void destroy(MemberNode* node) {
		if (node == NULL) {
			return;
		}
		else{
			for (int i = 0; i < node->children.size(); i++) {
				destroy(node->children[i]);
			}
			delete node;
			node = NULL;
		}
	}
public:
	FamilyTree() {
		root = NULL;
	}
	FamilyTree(String name) {
		root = new MemberNode;
		root->name = name;
		root->parent = NULL;
		root->children.make_empty();
	}
	~FamilyTree() {
		if (root!= NULL) {
			destroy(root);
			root = NULL;
		}
	}
	//查找家庭成员
	MemberNode* find(const String& name, MemberNode* root)const;
	//完善家庭
	void completeFamily(const String& parent, Vector<String>& children, MemberNode* root);
	//添加家庭成员
	void addMember(const String& parent,const String& child, MemberNode* root);
	//解散局部家庭
	void dissolveFamily(const String& name, MemberNode* root);
	//更改家庭成员姓名
	void changeName(const String& oldName, const String& newName, MemberNode* root);
	//打印家庭成员
	void printchildren(MemberNode* parent)const;
	//获取根节点，用于外部调用
	MemberNode* getRoot()const {
		return root;
	}
};
//查找家庭成员
MemberNode* FamilyTree::find(const String& name, MemberNode* root)const {
	if (root == NULL) {
		return NULL;
	}
	//如果找到了，则返回该结点
	if (root->name == name) {
		return root;
	}
	else {
		//否则，遍历子结点
		for (int i = 0; i < root->children.size(); i++) {
			MemberNode* node = find(name, root->children[i]);
			if (node!= NULL) {
				return node;
			}
		}
		return NULL;
	}
}
//完善家庭
void FamilyTree::completeFamily(const String& parent, Vector<String>& children, MemberNode* root) {
	MemberNode* parentNode = find(parent,root);
	if (parentNode == NULL) {
		cout << "父亲不存在！" << endl;
		return;
	}
	for (int i = 0; i < children.size(); i++) {
		    MemberNode* have_childNode = find(children[i], root);
			//如果孩子不在家庭中，则添加
			if (have_childNode == NULL) {
				MemberNode* childNode = new MemberNode(children[i]);
				childNode->parent = parentNode;
				parentNode->children.push_back(childNode);
			}
			else {
				//如果孩子已经在家谱中，但不是父亲的第一代子孙，则报输入错误
				if (have_childNode->parent != parentNode) {
					cout << "输入错误！ " << children[i] << "不是" << parent << "的第一代子孙！" << endl;
					return;
				}
				//如果孩子已经在家谱中，且是父亲的第一代子孙，则不做任何操作
			}
	}
	printchildren(parentNode);
}
//添加家庭成员
void FamilyTree::addMember(const String& parent, const String& child, MemberNode* root) {
	MemberNode* parentNode = find(parent, root);
	if (parentNode == NULL) {
		cout << "父亲不存在！" << endl;
		return;
	}
	MemberNode* childNode = find(child, root);
	if (childNode != NULL) {
		cout << "孩子已经在家庭中！" << endl;
		return;
	}
	MemberNode* newChildNode = new MemberNode(child);
	newChildNode->parent = parentNode;
	parentNode->children.push_back(newChildNode);
	printchildren(parentNode);
}
//解散局部家庭
void FamilyTree::dissolveFamily(const String& name, MemberNode* root) {
	MemberNode* node = find(name, root);
	if (node == NULL) {
		cout<<name<<"不存在！"<<endl;
		return;
	}
	if (node->children.size() == 0) {
		cout << name << "没有孩子！" << endl;
		return;
	}
	cout << "要解散的家庭的成员姓名: " << name<<endl;
	printchildren(node);
	//删除父节点的所有子树
	for (int i = 0; i < node->children.size(); i++) {
		destroy(node->children[i]);
	}
}
//更改家庭成员姓名
void FamilyTree::changeName(const String& oldName, const String& newName, MemberNode* root) {
	MemberNode* node = find(oldName, root);
	if (node == NULL) {
		cout << "原姓名不存在！" << endl;
		return;
	}
	node->name = newName;
	cout << oldName << "已更名为" << newName << endl;
}
//打印家庭成员
void FamilyTree::printchildren(MemberNode* parent)const {
	cout << parent->name << "的第一代子孙是:";
	for (int i = 0; i < parent->children.size(); i++) {
		cout << parent->children[i]->name << " ";
	}
	cout<<endl;
}
//家谱管理系统菜单函数
void menu() {
	cout<<"**              家谱管理系统                **"<<endl;
	cout<<"=============================================="<<endl;
	cout<<"**         请选择要执行的操作:              **" << endl;
	cout<<"**            A --- 完善家谱                **" << endl;
	cout<<"**            B --- 添加家庭成员            **" << endl;
	cout<<"**            C --- 解散局部家庭            **" << endl;
	cout<<"**            D --- 更改家庭成员姓名        **" << endl;
	cout<<"**            E --- 退出系统                **" << endl;
	cout<<"----------------------------------------------"<< endl;
}

int main() {
	menu();
	cout<<"首先建立一个家谱！"<<endl;
	String ancestor;
	cout << "请输入祖先姓名: ";
	cin >> ancestor;
	cin.ignore(1024, '\n');//清除缓冲区
	//建立家谱
	FamilyTree family(ancestor);
	cout << "此家谱的祖先是: " << ancestor << endl;
	while (1) {
		cout << endl;
		char choice;
		cout << "请输入要执行的操作: ";
		cin >> choice;
		cin.ignore(1024, '\n');//因为输入格式基本都是字符串类型，所以缓冲区的残留需要清理
		if(!('a'<=choice&&choice<='e')&&!(choice>='A'&&choice<='E')){
			cout<<"输入错误，请重新输入"<<endl;
			cin.clear();
			continue;
		}
		switch (choice) {
		case 'a':
		case 'A':
		{
			String parent;
			cout << "请输入要建立家庭的人的姓名:  ";
			cin >> parent;
			cin.ignore(1024, '\n');//清除缓冲区
			if (family.find(parent, family.getRoot()) == NULL) {
				cout << "输入错误，" << parent << "不存在！" << endl;
				continue;
			}
			int n;
			cout << "请输入" << parent << "的孩子数:  ";
			cin >> n;
			if (cin.fail() || n < 0) {
				cout << "输入错误，请重新输入" << endl;
				cin.clear();
				cin.ignore(1024, '\n');//清除缓冲区
				continue;
			}
			Vector<String> children;
			cout << "请依次输入" << parent << "的孩子姓名:  ";
			for (int i = 0; i < n; i++) {
				String child;
				cin >> child;
				children.push_back(child);
			}

			family.completeFamily(parent, children, family.getRoot());
			break;
		}
		case 'b':
		case 'B':
		{
			String parent;
			cout << "请输入要添加人儿子（或女儿）的人的姓名: ";
			cin >> parent;
			cin.ignore(1024, '\n');//清除缓冲区
			if (family.find(parent, family.getRoot()) == NULL) {
				cout << "输入错误，" << parent << "不存在！" << endl;
				continue;
			}
			String child;
			cout << "请输入" << parent << "新添加的儿子（或女儿）的姓名: ";
			cin >> child;
			cin.ignore(1024, '\n');
			family.addMember(parent, child, family.getRoot());
			break;
		}
		case 'c':
		case 'C': {
			String name;
			cout << "请输入要解散的家庭的姓名: ";
			cin >> name;
			cin.ignore(1024, '\n');//清除缓冲区
			family.dissolveFamily(name, family.getRoot());
			break;
		}
		case 'd':
		case 'D': {
			String oldName;
			cout << "请输入要更改姓名的人的目前姓名: ";
			cin >> oldName;
			cin.ignore(1024, '\n');//清除缓冲区
			String newName;
			cout << "请输入更改后的姓名: ";
			cin >> newName;
			cin.ignore(1024, '\n');//清除缓冲区
			family.changeName(oldName, newName, family.getRoot());
			break;
		}
		case 'e':
		case 'E': {
			cout << "系统已退出" << endl;
			exit(0);
		}
		}
	}
	return 0;
}