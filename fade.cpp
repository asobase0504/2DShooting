//**************************************************
//
// 画面の遷移
// Author  : Yuda Kaito
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "rectangle.h"
#include "fade.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const float	ALPHA_CHANGE = 0.07f;	// フェードのα値の変化量
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int		s_nIdx;
FADE	s_fade;				// 今のフェード
float	s_fAlpha;			// ポリゴン(フェード)のα値
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitFade(void)
{
	s_fAlpha = 0.0f;	// 黒いポリゴン(不透明)にしておく
	s_fade = FADE_NONE;	// 何もしてない状態

	{// 全面張り
	 // 矩形の設定
		s_nIdx = SetRectangle(TEXTURE_BG);

		float fWidth = SCREEN_WIDTH * 0.5f;
		float fHeight = SCREEN_HEIGHT * 0.5f;

		D3DXVECTOR3 size = D3DXVECTOR3(fWidth, fHeight, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdx, pos, size);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitFade(void)
{
	// 使うのを止める
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateFade(void)
{
	if (s_fade == FADE_NONE)
	{// フェードしてない
		return;
	}

	switch (s_fade)
	{
	case FADE_OUT:	// フェードアウト状態
		s_fAlpha += ALPHA_CHANGE;	// ポリゴンを不透明にしていく

		if (s_fAlpha >= 1.0f)
		{// 不透明になった
			s_fAlpha = 1.0f;
			s_fade = FADE_IN;	// フェードイン状態に
		}
		break;

	case FADE_IN:	// フェードイン状態
		s_fAlpha -= ALPHA_CHANGE;	// ポリゴンを透明にしていく

		if (s_fAlpha <= 0.0f)
		{// 透明になった
			s_fAlpha = 0.0f;
			s_fade = FADE_NONE;	// 何もしていない状態に
		}
		break;

	case FADE_NONE:	// 何もしてない状態
	default:
		assert(false);
		break;
	}

	// 頂点カラーの設定処理
	SetColorRectangle(s_nIdx, D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha));
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawFade(void)
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
//void StartFadeOut(void)
//{
//	s_fade = FADE_OUT;	// フェードアウト状態に
//	s_fAlpha = 0.0f;	// 黒いポリゴン(不透明)にしておく
//}

//--------------------------------------------------
// 取得
//--------------------------------------------------
FADE GetFade(void)
{
	return s_fade;
}