#include<iostream>
#include "menu.h"
using namespace std;
int main() {  //菜单操作
	menu user;
	user.fileread();   //文件流数据读入
	user.displaymenu();   //菜单
	user.fileout();   //文件更新
}