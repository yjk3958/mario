// stdafx.h : �̸� �����ϵ� ������� : ���� ����ϴ� �͵��� �̸� ������ �δ� ��
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "iniDataManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "cameraManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
#include "database.h"

using namespace std;
using namespace HEPTA_UTIL;

//=======================================================
// ## ������ ���� ������ ## 2017.11.08 ##
//=======================================================

#define WINNAME		(LPTSTR)TEXT("Hepta Window API")
#define WINSTARTX	50		//������ ������ǥ X
#define WINSTARTY	50		//������ ������ǥ Y
#define WINSIZEX	1250	//������ ����ũ��
#define WINSIZEY	800		//������ ����ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define KEYMANAGER		keyManager::getSingleton()
#define RND				randomFunction::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define CAMERAMANAGER	cameraManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define KEYANIMANAGER	keyAniManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define DATABASE		database::getSingleton()

//=======================================================
// ## ��ũ�� ## 2017.11.15 ##
//=======================================================

#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}

//=======================================================
// ## ������ ���� extern ## 2017.11.08 ##
//=======================================================

extern HINSTANCE	_hInstance;		//�ν��Ͻ� �ڵ�
extern HWND			_hWnd;			//�ڵ�
extern POINT		_ptMouse;
extern BOOL			_leftButtonDown;

//=======================================================
//## ������ ������ ## 2018.02.10 ##
//=======================================================
#define MODESELECTX 400
#define MODESELECTY 300

#define CAMERAX		800
#define CAMERAY		600
#define CAMERASTARTX 50		//ī�޶� ������X
#define CAMERASTARTY 70		//ī�޶� ������Y

#define SAMPLETILEBOXX 300
#define SAMPLETILEBOXY 400
#define SAMPLETILESTARTX 900
#define SAMPLETILESTARTY 70


enum MODE
{
	MODE_SELECT,
	MODE_MAPTOOL,
	MODE_PLAYGROUND
};

enum SELECT
{
	SELECT_MAPTOOL,
	SELECT_PLAY,
	SELECT_NONE
};

extern MODE _md;
