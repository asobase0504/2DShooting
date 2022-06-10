//=========================================
// 
// ゲーム内処理
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "debug.h"
#include <stdio.h>
#include "input.h"
#include "game.h"
#include "transition.h"
#include "application.h"
#include "renderer.h"
#include "mode.h"

//------------------------------------
// 定義
//------------------------------------
namespace
{
const int  DEBUG_MAXWORD = 4096;
}

//------------------------------------
// 静的変数宣言
//------------------------------------
namespace
{
LPD3DXFONT s_pFont = NULL;	// フォントへのポインタ
}

//------------------------------------
// プロトタイプ宣言
//------------------------------------

//=========================================
// デバッグ表示の初期化
//=========================================
void InitDebug(void)
{
	// デバッグ表示用フォントの生成
	D3DXCreateFont(CApplication::Instance()->GetRenderer()->GetDevice(), 32, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &s_pFont);
}

//=========================================
// デバッグ表示の終了処理
//=========================================
void UninitDebug(void)
{
	// デバッグ表示用フォントの破棄
	if (s_pFont != NULL)
	{
		s_pFont->Release();
		s_pFont = NULL;
	}
}

//=========================================
// デバッグ表示
//=========================================
void DrawDebug(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[DEBUG_MAXWORD];
	int nLength = 0;

	/* ↓文字列の代入↓ */

	sprintf(&aStr[nLength], "FPS  : %2d\n\n", GetFPS());
	nLength = (int)strlen(&aStr[0]);

	sprintf(&aStr[nLength], "MODE : %2d\n\n", GetMode());
	nLength = (int)strlen(&aStr[0]);

	sprintf(&aStr[nLength], "FADE : %2d\n\n", GetTransition());
	nLength = (int)strlen(&aStr[0]);

	// テキストの描画
	s_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.25f, 0.75f, 1.0f, 1.0f));
}