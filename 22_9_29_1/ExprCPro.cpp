#define _CRT_SECURE_NO_WARNINGS
#include"Expr.h"
#include<iostream>
#include<tchar.h>//ʹ_TCHAR������
using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	//�������
	cout << "=========���ʽ��ֵ=========" << endl;
	cout << "1 ֧���������㣺+ - * /" << endl;
	cout << "2 ֧�����ţ���" << endl;
	cout << "3 ֧�ָ�����" << endl;
	cout << "��������ʽ�����س�����" << endl;
	cout << "���磺5*��3+4��/2" << endl;

	//������ʽ
	char expr[256] = { 0 };
	cout << "���ʽ��";
	cin >> expr;

	//������
	cout << "�����" << parse(expr) << endl;

	return 0;
}