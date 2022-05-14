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
#include <stdio.h>
#include <assert.h>

//--------------------------------------------------
// 定義
//--------------------------------------------------
namespace
{
const int MAX_X_BLOCK = 40;	// X軸の最大数
const int MAX_Y_BLOCK = 17;	// Y軸の最大数
const float BLOCK_SIZE = 30.0f;
const char* FILE_NAME = "data/map_03.txt";	// マップファイル名
const float X_CENTER = SCREEN_WIDTH * 0.5f - (MAX_X_BLOCK * 0.5f * (BLOCK_SIZE));	// マップを中央に配置するため(X軸)
const float Y_CENTER = SCREEN_HEIGHT * 0.5f - (MAX_Y_BLOCK * 0.5f * (BLOCK_SIZE));	// マップを中央に配置するため(Y軸)
}

//--------------------------------------------------
// 静的変数
//--------------------------------------------------
namespace
{
BLOCKTYPE s_aMapIdx[MAX_Y_BLOCK][MAX_X_BLOCK];	// マップデータの番号
}

//==================================================
// 初期化
//==================================================
void InitMap(void)
{

}

//==================================================
// 終了
//==================================================
void UninitMap(void)
{

}

//==================================================
// 更新
//==================================================
void UpdateMap(void)
{

}

//==================================================
// 描画
//==================================================
void DrawMap(void)
{

}

//==================================================
// 設定
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
				fscanf(pFile, "%d", &s_aMapIdx[y][x]);
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
