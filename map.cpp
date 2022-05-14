//==================================================
//
// �}�b�v�̐���
// Author : Yuda Kaito
//
//==================================================
//--------------------------------------------------
// include
//--------------------------------------------------
#include "map.h"
#include "main.h"
#include "block.h"
#include <stdio.h>
#include <assert.h>

//--------------------------------------------------
// ��`
//--------------------------------------------------
namespace
{
const int MAX_X_BLOCK = 40;	// X���̍ő吔
const int MAX_Y_BLOCK = 17;	// Y���̍ő吔
const float BLOCK_SIZE = 30.0f;
const char* FILE_NAME = "data/map_03.txt";	// �}�b�v�t�@�C����
const float X_CENTER = SCREEN_WIDTH * 0.5f - (MAX_X_BLOCK * 0.5f * (BLOCK_SIZE));	// �}�b�v�𒆉��ɔz�u���邽��(X��)
const float Y_CENTER = SCREEN_HEIGHT * 0.5f - (MAX_Y_BLOCK * 0.5f * (BLOCK_SIZE));	// �}�b�v�𒆉��ɔz�u���邽��(Y��)
}

//--------------------------------------------------
// �ÓI�ϐ�
//--------------------------------------------------
namespace
{
BLOCKTYPE s_aMapIdx[MAX_Y_BLOCK][MAX_X_BLOCK];	// �}�b�v�f�[�^�̔ԍ�
}

//==================================================
// ������
//==================================================
void InitMap(void)
{

}

//==================================================
// �I��
//==================================================
void UninitMap(void)
{

}

//==================================================
// �X�V
//==================================================
void UpdateMap(void)
{

}

//==================================================
// �`��
//==================================================
void DrawMap(void)
{

}

//==================================================
// �ݒ�
//==================================================
void SetMap(void)
{
	for (int y = 0; y < MAX_Y_BLOCK; y++)
	{
		for (int x = 0; x < MAX_X_BLOCK; x++)
		{
			SetBlock(D3DXVECTOR3(x * (BLOCK_SIZE) + X_CENTER, y * (BLOCK_SIZE) + Y_CENTER, 0.0f), D3DXVECTOR3(BLOCK_SIZE , BLOCK_SIZE, 0.0f), s_aMapIdx[y][x]);
		}
	}
}

//==================================================
// �Ǎ�
//==================================================
void LoadMap(void)
{
	FILE *pFile = fopen(FILE_NAME, "r");		//�t�@�C���|�C���^��錾

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		for (int y = 0; y < MAX_Y_BLOCK; y++)
		{
			for (int x = 0; x < MAX_X_BLOCK; x++)
			{
				//��s�ǂݍ���
				fscanf(pFile, "%d", &s_aMapIdx[y][x]);
			}
		}
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		MessageBox(NULL, TEXT("�t�@�C�����J���܂���ł���"), TEXT("FILE"), MB_ICONHAND);
		assert(false);
	}
	//�t�@�C�������
	fclose(pFile);
}
