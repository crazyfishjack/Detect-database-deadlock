#include<iostream>
#include<string.h>
#include<algorithm>
#include<queue>
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<conio.h>
#include<fstream>
using namespace std;
#pragma warning(disable:4996)
typedef struct {
	char q;
	char z;
}U;
typedef struct {
	char data;
	int r;
}T;
U u[100];
T t[100];
char m;
int un;
int tn = 0;
int flag = 0;
void initT() {
	for (int i = 0;i < un;i++) {
		if (tn == 0) {
			t[tn++].data = u[i].q;
			t[tn].data = u[i].z;
			t[tn++].r++;
		}
		else {
			int flag1 = 0;
			for (int j = 0;j < tn;j++)
				if (t[j].data == u[i].q)flag1 = 1;
			if (flag1 == 0)t[tn++].data = u[i].q;
			flag1 = 0;
			for (int j = 0;j < tn;j++)
				if (t[j].data == u[i].z){
					t[j].r++;
					flag1 = 1;
				}
			if (flag1 == 0) {
				t[tn].data = u[i].z;
				t[tn++].r++;
			}
		}
	}
	for (int i = 0;i < tn;i++)
		t[i].r = 0;
	for (int i = 0;i < un;i++) {
		if (tn == 0) {
			t[tn++].data = u[i].q;
			t[tn].data = u[i].z;
			t[tn++].r++;
		}
		else {
			int flag1 = 0;
			for (int j = 0;j < tn;j++)
				if (t[j].data == u[i].q)flag1 = 1;
			if (flag1 == 0)t[tn++].data = u[i].q;
			flag1 = 0;
			for (int j = 0;j < tn;j++)
				if (t[j].data == u[i].z){
					t[j].r++;
					flag1 = 1;
				}
			if (flag1 == 0) {
				t[tn].data = u[i].z;
				t[tn++].r++;
			}
		}
	}
}
void add(){
	cout << "您正在添加事务关系，请输入两个事件（前一个事件等待后一个事件）：" << endl;
	int flag3 = 0;
	char sw1, sw2;
	cin >> sw1 >> sw2;
	for (int i = 0;i < un;i++)
		if (u[i].q == sw1 && u[i].z == sw2) {
			cout << "已经存在该事务关系"<<endl;
			flag3 = 1;
		}
	if (flag3 == 0) {
		u[un].q = sw1;
		u[un++].z = sw2;
		tn = 0;
		initT();
		cout << "添加成功" << endl;
	}
}
void del() {
	cout << "您正在删除事务关系，请输入两个事件（前一个事件等待后一个事件）：" << endl;
	int flag2 = 0;
	char sw1, sw2;
	cin >> sw1 >> sw2;
	for (int i = 0;i < un;i++) {
		if (u[i].q == sw1 && u[i].z == sw2) {
			un--;
			for (int j = i;j < un;j++) {
				u[j].q = u[i + 1].q;
				u[j].z = u[i + 1].z;
			}
			flag2 = 1;
		}
	}
	if (flag2)cout << "删除成功" << endl;
	else cout << "未找到该事务关系" << endl;
}
int pd() {
	for (int i = 0;i < tn;i++) {
		if (t[i].r == 0)
			return 1;
	}
	return 0;
}
void tp() {
	while (pd()) {
		for (int i = 0;i < tn;i++) {
			if (t[i].r == 0) {
				for (int j = 0;j < un;j++)
					if (u[j].q == t[i].data)
						for (int k = 0;k < tn;k++)
							if (u[j].z == t[k].data)
								t[k].r--;
				t[i].r --;
			}
		}
	}
	for (int i = 0;i < tn;i++) {
		if (t[i].r != -1)
			flag = 1;
	}
}
void show() {
	cout << "事务等待关系图:" << endl;
	for (int i = 0;i < un;i++)
		cout << u[i].q << " " << u[i].z << endl;
}
int main()
{
	cout << "检测死锁程序:" << endl << endl;
	ifstream fin("事务等待关系.txt");
	streambuf* cinbackup;
	cinbackup = cin.rdbuf(fin.rdbuf());
	for (un = 0;cin >> u[un].q;un++)
		cin >> u[un].z;
	cin.rdbuf(cinbackup);
	cout << "读入事务关系图完毕" << endl << endl;
	while (1) {
		initT();
		tp();
		if (flag == 0)cout << "检测结果:无死锁" << endl << endl;
		else {
			cout << "检测结果:有死锁" << endl ;
			for (int i = 0;i < tn;i++)
				if (t[i].r != -1)cout << t[i].data << ",";
			cout << "之间存在死锁" << endl << endl;
		}
		flag = 0;
		cout << "按1添加事务等待关系，按2删除事务等待关系,按3展示事物等待关系"<<endl;
out:
		m = getch();
		if (m == '1')add();
		else if (m == '2')del();
		else if (m == '3')show();
		else goto out;
	}
	return 0;
}
