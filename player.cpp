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
// コンストラクタ
// Author : Yuda Kaito
//--------------------------------------------------
CPlayer::CPlayer()
{
}

//--------------------------------------------------
// デストラクタ
// Author : Yuda Kaito
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// 初期化
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Init()
{
	CObject2D::Init();
}

//--------------------------------------------------
// 終了
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Update()
{
	if (!m_isUse)
	{
		return;
	}

	/* ↓使用している↓ */

	CObject2D::Update();

	m_posOld = m_pos;
	Move();
	Collision();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetBullet(m_pos, D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	}
}

//--------------------------------------------------
// 描画
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// 設定
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Set(D3DXVECTOR3& pos, D3DXVECTOR3& size, PALYERTYPE type)
{
	m_isUse = true;
	m_pos = pos;
	m_scale = size;
	m_type = type;

	CObject2D::CreateVtxBuff();		// 頂点バッファの生成
	CObject2D::SetTexture(GetTexture(TEXTURE_Number_001));
	CObject2D::SetPos(m_pos);		// 位置の設定
	CObject2D::SetSize(m_scale);	// 大きさの設定
	switch (type)
	{
	case PALYERTYPE::WHITE:
		CObject2D::SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		break;
	case PALYERTYPE::BLOCK:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// 移動
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Move()
{
	float moveLength = 0.0f;
	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (moveLength > 0.0f)
	{
		D3DXVec3Normalize(&moveInput, &moveInput);

		move = moveInput;
	}

	// 方向ベクトル掛ける移動量
	m_move = move * moveLength * 2.0f * 2.0f;
	m_pos += m_move;
	CObject2D::SetPos(m_pos);		// 位置の設定
}

//--------------------------------------------------
// 当たり判定
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Collision()
{
	D3DXVECTOR3 outpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float dist;

	for (int cntBlock = 0; cntBlock < MAX_BLOCK; cntBlock++)
	{
		Block* pBlock = (GetBlock() + cntBlock);
		if (!pBlock->bUse || (int)m_type == (int)pBlock->type)
		{
			continue;
		}

		if (m_move.y > 0.0f)
		{
			if (RectTopCollision(pBlock->pos, pBlock->size * 0.5f, m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.y += 1.0f;
				dist = (m_scale.y) + (m_pos.y - outpos.y);
				m_pos.y -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
		if (m_move.x > 0.0f)
		{
			if (RectLeftCollision(pBlock->pos, pBlock->size * 0.5f, m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.x += 1.0f;
				dist = (m_scale.x) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
		if (m_move.x < 0.0f)
		{
			if (RectRightCollision(pBlock->pos, pBlock->size * 0.5f, m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.x += -1.0f;
				float dist = (-m_scale.x) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
		if (m_move.y < 0.0f)
		{
			if (RectDownCollision(pBlock->pos, pBlock->size * 0.5f, m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.y = -1.0f;
				dist = (-m_scale.y) + (m_pos.y - outpos.y);

				m_pos.y -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
	}
}
