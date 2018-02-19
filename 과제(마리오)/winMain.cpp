#include "stdafx.h"
#include "playGround.h"
#include "mapTool.h"
#include "modeSelect.h"
//API :: Application Programming Interface

//=======================================================
//					##  �������� ##
//=======================================================
HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
HWND		_hWnd;			//�ڵ�

//����Ʈ ����ü
POINT _ptMouse;

LPTSTR _lpszClass = TEXT("Hepta Window API");

BOOL _leftButtonDown;

MODE _md; //����â , ����, �÷��̱׶��带 ���ϴ� ����
//���� ���ε�
playGround _pg;
mapTool _mt;
modeSelect _ms;

//�Լ��� ������ Ÿ��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;		//�޽��� ����ü
	WNDCLASS	wndClass;		//������ ���� ����ü

	_md = MODE_MAPTOOL;
	_hInstance = hInstance;

	//������ ������ ���� �����Ѵ�
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��� ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//Ŀ�� ������ ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���� ������ ���
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;							//������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

	//������ ���� ���
	RegisterClass(&wndClass);

	//������ ���� ������ â ����

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,		//������ ��Ÿ��
		WINSTARTX,					//������ â ������ǥ X
		WINSTARTY,					//������ â ������ǥ Y
		WINSIZEX,					//������ ����ũ��
		WINSIZEY,					//������ ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	if (_md == MODE_SELECT)
	{
		//Ŭ���̾�Ʈ ���� ������
		setWindowSize(WINSTARTX, WINSTARTY, MODESELECTX, MODESELECTY);
		//������ ������ â�� ȭ�鿡 ���������ش�(�����ش�)
		ShowWindow(_hWnd, cmdShow);
		//Ÿ�̸Ӵ� �޽��� ó�� ���� ����
		if (FAILED(_ms.init()))	return 0;
		while (GetMessage(&message, 0, 0, 0))
		{
			TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
			DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
		}
	}

	if (_md == MODE_MAPTOOL)
	{
		//Ŭ���̾�Ʈ ���� ������
		setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
		//������ ������ â�� ȭ�鿡 ���������ش�(�����ش�)
		ShowWindow(_hWnd, cmdShow);
		//Ÿ�̸Ӵ� �޽��� ó�� ���� ����
		if (FAILED(_mt.init()))	return 0;

		//����ϰ� �ִٰ� �Է��� ������ ó��
		while (GetMessage(&message, 0, 0, 0))
		{
			TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
			DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
		}
		//while (true)
		//{
		//	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		//	{
		//		if (message.message == WM_QUIT) break;

		//		TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
		//		DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
		//	}
		//	else
		//	{
		//		TIMEMANAGER->update(60.0f);
		//		_mt.update();
		//		_mt.render();
		//	}
		//}
	}

	if (_md == MODE_PLAYGROUND)
	{
		//Ŭ���̾�Ʈ ���� ������
		setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
		//������ ������ â�� ȭ�鿡 ���������ش�(�����ش�)
		ShowWindow(_hWnd, cmdShow);
		//Ÿ�̸Ӵ� �޽��� ó�� ���� ����
		if (FAILED(_pg.init()))	return 0;
		
		//��� ���ư��� �ִ���
		while (true)
		{
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT) break;

				TranslateMessage(&message);		//Ű���� �Է� �� �� �޽��� ó�� ���
				DispatchMessage(&message);		//������ �����쿡 �޽����� �������ִ� ����
			}
			else
			{
				TIMEMANAGER->update(60.0f);
				_pg.update();
				_pg.render();
			}
		}
	}


	_pg.release();
	_ms.release();
	_mt.release();
	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (_md)
	{
	case MODE_SELECT:
		return _ms.MainProc(hWnd, iMessage, wParam, lParam);
	case MODE_MAPTOOL:
		return _mt.MainProc(hWnd, iMessage, wParam, lParam);
	case MODE_PLAYGROUND:
		return _pg.MainProc(hWnd, iMessage, wParam, lParam);
	}
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//������ ������ �������� ���ش�
	AdjustWindowRect(&winRect, WINSTYLE, false);

	//������ ��ġ�� ������
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}

