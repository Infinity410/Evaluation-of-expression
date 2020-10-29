#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<iomanip>
#include <Windows.h>
using namespace std;

typedef struct Node {
	double num;//操作数
	char op;//操作符
	bool flag;//true表示操作数，false表示操作符
}node;
//设置优先级(注意默认操作数的优先级最高，即其不需要进栈，进栈的都是运算符)
map<char, int> p;

void menu();
void change_into();
double calculate_back();
double calculate_medi();
char getPriority(char theta1, char theta2);
double calculate(double b, char theta, double a);
int getIndex(char theta);

vector<char> v1;//中缀表达式的数组
vector<char> v3;//后缀表达式的数组
int main()
{
	menu();
	return 0;
}

int times = 0;
void menu()//菜单
{
	cout << "\t\t------------------------------------------------------" << endl;
	cout << "\t\t                       表达式求值                     " << endl;
	cout << endl;
	cout << "\t\t1. 中缀表达式到后缀表达式的转换 " << endl;
	cout << "\t\t2. 后缀表达式的计算 " << endl;
	cout << "\t\t3. 中缀表达式的计算" << endl;
	cout << "\t\t4. 退出 " << endl;
	cout << endl;
	cout << "\t\t------------------------------------------------------" << endl;
	char n;
	cin >> n;
	switch (n)
	{
	case '1':
		change_into();
		break;
	case '2':
		if (times == 0)
		{
			cout << "请先执行功能1，5秒后返回菜单" << endl;
			Sleep(5 * 1000);    //程序延时5s
			system("CLS");
			menu();
		}
		else
		{
			double ans;
			ans = calculate_back();
			cout << "后缀表达式：";
			for (int i = 0; i < v3.size(); i++)
			{
				cout << v3[i];
			}
			cout << endl;
			cout << "计算结果为：" << ans << endl;
			cout << endl;
			cout << "输入1返回菜单，输入其他结束程序" << endl;
			char o;
			cin >> o;
			if (o == '1')
			{
				system("CLS");
				menu();
			}
			else
			{
				exit(0);
			}
		}
		break;
	case '3':
		cout << "中缀表达式：";
		for (int i = 0; i < v1.size(); i++)
		{
			cout << v1[i];
		}
		cout << endl;
		double ans;
		ans = calculate_medi();
		cout << "计算结果为：" << ans << endl;
		cout << endl;
		cout << "输入1返回菜单，输入其他结束程序" << endl;
		char o;
		cin >> o;
		if (o == '1')
		{
			system("CLS");
			menu();
		}
		else
		{
			exit(0);
		}
		break;
	case '4':
		exit(0);
		break;
	default:
		system("CLS");
		menu();
		break;
	}
}

stack<node> s;//操作符栈
queue<node> q;//后缀表达式队列
void change_into()//中缀表达式转后缀表达式
{
	char c;
	p['+'] = p['-'] = 1;//通过hashmap赋值，判断顺序
	p['*'] = p['/'] = 2;
	cout << "输入中缀表达式，以#号结束：";
	cin >> c;
	char c1[100];	int string_num  = -1;//字符数组用于记录中缀表达式
	vector<char> v2;	
	c1[++string_num] = c;
	while (c != '#')
	{
		cin >> c;
		c1[++string_num] = c;
	}
	string_num++;
	v2.push_back('#');//令#入栈判断结束条件
	int num = 0;
	node temp;
	//输出过程，并控制格式
	cout << setw(num + 1);
	for (int j = 0; j < string_num; j++)
	{
		cout << c1[j];
		v1.push_back(c1[j]);
	}
	cout.width(10);
	num++;
	for (int k = 0; k < v2.size(); k++)
	{
		cout << v2[k];
	}
	cout.width(10);
	for (int k = 0; k < v3.size(); k++)
	{
		cout << v3[k];
	}
	cout << endl;

	for (int i = 0; i < string_num;)
	{
		if (num != string_num)//输出中缀表达式
		{
			cout << setw(num + 1);
			for (int j = num; j < string_num; j++)
			{
				cout << c1[j];
			}
			cout.width(10);
			num++;
		}
		else
		{
			cout << setw(string_num + 10);
		}
		if (c1[i] == '(')//遇到左括号：将其入栈
		{
			temp.flag = false;
			temp.op = c1[i];
			s.push(temp);
			v2.push_back(c1[i]);
			i++;
		}
		else if (c1[i] == ')')//遇到右括号：执行出栈操作，输出到后缀表达式，直到弹出的是左括号
		{
			while (!s.empty() && s.top().op != '(')
			{
				q.push(s.top());
				v3.push_back(s.top().op);
				s.pop();
				v2.pop_back();
			}
			s.pop();//弹出左括号
			v2.pop_back();
			i++;
		}
		else if (c1[i] >= '0' && c1[i] <= '9')//如果是数字
		{
			temp.flag = true;
			temp.num = c1[i] - '0';
			v3.push_back(c1[i]);
			i++;
			q.push(temp);//操作数进入后缀表达式
		}
		else//如果是操作符
		{
			temp.flag = false;
			while (!s.empty() && p[s.top().op] >= p[c1[i]])//遇到其他运算符：弹出所有优先加大于或等于该运算符的栈顶元素，然后将该运算符入栈
			{
				q.push(s.top());
				v3.push_back(s.top().op);
				s.pop();
				v2.pop_back();
			}
			temp.op = c1[i];
			s.push(temp);
			v2.push_back(temp.op);
			i++;
		}
		for (int k = 0; k < v2.size(); k++)
		{
			if (v2.front() == v2.back() && v2.size() != 1)
			{
				cout << " ";
			}
			else 
			{ 
				cout << v2[k]; 
			}
		}
		cout << setw(string_num - v2.size());
		for (int k = 0; k < v3.size(); k++)//将栈中内容依次弹出后缀表达式
		{
			cout << v3[k];
		}
		cout << endl;
	}
	cout << endl;
	cout << "输入1返回菜单，输入其他结束程序" << endl;
	char o;
	cin >> o;
	if (o == '1')
	{
		system("CLS");
		times++;
		menu();
	}
	else
	{
		exit(0);
	}
	
}

