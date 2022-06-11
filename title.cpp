//**************************************************
//
// Hackathon ( title.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h" 
#include "input.h"
#include "mode.h"
#include "transition.h"
#include "rectangle.h"
#include "title.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// タイトルの幅
const float	TITLE_HEIGHT = 600.0f;	// タイトルの高さ

typedef enum
{
	MENU_GAME = 0,	// ゲーム
	MENU_MAX
}MENU;
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_nIdx;				// 矩形のインデックス
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void Input(void);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitTitle(void)
{
	{// ロゴ
		// 矩形の設定
		s_nIdx = SetRectangle(TEXTURE_BG);

		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdx, pos, size);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTitle(void)
{
	// 使うのを止める
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateTitle(void)
{
	// 入力
	Input();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTitle(void)
{
	// 矩形の描画
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// 入力
//--------------------------------------------------
void Input(void)
{
	if (GetTransition() != FADE_NONE)
	{// フェードしている
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
//		ChangeMode(MODE_TUTORIAL);
	}
}
}// namespaceはここまで
