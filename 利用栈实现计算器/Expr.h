#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

//������ջ
typedef struct StackNodeOPND {
	double num;
	StackNodeOPND* next;
}*OPND;

//������ջ
typedef struct StackNodeOPTR {
	char op;
	StackNodeOPTR* next;
}*OPTR;


//��ʼ��
int init(OPND& opnd);
//��������ջ
int push(OPND& opnd,double value);
//��������ջ
int pop(OPND& opnd, double& value);
//���ջ��������
int getTop(OPND& opnd, double& value);
//�ж�ջ�Ƿ�Ϊ��
int isEmpty(OPND& opnd);

//��ʼ��
int init(OPTR& optr);
//��������ջ
int push(OPTR& optr,char c);
//���ջ��������
int getTop(OPTR& optr, char& c);
//����������
int pop(OPTR& optr, char& op);
//�жϲ�����ջ�Ƿ�Ϊ��
int isEmpty(OPTR& optr);

//�������ʽ
double parse(char expr[]);
//�Ƚ����ȼ�
char precede(char a, char b);
//������ʽ
double calc(double a, char theta, double b);