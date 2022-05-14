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
#include "player.h"
#include "rectangle.h"
#include "color.h"
#include "input.h"
#include "collision.h"
#include "block.h"
#include "map.h"
#include "bullet.h"

// デバッグ
#include <assert.h>

//--------------------------------------------------
// 定義
//--------------------------------------------------
namespace
{
const int MAX_PLAYER = 2;

//--------------------------------------------------
// ブロックの構造体
//--------------------------------------------------
struct Player
{
	int nIdx;	// 番号
	PALYERTYPE type;
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
void MovePlayer();
void CollisionPlayer(D3DXVECTOR3& pos, const D3DXVECTOR3& inVec, float posDist);

//--------------------------------------------------
// 静的変数
//--------------------------------------------------
namespace
{
Player s_aPlayer[MAX_PLAYER];
}

//==================================================
// 初期化
//==================================================
void InitPlayer(void)
{
	ZeroMemory(s_aPlayer, sizeof(s_aPlayer));
}

//==================================================
// 終了
//==================================================
void UninitPlayer(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		StopUseRectangle(s_aPlayer[i].nIdx);
	}
}

//==================================================
// 更新
//==================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player* pPlayer = &s_aPlayer[i];

		if (!pPlayer->bUse)
		{
			continue;
		}
		pPlayer->posOld = pPlayer->pos;

		/* ↓使用している↓ */

		MovePlayer();
		CollisionPlayer(pPlayer->pos, pPlayer->move,1.0f);

		// 再表示
		SetPosRectangle(pPlayer->nIdx, pPlayer->pos, pPlayer->size);

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetBullet(pPlayer->pos, D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		}
	}
}

//==================================================
// 描画
//==================================================
void DrawPlayer(void)
{

}

//==================================================
// 設定
//==================================================
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 size, PALYERTYPE type)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player* pPlayer = &s_aPlayer[i];

		if (pPlayer->bUse)
		{
			continue;
		}

		/* ↓使用していない↓ */

		pPlayer->nIdx = SetRectangle(TEXTURE_Number_001);
		pPlayer->bUse = true;
		pPlayer->size = size;
		pPlayer->pos = pos;
		pPlayer->type = type;

		switch (type)
		{
		case PALYERTYPE::WHITE:
			SetColorRectangle(pPlayer->nIdx, GetColor(COLOR_WHITE));
			break;
		case PALYERTYPE::BLOCK:
			SetColorRectangle(pPlayer->nIdx, GetColor(COLOR_BLACK));
			break;
		default:
			break;
		}

		SetPosRectangle(pPlayer->nIdx, pos, size);
		break;
	}
}

//==================================================
// 移動
//==================================================
void MovePlayer()
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);			// 移動量の初期化
	float moveLength = 0.0f;
	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		Player* pPlayer = &s_aPlayer[i];

		moveInput.x = 0.0f;
		moveInput.y = 0.0f;

		// モデルの移動
		if (GetKeyboardPress(DIK_W))
		{
			moveInput.y -= 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_A))
		{
			moveInput.x -= 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_S))
		{
			moveInput.y += 1.0f;
			moveLength = 1.0f;
		}
		if (GetKeyboardPress(DIK_D))
		{
			moveInput.x += 1.0f;
			moveLength = 1.0f;
		}

		if (moveLength > 0.0f)
		{
			D3DXVec3Normalize(&moveInput, &moveInput);

			//// move の長さは 1 になる。
			//move.x = moveInput.x - moveInput.y;
			//move.y = moveInput.x + moveInput.y;
			move = moveInput;
		}

		// 方向ベクトル掛ける移動量
		pPlayer->move = move * moveLength * 2.0f * 2.0f;
		pPlayer->pos += pPlayer->move;
	}
}

//==================================================
// 当たり判定
//==================================================
void CollisionPlayer(D3DXVECTOR3& pos, const D3DXVECTOR3& inVec,float posDist)
{
	if (posDist == 0.0f)
	{
		return;
	}

	for (int cntPlayer = 0; cntPlayer < MAX_PLAYER; cntPlayer++)
	{
		Player* pPlayer = &s_aPlayer[cntPlayer];
		D3DXVECTOR3 outpos = {};
		D3DXVECTOR3 vec = D3DXVECTOR3(0.0f,0.0f,0.0f);
		float outT1;
		float outT2;
		float dist;

		for (int cntBlock = 0; cntBlock < MAX_BLOCK; cntBlock++)
		{
			Block* pBlock = (GetBlock() + cntBlock);
			if (!pBlock->bUse || (int)pPlayer->type == (int)pBlock->type)
			{
				continue;
			}

			//if (inVec.y < 0.0f)
			//{
			//	if (RectDownCollision(pBlock->pos, pBlock->size * 0.5f, pPlayer->pos, pPlayer->size * 0.5f, &outpos, &outT1, &outT2))
			//	{
			//		vec.y = -1.0f;
			//		dist = (-pPlayer->size.y * 0.5f) + (pPlayer->pos.y - outpos.y);

			//		if (RectRightCollision(pBlock->pos, pBlock->size * 0.5f, pPlayer->pos, pPlayer->size * 0.5f, &outpos, &outT1, &outT2))
			//		{
			//			pPlayer->pos.y -= dist + dist* 0.0001f;
			//		}
			//	}
			//}

			if (inVec.y > 0.0f)
			{
				if (RectTopCollision(pBlock->pos, pBlock->size * 0.5f, pPlayer->pos, pPlayer->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.y += 1.0f;
					dist = (pPlayer->size.y * 0.5f) + (pPlayer->pos.y - outpos.y);
					pPlayer->pos.y -= dist + dist* 0.0001f;
				}
			}
			if (inVec.x > 0.0f)
			{
				if (RectLeftCollision(pBlock->pos, pBlock->size * 0.5f, pPlayer->pos, pPlayer->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.x += 1.0f;
					dist = (pPlayer->size.x * 0.5f) + (pPlayer->pos.x - outpos.x);
					pPlayer->pos.x -= dist + dist* 0.0001f;

				}
			}
			if (inVec.x < 0.0f)
			{
				if (RectRightCollision(pBlock->pos, pBlock->size * 0.5f, pPlayer->pos, pPlayer->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.x += -1.0f;
					float dist = (-pPlayer->size.x * 0.5f) + (pPlayer->pos.x - outpos.x);
					pPlayer->pos.x -= dist + dist* 0.0001f;
				}
			}
			if (inVec.y < 0.0f)
			{
				if (RectDownCollision(pBlock->pos, pBlock->size * 0.5f, pPlayer->pos, pPlayer->size * 0.5f, &outpos, &outT1, &outT2))
				{
					vec.y = -1.0f;
					dist = (-pPlayer->size.y * 0.5f) + (pPlayer->pos.y - outpos.y);

					pPlayer->pos.y -= dist + dist* 0.0001f;
				}
			}
		}
	}
}
