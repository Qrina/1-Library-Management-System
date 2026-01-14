#pragma once
#include <iostream>
using namespace std;
class node {
public:
	string stuname, xuehao,begintime,endtime; //学生姓名 学号 借阅时间 归还时间
	node* next;
	node(string n = "",string xh="", string b = "", string en = "") :
		stuname(n),xuehao(xh), begintime(b), endtime(en),next(0){}
};
class borrowbook {
	node* head,*p,*last; //头指针 辅助指针 尾指针
public:
	borrowbook():head(0),p(0),last(0){}
	borrowbook(borrowbook& a);
	void addnode(string a, string b, string c,string d);    //增加信息节点
	void deletenode(string xh);    //删除信息节点
	void pointout();     //打印借阅信息
	void pointfout(ofstream& fout);  //信息输出流
};