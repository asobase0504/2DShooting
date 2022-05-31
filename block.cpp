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
// コンストラクタ
//--------------------------------------------------
CBlock::CBlock()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBlock::~CBlock()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
void CBlock::Init()
{
//	CObject2D::Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
void CBlock::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBlock::Update()
{
	if (!m_isUse)
	{
		return;
	}

	/* ↓使用していない↓ */

	//m_scale -= m_scale * 0.15f;

	//if (D3DXVec3Length(&m_scale) <= 1.0f)
	//{
	//	m_isUse = false;
	//	SetDrawStatus(false);
	//}

	//SetPos(m_pos);
	//SetSize(m_scale);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBlock::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	if (m_isUse)
	{
		return;
	}

	/* ↓使用していない↓ */

	CreateVtxBuff();

	m_isUse = true;
	m_type = type;
	SetPos(pos);
	SetSize(size);

	switch (m_type)
	{
	case TYPE::NONE:
		SetDrawStatus(false);
		break;
	case TYPE::BLACK:
		SetColor(GetColor(COLOR_BLACK));
		break;
	case TYPE::WHITE:
		SetColor(GetColor(COLOR_WHITE));
		break;
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}
}

//--------------------------------------------------
// 種別の切り替え
//--------------------------------------------------
void CBlock::ChangeType(TYPE type)
{
	switch (m_type)
	{
	case TYPE::NONE:
		break;
	case TYPE::BLACK:
		m_type = TYPE::WHITE;
		SetColor(GetColor(COLOR_WHITE));

		break;
	case TYPE::WHITE:
		m_type = TYPE::BLACK;
		SetColor(GetColor(COLOR_BLACK));

		break;
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}
}

//--------------------------------------------------
// 種別の取得
//--------------------------------------------------
CBlock::TYPE CBlock::GetType()
{
	return m_type;
}
