#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
public:

	//구조체 형식을 선언하면서 구조체를 만들고
	typedef struct tagCameraInfo
	{
		HDC		hMemDC;		//메모리 DC
		HBITMAP	hBit;		//비트맵
		HBITMAP hOBit;		//올드 비트맵
		float	x;			//카메라 X좌표(left)
		float	y;			//카메라 Y좌표(top)
		int		width;		//가로 크기(카메라)
		int		height;		//세로 크기(카메라)

		int		groundWidth;	//배경 총 가로크기
		int		groundHeight;	//배경 총 세로크기
		
		float	mdX;
		float	mdY;


		float	magnification;	//배율
	//초기화까지 동시에 한다
		tagCameraInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			groundWidth = 0;
			groundHeight = 0;
			magnification = 1;
			mdX = 0;
			mdY = 0;
		}
	}CAMERA_INFO, *LPCAMERA_INFO;
private :
	LPCAMERA_INFO	_cameraInfo;	//카메라 정보 구조체
public:
	cameraManager();
	~cameraManager();

	HRESULT init(int groundTotalWidth, int groundTotalHeight, int cameraWidth, int cameraHeight, float x = 0, float y = 0, float magnification = 1);
	void release();
	void cameraMove(float focusX, float focusY);
	void render(HDC hdc);

	inline HDC getMemDC() { return _cameraInfo->hMemDC; }
	inline float getX() { return _cameraInfo->x; }
	inline float getY() {
		return _cameraInfo->y; }
	inline float getMg() { return _cameraInfo->magnification; }
	inline float getMdX() { return _cameraInfo->mdX; }
	inline float getMdY() { return _cameraInfo->mdY; }
	inline void setMagnification(float mag) { _cameraInfo->magnification = mag; }


};

