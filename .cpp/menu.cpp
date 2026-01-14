#include "menu.h"
#include "Btree.h"
#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;
void menu::fileread() {   //文件信息读入
	ifstream fin("bookdata.txt", ios::in);
	if (!fin) {
		cout << "打开文件失败！" << endl;
		return;
	}
	int id, allnum, borrownum;
	string  name, writer,  bname,xh, btime, etime;
	while (fin >> id >> name >> writer >> allnum >> borrownum) {
		borrowbook A;   //该图书的借阅信息链表
		int t = borrownum;
		if (t > 0) {
			while (t--) {  //先添加t个读者的借阅信息到链表中
				fin >> bname >> xh >> btime >> etime;
				A.addnode(bname, xh, btime, etime);
			}
		}
		bookinform B(id,name,writer,allnum,borrownum,A);   //该图书的所有信息
		bookdata.addBNode(id, B);  //二叉树中插入新结点
	}
	fin.close();
}
void menu::fileout() {
	ofstream fout("bookdata.txt", ios::out);  // 打开文件
	bookdata.filetree(fout); 
	fout.close();
}
bool menu::enter() {    //管理员登录
	while (1) {
		cout << "请输入管理员的用户名：\n";
		string s;
		cin >> s;
		cout << "请输入密码：\n";
		string t;
		cin >> t;
		if (s == manager && t == key) {
			cout << "登录成功！\n";
			break;
		}
		else {
			cout << "用户名或密码错误！请重新输入\n";
			cout << "--------------------------\n";
		}
	}
	return true;
}
void menu::addbook() {   //新增图书
	cout << "请输入增加图书的信息(书号 书名 作者名 存量)\n";
	 int id,num,bnum=0; string name, writer;
	cin >> id >> name >> writer >> num;
	borrowbook a;
	bookinform b(id,name,writer,num,bnum,a);
	bookdata.addBNode(id, b);
	cout << "图书添加成功！\n";
}
BNode* menu::querybook() {  //图书查找
	cout << "请选择查找图书的方式：1.书号 2.书名\n";
	int a;
	cin >> a;
	if (a == 1) {   //书号查询
		cout << "请输入书号：\n";
		int id;
		cin >> id;
		BNode* p=bookdata.searchbook1(id);
		return p;
	}
	else if(a==2){    //书名查询
		cout << "请输入书名：\n";
		string s;
		cin >> s;
		BNode* b = bookdata.searchbook2(s);
		return b;
	}
}
void menu::consult() {  //信息查询
	BNode* q = querybook();
	if (q == NULL) cout << "查找错误，该图书不存在！\n"; 
	else {
		q->informpoint();
		cout << "信息查询成功！\n";
	}
}
void menu::renewbook() {    //图书信息更新
	BNode* q = querybook();
	if (q == NULL) cout << "查找错误，该图书不存在！\n";
	else {
			cout << "请选择要更新的信息：\n";
			cout << "1.书名\n";
			cout << "2.作者\n";
			cout << "3.现存量\n";
			int a;
			cin >> a;
			string s;
			cout << "请输入更新的信息\n";
			if (a == 1) {
				cin >> s;
				q->data.name = s;
			}
			else if (a ==2) {
				string s;
				q->data.writer = s;
			}
			else if (a == 3) {
				int t;
				cin >> t; 
				q->data.allnum = t;
			}
			cout << "信息更新成功！\n";
	}
}
void menu::borbook() {   //借书
	BNode* q = querybook();
	if (q == NULL) cout << "查找错误，该图书不存在！\n";
	else {
		cout << "请输入你的姓名，学号，借书日期，还书日期(格式20230823)（每本书最长借三个月）\n";
		string name, xh, btm, etm;
		cin >> name >> xh >> btm>>etm;
		q->data.borrownum++;
		(q->data.borrowdata).addnode(name, xh, btm, etm);  //增加借书信息
		cout << "借书成功，请在规定时间内还书，谢谢*\n";
	}
}
void menu::backbook() {  //还书
	BNode* q = querybook();
	if (q == NULL) cout << "查找错误，该图书不存在！\n";
	else {
		cout << "请输入你的学号\n";
		string xh;
		cin >> xh;
		(q->data.borrowdata).deletenode(xh);
	}
}
void menu::cutbook() {   //旧书删除
	BNode* q = querybook();
	if (q == NULL) cout << "查找错误，该图书不存在！\n";
	else {
		bookdata.deleteBNode(q);
	}
}
void menu::displaymenu() {  //菜单
	while (1) {
		cout << "*********欢迎使用图书馆管理系统*********\n" ;
		cout << "**请选择用户身份：\n";
		cout << "1-管理员 \n";
		cout << "2-读者\n";      //用户操作部分------------------
		cout << "3-退出系统\n";
		cout << "--------------------------\n";
		int a;
		cin >> a;
		if (a == 1) {   //管理员
			//登录界面
			if (enter()) {
				while (1) {
					cout << "**请选择要进行的操作：\n";
					cout << "1.图书查询\n";
					cout << "2.新书添加\n"; 
					cout << "3.旧书删除\n";
					cout << "4.图书信息更新\n";
					cout << "5.借书\n";
					cout << "6.还书\n";
					cout << "7.打印当前AVL树（横版）\n";
					cout << "--------------------------\n";
					cin >> a;
					switch (a) {
					case 1:
						consult();
						cout << "--------------------------\n";
						break;
					case 2:
						addbook();
						cout << "--------------------------\n";
						break;
					case 3:
						cutbook();
						cout << "--------------------------\n";
						break;
					case 4:
						renewbook();
						cout << "--------------------------\n";
						break;
					case 5:
						borbook();
						cout << "--------------------------\n";
						break;
					case 6:
						backbook();
						cout << "--------------------------\n";
						break;
					case 7:
						printtree();
						cout << "--------------------------\n";
						break;
					default:
						cout << "输入错误！，请返回重新输入！\n";
						cout << "--------------------------\n";
						break;
					}
					cout << "**请选择接下来的操作：\n";
					cout << "1.返回管理员操作菜单 \n";
					cout << "2.退出操作 \n";
					cout << "--------------------------\n";
					std::cin >> a;
					if (a == 2) {
						break;
					}
					else if (a == 1) {
						cout << "--------------------------\n";
						continue;
					}
				}
			}
		}
		else if (a == 2) {
			while (1) {
				cout << "**请选择要进行的操作：\n";
				cout << "1.图书查询\n";
				cout << "2.借书\n";
				cout << "3.还书\n";
				cout << "--------------------------\n";
				cin >> a;
				switch (a) {
				case 1:
					consult();
					cout << "--------------------------\n";
					break;
				case 2:
					borbook();
					cout << "--------------------------\n";
					break;
				case 3:
					backbook();
					cout << "--------------------------\n";
					break;
				default:
					cout << "输入错误！，请返回重新输入！\n";
					cout << "--------------------------\n";
					break;
				}
				cout << "**请选择接下来的操作：\n";
				cout << "1.返回用户操作菜单 \n";
				cout << "2.退出用户操作 \n";
				cin >> a;
				if (a == 2)  break;
				else if (a == 1) {
					cout << "--------------------------\n";
					continue;
				}
			}
		}
		else if (a == 3) {
			break;
		}
		else {
				cout << "输入错误！，请重新输入！\n";
				cout << "--------------------------\n";
				break;
		}
	}
	std::cout << "******已退出*******\n";
	std::cout << "感谢您的使用----------------------------";
	
}
void menu::printtree() {  //打印二叉树
	cout << "当前AVL树结构如下：\n";
	bookdata.printBtree();
}