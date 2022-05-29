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
#include "texture.h"
#include <stdio.h>
#include <assert.h>

//--------------------------------------------------
// ��`
//--------------------------------------------------
namespace
{
const int MAX_X_BLOCK = 40;	// X���̍ő吔
const int MAX_Y_BLOCK = 17;	// Y���̍ő吔
const float BLOCK_SIZE = 30.0f;	// �u���b�N�̃T�C�Y
const char* FILE_NAME = "data/map_03.txt";	// �}�b�v�t�@�C����
const float X_CENTER = SCREEN_WIDTH * 0.5f - (MAX_X_BLOCK * 0.5f * BLOCK_SIZE);	// �}�b�v�𒆉��ɔz�u���邽��(X��)
const float Y_CENTER = SCREEN_HEIGHT * 0.5f - (MAX_Y_BLOCK * 0.5f * BLOCK_SIZE);	// �}�b�v�𒆉��ɔz�u���邽��(Y��)
}

//--------------------------------------------------
// �ÓI�ϐ�
//--------------------------------------------------
namespace
{
CBlock s_block[MAX_X_BLOCK * MAX_Y_BLOCK];
CBlock::TYPE s_blockIdx[MAX_X_BLOCK][MAX_Y_BLOCK];
}

//==================================================
// ������
//==================================================
void InitMap(void)
{
	int index;
	for (int y = 0; y < MAX_Y_BLOCK; y++)
	{
		for (int x = 0; x < MAX_X_BLOCK; x++)
		{
			index = y * MAX_X_BLOCK + x;
			s_block[index].Init();
		}
	}
}

//==================================================
// �I��
//==================================================
void UninitMap(void)
{
	int index;
	for (int y = 0; y < MAX_Y_BLOCK; y++)
	{
		for (int x = 0; x < MAX_X_BLOCK; x++)
		{
			index = y * MAX_X_BLOCK + x;
			s_block[index].Uninit();
		}
	}
}

//==================================================
// �X�V
//==================================================
void UpdateMap(void)
{
	int index;
	for (int y = 0; y < MAX_Y_BLOCK; y++)
	{
		for (int x = 0; x < MAX_X_BLOCK; x++)
		{
			index = y * MAX_X_BLOCK + x;
			s_block[index].Update();
		}
	}
}

//==================================================
// �`��
//==================================================
void DrawMap(void)
{
	int index;
	for (int y = 0; y < MAX_Y_BLOCK; y++)
	{
		for (int x = 0; x < MAX_X_BLOCK; x++)
		{
			index = y * MAX_X_BLOCK + x;
			s_block[index].Draw();
		}
	}
}

//==================================================
// �ݒ�
//==================================================
void SetMap(void)
{
	int index;
	for (int y = 0; y < MAX_Y_BLOCK; y++)
	{
		for (int x = 0; x < MAX_X_BLOCK; x++)
		{
			index = y * MAX_X_BLOCK + x;
			s_block[index].Create(D3DXVECTOR3(x * BLOCK_SIZE + X_CENTER, y * BLOCK_SIZE + Y_CENTER, 0.0f), D3DXVECTOR3(BLOCK_SIZE * 0.5f, BLOCK_SIZE * 0.5f, 0.0f), s_blockIdx[x][y]);
			s_block[index].SetTexture(GetTexture(TEXTURE_Number_000));
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
				fscanf(pFile, "%d", &s_blockIdx[x][y]);
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

CBlock* GetBlock(void)
{
	return s_block;
}
