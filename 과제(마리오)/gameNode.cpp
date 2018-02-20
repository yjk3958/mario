#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

HRESULT gameNode::init(void)  
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		SOUNDMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		INIDATA->init();
		DATABASE->init();
	}

	return S_OK;
}

void gameNode::release(void)  
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		INIDATA->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		DATABASE->release();
		DATABASE->releaseSingleton();
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)	  
{
	SOUNDMANAGER->update();
}

void gameNode::render(void)
{

}
//맵 셋팅 함수
void gameNode::setMap(void)
{

}

//저장, 로드
void gameNode::save(void)
{

}
void gameNode::load(void)
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//조사숙제
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

			if (_leftButtonDown) this->setMap();
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