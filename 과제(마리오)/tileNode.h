#pragma once

//�� Ÿ���� �԰��� 32�� �Ѵ�
#define TILESIZE 32

//Ÿ�� ���� X Axis 20, Y Axis 20
#define TILEX 20
#define TILEY 20

//Ÿ�� �� ������ 
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//Ÿ���� �Ӽ��� �ο��غ��ô�
//Ÿ�� �Ӽ��� �̳����� �ص� �����ϴ�

//�������� �� ��Ʈ�ʵ� ���� �����µ�... �޸� �ɴ޷���
//������ 8�Ⱑ �� ���������� ����...
#define ATTR_UNMOVE 0x00000001		//��
#define ATTR_SWAMP	0x00000002		//�̼� �������� Ÿ��
#define ATTR_POISON 0x00000004		//�� Ÿ��
#define ATTR_FROZEN 0x00000008		//���� Ÿ��


//������ ���� ����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};
//������Ʈ �� ���� ����
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//������ (���� �ε��� ������ ������ �Ҵ��� �� �����ǿ���)
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	int x;
	int y;
};