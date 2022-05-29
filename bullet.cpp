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
// 静的メンバー変数の宣言
//--------------------------------------------------
int CBullet::m_maxNumAll = 50;	// 最大数

//--------------------------------------------------
// コンストラクタ
// Author : Yuda Kaito
//--------------------------------------------------
CBullet::CBullet() : 
	m_type(NONE),
	m_posOld(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_move(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
}

//--------------------------------------------------
// デストラクタ
// Author : Yuda Kaito
//--------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------
// 初期化
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Init()
{
	CObject2D::Init();
}

//--------------------------------------------------
// 終了
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Update()
{
	if (!m_isUse)
	{
		return;
	}

	/* ↓使用している↓ */

	CObject2D::Update();

	// 位置の更新
	SetPos(m_pos + m_move);

	// ブロックとの衝突判定
	HitWithBlock(m_pos, m_move);
}

//--------------------------------------------------
// 描画
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// 設定
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Set(D3DXVECTOR3 & inPos, D3DXVECTOR3 & inMove)
{
	SetDrawStatus(true);
	m_move = inMove;
	m_type = TYPE::WHITE;

	// 表示
	CreateVtxBuff();
	SetPos(inPos);
	SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	SetColor(GetColor(COLOR_WHITE));;
	
}

//--------------------------------------------------
// 総数の取得
// Author : Yuda Kaito
//--------------------------------------------------
int CBullet::GetNumAll()
{
	return m_maxNumAll;
}

//--------------------------------------------------
// ブロックとの当たり判定
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::HitWithBlock(D3DXVECTOR3 & inPos, const D3DXVECTOR3 & inVec)
{
	if (!GetDrawStatus())
	{
		return;
	}

	D3DXVECTOR3 outpos = {};
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float outT1;
	float outT2;
	float dist;

	for (int cntBlock = 0; cntBlock < CBlock::MAX_BLOCK; cntBlock++)
	{
		CBlock* pBlock = (GetBlock() + cntBlock);
		
		if (!pBlock->GetUseStatus() || (int)m_type == (int)pBlock->GetType())
		{
			continue;
		}

		if (!((D3DXVec3LengthSq(&(*pBlock->GetScale() + m_scale))) >= D3DXVec3LengthSq(&(*pBlock->GetPos() - m_pos))))
		{
			continue;
		}

		if (m_move.y > 0.0f)
		{
			if (RectTopCollision(*pBlock->GetPos(), *pBlock->GetScale() * 0.5f, m_pos, m_scale * 0.5f, &outpos, &outT1, &outT2))
			{
				vec.y += 1.0f;
				dist = (m_scale.y * 0.5f) + (m_pos.y - outpos.y);
				m_pos.y -= dist + dist* 0.0001f;
			}
		}
		if (m_move.x > 0.0f)
		{
			if (RectLeftCollision(*pBlock->GetPos(), *pBlock->GetScale() * 0.5f, m_pos, m_scale * 0.5f, &outpos, &outT1, &outT2))
			{
				vec.x += 1.0f;
				dist = (m_scale.x * 0.5f) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;

			}
		}
		if (m_move.x < 0.0f)
		{
			if (RectRightCollision(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, &outT1, &outT2))
			{
				switch (pBlock->GetType())
				{
				case CBlock::TYPE::NONE:
					SetDrawStatus(false);
					break;
				case CBlock::TYPE::BLOCK:
					pBlock->ChangeType(CBlock::TYPE::WHITE);
					break;
				case CBlock::TYPE::WHITE:
					pBlock->ChangeType(CBlock::TYPE::BLOCK);
					break;
				default:
					MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
					assert(false);
					break;
				}
			}
		}
		if (m_move.y < 0.0f)
		{
			if (RectDownCollision(*pBlock->GetPos(), *pBlock->GetScale() * 0.5f, m_pos, m_scale * 0.5f, &outpos, &outT1, &outT2))
			{
				vec.y = -1.0f;
				dist = (-m_scale.y * 0.5f) + (m_pos.y - outpos.y);

				m_pos.y -= dist + dist* 0.0001f;
			}
		}
	}
}
