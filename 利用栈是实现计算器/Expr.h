#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

//操作数栈
typedef struct StackNodeOPND {
	double num;
	StackNodeOPND* next;
}*OPND;

//操作符栈
typedef struct StackNodeOPTR {
	char op;
	StackNodeOPTR* next;
}*OPTR;


//初始化
int init(OPND& opnd);
//操作数入栈
int push(OPND& opnd,double value);
//操作数出栈
int pop(OPND& opnd, double& value);
//获得栈顶操作数
int getTop(OPND& opnd, double& value);
//判断栈是否为空
int isEmpty(OPND& opnd);

//初始化
int init(OPTR& optr);
//操作符入栈
int push(OPTR& optr,char c);
//获得栈顶操作符
int getTop(OPTR& optr, char& c);
//操作数出符
int pop(OPTR& optr, char& op);
//判断操作符栈是否为空
int isEmpty(OPTR& optr);

//解析表达式
double parse(char expr[]);
//比较优先级
char precede(char a, char b);
//计算表达式
double calc(double a, char theta, double b);