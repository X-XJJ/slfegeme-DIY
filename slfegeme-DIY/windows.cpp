#include <windows.h>
#include <iostream>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include <strsafe.h>
#include <mmsystem.h>

#pragma  comment(lib,"WinMM.Lib")

//全局变量
#define ID_TIMER1 100001
#define ID_TIMER2 100002

#define MAX_X 540
#define MAX_Y 440

HWND hwndgamewindow;
HWND hwndtimewindow;
HWND hwndname;

int tag = -1;
int c_c = 0;
charactor ch1;
int c_m = 0;
int count;
int x = 3;
int conttime = 0;
BITMAP bm0, bm1, bm2, bm3, bm4, bm5, bm6, bm7, bm8, bm9;
int scoreonce[1] = { 0 };
int scoreall[1] = { 0 };
int stime[1] = { 0 };

HBITMAP g_hbmup = NULL;
HBITMAP g_hbmdown = NULL;
HBITMAP g_hbmleft = NULL;
HBITMAP g_hbmright = NULL;
HBITMAP g_hbmspace = NULL;
HBITMAP g_hbmcuxin = NULL;
HBITMAP g_hbmgoodjob = NULL;
HBITMAP g_hbmdefen = NULL;
HBITMAP g_hbmdaojishi = NULL;
HBITMAP g_hbmjiafen = NULL;

HDC hdc;
HDC hdcMem0;
HDC hdcMem1;
HDC hdcMem2;
HDC hdcMem3;
HDC hdcMem4;
HDC hdcMem5;
HDC hdcMem6;
HDC hdcMem7;
HDC hdcMem8;
HDC hdcMem9;


