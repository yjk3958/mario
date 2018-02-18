#include "stdafx.h"
#include "modeSelect.h"


modeSelect::modeSelect()
{
}


modeSelect::~modeSelect()
{

}

HRESULT modeSelect::init(void)
{
	gameNode::init(true);

	//선택하는 버튼 생성
	_btnMapTool = CreateWindow("button", "MapTool", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 75, MODESELECTY/2-30, 100, 60, _hWnd, HMENU(0), _hInstance, NULL);

	_btnPlay = CreateWindow("button", "Play", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 225, MODESELECTY / 2-30, 100, 60, _hWnd, HMENU(1), _hInstance, NULL);

	return S_OK;
}
void modeSelect::release(void)
{

}
void modeSelect::update(void) 
{

}
void modeSelect::render(void) 
{

}
LRESULT modeSelect::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		this->render();

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
		this->update();
		break;
	case WM_LBUTTONDOWN:
		_leftButtonDown = true;
		this->setMap();
		break;
	case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;
	case WM_MOUSEMOVE:
	{
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
	}
	break;
	case WM_COMMAND: //버튼 눌렀을때
		switch (LOWORD(wParam))
		{
		case SELECT_MAPTOOL:
			_md = MODE_MAPTOOL;
			break;

		case SELECT_PLAY:
			_md = MODE_PLAYGROUND;
			break;
		}
		break;


	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}