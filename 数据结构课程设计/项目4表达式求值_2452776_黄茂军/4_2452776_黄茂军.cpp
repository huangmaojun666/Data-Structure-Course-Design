#include<iostream>
#include"4_2452776_黄茂军.h"//自定义栈和字符串
using namespace std;
//操作数栈
stack<int> num_stack;

//运算符栈
stack<String> operator_stack;
//定义运算符优先级函数
int pre(String op) {
	if (op == "u+" || op == "u-")return 4;//一元运算符优先级最高
	else if (op == "^")return 3;//乘方
	else if (op == "%"||op=="*"||op=="/")return 2;//乘除取模
	else if(op== "+" || op == "-")return 1;//加减
	else return 0;//等号
}
//定义计算函数
int compute(int a, int b, char op) {
	switch (op) {
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	case '%':return a % b;
	case '^': {
		int result = 1;
		for (int i = 0; i < b; ++i) {
			result *= a;
		}
		return result;
	}
	default:return 0;
	}
}
//判断是否为一元运算符
bool is_unary(String op) {
	return op == "u+" || op == "u-";
}
//判断是否为右结合运算符
bool is_right_ass(String op) {
	return op == "^" || op == "u+" || op == "u-";
}
//判断是否为运算符
bool is_op(char op) {
	return op == '^' || op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '(' || op == ')' || op == '='||op==' ';
}
//判断是否为数字
bool is_num(char op) {
	return op >= '0' && op <= '9';
}
//判断数字是否合法(首位不能为0）
bool is_rightnum(Vector<char>& digit) {
	return !(digit.size()>1&&digit[0]=='0');
}
//将字符数组转换为数字
int to_number(Vector<char>& digit) {
	int num = 0;
	for (int i = 0; i < digit.size(); i++) {
		num = num * 10 + (digit[i] - '0');
	}
	return num;
}

int main() {
	String express;
	while (1) {
		num_stack.make_empty();
		operator_stack.make_empty();
		int inputerro = 0;//用于标志输入错误
		cout << "请输入表达式:" << endl;
		express.getline(cin);
		//如果输入表达式未加=，手动添加
		if (express[express.size() - 1] != '=') {
			express = express + "=";
		}
		Vector<char> digit;//用于存储连续数字字符方便转化
		for (int i = 0; i < express.size(); i++) {
			//初步判断是否输入错误
			if (!is_num(express[i]) && !is_op(express[i])) {
				cout << "表达式输入错误，请重新输入！" << endl;
				inputerro = 1;
				break;
			}
			else {
				//如果字符为数字
				if (is_num(express[i])) {
					while (i < express.size() && is_num(express[i])) {
						digit.push_back(express[i]);
						i++;
					}
					i--;
					//判断数字是否合法
					if (!is_rightnum(digit)) {
						cout << "表达式输入错误，请重新输入！" << endl;
						inputerro = 1;
						digit.make_empty();
						break;
					}
					//将数字入栈
					num_stack.push(to_number(digit));
					digit.make_empty();
				}
				//如果字符为运算符
				else {
					//处理运算符
					String op;
					//如果为空格则跳过
					if(express[i]==' ')
						continue;
					//判断是否为一元运算符
					else if ((express[i] == '+' || express[i] == '-') && (i == 0 || is_op(express[i - 1]) && express[i - 1] != ')')) {
						op = (express[i] == '+') ? "u+" : "u-";
					}
					else {
						char temp[2] = { express[i],'\0' };
						op = temp;
					}
					//处理右括号
					if (op == ")") {
						if (operator_stack.is_empty() ) {
							cout << "表达式输入错误，请重新输入！" << endl;
							inputerro = 1;
							break;
						}
						else {
							if (operator_stack.get_top() == "(") {
								cout << "表达式输入错误，请重新输入！" << endl;
								inputerro = 1;
								break;
							}
						}
						while (!operator_stack.is_empty() && operator_stack.get_top() != "(") {
							String oper;
							operator_stack.pop(oper);
							if (is_unary(oper)) {
								if (num_stack.is_empty()) {
									cout << "表达式输入错误，请重新输入！" << endl;
									inputerro = 1;
									break;
								}

								int a;
								num_stack.pop(a);
								num_stack.push((oper == "u+") ? a : -a);
							}
							else {
								if (num_stack.size() < 2) {
									cout << "表达式输入错误，请重新输入！" << endl;
									inputerro = 1;
									break;
								}
								int a, b; 
								num_stack.pop(b);
								num_stack.pop(a);
								num_stack.push(compute(a, b, oper[0]));
							}
						}
						if (!operator_stack.is_empty() && operator_stack.get_top() == "(") {
							String op;
							operator_stack.pop(op);//弹出左括号
						}
					}
					//左括号或栈为空直接进栈
					else if(op=="("||operator_stack.is_empty()) {
						operator_stack.push(op);
					}
					else {
						//处理其他运算符
						//如果运算符为右结合，且优先级大于等于栈顶运算符，直接入栈
						//如果运算符为左结合，且优先级大于栈顶运算符，直接入栈
						//否则弹出栈顶运算符进行计算，直到满足上述条件
						while (1) {
							//循环终止条件
							if (operator_stack.is_empty() || operator_stack.get_top() == "(") {
								operator_stack.push(op);
								break;
							}
							else if ((is_right_ass(op) && pre(op) >= pre(operator_stack.get_top())) || (!is_right_ass(op) && pre(op) > pre(operator_stack.get_top()))) {
								operator_stack.push(op);
								break;
							}
							//否则一直弹出栈顶运算符进行计算
							else {
								String oper;
								operator_stack.pop(oper);
								if (is_unary(String(oper))) {
									if (num_stack.is_empty()) {
										cout << "表达式输入错误，请重新输入！" << endl;
										inputerro = 1;
										break;
									}
									int a;
									num_stack.pop(a);
									num_stack.push((oper == "u+") ? a : -a);
								}
								else {
									if (num_stack.size() < 2) {
										cout << "表达式输入错误，请重新输入！" << endl;
										inputerro = 1;
										break;
									}
									int a, b;
									num_stack.pop(b);
									num_stack.pop(a);
									num_stack.push(compute(a, b, oper[0]));
								}
							}
						}

					}
				}
			}
		}
		if (inputerro) {
			continue;
		}
		//如果最后运算符栈不是只剩一个"="，操作数栈不是只有一个数字,则返回输入错误
		if (num_stack.size() != 1 || operator_stack.size() != 1 ) {
			cout << "输入错误，请重新输入！" << endl;
			continue;
		}
		//输出运算结果
		cout << num_stack.get_top() << endl;
		cout << "是否继续？(y/n)  " ;
		char choice;
		cin >> choice;
		cin.ignore();
		if (choice != 'y' && choice != 'Y') {
			break;
		}
	}
	return 0;
}
