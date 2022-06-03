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

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CGame::CGame() :
	isPause(false),
	idxBg(0),
	object(nullptr)
{
	memset(player, 0, sizeof(player));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{

}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	isPause = false;	// ポーズ解除

	// 背景
	if (object == nullptr)
	{
		object = new CObject2D;

		if (object == nullptr)
		{
			MessageBox(NULL, TEXT("動的確保に失敗しました。"), TEXT("動的確保に失敗しました。"), MB_ICONHAND);
			assert(false);
		}

		// オブジェクトの生成
		object->Init();
		object->CreateVtxBuff();
		object->SetTexture(GetTexture(TEXTURE_BG));
		object->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		object->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}

	for (int i = 0; i < 2; i++)
	{// プレイヤー
		if (player[i] != nullptr)
		{
			continue;
		}

		/* ↓ 使用されていない場合 ↓ */

		player[i] = new CPlayer;

		if (player != nullptr)
		{
			player[i]->Init();
		}
		else
		{
			MessageBox(NULL, TEXT("動的確保に失敗しました。"), TEXT("動的確保に失敗しました。"), MB_ICONHAND);
			assert(false);
		}
	}

	// プレイヤーの生成
	player[0]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::WHITE);
	player[1]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::BLACK);

	InitMap();
	LoadMap();
	SetMap();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	// サウンドの停止
	StopSound();

	// オブジェクトの解放
	if (object != nullptr)
	{
		object->Uninit();

		delete object;
		object = nullptr;
	}

	for (int i = 0; i < 2; i++)
	{
		if (player[i] == nullptr)
		{
			continue;
		}

		player[i]->Uninit();

		delete player[i];
		player[i] = nullptr;
	}

	StopUseRectangle(idxBg);	// 使うのを止める

	UninitMap();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	player[0]->Update();
	player[1]->Update();

	for (int i = 0; i < CBullet::MAX_BULLET; i++)
	{
		if (player[0]->GetBullet() == nullptr || !player[0]->GetBullet()[i].GetDrawStatus())
		{
			continue;
		}

		player[0]->GetBullet()[i].HitWithBullet(player[1]->GetBullet());
	}

	UpdateMap();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	// 背景の描画
	if (object != nullptr)
	{
		object->Draw();
	}

	DrawMap();

	// 矩形の描画
	DrawRectangle();

	// プレイヤ―の描画
	player[0]->Draw();
	player[1]->Draw();

	// 円形の描画
	DrawFan();
}

//--------------------------------------------------
// ポーズの有効無効設定
// 引数  : bool bPause / ポーズするかどうか [ true : する false : しない ]
//--------------------------------------------------
void CGame::SetEnablePause(bool bPause)
{
	isPause = bPause;
}

//--------------------------------------------------
// ポーズの有効無効取得
// 返値  : bool / ポーズしてるかどうか
//--------------------------------------------------
bool CGame::GetEnablePause(void)
{
	return isPause;
}
