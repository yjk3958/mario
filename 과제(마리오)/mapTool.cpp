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
	gameNode::init(true);

	IMAGEMANAGER->addFrameImage("backGround", "./image/Mario-backGround+ground.bmp", 80, 64, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cloud", "./image/Mario-cloud+grass.bmp", 128, 112, 8, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("endPlate", "./image/Mario-endPlate.bmp", 32, 32, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("object", "./image/Mario-object.bmp", 96, 176, 6, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("item", "./image/Mario-item.bmp", 32, 16, 6, 11, true, RGB(255, 0, 255));
	
	CAMERAMANAGER->init(TILESIZE*TILEBASEX, TILESIZE*TILEBASEY, CAMERAX, CAMERAY, 0.0f, 0.0f, 4.0);

	_image = IMAGEMANAGER->findImage("backGround");
	
	_checkBox = false;

	setup();
	return S_OK;
}
void mapTool::release(void)		
{
	gameNode::release();
}
void mapTool::update(void)		
{
	gameNode::update();
}
void mapTool::render(void)		
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================

	RectangleMake(getMemDC(), CAMERASTARTX, CAMERASTARTY, CAMERAX, CAMERAY);
	RectangleMake(getMemDC(), SAMPLETILESTARTX, SAMPLETILESTARTY, SAMPLETILEBOXX, SAMPLETILEBOXY);

	//for (int i = 0; i < _image->getMaxFrameX(); ++i)
	//{
	//	for (int j = 0; j < _image->getMaxFrameY(); ++j)
	//	{
	//		RectangleMake(getMemDC(), SAMPLETILESTARTX + i * TILESIZE*4, SAMPLETILESTRATY + j *TILESIZE * 4, TILESIZE * 4, TILESIZE * 4);
	//	}
	//}
	
	//_image->render(CAMERAMANAGER->getMemDC(), 0, 0);


	//타일 갯수만치 배경
	for (int i = 0; i < _vTile.size(); ++i)
	{
		IMAGEMANAGER->frameRender("backGround", CAMERAMANAGER->getMemDC(),
			_vTile[i].rc.left, _vTile[i].rc.top,
			_vTile[i].terrainFrameX, _vTile[i].terrainFrameY);
	}

	//타일 갯수만치 오브젝트
	for (int i = 0; i < _vTile.size(); ++i)
	{
		if (_vTile[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("object", CAMERAMANAGER->getMemDC(),
			_vTile[i].rc.left, _vTile[i].rc.top,
			_vTile[i].objFrameX, _vTile[i].objFrameY);
	}

	CAMERAMANAGER->render(getMemDC());

	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

						
void mapTool::setup() 
{
	_btnSave = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);

	_btnLoad = CreateWindow("button", "Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);

	_btnTerrainDraw = CreateWindow("button", "Terrain", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);

	_btnObjectDraw = CreateWindow("button", "Object", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1000, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);

	_btnEraser = CreateWindow("button", "지우개", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);

	_btnDrag = CreateWindow("button", "범위지정", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 900, 620, 100, 30, _hWnd, HMENU(5), _hInstance, NULL);

	_ctrSelect = CTRL_TERRAINDRAW;

	//기본 타일 세팅
	for (int i = 0; i < TILEBASEY; ++i)
	{
		for (int j = 0; j < TILEBASEX; ++j)
		{
			tagTile tile;
			SetRect(&tile.rc,
				j*TILESIZE,
				i*TILESIZE,
				j*TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);		//타일 위치조정
			_vTile.push_back(tile);			//타일 백터에 넣기
		}
	}

	//세부 타일정보 세팅
	for (int i = 0; i < _vTile.size(); ++i)
	{
		_vTile[i].item = ITEM_NONE;
		_vTile[i].obj = OBJ_NONE;
		_vTile[i].objFrameX = 0;
		_vTile[i].objFrameY = 0;
		_vTile[i].terrain = TR_NONE;
		_vTile[i].terrainFrameX = 0;
		_vTile[i].terrainFrameY = 0;
	}
	setSampleTile();

}
void mapTool::setMap()
{
	int sampleTileX = _image->getMaxFrameX();
	int sampleTileY = _image->getMaxFrameY();
	/*for (int i = 0; i < sampleTileX*sampleTileY; ++i)
	{
		if(PtInRect(&_sam))
	}*/
	if (_checkBox)
	{
		int startX = _basePoint.x / TILESIZE;
		int startY = _basePoint.y / TILESIZE;
		int endX = _endPoint.x / TILESIZE;
		int endY = _endPoint.y / TILESIZE;

		if (_currentCtrl == CTRL_TERRAINDRAW)
		{




		}

	}
	else
	{
		



	}
}


void mapTool::save()
{
	HANDLE file;
	DWORD write;

	const int i = _vTile.size();

	tagTile* saveTile = new tagTile[i];

	file = CreateFile("saveMap.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


	WriteFile(file, saveTile, sizeof(tagTile)*i, &write, NULL);

	CloseHandle(file);
}
void mapTool::load()
{
	HANDLE file;
	DWORD read;

	const int i = _vTile.size();

	tagTile* saveTile = new tagTile[i];

	file = CreateFile("saveMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, saveTile, sizeof(tagTile)*i, &read, NULL);

	CloseHandle(file);
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
			if(!_checkBox)this->setMap();
			if (_checkBox)
			{
				_basePoint = _endPoint = _ptMouse;
			}
			break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
			if (_checkBox)
			{
				this->setMap();
				_checkBox = false;
			}
			break;
		case WM_MOUSEMOVE:
		{
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
			if (_leftButtonDown&&!_checkBox) this->setMap();
			if (_leftButtonDown&&_checkBox) _endPoint = _ptMouse;
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
			case CTRL_BOXMAKE:
				if(!_checkBox)_checkBox = true;
				if (_checkBox)_checkBox = false;
			case CTRL_TERRAINDRAW :
				this ->setCtrlSelect(LOWORD(wParam));
				_currentCtrl = CTRL_TERRAINDRAW;
				_image = IMAGEMANAGER->findImage("backGround");
				this->setSampleTile();

			case CTRL_OBJDRAW :
				this->setCtrlSelect(LOWORD(wParam));
				_currentCtrl = CTRL_OBJDRAW;
				_image = IMAGEMANAGER->findImage("object");
				this->setSampleTile();
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


void mapTool::setSampleTile()
{
	int sampleTileX = _image->getMaxFrameX();
	int sampleTileY = _image->getMaxFrameY();

	for (int i = 0; i < sampleTileY; ++i)
	{
		for (int j = 0; j < sampleTileX; ++j)
		{
			_sampleTile[i * sampleTileX + j].terrainFrameX = j;
			_sampleTile[i * sampleTileX + j].terrainFrameY = i;

			//렉트 셋팅 함수
			SetRect(&_sampleTile[i * sampleTileX + j].rcTile,
				(SAMPLETILESTARTX- _image->getWidth()) + j * TILESIZE,
				SAMPLETILESTARTY+i * TILESIZE,
				(SAMPLETILESTARTX - _image->getWidth()) + j * TILESIZE + TILESIZE,
				SAMPLETILESTARTY+i * TILESIZE + TILESIZE);
		}
	}

}