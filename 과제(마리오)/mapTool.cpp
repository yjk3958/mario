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
	setSampleTile();
	_checkBox = false;
	_cameraBox = RectMake(CAMERASTARTX, CAMERASTARTY, CAMERAX, CAMERAY);
	_sampleBox = RectMake(SAMPLETILESTARTX, SAMPLETILESTARTY, SAMPLETILEBOXX, SAMPLETILEBOXY);
	_page = 1;

	_currentLineX = TILEBASEX;
	_currentLineY = TILEBASEY;

	_ctrlCameraRect[CTRL_UP] = RectMakeCenter(CAMERASTARTX+CAMERAX / 2, CAMERASTARTY - 25, 100, 40);
	_ctrlCameraRect[CTRL_DOWN] = RectMakeCenter(CAMERASTARTX+CAMERAX / 2, CAMERASTARTY + CAMERAY + 25, 100, 40);
	_ctrlCameraRect[CTRL_LEFT] = RectMakeCenter(CAMERASTARTX - 25, CAMERASTARTY+ CAMERAY / 2, 40, 100);
	_ctrlCameraRect[CTRL_RIGHT] = RectMakeCenter(CAMERASTARTX+CAMERAX + 25, CAMERASTARTY+CAMERAY / 2, 40, 100);
	_ctrlPage[0] = RectMakeCenter(SAMPLETILESTARTX + SAMPLETILEBOXX / 2 - 50, SAMPLETILESTARTY + SAMPLETILEBOXY - 20, 40, 15);
	_ctrlPage[1] = RectMakeCenter(SAMPLETILESTARTX + SAMPLETILEBOXX / 2 + 50, SAMPLETILESTARTY + SAMPLETILEBOXY - 20, 40, 15);
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
	Rectangle(getMemDC(), _ctrlPage[0].left, _ctrlPage[0].top, _ctrlPage[0].right, _ctrlPage[0].bottom);
	Rectangle(getMemDC(), _ctrlPage[1].left, _ctrlPage[1].top, _ctrlPage[1].right, _ctrlPage[1].bottom);
	//for (int i = 0; i < _image->getMaxFrameX(); ++i)
	//{
	//	for (int j = 0; j < _image->getMaxFrameY(); ++j)
	//	{
	//		RectangleMake(getMemDC(), SAMPLETILESTARTX + i * TILESIZE*4, SAMPLETILESTRATY + j *TILESIZE * 4, TILESIZE * 4, TILESIZE * 4);
	//	}
	//}
	
	//_image->render(CAMERAMANAGER->getMemDC(), 0, 0);
	for (int i = 0; i < 4; ++i)
	{
		Rectangle(getMemDC(), _ctrlCameraRect[i].left, _ctrlCameraRect[i].top, _ctrlCameraRect[i].right, _ctrlCameraRect[i].bottom);
	}

	//타일 갯수만치 배경
	for (int i = 0; i < _vTile.size(); ++i)
	{
		

		Rectangle(CAMERAMANAGER->getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].rc.right, _vTile[i].rc.bottom);
		Rectangle(getMemDC(), _vTile[i].rc.left, _vTile[i].rc.top, _vTile[i].rc.right, _vTile[i].rc.bottom);
		
		IMAGEMANAGER->frameRender("backGround", CAMERAMANAGER->getMemDC(),
			_vTile[i].rc.left, _vTile[i].rc.top,
			_vTile[i].terrainFrameX, _vTile[i].terrainFrameY);

		//if (PtInRect(&_vTile[i].rc, PointMake(CAMERAMANAGER->getX() + CAMERAX/2, CAMERAMANAGER->getY() + CAMERAY/2)))
		//{
		//TCHAR md[128];
		//wsprintf(md, "%d, %d", _vTile[i].rc.left, _vTile[i].rc.top);
		//TextOut(getMemDC(), 10, 20, md, strlen(md));
		//}
	}

	for (int i = 0; i < _vTile.size(); ++i)
	{
		if (_vTile[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("object", CAMERAMANAGER->getMemDC(),
			_vTile[i].rc.left, _vTile[i].rc.top,
			_vTile[i].objFrameX, _vTile[i].objFrameY);
	}



	//타일 갯수만치 오브젝트


	for (int i = 0; i < _vSampleTile.size(); ++i)
	{
		if (_vSampleTile.size() > 20)
		{
			if ((_page == 1 && i < 20)||
				(_page == 2 && (i < 40 && i >= 20))||
				(_page == 3 && (i < 60 && i >= 40))||
				(_page == 4 && (i < 80 && i >= 60))
				)
			{
				Rectangle(getMemDC(), _vSampleTile[i].rcTile.left, _vSampleTile[i].rcTile.top, _vSampleTile[i].rcTile.right, _vSampleTile[i].rcTile.bottom);
				_image->frameMagRender(getMemDC(), _vSampleTile[i].rcTile.left, _vSampleTile[i].rcTile.top, _vSampleTile[i].terrainFrameX, _vSampleTile[i].terrainFrameY, 4);
			}

			else continue;
		}
		else
		{
			Rectangle(getMemDC(), _vSampleTile[i].rcTile.left, _vSampleTile[i].rcTile.top, _vSampleTile[i].rcTile.right, _vSampleTile[i].rcTile.bottom);
			_image->frameMagRender(getMemDC(), _vSampleTile[i].rcTile.left, _vSampleTile[i].rcTile.top, _vSampleTile[i].terrainFrameX, _vSampleTile[i].terrainFrameY, 4);
		}
	}


	CAMERAMANAGER->render(getMemDC());
	TCHAR text[128];
	wsprintf(text, "카메라 마우스 좌표 : %d , %d", _ptCameraMouse.x, _ptCameraMouse.y);
	TextOut(getMemDC(), 10, 10, text, strlen(text));

	TCHAR dr[128];
	sprintf(dr, "카메라 매니저 시작점 좌표 : %f, %f", CAMERAMANAGER->getX(), CAMERAMANAGER->getY());
	TextOut(getMemDC(), 10, 30, dr, strlen(dr));

	TCHAR cr[128];
	wsprintf(cr, "샘플타일 종류 좌표 : %d , %d", _currentFrameX, _currentFrameY);
	TextOut(getMemDC(), 10, 50, cr, strlen(cr));

	TCHAR tr[128];
	wsprintf(tr, "사이즈  %d", _vTile.size());
	TextOut(getMemDC(), 10, 70, tr, strlen(tr));

	TCHAR t[128];
	wsprintf(t, "%d", _currentCtrl);
	TextOut(getMemDC(), 10, 90, t, strlen(t));
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

	_btnMakeTile = CreateWindow("button", "MakeTile", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 1000, 620, 100, 30, _hWnd, HMENU(6), _hInstance, NULL);

	_ctrSelect = CTRL_TERRAINDRAW;

	//기본 타일 세팅
	for (int i = 0; i < TILEBASEY; ++i)
	{
		for (int j = 0; j < TILEBASEX; ++j)
		{
			tagTile tile;
			SetRect(&tile.rc,
			j * TILESIZE,
			i * TILESIZE,
			j * TILESIZE + TILESIZE,
			i * TILESIZE + TILESIZE);		//타일 위치조정
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

		for (int i = 0; i < _vTile.size(); ++i)
		{
			if (PtInRect(&_vTile[i].rc, _ptCameraMouse))
			{
				if (_currentCtrl == CTRL_OBJDRAW)
				{
					_vTile[i].objFrameX = _currentFrameX;
					_vTile[i].objFrameY = _currentFrameY;
				} 
				if (_currentCtrl == CTRL_TERRAINDRAW)
				{
					_vTile[i].terrainFrameX = _currentFrameX;
					_vTile[i].terrainFrameY = _currentFrameY;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < _vTile.size(); ++i)
		{
			if (PtInRect(&_vTile[i].rc, _ptCameraMouse))
			{
				if (_currentCtrl == CTRL_OBJDRAW)
				{
					_vTile[i].obj = OBJ_BLOCK;
					_vTile[i].objFrameX = _currentFrameX;
					_vTile[i].objFrameY = _currentFrameY;
				}
				if (_currentCtrl == CTRL_TERRAINDRAW)
				{
					_vTile[i].terrainFrameX = _currentFrameX;
					_vTile[i].terrainFrameY = _currentFrameY;
				}
				InvalidateRect(_hWnd, NULL, false);
				break;
			}

		}
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


	WriteFile(file, &saveTile, sizeof(tagTile)*i, &write, NULL);
	 
	CloseHandle(file);
}
void mapTool::load()
{
	HANDLE file;
	DWORD read;

	const int i = _vTile.size();

	tagTile saveTile;

	file = CreateFile("saveMap.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	ReadFile(file, &saveTile, sizeof(tagTile) * i, &read, NULL);

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

			for (int i = 0; i < CTRL_NONE; ++i)
			{
				if (PtInRect(&_ctrlCameraRect[i], _ptMouse))
				{
					setCameraMove((CTRLDIRECTION)i);
					InvalidateRect(hWnd, NULL, false);
					break;
				}
				else setCameraMove(CTRL_NONE);
			
			}

			if(!_checkBox)this->setMap();
			if (_checkBox)
			{
				_basePoint = _endPoint = _ptCameraMouse;
			}
			if (PtInRect(&_ctrlPage[0], _ptMouse))
			{
				_page--;
				if (_page < 1) _page = 1;
				InvalidateRect(hWnd, NULL, false);
				break;
			}
			if (PtInRect(&_ctrlPage[1], _ptMouse))
			{
				_page++;
				if (_page > 4)_page = 4;
				InvalidateRect(hWnd, NULL, false);
				break;
			}
			if (PtInRect(&_sampleBox, _ptMouse))
			{
				for (int i = 0; i < _vSampleTile.size(); ++i)
				{
					if (PtInRect(&_vSampleTile[i].rcTile, _ptMouse))
					{
						_currentFrameX = _vSampleTile[i].terrainFrameX;
						_currentFrameY = _vSampleTile[i].terrainFrameY;
						break;
					}
					else continue;
				}
			}
			InvalidateRect(hWnd, NULL, false);
			break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
			if (_checkBox)
			{
				if(PtInRect(&_cameraBox,_ptMouse)) this->setMap();
				_checkBox = false;
			}
			setCameraMove(CTRL_NONE);
			break;
		case WM_MOUSEMOVE:
		{
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
			if (PtInRect(&_cameraBox, _ptMouse))
			{
				_ptCameraMouse.x = CAMERAMANAGER->getX() + (_ptMouse.x - CAMERASTARTX)/CAMERAMANAGER->getMg();
				_ptCameraMouse.y = CAMERAMANAGER->getY() + (_ptMouse.y - CAMERASTARTY) / CAMERAMANAGER->getMg();
			}
			else
			{
				_ptCameraMouse.x = _ptMouse.x;
				_ptCameraMouse.y = _ptMouse.y;
			}

			if (_leftButtonDown&&!_checkBox) this->setMap();
			if (_leftButtonDown&&_checkBox) _endPoint = _ptCameraMouse;
			InvalidateRect(hWnd, NULL, false);
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
				break;
			case CTRL_TERRAINDRAW :
				this ->setCtrlSelect(LOWORD(wParam));
				_currentCtrl = CTRL_TERRAINDRAW;
				//_currentFrameX = _currentFrameY = 0;
				_image = IMAGEMANAGER->findImage("backGround");
				this->setSampleTile();
				InvalidateRect(hWnd, NULL, false);
				break;
			case CTRL_OBJDRAW :
				this->setCtrlSelect(LOWORD(wParam));
				_currentCtrl = CTRL_OBJDRAW;
				//_currentFrameX = _currentFrameY = 0;
				_image = IMAGEMANAGER->findImage("object");
				this->setSampleTile();
				InvalidateRect(hWnd, NULL, false);
				break;
			case CTRL_TILEMAKE :
				this->setCtrlSelect(LOWORD(wParam));
				if (_tileMake) _tileMake = false;
				else _tileMake = true;
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


void mapTool::setSampleTile()
{
	//int sampleTileX = _image->getMaxFrameX();
	//int sampleTileY = _image->getMaxFrameY();

	//for (int i = 0; i < sampleTileY; ++i)
	//{
	//	for (int j = 0; j < sampleTileX; ++j)
	//	{
	//		_sampleTile[i * sampleTileX + j].terrainFrameX = j;
	//		_sampleTile[i * sampleTileX + j].terrainFrameY = i;

	//		//렉트 셋팅 함수
	//		SetRect(&_sampleTile[i * sampleTileX + j].rcTile,
	//			(SAMPLETILESTARTX- _image->getWidth()) + j * TILESIZE,
	//			SAMPLETILESTARTY+i * TILESIZE,
	//			(SAMPLETILESTARTX - _image->getWidth()) + j * TILESIZE + TILESIZE,
	//			SAMPLETILESTARTY+i * TILESIZE + TILESIZE);
	//	}
	//}

	_vSampleTile.clear();

	int sampleTileX = _image->getMaxFrameX()+1;
	int sampleTileY = _image->getMaxFrameY()+1;


	for (int i = 0; i < sampleTileY; ++i)
	{
		for (int j = 0; j < sampleTileX; ++j)
		{
			tagSampleTile sampleTile;
			sampleTile.terrainFrameX = j;
			sampleTile.terrainFrameY = i;
			_vSampleTile.push_back(sampleTile);
		}
	}

	for (int i = 0; i < _vSampleTile.size(); ++i)
	{
		int j = 0;
		if (i <20) j = i;
		if ((i < 40 && i >= 20)) j = i - 20;
		if ((i < 60 && i >= 40)) j = i - 40;
		if ((i < 80 && i >= 60)) j = i - 60;
		SetRect(&_vSampleTile[i].rcTile,
			SAMPLETILESTARTX + 14 + (j % 4) * 70,
			SAMPLETILESTARTY + 20 + ((int)(j / 4)) * 70,
			SAMPLETILESTARTX + 14 + (j % 4) * 70 + 64,
			SAMPLETILESTARTY + 20 + ((int)(j / 4)) * 70 + 64
		);
	}

}

void mapTool::setObjNum()
{
	for (int i = 0; i < _vTile.size(); ++i)
	{
		if (_vTile[i].objFrameX == 0 && _vTile[i].objFrameY == 0) _vTile[i].obj = OBJ_BLOCK;
		if (_vTile[i].objFrameX == 0 && _vTile[i].objFrameY == 0) _vTile[i].obj = OBJ_ITEMBOX;
	}
}

void mapTool::setCameraMove(CTRLDIRECTION dir)
{
	switch (dir)
	{
	case CTRL_UP:
			CAMERAMANAGER->cameraMove(CAMERAMANAGER->getMdX(), CAMERAMANAGER->getMdY() - TILESIZE);
			if (_tileMake) createExtraMap();
		break;
	case CTRL_DOWN:
		CAMERAMANAGER->cameraMove(CAMERAMANAGER->getMdX(), CAMERAMANAGER->getMdY() + TILESIZE);
		if (_tileMake) createExtraMap();
		break;
	case CTRL_LEFT:
		CAMERAMANAGER->cameraMove(CAMERAMANAGER->getMdX() - TILESIZE, CAMERAMANAGER->getMdY());
		if (_tileMake) createExtraMap();
		break;
	case CTRL_RIGHT:
		CAMERAMANAGER->cameraMove(CAMERAMANAGER->getMdX() + TILESIZE, CAMERAMANAGER->getMdY());
		if (_tileMake) createExtraMap();
		break;
	case CTRL_NONE:
		break;
	}
}

void mapTool::createExtraMap()
{
	int vNum = 0;
	_vDummyTile.clear();

	if (CAMERAMANAGER->getTopEnd()&& 
		(PtInRect(&_ctrlCameraRect[CTRL_UP],_ptMouse)
	|| PtInRect(&_ctrlCameraRect[CTRL_DOWN], _ptMouse)))
	{
		for (int i = 0; i < _vTile.size(); ++i)
		{
			tagTile dummyTile;
			dummyTile.item = _vTile[i].item;
			dummyTile.obj = _vTile[i].obj;
			dummyTile.objFrameX = _vTile[i].objFrameX;
			dummyTile.objFrameY = _vTile[i].objFrameY;
			dummyTile.rc = _vTile[i].rc;
			dummyTile.terrain = _vTile[i].terrain;
			dummyTile.terrainFrameX = _vTile[i].terrainFrameX;
			dummyTile.terrainFrameY = _vTile[i].terrainFrameY;
			_vDummyTile.push_back(dummyTile);
		}

		for (int i = 0; i < _currentLineX; ++i)
		{
			tagTile tile;
			_vTile.push_back(tile);
		}

		_currentLineY++;
	}

	if (CAMERAMANAGER->getTopEnd() &&
		(PtInRect(&_ctrlCameraRect[CTRL_LEFT], _ptMouse)
			|| PtInRect(&_ctrlCameraRect[CTRL_RIGHT], _ptMouse)))
	{
		for (int i = 0; i < _vTile.size(); ++i)
		{
			tagTile dummyTile;
			dummyTile.item = _vTile[i].item;
			dummyTile.obj = _vTile[i].obj;
			dummyTile.objFrameX = _vTile[i].objFrameX;
			dummyTile.objFrameY = _vTile[i].objFrameY;
			dummyTile.rc = _vTile[i].rc;
			dummyTile.terrain = _vTile[i].terrain;
			dummyTile.terrainFrameX = _vTile[i].terrainFrameX;
			dummyTile.terrainFrameY = _vTile[i].terrainFrameY;
			_vDummyTile.push_back(dummyTile);
		}

		for (int i = 0; i < _currentLineY; ++i)
		{
			tagTile tile;
			_vTile.push_back(tile);
		}

		_currentLineX++;
	}

	for (int i = 0; i < _currentLineY; ++i)
	{
		for (int j = 0; j < _currentLineX; ++j)
		{
			SetRect(&_vTile[vNum].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
			vNum++;
		}
	}

	for (int i = 0; i < _vTile.size(); ++i)
	{
		for (int j = 0; j < _vDummyTile.size(); ++j)
		{
			if (_vDummyTile[j].rc.left == _vTile[i].rc.left
				&& _vDummyTile[j].rc.top == _vTile[i].rc.top)
			{
				_vTile[i].item = _vDummyTile[j].item;
				_vTile[i].obj = _vDummyTile[j].obj;
				_vTile[i].objFrameX = _vDummyTile[j].objFrameX;
				_vTile[i].objFrameY = _vDummyTile[j].objFrameY;
				_vTile[i].terrain = _vDummyTile[j].terrain;
				_vTile[i].terrainFrameX = _vDummyTile[j].terrainFrameX;
				_vTile[i].terrainFrameY = _vDummyTile[j].terrainFrameY;
				break;
			}
			else
			{
				_vTile[i].item = ITEM_NONE;
				_vTile[i].obj = OBJ_NONE;
				_vTile[i].objFrameX = 0;
				_vTile[i].objFrameY = 0;
				_vTile[i].terrain = TR_NONE;
				_vTile[i].terrainFrameX = 0;
				_vTile[i].terrainFrameY = 0;
			}
		}
	}
}