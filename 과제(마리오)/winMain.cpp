#include "stdafx.h"
#include "playGround.h"
#include "mapTool.h"
#include "modeSelect.h"
//API :: Application Programming Interface

//=======================================================
//					##  전역변수 ##
//=======================================================
HINSTANCE	_hInstance;		//인스턴스 핸들
HWND		_hWnd;			//핸들

//포인트 구조체
POINT _ptMouse;
POINT _ptCameraMouse;

LPTSTR _lpszClass = TEXT("Hepta Window API");

BOOL _leftButtonDown;

MODE _md; //선택창 , 맵툴, 플레이그라운드를 정하는 변수
//정적 바인딩
playGround _pg;
mapTool _mt;
modeSelect _ms;

//함수의 프로토 타입
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;		//메시지 구조체
	WNDCLASS	wndClass;		//윈도우 정보 구조체

	_md = MODE_MAPTOOL;
	_hInstance = hInstance;

	//윈도우 정보를 먼저 셋팅한다
	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 배경 색
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//커서 아이콘 모양
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//어플 아이콘 모양
	wndClass.hInstance = hInstance;									//윈도우 인스턴스 번호
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;							//윈도우 클래스 이름
	wndClass.lpszMenuName = NULL;									//윈도우 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 창 스타일

	//윈도우 정보 등록
	RegisterClass(&wndClass);

	//정보를 토대로 윈도우 창 형성

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,		//윈도우 스타일
		WINSTARTX,					//윈도우 창 시작좌표 X
		WINSTARTY,					//윈도우 창 시작좌표 Y
		WINSIZEX,					//윈도우 가로크기
		WINSIZEY,					//윈도우 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	if (_md == MODE_SELECT)
	{
		//클라이언트 영역 재조정
		setWindowSize(WINSTARTX, WINSTARTY, MODESELECTX, MODESELECTY);
		//실제로 윈도우 창을 화면에 투영시켜준다(보여준다)
		ShowWindow(_hWnd, cmdShow);
		//타이머는 메시지 처리 위에 선언
		if (FAILED(_ms.init()))	return 0;
		while (GetMessage(&message, 0, 0, 0))
		{
			TranslateMessage(&message);		//키보드 입력 시 그 메시지 처리 담당
			DispatchMessage(&message);		//실제로 윈도우에 메시지를 전달해주는 역할
		}
	}

	if (_md == MODE_MAPTOOL)
	{
		//클라이언트 영역 재조정
		setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
		//실제로 윈도우 창을 화면에 투영시켜준다(보여준다)
		ShowWindow(_hWnd, cmdShow);
		//타이머는 메시지 처리 위에 선언
		if (FAILED(_mt.init()))	return 0;

		//대기하고 있다가 입력이 들어오면 처리
		while (GetMessage(&message, 0, 0, 0))
		{
			TranslateMessage(&message);		//키보드 입력 시 그 메시지 처리 담당
			DispatchMessage(&message);		//실제로 윈도우에 메시지를 전달해주는 역할
		}
		//while (true)
		//{
		//	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		//	{
		//		if (message.message == WM_QUIT) break;

		//		TranslateMessage(&message);		//키보드 입력 시 그 메시지 처리 담당
		//		DispatchMessage(&message);		//실제로 윈도우에 메시지를 전달해주는 역할
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
		//클라이언트 영역 재조정
		setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
		//실제로 윈도우 창을 화면에 투영시켜준다(보여준다)
		ShowWindow(_hWnd, cmdShow);
		//타이머는 메시지 처리 위에 선언
		if (FAILED(_pg.init()))	return 0;
		
		//계속 돌아가고 있는중
		while (true)
		{
			if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			{
				if (message.message == WM_QUIT) break;

				TranslateMessage(&message);		//키보드 입력 시 그 메시지 처리 담당
				DispatchMessage(&message);		//실제로 윈도우에 메시지를 전달해주는 역할
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

	//윈도우 사이즈 재조정을 해준다
	AdjustWindowRect(&winRect, WINSTYLE, false);

	//윈도우 위치를 재조정
	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}

