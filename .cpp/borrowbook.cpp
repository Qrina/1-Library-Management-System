#include "borrowbook.h"
#include <iostream>
#include <fstream>
using namespace std; 
borrowbook::borrowbook(borrowbook& a) {   //拷贝构造
	if (a.last == NULL) {
		head = last = 0;
		return;
	}
	node* p1 = new node((a.head)->stuname, (a.head)->xuehao,(a.head)->begintime, (a.head)->endtime);
	last = head = p1;
	p = a.head->next;
	for(p;p;p=p->next){
		p1 = new node((p)->stuname,(p)->xuehao, (p)->begintime, (p)->endtime);
		last->next = p1;
		last = p1;
  }
}
void borrowbook::addnode(string a,string b,string c,string d) {   //增加结点
	p = new node(a, b, c,d);
	if (head == NULL) head = p;
	else
		last->next = p;
	last = p;
}
void borrowbook::pointout() {  //输出
	node* q = head;
	for (q; q != NULL; q = q->next) {
		cout << "姓名：" << q->stuname<<" 学号："<<q->xuehao << " 借阅日期：" << q->begintime << " 还书日期：" << q->endtime << endl;
	}
}
void borrowbook::pointfout(ofstream& fout) {   //输出流
	node* q = head;
	for (q; q != NULL; q = q->next) {
		fout << "  " << q->stuname << "  " << q->xuehao << "  " << q->begintime << "  " << q->endtime ;
	}
	fout << endl;
}
void borrowbook::deletenode(string xh) {   //删除结点
	if (head == NULL) {
		cout << "未查询到借书信息!\n";
		return;
	}//空的情况 直接返回 
	if (head->xuehao == xh)        //头节点的情况 
	{
		p = head;
		head = head->next;
		if (head==NULL) last = head;  //只有一个数的情况 
		delete p;
		cout << "还书成功！谢谢使用*\n";
		return;
	}
	p = head;
	node* pos = p;
	for (p = p->next; p; p = p->next)   //后续查找 
	{
		if (p->xuehao==xh)
		{
			pos->next = p->next;
			if (p == last) last = pos;  //为末节点的情况 
			delete p;
			cout << "还书成功！谢谢使用*\n";
			return;
		}
		pos = p;
	}
	cout << "未查询到借书信息!\n";
	return;
}