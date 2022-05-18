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
static int m_maxNumAll = 5;	// 最大数

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
	//HitWithBlock(m_pos, m_move);
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
	m_isUse = true;
	m_move = inMove;
	m_type = TYPE::WHITE;

	// 表示
	CreateVtxBuff();
	SetPos(inPos);
	SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
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
}