stack<node> s1;//存放操作数的，为了计算后缀表达式的值
double calculate_back()
{
	cout << endl;
	double num_a, num_b;//操作数a,b
	node cur, temp;
	vector<char> b1;
	b1 = v3;
	vector<int> b2;
	int num = 1;
	int string_num = b1.size();
	//输出后缀表达式，控制格式
	cout.setf(ios::right);
	for (int j = 0; j < b1.size(); j++)
	{
		cout << b1[j];
	}
	cout << endl;

	while (!q.empty())//后缀队列非空
	{
		if (num != string_num)
		{
			cout << setw(num + 1);
			cout.setf(ios::right);
			for (int j = num; j < b1.size(); j++)
			{
				
				cout << b1[j];
			}
			cout.width(10);
			num++;
		}
		else
		{
			for (int j = 0; j < b1.size(); j++)
			{
				cout << " ";
			}
		}
		cur = q.front();//记录队首元素
		q.pop();
		if (cur.flag == true)//是操作数进入栈
		{
			s1.push(cur);
			b2.push_back(cur.num);
		}
		else//是操作符就运算
		{
			num_b = s1.top().num;//弹出第二操作数
			s1.pop();
			b2.pop_back();
			num_a = s1.top().num;//弹出第一操作数
			s1.pop();
			b2.pop_back();
			temp.flag = true;
			if (cur.op == '+')
			{
				temp.num = num_a + num_b;
			}
			else if (cur.op == '-')
			{
				temp.num = num_a - num_b;
			}
			else if (cur.op == '*')
			{
				temp.num = num_a * num_b;
			}
			else
			{
				if (num_b == 0)//除数不能为0
				{
					cout << "除数为0,不能计算，结束程序" << endl;
					exit(-1);
				}
				temp.num = num_a / num_b;
			}
			s1.push(temp);//把计算后的结果再次压栈
			b2.push_back(temp.num);
		}
		cout.setf(ios::right);
		cout.width(10);
		cout << setw(string_num - b2.size());
		for (int k = 0; k < b2.size(); k++)
		{
			cout << b2[k];
		}
		cout << endl;
	}
	return s1.top().num;
}

int getIndex(char theta)   //获取theta所对应的索引
{
	int index = 0;
	switch (theta)
	{
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '(':
		index = 4;
		break;
	case ')':
		index = 5;
		break;
	case '#':
		index = 6;
		break;
	default:
		break;
	}
	return index;
}

char getPriority(char theta1, char theta2)   //获取theta1与theta2之间的优先级
{
	const char priority[][7] =     //算符间的优先级关系
	{
		{ '>','>','<','<','<','>','>' },
		{ '>','>','<','<','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '<','<','<','<','<','=','0' },
		{ '>','>','>','>','0','>','>' },
		{ '<','<','<','<','<','0','=' },
	};

	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}

double calculate(double b, char theta, double a)   //计算b theta a
{
	switch (theta)
	{
	case '+':
		return b + a;
	case '-':
		return b - a;
	case '*':
		return b * a;
	case '/':
		return b / a;
	default:
		break;
	}
}

double calculate_medi()//中缀表达式求值
{
	stack<char> opter;    //运算符栈
	stack<double> opval;  //操作数栈
	opter.push('#');      //首先将'#'入栈opter
	int i = 0;
	char c = v1[i];
	while (c != '#' || opter.top() != '#')
	{
		if (isdigit(v1[i]))
		{
			opval.push(v1[i] - '0');
			c = v1[++i];
		}
		else
		{
			switch (getPriority(opter.top(), v1[i]))   //获取运算符栈opter栈顶元素与c之间的优先级，用'>'，'<'，'='表示
			{
			case '<':
				opter.push(v1[i]);
				c = v1[++i];
				break;
			case '=':               //=将opter栈顶元素弹出，用于括号的处理
				opter.pop();
				c = v1[++i];
				break;
			case '>':               //>则计算
				char theta = opter.top();
				opter.pop();
				double a = opval.top();
				opval.pop();
				double b = opval.top();
				opval.pop();
				opval.push(calculate(b, theta, a));
			}
		}
	}
	return opval.top();
}
