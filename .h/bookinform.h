#pragma once
#include <iostream>
#include "borrowbook.h"
using namespace std;
class bookinform {
public:
	int ID;  //书号
	string name, writer;     //书名，作者
	int allnum,borrownum;      //现存总数  借阅数量
	borrowbook borrowdata;  //借阅信息
	bookinform(int id , string na, string w , int all, int b , borrowbook bi) :
		ID(id),name(na),writer(w), allnum(all),borrownum(b), borrowdata(bi) {}
	void pointbf() {
		cout << "书号：" << ID << " 书名：" << name << " 作者："<<writer << " 现存总数：" << allnum << " 已借阅量：" << borrownum << endl;
		cout << "借阅信息：\n";
		borrowdata.pointout();
	}
};