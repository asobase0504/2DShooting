//=========================================
// 
// レンダーステートクラス
// Author YudaKaito
// 
//=========================================
#include "application.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "transition.h"
#include "debug.h"
#include "mode.h"
#include "game.h"
#include "title.h"
#include "sound.h"

//=============================================================================
// 静的メンバー変数の初期化
//=============================================================================
CApplication* CApplication::application = nullptr;

//=============================================================================
// インスタンスの生成
//=============================================================================
CApplication* CApplication::Instance()
{
	if (application == nullptr)
	{
		application = new CApplication;
	}

	return application;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CApplication::CApplication() :
	s_renderer(nullptr),
	mode(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CApplication::~CApplication()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (s_renderer == nullptr)
	{
		s_renderer = new CRenderer;

		if (s_renderer != nullptr)
		{
			// レンダーステートの初期化
			if (FAILED(s_renderer->Init(hWnd, true)))
			{
				return E_FAIL;
			}
		}
	}

	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// サウンドの初期化
	//InitSound(hWnd);

	// 遷移の初期化
	InitTransition();

	// モードの初期化
	if (mode == nullptr)
	{
		mode = new CGame;

		if (mode != nullptr)
		{
			// レンダーステートの初期化
			if (FAILED(mode->Init()))
			{
				return E_FAIL;
			}
		}
	}
	mode->Change(CMode::MODE_GAME);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CApplication::Uninit()
{
	// サウンドの終了
	//	UninitSound();

	// レンダーステートの終了
	if (s_renderer != nullptr)
	{
		s_renderer->Uninit();
		delete s_renderer;
		s_renderer = nullptr;
	}

	// 入力処理の終了
	UninitInput();

	// 遷移の終了
	UninitTransition();

	// モードの終了
	if (mode != nullptr)
	{
		mode->Uninit();
		delete mode;
		mode = nullptr;
	}

	// デバッグの終了
	UninitDebug();
}

//=============================================================================
// 更新
//=============================================================================
void CApplication::Update()
{
	// レンダーステートの更新
	if (s_renderer != nullptr)
	{
		s_renderer->Update();
	}

	UpdateInput();		// 入力
	mode->Update();		// モード
	UpdateTransition();	// 遷移

	// モードの設定
	//mode->Set();

//#ifdef  _DEBUG
//
//	if (GetKeyboardTrigger(DIK_F1) || GetJoypadTrigger(JOYKEY_BACK, 0))
//	{// F1キーが押された
//		s_bDebug = !s_bDebug;
//	}
//
//#endif //  _DEBUG
}

//=============================================================================
// 描画
//=============================================================================
void CApplication::Draw()
{
	// レンダーステートの更新
	if (s_renderer != nullptr)
	{
		s_renderer->Draw();
	}
}
