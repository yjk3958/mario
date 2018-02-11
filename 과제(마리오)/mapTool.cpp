#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{

}


HRESULT mapTool::init(void)		
{
	IMAGEMANAGER->addFrameImage("backGround", "./image/Mario-backGround+ground.bmp", 80, 64, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cloud", "./image/Mario-cloud+grass.bmp", 128, 112, 8, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("endPlate", "./image/Mario-endPlate.bmp", 32, 32, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("object", "./image/Mario-object.bmp", 96, 176, 6, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("item", "./image/Mario-item.bmp", 32, 16, 6, 11, true, RGB(255, 0, 255));
	
	_image = IMAGEMANAGER->findImage("backGround");

	setup();
	return S_OK;
}
void mapTool::release(void)		
{

}
void mapTool::update(void)		
{

}
void mapTool::render(void)		
{

}

						
void mapTool::setup() 
{
	_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);

	_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);

	_btnTerrainDraw = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);

	_btnObjectDraw = CreateWindow("button", "Object", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);

	_btnEraser = CreateWindow("button", "지우개", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);

	_btnDrag = CreateWindow("button", "범위지정", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 700, 620, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);

	_ctrSelect = CTRL_TERRAINDRAW;


}
void mapTool::setMap()
{

}


void mapTool::save()
{

}
void mapTool::load()
{

}
//
//TERRAIN mapTool::terrainSelect(int frameX, int frameY)
//{
//
//}
//OBJECT mapTool::objSelect(int frameX, int frameY)	  
//{
//
//}
//ITEM mapTool::itemSelect(int frameX, int frameY)
//{
//
//}

LRESULT mapTool::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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

			if (_leftButtonDown) this->setMap();
		}
		break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case CTRL_SAVE:
				this->save();
				break;

			case CTRL_LOAD:
				this->load();
				InvalidateRect(hWnd, NULL, false);
				break;

			default:
				this->setCtrlSelect(LOWORD(wParam));
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