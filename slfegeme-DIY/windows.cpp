#include <windows.h>
#include <iostream>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include <strsafe.h>
#include <mmsystem.h>

#pragma  comment(lib,"WinMM.Lib")

//ȫ�ֱ���
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


//��������
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MyWindowProc(HWND, UINT, WPARAM, LPARAM);
//������ں���
int WINAPI WinMain(
	HINSTANCE hinstance,	// ����ʵ��������ڳ������У����̴������ɲ���ϵͳ��Ӧ�ó�����
	HINSTANCE hPrevInstance,	// �����̵ĳ���ʵ�����
	LPSTR lpCmdLine,		// �����в�������λ����������C����main��������argc��argv,����û�а��ո�����з�
	int nCmdShow)			// ����ָ�������Ƿ���Ҫ��ʾ�Ĳ�����
{

	WNDCLASS wc;
	MSG msg;
	BOOL fGotMessage;
	// ���ھ����hwnd�����������ڵľ��������������õ���2�����ڡ�
	HWND hwndX;

	wc.style = 0; // ��������ʽ
	wc.lpfnWndProc = MyWindowProc; //����ָ�봦������Ϣ
	wc.cbClsExtra = 0;		// no extra class memory 
	wc.cbWndExtra = 0;		// no extra window memory 
	wc.hInstance = hinstance;		// handle to instance 
	// hIcon��Ա����ָ�����ڵ�ͼ��
	// ����ֱ��ʹ��LoadIcon����������һ��ϵͳԤ�����ͼ�꣬������Ա��Ҳ�����Լ�����ͼ�ꡣ
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);
	// Cursor������꣬�������趨����������ʽ��
	// ֱ��ʹ��LoadCursor API����������һ��ϵͳԤ����Ĺ����ʽ������IDC_CROSS,IDC_HAND����ʽ
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	// GetStockObject�Ĺ����Ǽ���һ��ϵͳԤ���壨��ջ�У���GDI����
	// ������ص���һ����ɫ�Ļ�ˢ���йػ�ˢ��GDI�������GDI˵����
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;		// ���ڵĲ˵�����Դ����
	wc.lpszClassName = "our_game";	// ����������һ�����֣��ڴ�������ʱ��Ҫ������֡�

	// Register the window class. 
	if (!RegisterClass(&wc))
	{
		// ����ע��ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBoxA(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	// ����ע��ɹ����������С�
	MessageBoxA(NULL, "������Ļ��ʾ����˳�������ϡ��¡����Ҽ��ո����\n"
		"3��һ�֣���ʱ�ؿ���\n��ȷһ����һ�֣���������5������֣�"
		"ȫ�Զ��5�֡�\n\n���ȷ����ʼ��Ϸ��", "��Ϸ����", MB_OK);

	hwndX = CreateWindowA("our_game", "413DIY",
		WS_OVERLAPPEDWINDOW, 40, 40, MAX_X, MAX_Y + 20,
		(HWND)NULL, (HMENU)NULL, hinstance, (LPVOID)NULL);


	//��������
	if (!hwndX)
	{
		DWORD dwError = GetLastError();
		// ���ڴ���ʧ�ܣ���Ϣ����ʾ�����˳���
		MessageBoxA(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
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

//��ʼ������ �洢�ķ�����
//5��λ�õĴ洢 ��ʼ��λ�� �������� �ܷ����� 
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
	{//��ͼƬ�ո��������ҵȼ����ڴ�
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
		init_game(ch1);  //��ʼ��
		//��ʱ��
		SetTimer(hwnd, ID_TIMER1, 3000, NULL);
		SetTimer(hwnd, ID_TIMER2, 1000, NULL);
		//��������
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
			"����ʱ��",      // Button text 
			WS_VISIBLE | WS_CHILD | SS_CENTER,  // Styles 
			290,         // x position 
			340,         // y position 
			70,        // Button width
			17,        // Button height
			hwnd,     // Parent window
			NULL,       // No menu.
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);      // Pointer not needed.


		//����
		PlaySoundA("Wings Of Piano.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					  break;
	}

	case WM_PAINT:

		PAINTSTRUCT ps;
		HPEN hPenWall;

		//�����߿�
		hdc = BeginPaint(hwnd, &ps);//Ҫ��������
		hPenWall = CreatePen(0, 10, RGB(0, 0, 0));
		SelectObject(hdc, hPenWall);
		POINT pt;
		pt.x = 0; pt.y = 0;
		MoveToEx(hdc, 0, 0, &pt);
		LineTo(hdc, 0, MAX_Y - 20);
		LineTo(hdc, MAX_X - 20, MAX_Y - 20);
		LineTo(hdc, MAX_X - 20, 0);
		LineTo(hdc, 0, 0);

		//���ֵ÷�
		StretchBlt(hdc, 20, 10, 150, 150, hdcMem8, 0, 0, 322, 300, SRCCOPY);
		ch1.changecharactor();
		scoreonce[0] = ch1.OnceGrade(ch1.sus, ch1.fal);
		CHAR toShow[100];
		if (scoreonce[0] == 10)
			scoreonce[0] = 5;
		StringCbPrintf(toShow, 100, "%d", scoreonce[0]);
		TextOut(hdc, 180, 70, toShow, lstrlen(toShow));

		//�ܵ÷�
		StretchBlt(hdc, 260, 10, 150, 150, hdcMem7, 0, 0, 322, 300, SRCCOPY);
		scoreall[0] = ch1.changegrade(ch1.grade, ch1.oncegrade);
		CHAR toShowall[100];
		StringCbPrintf(toShowall, 100, "%d", scoreall[0]);
		TextOut(hdc, 400, 70, toShowall, lstrlen(toShowall));
		//�����������ҿո�
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
		//���������
		if (tag <= 4 && tag >= 0)
			StretchBlt(hdc, 60, 300, 150, 150, hdcMem5, 0, 0, 332, 300, SRCCOPY);
		else if (tag > 4)
		{
			StretchBlt(hdc, 60, 300, 150, 150, hdcMem6, 0, 0, 332, 300, SRCCOPY);
			StretchBlt(hdc, 210, 60, 30, 30, hdcMem9, 0, 0, 123, 97, SRCCOPY);

		}

		break;

	case WM_KEYDOWN:    //�а���������
	{
		keys[cout] = wParam;

		if (cout == 4)
		{
			for (c_c = 0; c_c < 5; c_c++)
			{
				switch (keys[c_c])
				{//��*cָ��ָ��ǰ��ǰ����������� ��*c����Ƚ� 
					//�Ʒ�
				case VK_LEFT:
					if (ch1.c[c_c] == LEFT)  //���¼� ������ļ��뵱ǰƥ�� ���
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
			InvalidateRect(hwnd, NULL, TRUE);  //�������»��Ƶ�����
			UpdateWindow(hwnd);   //������ϢWM_PAINT
			SetTimer(hwnd, ID_TIMER1, 3000, NULL);//���ü�ʱ��
			SetTimer(hwndtimewindow, ID_TIMER2, 1000, NULL);//���ü�ʱ��

			//��������ָ��
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
			SetTimer(hwndtimewindow, ID_TIMER2, 1000, NULL);//���ü�ʱ��


			InvalidateRect(hwnd, NULL, TRUE);  //�������»��Ƶ�����
			InvalidateRect(hwndtimewindow, NULL, TRUE);  //�������»��Ƶ�����

			UpdateWindow(hwnd);   //������ϢWM_PAINT 
			UpdateWindow(hwndtimewindow);   //������ϢWM_PAINT 
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

			InvalidateRect(hwndtimewindow, NULL, TRUE);  //�������»��Ƶ�����
			UpdateWindow(hwndtimewindow);   //������ϢWM_PAINT 
			break;
		}

		break;

	case WM_DESTROY:
		MessageBoxA(NULL, "ȷ��Ҫ�˳���", "", MB_OK);
		ExitProcess(0);
		break;

	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}