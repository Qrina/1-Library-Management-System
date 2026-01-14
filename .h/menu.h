#pragma once
#include <iostream>
#include "Btree.h"
using namespace std;
class menu {   //菜单操作
private:
	Btree bookdata;
	string manager,key;
public:
	menu() {
		manager = "Q";
		key = "666666";
	}
	void fileread();   //信息读入
	void displaymenu();  //显示菜单
	bool enter();      //管理员登录
	void addbook();    //添加图书
	BNode* querybook(); //查找图书
	void consult();    //查询图书
	void renewbook();
	void borbook();   //借书
	void backbook();  //还书
	void cutbook();   //删除图书
	void fileout();   //文件输出流更新
	void printtree();  //打印二叉树
};