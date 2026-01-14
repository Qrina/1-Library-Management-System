#pragma once
#include <iostream>
#include<bitset>
#include "bookinform.h"
#include "filter.h"
#include <bitset>
using namespace std;
struct BNode {  //二叉树节点
	int key;
	bookinform data;  //图书信息
	BNode* lchild, * rchild, * parent;
	int ht;  //平衡因子
	BNode(int k, bookinform d) :key(k), data(d), lchild(0), rchild(0), parent(0), ht(0) {}
	void informpoint();
};
class Btree {
public:
	BNode* r;
	filter bl;  //对应书名查找
	filter b2;  //对应书号查找
	Btree() {
		r = NULL;
	}
	~Btree() {
		bl.~filter();
		b2.~filter();
		DesBtree(r);
	}
	void DesBtree(BNode* r);  
	void addBNode  (int k, bookinform d);  //增加结点
	void LL(BNode* p);
	void RR(BNode* p);
	void LR(BNode* p);
	void RL(BNode* p);
	BNode* searchbook1(int ID);   //书号查找
	BNode* search1(BNode* p, int k);
	BNode* searchbook2(string name);  //书名查找
	BNode* search2(BNode* b,string name);
	void deleteBNode(BNode* k);      //删除结点
	void filetree(ofstream& fout);   //信息输出流
	void fileBNode(BNode* b, ofstream& fout);
	void printBtree();     //打印二叉树
	void printBNode(BNode* b, int t); 
};