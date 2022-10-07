#define _CRT_SECURE_NO_WARNINGS
#include"Expr.h"
#include<iostream>
using namespace std;

//初始化
int init(OPND& opnd) {
	//销毁链表元素
	while (opnd != NULL)
	{
		//删除旧节点
		OPND temp = opnd;
		opnd = temp->next;
		free(temp);
	}
	opnd = NULL;
	return 0;
}

//操作数入栈
int push(OPND& opnd, double value) {
	//新增节点，栈顶上移
	OPND temp = (OPND)malloc(sizeof(StackNodeOPND));
	if (!temp) {
		return -1;
	}
	temp->num = value;
	temp->next = opnd;
	opnd = temp;

	return 0;
}

//操作数出栈
int pop(OPND& opnd, double& value) {

	//空栈
	if (opnd == NULL) {
		return -1;
	}
	//弹出操作数
	value = opnd->num;

	//删除旧节点
	OPND temp = opnd;
	opnd = temp->next;
	free(temp);

	return 0;
}

//获得栈顶操作数
int getTop(OPND& opnd, double& value) {
	if (opnd == NULL) {
		return -1;
	}
	value = opnd->num;

	return 0;
}

//判断栈是否为空
int isEmpty(OPND& opnd) {
	if (opnd == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//初始化
int init(OPTR& optr) {
	//销毁链表元素
	while (optr != NULL)
	{
		//删除旧节点
		OPTR temp = optr;
		optr = temp->next;
		free(temp);
	}
	optr = NULL;
	return 0;
}

//操作符入栈
int push(OPTR& optr, char c) {
	//新增节点，栈顶上移
	OPTR temp = (OPTR)malloc(sizeof(StackNodeOPTR));
	if (!temp) {
		return -1;
	}
	temp->op = c;
	temp->next = optr;
	optr = temp;

	return 0;
}

//获得栈顶操作符
int getTop(OPTR& optr, char& c) {
	if (optr == NULL) {
		return -1;
	}
	c = optr->op;

	return 0;
}

//操作符出栈
int pop(OPTR& optr, char& op) {

	//空栈
	if (optr == NULL) {
		return -1;
	}
	//弹出操作数
	op = optr->op;

	//删除旧节点
	OPTR temp = optr;
	optr = temp->next;
	free(temp);

	return 0;
}

//判断栈是否为空
int isEmpty(OPTR& optr) {
	if (optr == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}


//解析表达式
double parse(char expr[]) {
	OPND opnd = NULL;//操作数栈
	OPTR optr = NULL;//操作符栈

	//初始化栈
	init(opnd);
	init(optr);

	for (int i = 0; expr[i] != '\0'; i++) {
		//读一个字符
		char c = expr[i];
		if (c >= '0' && c <= '9' || c == '.') {
			//处理操作数
			char token[20] = { 0 };
			int j = 0;
			while (expr[i + j] >= '0' && expr[i + j] <= '9' || expr[i + j] == '.') {
				token[j] = expr[i + j];
				j++;
			}
			token[j] = '\0';
			i = i + j - 1;

			//将token转化成数字，压到操作数栈
			double value = atof(token);

			push(opnd, value);
		}
		else {
			//处理操作符
			//push(optr, c);
			//if(optr==NULL)
			//	push(optr, c);

			//获得栈顶操作符，比较优先级
			char op = 0;
			getTop(optr, op);
			switch (precede(op, c)) {
			case '<': {//栈顶元素优先权低，直接入栈
				push(optr, c);
				break; 
			}
			case '=': {//弹出括号
				pop(optr, op);
				break;
			}
			case '>': {//退栈并将运算结果入栈
				//表达式计算，结果入栈
				double a = 0;
				double b = 0;
				//弹出两个操作数和一个操作符
				pop(opnd, b);
				pop(opnd, a);
				pop(optr, op);

				//计算结果，入栈
				push(opnd, calc(a, op, b));
				i--;
				break;
			}
			}
		}
	}

	//最后一次计算
	if (!isEmpty(optr)) {
		double a = 0;
		double b = 0;
		char op = 0;

		//操作数、操作符出栈
		pop(opnd, b);
		pop(opnd, a);
		pop(optr, op);
		
		//计算结果，入栈
		push(opnd, calc(a, op, b));
	}

	//最终结果
	double value = 0;
	pop(opnd, value);

	////测试代码
	////遍历链表，输出操作符
	//cout<< "操作符：";
	//while (optr != NULL) {
	//	//删除旧节点
	//	OPTR temp = optr;
	//	optr = temp->next;
	//	cout << temp->op << ' ';
	//	free(temp);
	//}
	//cout << endl;

	////遍历链表，输出操作数
	//cout << "操作数：";
	//while (opnd != NULL) {
	//	//删除旧节点
	//	OPND temp = opnd;
	//	opnd = temp->next;
	//	cout << temp->num << ' ';
	//	free(temp);
	//}
	//cout << endl;

	return value;
}

//比较优先级 a:栈顶操作符 b:当前操作符
//<当前操作符优先 =左右括号相遇 >栈顶优先
char precede(char a, char b) {

	if (a == 0)
		return '<';
	//运算符之间的关系存在二维数组中
	char aPriorTable[6][6]{
		{'>','>','<','<','<','>'},//加号+
		{'>','>','<','<','<','>'},//减号-
		{'>','>','>','>','<','>'},//乘号*
		{'>','>','>','>','<','>'},//除号/
		{'<','<','<','<','<','='},//左括号（
		{'>','>','>','>','>','>'},//右括号）
	};

	int x = -1;
	int y = -1;
	char opr[] = "+-*/()";
	for (int i = 0; i < 6; i++) {
		if (a == opr[i])
			x = i;
		if (b == opr[i]) {
			y = i;
		}
	}

	return aPriorTable[x][y];
}

//计算表达式
double calc(double a, char theta, double b) {
	//运算
	double value = 0;
	switch (theta) {
	case '+':value = a + b; break;
	case '-':value = a - b; break;
	case '*':value = a * b; break;
	case '/':value = a / b; break;
	default: {
		cout << "表达式错误" << endl;
		exit(0);
	}
	}

	return value;
}