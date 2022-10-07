#define _CRT_SECURE_NO_WARNINGS
#include"Expr.h"
#include<iostream>
#include<tchar.h>//使_TCHAR不报错
using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	//输出界面
	cout << "=========表达式求值=========" << endl;
	cout << "1 支持四则运算：+ - * /" << endl;
	cout << "2 支持括号（）" << endl;
	cout << "3 支持浮点数" << endl;
	cout << "请输入表达式，按回车结束" << endl;
	cout << "例如：5*（3+4）/2" << endl;

	//输入表达式
	char expr[256] = { 0 };
	cout << "表达式：";
	cin >> expr;

	//输出结果
	cout << "结果：" << parse(expr) << endl;

	return 0;
}