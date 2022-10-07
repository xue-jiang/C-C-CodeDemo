#define _CRT_SECURE_NO_WARNINGS
#include"Expr.h"
#include<iostream>
using namespace std;

//��ʼ��
int init(OPND& opnd) {
	//��������Ԫ��
	while (opnd != NULL)
	{
		//ɾ���ɽڵ�
		OPND temp = opnd;
		opnd = temp->next;
		free(temp);
	}
	opnd = NULL;
	return 0;
}

//��������ջ
int push(OPND& opnd, double value) {
	//�����ڵ㣬ջ������
	OPND temp = (OPND)malloc(sizeof(StackNodeOPND));
	if (!temp) {
		return -1;
	}
	temp->num = value;
	temp->next = opnd;
	opnd = temp;

	return 0;
}

//��������ջ
int pop(OPND& opnd, double& value) {

	//��ջ
	if (opnd == NULL) {
		return -1;
	}
	//����������
	value = opnd->num;

	//ɾ���ɽڵ�
	OPND temp = opnd;
	opnd = temp->next;
	free(temp);

	return 0;
}

//���ջ��������
int getTop(OPND& opnd, double& value) {
	if (opnd == NULL) {
		return -1;
	}
	value = opnd->num;

	return 0;
}

//�ж�ջ�Ƿ�Ϊ��
int isEmpty(OPND& opnd) {
	if (opnd == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//��ʼ��
int init(OPTR& optr) {
	//��������Ԫ��
	while (optr != NULL)
	{
		//ɾ���ɽڵ�
		OPTR temp = optr;
		optr = temp->next;
		free(temp);
	}
	optr = NULL;
	return 0;
}

//��������ջ
int push(OPTR& optr, char c) {
	//�����ڵ㣬ջ������
	OPTR temp = (OPTR)malloc(sizeof(StackNodeOPTR));
	if (!temp) {
		return -1;
	}
	temp->op = c;
	temp->next = optr;
	optr = temp;

	return 0;
}

//���ջ��������
int getTop(OPTR& optr, char& c) {
	if (optr == NULL) {
		return -1;
	}
	c = optr->op;

	return 0;
}

//��������ջ
int pop(OPTR& optr, char& op) {

	//��ջ
	if (optr == NULL) {
		return -1;
	}
	//����������
	op = optr->op;

	//ɾ���ɽڵ�
	OPTR temp = optr;
	optr = temp->next;
	free(temp);

	return 0;
}

//�ж�ջ�Ƿ�Ϊ��
int isEmpty(OPTR& optr) {
	if (optr == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}


//�������ʽ
double parse(char expr[]) {
	OPND opnd = NULL;//������ջ
	OPTR optr = NULL;//������ջ

	//��ʼ��ջ
	init(opnd);
	init(optr);

	for (int i = 0; expr[i] != '\0'; i++) {
		//��һ���ַ�
		char c = expr[i];
		if (c >= '0' && c <= '9' || c == '.') {
			//���������
			char token[20] = { 0 };
			int j = 0;
			while (expr[i + j] >= '0' && expr[i + j] <= '9' || expr[i + j] == '.') {
				token[j] = expr[i + j];
				j++;
			}
			token[j] = '\0';
			i = i + j - 1;

			//��tokenת�������֣�ѹ��������ջ
			double value = atof(token);

			push(opnd, value);
		}
		else {
			//���������
			//push(optr, c);
			//if(optr==NULL)
			//	push(optr, c);

			//���ջ�����������Ƚ����ȼ�
			char op = 0;
			getTop(optr, op);
			switch (precede(op, c)) {
			case '<': {//ջ��Ԫ������Ȩ�ͣ�ֱ����ջ
				push(optr, c);
				break; 
			}
			case '=': {//��������
				pop(optr, op);
				break;
			}
			case '>': {//��ջ������������ջ
				//���ʽ���㣬�����ջ
				double a = 0;
				double b = 0;
				//����������������һ��������
				pop(opnd, b);
				pop(opnd, a);
				pop(optr, op);

				//����������ջ
				push(opnd, calc(a, op, b));
				i--;
				break;
			}
			}
		}
	}

	//���һ�μ���
	if (!isEmpty(optr)) {
		double a = 0;
		double b = 0;
		char op = 0;

		//����������������ջ
		pop(opnd, b);
		pop(opnd, a);
		pop(optr, op);
		
		//����������ջ
		push(opnd, calc(a, op, b));
	}

	//���ս��
	double value = 0;
	pop(opnd, value);

	////���Դ���
	////�����������������
	//cout<< "��������";
	//while (optr != NULL) {
	//	//ɾ���ɽڵ�
	//	OPTR temp = optr;
	//	optr = temp->next;
	//	cout << temp->op << ' ';
	//	free(temp);
	//}
	//cout << endl;

	////�����������������
	//cout << "��������";
	//while (opnd != NULL) {
	//	//ɾ���ɽڵ�
	//	OPND temp = opnd;
	//	opnd = temp->next;
	//	cout << temp->num << ' ';
	//	free(temp);
	//}
	//cout << endl;

	return value;
}

//�Ƚ����ȼ� a:ջ�������� b:��ǰ������
//<��ǰ���������� =������������ >ջ������
char precede(char a, char b) {

	if (a == 0)
		return '<';
	//�����֮��Ĺ�ϵ���ڶ�ά������
	char aPriorTable[6][6]{
		{'>','>','<','<','<','>'},//�Ӻ�+
		{'>','>','<','<','<','>'},//����-
		{'>','>','>','>','<','>'},//�˺�*
		{'>','>','>','>','<','>'},//����/
		{'<','<','<','<','<','='},//�����ţ�
		{'>','>','>','>','>','>'},//�����ţ�
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

//������ʽ
double calc(double a, char theta, double b) {
	//����
	double value = 0;
	switch (theta) {
	case '+':value = a + b; break;
	case '-':value = a - b; break;
	case '*':value = a * b; break;
	case '/':value = a / b; break;
	default: {
		cout << "���ʽ����" << endl;
		exit(0);
	}
	}

	return value;
}