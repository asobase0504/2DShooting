//==================================================
//
// マップの生成
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
// 定義
//--------------------------------------------------
namespace
{
const int MAX_X_BLOCK = 40;	// X軸の最大数
const int MAX_Y_BLOCK = 17;	// Y軸の最大数
const float BLOCK_SIZE = 30.0f;	// ブロックのサイズ
const char* FILE_NAME = "data/map_03.txt";	// マップファイル名
const float X_CENTER = SCREEN_WIDTH * 0.5f - (MAX_X_BLOCK * 0.5f * BLOCK_SIZE);	// マップを中央に配置するため(X軸)
const float Y_CENTER = SCREEN_HEIGHT * 0.5f - (MAX_Y_BLOCK * 0.5f * BLOCK_SIZE);	// マップを中央に配置するため(Y軸)
}

//--------------------------------------------------
// 静的変数
//--------------------------------------------------
namespace
{
CBlock s_block[MAX_X_BLOCK * MAX_Y_BLOCK];
CBlock::TYPE s_blockIdx[MAX_X_BLOCK][MAX_Y_BLOCK];
}

//==================================================
// 初期化
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
// 終了
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
// 更新
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
// 描画
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
// 設定
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
// 読込
//==================================================
void LoadMap(void)
{
	FILE *pFile = fopen(FILE_NAME, "r");		//ファイルポインタを宣言

	if (pFile != NULL)
	{//ファイルが開いた場合
		for (int y = 0; y < MAX_Y_BLOCK; y++)
		{
			for (int x = 0; x < MAX_X_BLOCK; x++)
			{
				//一行読み込み
				fscanf(pFile, "%d", &s_blockIdx[x][y]);
			}
		}
	}
	else
	{//ファイルが開かない場合
		MessageBox(NULL, TEXT("ファイルが開きませんでした"), TEXT("FILE"), MB_ICONHAND);
		assert(false);
	}
	//ファイルを閉じる
	fclose(pFile);
}

CBlock* GetBlock(void)
{
	return s_block;
}
