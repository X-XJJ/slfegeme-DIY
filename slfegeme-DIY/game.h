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
	int sus, fal;  //ԭΪgread ���� ��int gread�ض�����
	int sum;// = sus + fal; //����ʹ�����ݳ�Ա��ʼֵ�趨�� ������ֱ��sum = sus + fal
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
	//�������ÿһ�ֵ�5��ͼ��Ӧ����
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
	//��¼�ܷ�
	return grade + oncegrade;
}                                    
int charactor::OnceGrade(int sus, int fal)
{
	//���ַ��� 
	if (sus == 5 ) oncegrade = 10;//�ɹ��Ĵ���
	else if (sus != 5 || fal != 0) oncegrade = sus;
	return oncegrade;
}