//函数声明
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MyWindowProc(HWND, UINT, WPARAM, LPARAM);
//程序入口函数
int WINAPI WinMain(
	HINSTANCE hinstance,	// 程序实例句柄，在程序运行，进程创建后，由操作系统向应用程序传入
	HINSTANCE hPrevInstance,	// 父进程的程序实例句柄
	LPSTR lpCmdLine,		// 命令行参数，地位和作用类似C语言main函数参数argc和argv,但是没有按空格进行切分
	int nCmdShow)			// 用于指明窗口是否需要显示的参数。
{

	WNDCLASS wc;
	MSG msg;
	BOOL fGotMessage;
	// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中用到了2个窗口。
	HWND hwndX;

	wc.style = 0; // 窗口类样式
	wc.lpfnWndProc = MyWindowProc; //函数指针处理窗口消息
	wc.cbClsExtra = 0;		// no extra class memory 
	wc.cbWndExtra = 0;		// no extra window memory 
	wc.hInstance = hinstance;		// handle to instance 
	// hIcon成员用来指定窗口的图标
	// 这里直接使用LoadIcon函数加载了一个系统预定义的图标，开发人员可也可以自己创建图标。
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	// Cursor是鼠标光标，这里是设定了鼠标光标的样式。
	// 直接使用LoadCursor API函数载入了一个系统预定义的光标样式，还有IDC_CROSS,IDC_HAND等样式
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	// GetStockObject的功能是加载一个系统预定义（在栈中）的GDI对象，
	// 这里加载的是一个白色的画刷，有关画刷和GDI对象，详见GDI说明。
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;		// 窗口的菜单的资源名。
	wc.lpszClassName = "our_game";	// 给窗口类起一个名字，在创建窗口时需要这个名字。

	// Register the window class. 
	if (!RegisterClass(&wc))
	{
		// 窗口注册失败，消息框提示，并退出。
		MessageBoxA(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	// 窗口注册成功，继续运行。
	MessageBoxA(NULL, "根据屏幕显示，按顺序输入上、下、左、右及空格键；\n"
		"3秒一局，过时重开；\n正确一个得一分，输入少于5个得零分，"
		"全对多加5分。\n\n点击确定开始游戏！", "游戏规则", MB_OK);

	hwndX = CreateWindowA("our_game", "413DIY",
		WS_OVERLAPPEDWINDOW, 40, 40, MAX_X, MAX_Y + 20,
		(HWND)NULL, (HMENU)NULL, hinstance, (LPVOID)NULL);


	//创建窗口
	if (!hwndX)
	{
		DWORD dwError = GetLastError();
		// 窗口创建失败，消息框提示，并退出。
		MessageBoxA(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}

	ShowWindow(hwndX, nCmdShow);

	UpdateWindow(hwndX);

	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0
		&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//初始化数据 存储的分数等
//5个位置的存储 初始化位置 单分置零 总分置零 
void init_game(charactor &ch)
{
	ch.changecharactor();
	ch.grade = 0;
	ch.sus = 0;
	ch.sum = 0;
	ch.fal = 0;
	ch.oncegrade = 0;
}

int cout = 0;
DWORD keys[5];

LRESULT CALLBACK MyWindowProc(
	HWND hwnd,// handle to window
	UINT uMsg,        // message identifier
	WPARAM wParam,    // first message parameter
	LPARAM lParam)    // second message parameter
{

	switch (uMsg)
	{
	case WM_CREATE:
	{//将图片空格上下左右等加入内存
		g_hbmspace = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP0));
		if (g_hbmspace == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmup = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
		if (g_hbmup == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmdown = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
		if (g_hbmdown == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmleft = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3));
		if (g_hbmleft == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmright = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP4));
		if (g_hbmright == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmcuxin = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP5));
		if (g_hbmcuxin == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmgoodjob = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP6));
		if (g_hbmgoodjob == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmdefen = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP7));
		if (g_hbmdefen == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);

		g_hbmdaojishi = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP8));
		if (g_hbmdaojishi == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);
		g_hbmjiafen = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP9));
		if (g_hbmjiafen == NULL)
			MessageBoxA(hwnd, "Could not load IDB_BALL!", "Error", MB_OK | MB_ICONEXCLAMATION);


		hdcMem0 = CreateCompatibleDC(hdc);
		hdcMem1 = CreateCompatibleDC(hdc);
		hdcMem2 = CreateCompatibleDC(hdc);
		hdcMem3 = CreateCompatibleDC(hdc);
		hdcMem4 = CreateCompatibleDC(hdc);
		hdcMem5 = CreateCompatibleDC(hdc);
		hdcMem6 = CreateCompatibleDC(hdc);
		hdcMem7 = CreateCompatibleDC(hdc);
		hdcMem8 = CreateCompatibleDC(hdc);
		hdcMem9 = CreateCompatibleDC(hdc);


		HBITMAP hbmOld0 = (HBITMAP)SelectObject(hdcMem0, g_hbmspace);
		GetObject(g_hbmspace, sizeof(bm0), &bm0);

		HBITMAP hbmOld1 = (HBITMAP)SelectObject(hdcMem1, g_hbmup);
		GetObject(g_hbmup, sizeof(bm1), &bm1);

		HBITMAP hbmOld2 = (HBITMAP)SelectObject(hdcMem2, g_hbmdown);
		GetObject(g_hbmdown, sizeof(bm2), &bm2);

		HBITMAP hbmOld3 = (HBITMAP)SelectObject(hdcMem3, g_hbmleft);
		GetObject(g_hbmleft, sizeof(bm3), &bm3);

		HBITMAP hbmOld4 = (HBITMAP)SelectObject(hdcMem4, g_hbmright);
		GetObject(g_hbmright, sizeof(bm4), &bm4);

		HBITMAP hbmOld5 = (HBITMAP)SelectObject(hdcMem5, g_hbmcuxin);
		GetObject(g_hbmcuxin, sizeof(bm5), &bm5);

		HBITMAP hbmOld6 = (HBITMAP)SelectObject(hdcMem6, g_hbmgoodjob);
		GetObject(g_hbmgoodjob, sizeof(bm6), &bm6);

		HBITMAP hbmOld7 = (HBITMAP)SelectObject(hdcMem7, g_hbmdefen);
		GetObject(g_hbmdefen, sizeof(bm7), &bm7);

		HBITMAP hbmOld8 = (HBITMAP)SelectObject(hdcMem8, g_hbmdaojishi);
		GetObject(g_hbmdaojishi, sizeof(bm8), &bm8);

		HBITMAP hbmOld9 = (HBITMAP)SelectObject(hdcMem9, g_hbmjiafen);
		GetObject(g_hbmjiafen, sizeof(bm9), &bm9);

		ch1 = charactor();
		init_game(ch1);  //初始化
		//计时器
		SetTimer(hwnd, ID_TIMER1, 3000, NULL);
		SetTimer(hwnd, ID_TIMER2, 1000, NULL);
		//创建窗口
		hwndgamewindow = CreateWindowA(
			"413",
			"DIY",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			40,
			40,
			MAX_X,
			MAX_Y,
			hwnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.

		hwndtimewindow = CreateWindow(
			"STATIC",  // Predefined class; Unicode assumed 
			"",      // Button text 
			WS_VISIBLE | WS_CHILD | SS_CENTER,  // Styles 
			360,         // x position 
			340,         // y position 
			50,        // Button width
			17,        // Button height
			hwnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.
		hwndname = CreateWindow(
			"STATIC",  // Predefined class; Unicode assumed 
			"倒计时：",      // Button text 
			WS_VISIBLE | WS_CHILD | SS_CENTER,  // Styles 
			290,         // x position 
			340,         // y position 
			70,        // Button width
			17,        // Button height
			hwnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.


		//声音
		PlaySoundA("Wings Of Piano.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					  break;
	}

	case WM_PAINT:

		PAINTSTRUCT ps;
		HPEN hPenWall;

		//画出边框
		hdc = BeginPaint(hwnd, &ps);//要画的区域
		hPenWall = CreatePen(0, 10, RGB(0, 0, 0));
		SelectObject(hdc, hPenWall);
		POINT pt;
		pt.x = 0; pt.y = 0;
		MoveToEx(hdc, 0, 0, &pt);
		LineTo(hdc, 0, MAX_Y - 20);
		LineTo(hdc, MAX_X - 20, MAX_Y - 20);
		LineTo(hdc, MAX_X - 20, 0);
		LineTo(hdc, 0, 0);

		//单局得分
		StretchBlt(hdc, 20, 10, 150, 150, hdcMem8, 0, 0, 322, 300, SRCCOPY);
		ch1.changecharactor();
		scoreonce[0] = ch1.OnceGrade(ch1.sus, ch1.fal);
		CHAR toShow[100];
		if (scoreonce[0] == 10)
			scoreonce[0] = 5;
		StringCbPrintf(toShow, 100, "%d", scoreonce[0]);
		TextOut(hdc, 180, 70, toShow, lstrlen(toShow));

		//总得分
		StretchBlt(hdc, 260, 10, 150, 150, hdcMem7, 0, 0, 322, 300, SRCCOPY);
		scoreall[0] = ch1.changegrade(ch1.grade, ch1.oncegrade);
		CHAR toShowall[100];
		StringCbPrintf(toShowall, 100, "%d", scoreall[0]);
		TextOut(hdc, 400, 70, toShowall, lstrlen(toShowall));
		//画出上下左右空格
		for (c_m = 0, count = 0; c_m < 5; c_m++, count++)
		{
			switch (ch1.c[c_m])
			{
			case 0:
				StretchBlt(hdc, 10 + count * 100, 140, 100, 150, hdcMem0, 0, 0, 332, 300, SRCCOPY);
				break;
			case 1:
				StretchBlt(hdc, 10 + count * 100, 140, 100, 150, hdcMem1, 0, 0, 332, 300, SRCCOPY);
				break;
			case 2:
				StretchBlt(hdc, 10 + count * 100, 140, 100, 150, hdcMem2, 0, 0, 332, 300, SRCCOPY);
				break;
			case 3:
				StretchBlt(hdc, 10 + count * 100, 140, 100, 150, hdcMem3, 0, 0, 332, 300, SRCCOPY);
				break;
			case 4:
				StretchBlt(hdc, 10 + count * 100, 140, 100, 150, hdcMem4, 0, 0, 332, 300, SRCCOPY);
				break;
			}
		}
		//真棒、粗心
		if (tag <= 4 && tag >= 0)
			StretchBlt(hdc, 60, 300, 150, 150, hdcMem5, 0, 0, 332, 300, SRCCOPY);
		else if (tag > 4)
		{
			StretchBlt(hdc, 60, 300, 150, 150, hdcMem6, 0, 0, 332, 300, SRCCOPY);
			StretchBlt(hdc, 210, 60, 30, 30, hdcMem9, 0, 0, 123, 97, SRCCOPY);

		}

		break;

	case WM_KEYDOWN:    //有按键被按下
	{
		keys[cout] = wParam;

		if (cout == 4)
		{
			for (c_c = 0; c_c < 5; c_c++)
			{
				switch (keys[c_c])
				{//用*c指针指向当前当前产生的随机数 用*c来与比较 
					//计分
				case VK_LEFT:
					if (ch1.c[c_c] == LEFT)  //按下键 如果按的键与当前匹配 则过
					{
						ch1.sus++;
					}
					else
					{
						ch1.fal++;
					}
					break;
				case VK_RIGHT:
					if (ch1.c[c_c] == RIGHT)
					{
						ch1.sus++;
					}

					else
					{
						ch1.fal++;
					}
					break;
				case VK_UP:
					if (ch1.c[c_c] == UP)
					{
						ch1.sus++;
					}
					else
					{
						ch1.fal++;
					}
					break;
				case VK_DOWN:
					if (ch1.c[c_c] == DOWN)
					{

						ch1.sus++;
					}
					else
					{

						ch1.fal++;
					}
					break;
				case VK_SPACE:
					if (ch1.c[c_c] == SPACE)
					{

						ch1.sus++;
					}
					else
					{

						ch1.fal++;
					}
					break;
				default:
					break;
				}

			}
			tag = ch1.OnceGrade(ch1.sus, ch1.fal);
			ch1.sum = ch1.sus + ch1.fal;
			KillTimer(hwnd, ID_TIMER1);
			KillTimer(hwndtimewindow, ID_TIMER2);
			InvalidateRect(hwnd, NULL, TRUE);  //设置重新绘制的区域
			UpdateWindow(hwnd);   //发送消息WM_PAINT
			SetTimer(hwnd, ID_TIMER1, 3000, NULL);//重置计时器
			SetTimer(hwndtimewindow, ID_TIMER2, 1000, NULL);//重置计时器

			//重置其他指标
			keys[5] = 0;
			cout = 0;
			tag = -1;
			x = 3;
			ch1.sus = 0, ch1.fal = 0;

		}
		else
		{
			cout++;
			tag = ch1.OnceGrade(ch1.sus, ch1.fal);
		}
		ch1.grade = ch1.changegrade(ch1.grade, ch1.oncegrade);
		break;
	}
	case WM_TIMER:
		switch (wParam)
		{
		case ID_TIMER1:
			stime[0] = x + 1;
			CHAR toShowtime[100];
			StringCbPrintf(toShowtime, 100, "%d", stime[0]);
			SetWindowTextA(hwndtimewindow, toShowtime);
			KillTimer(hwndtimewindow, ID_TIMER2);
			SetTimer(hwndtimewindow, ID_TIMER2, 1000, NULL);//重置计时器


			InvalidateRect(hwnd, NULL, TRUE);  //设置重新绘制的区域
			InvalidateRect(hwndtimewindow, NULL, TRUE);  //设置重新绘制的区域

			UpdateWindow(hwnd);   //发送消息WM_PAINT 
			UpdateWindow(hwndtimewindow);   //发送消息WM_PAINT 
			tag = -1;
			keys[5] = 0;
			cout = 0;
			x = 3;

			break;
		case ID_TIMER2:
			x--;
			stime[0] = x + 1;
			//CHAR toShowtime[100];
			StringCbPrintf(toShowtime, 100, "%d", stime[0]);
			SetWindowTextA(hwndtimewindow, toShowtime);

			InvalidateRect(hwndtimewindow, NULL, TRUE);  //设置重新绘制的区域
			UpdateWindow(hwndtimewindow);   //发送消息WM_PAINT 
			break;
		}

		break;

	case WM_DESTROY:
		MessageBoxA(NULL, "确定要退出吗？", "", MB_OK);
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}