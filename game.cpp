//==================================================
//
// ゲームモード
// Author : Yuda Kaito
//
//==================================================

//==================================================
// インクルード
//==================================================
// 主要系統
#include "main.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
// 描画系統
#include "rectangle.h"
#include "fan.h"
#include "color.h"
// 処理系統
#include "time.h"
#include "utility.h"
#include "block.h"
#include "map.h"
#include "player.h"
#include "bullet.h"
// オブジェクト系統
#include "object.h"
#include "object2d.h"

#include <assert.h>

//==================================================
// スタティック変数
//==================================================
namespace
{
bool		s_bPause = false;		// ポーズ中かどうか [してる  : true してない  : false]
int			s_nIdxBg;				// 背景の矩形インデックス
CObject2D*	s_Object[10];			// オブジェクトのインスタンス
CPlayer* s_pPlayer[2];
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	s_bPause = false;	// ポーズ解除

	for (int i = 0; i < 10; i++)
	{// 背景
		if (s_Object[i] != nullptr)
		{
			continue;
		}

		s_Object[i] = new CObject2D;

		s_Object[i]->Init();
		s_Object[i]->CreateVtxBuff();
		s_Object[i]->SetTexture(GetTexture(TEXTURE_BG));
		s_Object[i]->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		s_Object[i]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

		break;
	}

	for (int i = 0; i < 2; i++)
	{// 背景
		if (s_pPlayer[i] != nullptr)
		{
			continue;
		}

		s_pPlayer[i] = new CPlayer;
		s_pPlayer[i]->Init();
	}

	s_pPlayer[0]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::WHITE);
	s_pPlayer[1]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::BLOCK);

	InitBlock();
	LoadMap();
	SetMap();

	InitBullet();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitGame(void)
{
	// サウンドの停止
	StopSound();

	// オブジェクトの解放
	for (int i = 0; i < 10; i++)
	{
		if (s_Object[i] == nullptr)
		{
			continue;
		}

		s_Object[i]->Uninit();

		delete s_Object[i];
		s_Object[i] = nullptr;
	}

	for (int i = 0; i < 2; i++)
	{
		if (s_pPlayer[i] == nullptr)
		{
			continue;
		}

		s_pPlayer[i]->Uninit();

		delete s_pPlayer[i];
		s_pPlayer[i] = nullptr;
	}

	StopUseRectangle(s_nIdxBg);	// 使うのを止める

	UninitBlock();
	UninitBullet();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	s_pPlayer[0]->Update();
	s_pPlayer[1]->Update();
	UpdateBlock();
	UpdateBullet();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawGame(void)
{
	for (int i = 0; i < 10; i++)
	{// 背景
		if (s_Object[i] == nullptr)
		{
			continue;
		}

		s_Object[i]->Draw();
	}

	// 矩形の描画
	DrawRectangle();

	s_pPlayer[0]->Draw();
	s_pPlayer[1]->Draw();

	// 円形の描画
	DrawFan();
}

//--------------------------------------------------
// ポーズの有効無効設定
//--------------------------------------------------
void SetEnablePause(bool bPause)
{
	s_bPause = bPause;
}

//--------------------------------------------------
// ポーズの有効無効取得
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_bPause;
}
