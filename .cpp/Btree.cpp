#include "Btree.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void Btree::DesBtree(BNode*r) {  
	if (!r) return;
	DesBtree(r->lchild);
	DesBtree(r->rchild);   //递归释放结点
	delete r;
	r = nullptr;
}
void Btree::addBNode(int k,bookinform b) {  //增加结点
	if (r == NULL) {  //空树
		r = new BNode(k, b);
		bl.insertToBloomFilter(b.name);
		b2.insertToBloomFilter(to_string(k));
		return;
	}
	BNode* p = NULL;
	BNode* t = r;
	while (t) {   //找到插入位置
		p = t;
		if (k < t->key) t = t->lchild;
		else if (k > t->key) t = t->rchild;
		else {
			t->data.allnum+=b.allnum;   //已经有该书 增加相应数量
			return;
		}
	}
	t = new BNode(k, b);  //插入该节点
	if (k < p->key) p->lchild = t;
	else p->rchild = t;
	t->parent = p;
	bl.insertToBloomFilter(b.name);
	b2.insertToBloomFilter(to_string(k));

	while (p) {     //向上更新平衡因子
		if (p->lchild == t) ++p->ht;
		else --p->ht;

		if (p->ht == 0) {   //从-1或1变为0 不影响祖先结点 
			break;
		}
		else if (p->ht == 1 || p->ht == -1) {  //从0变为1或者-1 影响祖先结点
			t = p;
			p = p->parent;
		}
		else if (p->ht == 2 || p->ht == -2) {   //从p开始不平衡
			if (p->ht == 2 && t->ht == 1)
				LL(p);
			else if (p->ht == -2 && t->ht == -1)
				RR(p);
			else if (p->ht == 2 && t->ht == -1)
				LR(p);
			else if (p->ht == -2 && t->ht == 1)
				RL(p);
			break;
		}
	} 
}
void Btree::LL(BNode* p) {
	BNode* A = p->lchild;
	BNode* B = A->rchild;
	p->lchild = B;
	if (B) B->parent = p;
	A->rchild = p;
	BNode* tmp = p->parent;
	A->parent = p->parent;
	p->parent = A;

	if (tmp == NULL) r = A;
	else {
		if (tmp->lchild == p) tmp->lchild = A;
		else tmp->rchild = A;
	}
	p->ht= A->ht = 0;
}
void Btree::RR(BNode* p) {
	BNode* A = p->rchild;
	BNode* B = A->lchild;
	p->rchild = B;
	if (B) B->parent = p;
	A->lchild = p;
	BNode* tmp = p->parent;
	A->parent = p->parent;
	p->parent = A;

	if (tmp == NULL) r = A;
	else {
		if (tmp->lchild == p) tmp->lchild = A;
		else tmp->rchild = A;
	}
	p->ht = A->ht = 0;
}
void Btree::LR(BNode* p) {
	BNode* A = p->lchild;
	BNode* B = A->rchild;
	int ht = B->ht;

	RR(A);
	LL(p);

	if (ht == 0) {
		p->ht = 0;
		A->ht = 0;
		B->ht = 0;
	}
	else if (ht == 1) {
		p->ht = -1;
		A->ht = 0;
		B->ht = 0;
	}
	else if (ht == -1) {
		p->ht = 0;
		A->ht = 1;
		B->ht = 0;
	}
}
void Btree::RL(BNode* p) {
	BNode* A = p->rchild;
	BNode* B = A->lchild;
	int ht = B->ht;

	LL(A);
	RR(p);

	if (ht == 0) {
		p->ht = 0;
		A->ht = 0;
		B->ht = 0;
	}
	else if (ht == 1) {
		p->ht = 0;
		A->ht = -1;
		B->ht = 0;
	}
	else if (ht == -1) {
		p->ht = 1;
		A->ht = 0;
		B->ht = 0;
	}
}
BNode* Btree::searchbook1(int ID) {   
	if (b2.searchInBloomFilter(to_string(ID))) {
		return search1(r, ID);
	}
	else 
	{
		cout << "查找次数为：" << num << endl;
		return NULL;
	}
		
}
BNode* Btree::search1(BNode* p, int k) {    //递归查找结点
	num++;
	if (p == NULL) return NULL;
	if (p->key == k) return p;
	if (p->key > k) {
		return search1(p->lchild, k);
	}
	if (p->key < k) {
		return search1(p->rchild, k);
	}
}
BNode* Btree::searchbook2(string na) {   //书名查找
	if (bl.searchInBloomFilter(na))
		return search2(r, na);
	else
		return NULL;
}
BNode* Btree::search2(BNode*b,string na) {  //递归查找节点
	if (b == NULL) return NULL;
	else if (b->data.name == na) return b;
	else {
		BNode* p = search2(b->lchild, na);
		if (p != NULL) return p;
		else
			return search2(b->rchild, na);
	}
}
void BNode::informpoint() {   //图书结点信息打印
	data.pointbf();
}
void Btree::deleteBNode(BNode* k) {
	BNode* t = k;
	BNode* p = t->parent;
	if (t->lchild!=NULL && t->rchild!=NULL) {  //左右子树都不空
		p = t;
		BNode* leftmax = t->lchild;
		while (leftmax->rchild) {
			p = leftmax;
			leftmax = leftmax->rchild;   //找左子树最大的结点
		}
		std::swap(t, leftmax);  //交换结点
		t = leftmax;
	}
	BNode* child;      //最多只有一个孩子结点的情况
	if (t->lchild)
		child = t->lchild;   //待删除结点的孩子结点
	else
		child = t->rchild;

	if (p == NULL) { //被删除的为根节点
		r = child;
	}
	else {
		if (p->lchild == t) { //删除该节点
			--p->ht;
			p->lchild = child;
		}
		else {
			++p->ht;
			p->rchild = child;
		}
		bool isr = true;
		while (p) {   //往上更新祖先结点的平衡因子
			if (isr == false) {
				if (p->lchild == child)
					--p->ht;
				else
					++p->ht;
		    }
			isr = false;

			if (p->ht == -1 || p->ht == 1)  //从0变为-1或1 不影响祖先结点
				break;
			else if (p->ht == -2 || p->ht == 2) {  //进行平衡操作
				int s = 0;    //标识哪边子树高
				BNode* h;
				if (p->ht < 0) {
					s= -1;
					h = p->rchild;
				}
				else {
					s = 1;
					h = p->lchild;
				}

				if (h->ht == 0) {  //LL和RR 子树ht为0的情况
					if (s < 0) {
						RR(p);
						p->ht = -1;
						h->ht = 1;
					}
					else {
						LL(p);
						p->ht=1;
						h->ht = -1;
					}
					break;
				}
				else if (h->ht == s) {   //LL和RR 子树ht不为0的情况
					if (s < 0) {
						RR(p);
						p = h;
						child = p->lchild;
					}
					else {
						LL(p);
						p = h;
						child = p->rchild;
					}
				}
				else {      //RL和LR的情况
					if (s < 0) {  
						BNode* tmp = p->rchild->lchild;
						RL(p);
						p = tmp;
						child = p->lchild;
					}
					else {
						BNode* tmp = (p->lchild)->rchild;
						LR(p);
						p = tmp;
						child = p->rchild;
					}
				}
			}
			child = p;
			p = p->parent;
		}
		
	}
	delete t;
	cout << "旧书信息删除成功！\n";
}
void Btree::filetree(ofstream& fout) {
	fileBNode(r,fout);
}
void Btree::fileBNode(BNode * b, ofstream& fout) {
	if (b != NULL) {
		fileBNode(b->lchild, fout);
		fout << b->data.ID << "  " << b->data.name << "  " << b->data.writer << "  " << b->data.allnum << "  " << b->data.borrownum;
		borrowbook d = b->data.borrowdata;
		d.pointfout(fout);
		fileBNode(b->rchild,fout);
	}
}
void Btree::printBtree() {  //打印二叉树
	printBNode(r, 0);
	cout << endl;
}
void Btree::printBNode(BNode* b, int t) {
	if (b != NULL) {
		printBNode(b->rchild, t + 1);
		for (int i = 0; i < t; i++) cout << "    ";
		cout << "|--" << b->key << endl;
		printBNode(b->lchild, t + 1);
	}
}