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
#include "map.h"
#include "block.h"
#include "bullet.h"
#include "object.h"
#include "object2D.h"
#include <vector>

// デバッグ
#include <assert.h>

//--------------------------------------------------
// コンストラクタ
// Author : Yuda Kaito
//--------------------------------------------------
CPlayer::CPlayer() : 
	CObject2D(),
	m_nIdx(0),
	m_bullet(nullptr),
	m_type(NONE),
	m_posOld(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
	ReleaseBullet();
}

//--------------------------------------------------
// 終了
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
	ReleaseBullet();
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
	Move();	// 移動
	Shot();	// 弾の発射
	Collision();	// ブロックとの当たり判定

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (!m_bullet[i].GetDrawStatus())
		{
			continue;
		}

		m_bullet[i].Update();
	}

}

//--------------------------------------------------
// 描画
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Draw()
{
	CObject2D::Draw();

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (!m_bullet[i].GetDrawStatus())
		{
			continue;
		}

		m_bullet[i].Draw();
	}
}

//--------------------------------------------------
// 設定
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Set(D3DXVECTOR3& pos, D3DXVECTOR3& size, PALYERTYPE type)
{
	m_type = type;	// 種別

	CreateVtxBuff();	// 頂点バッファの生成
	SetTexture(GetTexture(TEXTURE_Number_001));	// テクスチャの設定
	SetPos(pos);	// 位置の設定
	SetSize(size);	// 大きさの設定

	switch (m_type)
	{
	case PALYERTYPE::WHITE:
		CObject2D::SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		break;
	case PALYERTYPE::BLACK:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}

	ReleaseBullet();
	m_bullet = new CBullet[CBullet::GetNumAll()];

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		m_bullet[i].Init();
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
// 弾の発射
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Shot()
{
	D3DXVECTOR3 vec(0.0f,0.0f,0.0f);

	if (GetKeyboardTrigger(DIK_UP))
	{
		vec.y = -5.0f;
	}
	else if (GetKeyboardTrigger(DIK_DOWN))
	{
		vec.y = 5.0f;
	}
	else if (GetKeyboardTrigger(DIK_LEFT))
	{
		vec.x = -5.0f;
	}
	else if (GetKeyboardTrigger(DIK_RIGHT))
	{
		vec.x = 5.0f;
	}

	if (D3DXVec3LengthSq(&vec) == 0.0f)
	{
		return;
	}

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (m_bullet[i].GetDrawStatus())
		{
			continue;
		}

		m_bullet[i].Set(m_posInblock, vec,(CBullet::TYPE)m_type);

		break;
	}
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

	for (int cntBlock = 0; cntBlock < CBlock::MAX_BLOCK; cntBlock++)
	{
		CBlock* pBlock = &GetBlock()[cntBlock];

		if (!pBlock->GetUseStatus())
		{
			continue;
		}

		if (Collision::PointAndRectangle(m_pos, *pBlock->GetPos(), *pBlock->GetScale()))
		{
			m_posInblock = *pBlock->GetPos();
		}

		if ((int)m_type == (int)pBlock->GetType())
		{
			continue;
		}
		if (m_move.y > 0.0f)
		{
			// プレイヤー上、ブロック下の当たり判定
			if (Collision::RectangleTop(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.y += 1.0f;
				dist = (m_scale.y) + (m_pos.y - outpos.y);
				m_pos.y -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
		if (m_move.x > 0.0f)
		{
			if (Collision::RectangleLeft(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.x += 1.0f;
				dist = (m_scale.x) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
		if (m_move.x < 0.0f)
		{
			if (Collision::RectangleRight(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.x += -1.0f;
				float dist = (-m_scale.x) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
		if (m_move.y < 0.0f)
		{
			if (Collision::RectangleDown(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.y = -1.0f;
				dist = (-m_scale.y) + (m_pos.y - outpos.y);

				m_pos.y -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// 位置の設定
			}
		}
	}
}

//--------------------------------------------------
// 弾インスタンスの解放
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::ReleaseBullet()
{
	if (m_bullet == nullptr)
	{
		return;
	}

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (m_bullet == nullptr)
		{
			continue;
		}

		// 終了処理
		m_bullet[i].Uninit();
	}

	// 破棄
	delete[] m_bullet;
	m_bullet = nullptr;
}
