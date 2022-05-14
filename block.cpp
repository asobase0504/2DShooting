//==================================================
//
// 正方形のポリゴンの生成
// Author : Yuda Kaito
//
//==================================================
//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"
#include "block.h"
#include "rectangle.h"
#include "color.h"
// デバッグ
#include <assert.h>

//--------------------------------------------------
// 定義
//--------------------------------------------------
namespace
{
}

//--------------------------------------------------
// 静的変数
//--------------------------------------------------
namespace
{
Block s_aBlock[MAX_BLOCK];
Block s_aBlockTile[MAX_BLOCK];

}

static void SetBlockTile(D3DXVECTOR3 pos, D3DXVECTOR3 size, BLOCKTYPE type);


//==================================================
// 初期化
//==================================================
void InitBlock(void)
{
	ZeroMemory(s_aBlock,sizeof(s_aBlock));
}

//==================================================
// 終了
//==================================================
void UninitBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		StopUseRectangle(s_aBlock[i].nIdx);
	}
}

//==================================================
// 更新
//==================================================
void UpdateBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		Block* pBlock = &s_aBlockTile[i];

		if (!pBlock->bUse)
		{
			continue;
		}

		/* ↓使用していない↓ */

		pBlock->size -= pBlock->size * 0.15f;

		if (D3DXVec3Length(&pBlock->size) <= 1.0f)
		{
			pBlock->bUse = false;
			SetDrawRectangle(pBlock->nIdx, false);
		}

		SetPosRectangle(pBlock->nIdx, pBlock->pos, pBlock->size);
	}

}

//==================================================
// 描画
//==================================================
void DrawBlock(void)
{

}

//==================================================
// 設定
//==================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size,BLOCKTYPE type)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		Block* pBlock = &s_aBlock[i];

		if (pBlock->bUse)
		{
			continue;
		}

		/* ↓使用していない↓ */

		pBlock->nIdx = SetRectangle(TEXTURE_Number_000);
		pBlock->bUse = true;
		pBlock->type = type;
		pBlock->pos = pos;
		pBlock->size = size;

		switch (pBlock->type)
		{
		case BLOCKTYPE::NONE:
			SetDrawRectangle(pBlock->nIdx,false);
			break;
		case BLOCKTYPE::BLOCK:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_BLACK));
			break;
		case BLOCKTYPE::WHITE:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_WHITE));
			break;
		default:
			MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
			assert(false);
			break;
		}

		SetPosRectangle(pBlock->nIdx, pos, size);
		break;
	}
}

//==================================================
// 設定
//==================================================
static void SetBlockTile(D3DXVECTOR3 pos, D3DXVECTOR3 size, BLOCKTYPE type)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		Block* pBlock = &s_aBlockTile[i];

		if (pBlock->bUse)
		{
			continue;
		}

		/* ↓使用していない↓ */

		pBlock->nIdx = SetRectangle(TEXTURE_Number_000);
		pBlock->bUse = true;
		pBlock->type = type;
		pBlock->pos = pos;
		pBlock->size = size;

		switch (pBlock->type)
		{
		case BLOCKTYPE::NONE:
			SetDrawRectangle(pBlock->nIdx, false);
			break;
		case BLOCKTYPE::BLOCK:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_WHITE));
			break;
		case BLOCKTYPE::WHITE:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_BLACK));
			break;
		default:
			MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
			assert(false);
			break;
		}

		SetPosRectangle(pBlock->nIdx, pos, size);
		break;
	}
}


//==================================================
// ブロックの変更
//==================================================
void ChangeBlock(int nIdx, BLOCKTYPE type)
{
	Block* pBlock = &s_aBlock[nIdx];

	switch (pBlock->type)
	{
	case BLOCKTYPE::NONE:
		break;
	case BLOCKTYPE::BLOCK:
		pBlock->type = BLOCKTYPE::WHITE;
		SetColorRectangle(pBlock->nIdx, GetColor(COLOR_WHITE));
		SetBlockTile(pBlock->pos, pBlock->size, pBlock->type);

		break;
	case BLOCKTYPE::WHITE:
		pBlock->type = BLOCKTYPE::BLOCK;
		SetColorRectangle(pBlock->nIdx, GetColor(COLOR_BLACK));
		SetBlockTile(pBlock->pos, pBlock->size, pBlock->type);
		break;
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}
}

Block* GetBlock(void)
{
	return s_aBlock;
}
