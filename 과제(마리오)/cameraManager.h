#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
public:

	//����ü ������ �����ϸ鼭 ����ü�� �����
	typedef struct tagCameraInfo
	{
		HDC		hMemDC;		//�޸� DC
		HBITMAP	hBit;		//��Ʈ��
		HBITMAP hOBit;		//�õ� ��Ʈ��
		float	x;			//ī�޶� X��ǥ(left)
		float	y;			//ī�޶� Y��ǥ(top)
		int		width;		//���� ũ��(ī�޶�)
		int		height;		//���� ũ��(ī�޶�)

		int		groundWidth;	//��� �� ����ũ��
		int		groundHeight;	//��� �� ����ũ��
		
		float	mdX;
		float	mdY;

		bool	topEnd;
		bool	bottomEnd;
		bool	leftEnd;
		bool	rightEnd;

		float	magnification;	//����
	//�ʱ�ȭ���� ���ÿ� �Ѵ�
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
			topEnd = false;
			bottomEnd = false;
			leftEnd = false;
			rightEnd = false;
		}
	}CAMERA_INFO, *LPCAMERA_INFO;
private :
	LPCAMERA_INFO	_cameraInfo;	//ī�޶� ���� ����ü
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

	inline bool getLeftEnd() { return _cameraInfo->leftEnd; }
	inline bool getRightEnd() { return _cameraInfo->rightEnd; }
	inline bool getTopEnd() { return _cameraInfo->topEnd; }
	inline bool getBottomEnd() { return _cameraInfo->bottomEnd; }
};

