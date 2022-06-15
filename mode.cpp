//**************************************************
//
// Hackathon ( mode.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "mode.h"
#include "transition.h"

// 描画の種類
#include "rectangle.h"
#include "fan.h"
#include "texture.h"

// モードの種類
#include "tutorial.h"
#include "game.h"
#include "title.h"
#include "result.h"

#include <assert.h>
#include <time.h>

CMode::CMode()
{
}

CMode::~CMode()
{
}

HRESULT CMode::Init()
{
	// テクスチャの読み込み
	srand((unsigned int)time(NULL));

	game = new CGame;

	return S_OK;
}

void CMode::Uninit()
{
	UninitTitle();	// タイトル

	UninitTutorial();	// チュートリアル

	// ゲーム
	if (game != nullptr)
	{
		game->Uninit();
		delete game;
		game = nullptr;
	}

	// リザルト
	UninitResult();

	// テクスチャ
	UnloadTextureAll();
}

void CMode::Update()
{
	switch (mode)
	{// どのモード？
	case MODE_TITLE:	// タイトル
		UpdateTitle();
		break;
	case MODE_TUTORIAL:	// チュートリアル
		UpdateTutorial();
		break;
	case MODE_GAME:		// ゲーム
		game->Update();
		break;
	case MODE_RESULT:	// リザルト
		UpdateResult();
		break;
	case MODE_NONE:
		/* 処理なし */
		break;
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}
}

void CMode::Draw()
{
	switch (mode)
	{// どのモード？
	case MODE_TITLE:	// タイトル
		DrawTitle();
		break;
	case MODE_TUTORIAL:	// チュートリアル
		DrawTutorial();
		break;
	case MODE_GAME:		// ゲーム
		game->Draw();
		break;
	case MODE_RESULT:	// リザルト
		DrawResult();
		break;
	case MODE_NONE:
		/* 処理なし */
		break;
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}
}

void CMode::Set()
{
	if (modeNext == MODE_NONE)
	{// 次のモードが決まってない
		return;
	}

	if (GetTransition() == FADE_NONE)
	{// 何もしていない状態なら
		SetTransitionOut();
	}

	if (GetTransition() != FADE_IN)
	{// フェードイン状態じゃない
		return;
	}

	switch (mode)
	{// 現在のモードの終了
	case MODE_TITLE:	// タイトル
		UninitTitle();
		break;

	case MODE_TUTORIAL:	// チュートリアル
		UninitTutorial();
		break;

	case MODE_GAME:		// ゲーム
		game->Uninit();
		break;

	case MODE_RESULT:	// リザルト
		UninitResult();
		break;

	case MODE_NONE:
		/* 処理なし */
		break;

	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}

	// テクスチャ
	UnloadTextureAll();

	mode = modeNext;	// 現在の画面(モード)を切り替える

	switch (modeNext)
	{// 次のモードの初期化
	case MODE_TITLE:	// タイトル
		InitTitle();
		break;

	case MODE_TUTORIAL:	// チュートリアル
		InitTutorial();
		break;

	case MODE_GAME:		// ゲーム
		game->Init();
		break;

	case MODE_RESULT:	// リザルト
		InitResult();
		break;

	case MODE_NONE:
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}

	modeNext = MODE_NONE;
}

void CMode::Change(CMode::MODE inmodeNext)
{
	assert(inmodeNext >= 0 && inmodeNext < MODE_MAX);

	modeNext = inmodeNext;
}
