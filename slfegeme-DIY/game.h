#include<iostream>
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>

class charactor
{
public:
	int  c[5];
	int grade;
	int sus, fal;  //原为gread 报错 与int gread重定义了
	int sum;// = sus + fal; //不许使用数据成员初始值设定项 即不可直接sum = sus + fal
	int oncegrade;
	charactor(){};
	void changecharactor();
	int  changegrade(int grade,int oncegrade);
	int OnceGrade(int sus, int fal);
};
enum keysign
{
	SPACE,  //0
	UP,  //1
	DOWN, //2
	LEFT,
	RIGHT,
};
void charactor::changecharactor()
{  
	//随机生成每一局的5个图对应的数
	FILETIME st;
	GetSystemTimeAsFileTime(&st);
	srand(st.dwLowDateTime);
	c[0] = rand() % 5;
	c[1] = rand() % 5;
	c[2] = rand() % 5;
	c[3] = rand() % 5;
	c[4] = rand() % 5;
}
int charactor::changegrade(int grade,int oncegrade)
{
	//记录总分
	return grade + oncegrade;
}                                    
int charactor::OnceGrade(int sus, int fal)
{
	//单局分数 
	if (sus == 5 ) oncegrade = 10;//成功的次数
	else if (sus != 5 || fal != 0) oncegrade = sus;
	return oncegrade;
}