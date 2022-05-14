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
#include "bullet.h"
#include "rectangle.h"
#include "color.h"
#include "input.h"
#include "collision.h"
#include "block.h"
#include "map.h"

// デバッグ
#include <assert.h>

//--------------------------------------------------
// 定義
//--------------------------------------------------
namespace
{
const int MAX_BULLET = 200;

//--------------------------------------------------
// ブロックの構造体
//--------------------------------------------------
struct Bullet
{
	int nIdx;	// 番号
	BULLETTYPE type;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move;
	bool bUse;	// 使用してるか否か
};
}

//--------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------
void CollisionBullet(D3DXVECTOR3& pos, const D3DXVECTOR3& inVec, float posDist);

//--------------------------------------------------
// 静的変数
//--------------------------------------------------
namespace
{
Bullet s_aBullet[MAX_BULLET];
}

//==================================================
// 初期化
//==================================================
void InitBullet(void)
{
	ZeroMemory(s_aBullet, sizeof(s_aBullet));
}

//==================================================
// 終了
//==================================================
void UninitBullet(void)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		StopUseRectangle(s_aBullet[i].nIdx);
	}
}

//==================================================
// 更新
//==================================================
void UpdateBullet(void)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		Bullet* pBullet = &s_aBullet[i];

		if (!pBullet->bUse)
		{
			continue;
		}

		pBullet->pos += pBullet->move;

		/* ↓使用している↓ */

		CollisionBullet(pBullet->pos, pBullet->move, 1.0f);

		// 再表示
		SetPosRectangle(pBullet->nIdx, pBullet->pos, pBullet->size);
	}
}

//==================================================
// 描画
//==================================================
void DrawBullet(void)
{

}

//==================================================
// 設定
//==================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		Bullet* pBullet = &s_aBullet[i];

		if (pBullet->bUse)
		{
			continue;
		}

		/* ↓使用していない↓ */

		pBullet->bUse = true;

		pBullet->move = move;
		pBullet->size = D3DXVECTOR3(15.0f,15.0f,0.0f);
		pBullet->pos = pos;
		pBullet->type = BULLETTYPE::WHITE;

		// 表示
		pBullet->nIdx = SetRectangle(TEXTURE_Number_001);
		SetColorRectangle(pBullet->nIdx, GetColor(COLOR_WHITE));
		SetPosRectangle(pBullet->nIdx, pBullet->pos, pBullet->size);
		break;
	}
}

//==================================================
// 当たり判定
//==================================================
void CollisionBullet(D3DXVECTOR3& pos, const D3DXVECTOR3& inVec, float posDist)
{
	if (posDist == 0.0f)
	{
		return;
	}

	for (int cntBullet = 0; cntBullet < MAX_BULLET; cntBullet++)
	{
		Bullet* pBullet = &s_aBullet[cntBullet];
		if (!pBullet->bUse)
		{
			continue;
		}

		D3DXVECTOR3 outpos = {};
		D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float outT1;
		float outT2;
		float dist;

		for (int cntBlock = 0; cntBlock < MAX_BLOCK; cntBlock++)
		{
			Block* pBlock = (GetBlock() + cntBlock);

			if (!pBlock->bUse || (int)pBullet->type == (int)pBlock->type)
			{
				continue;
			}

			if (!((D3DXVec3LengthSq(&(pBlock->size + pBullet->size))) >= D3DXVec3LengthSq(&(pBlock->pos - pBullet->pos))))
			{
				continue;
			}

			if (inVec.y > 0.0f)
			{
				if (RectTopCollision(pBlock->pos, pBlock->size * 0.5f, pBullet->pos, pBullet->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.y += 1.0f;
					dist = (pBullet->size.y * 0.5f) + (pBullet->pos.y - outpos.y);
					pBullet->pos.y -= dist + dist* 0.0001f;
				}
			}
			if (inVec.x > 0.0f)
			{
				if (RectLeftCollision(pBlock->pos, pBlock->size * 0.5f, pBullet->pos, pBullet->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.x += 1.0f;
					dist = (pBullet->size.x * 0.5f) + (pBullet->pos.x - outpos.x);
					pBullet->pos.x -= dist + dist* 0.0001f;

				}
			}
			if (inVec.x < 0.0f)
			{
				if (RectRightCollision(pBlock->pos, pBlock->size * 0.5f, pBullet->pos, pBullet->size * 0.5f, &outpos, &outT1, &outT2))
				{
					switch (pBlock->type)
					{
					case BLOCKTYPE::NONE:
						SetDrawRectangle(pBullet->nIdx, false);
						pBullet->bUse = false;
						break;
					case BLOCKTYPE::BLOCK:
						ChangeBlock(cntBlock, BLOCKTYPE::WHITE);
						break;
					case BLOCKTYPE::WHITE:
						ChangeBlock(cntBlock, BLOCKTYPE::BLOCK);
						break;
					default:
						assert(false);
						break;
					}
				}
			}
			if (inVec.y < 0.0f)
			{
				if (RectDownCollision(pBlock->pos, pBlock->size * 0.5f, pBullet->pos, pBullet->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.y = -1.0f;
					dist = (-pBullet->size.y * 0.5f) + (pBullet->pos.y - outpos.y);

					pBullet->pos.y -= dist + dist* 0.0001f;
				}
			}
		}
	}
}
