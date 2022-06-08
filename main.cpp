//==================================================
// 
// メイン関数
// Author : Yuda Kaito
// 
//==================================================

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "transition.h"
#include "debug.h"
#include "mode.h"
#include "sound.h"

#include <stdio.h>

//==================================================
// 定義
//==================================================
namespace
{
const char	*CLASS_NAME = "windowClass";		// ウインドウクラスの名前
const char	*WINDOW_NAME = "練習場";	// ウインドウの名前 (キャプションに表示)
}

//==================================================
// スタティック変数
//==================================================
namespace
{
LPD3DXFONT			s_pFont = NULL;			// フォントへのポインタ
int					s_nCountFPS = 0;		// FPSカウンター
bool				s_bDebug = true;		// デバッグ表示をするか [表示  : true 非表示  : false]
CRenderer*			s_renderer;
}// namespaceはここまで

//==================================================
// プロトタイプ宣言
//==================================================
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
static void Uninit(void);
static void Update(void);
static void Draw(void);

//--------------------------------------------------
// main関数
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{// ウインドウクラスの構造体
		sizeof(WNDCLASSEX),					// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							// ウインドウのスタイル
		WindowProc,							// ウインドウプロシージャ
		0,									// ０にする (通常は使用しない)
		0,									// ０にする (通常は使用しない)
		hInstance,							// インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),	// タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			// クライアント領域の背景色
		NULL,								// メニューバー
		CLASS_NAME,							// ウインドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)		// ファイルのアイコン
	};

	HWND hWnd;											// ウインドウハンドル (識別子)
	MSG msg;											// メッセージを格納する変数
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};	// 画面サイズの構造体
	DWORD dwCurrentTime;								// 現在時刻
	DWORD dwExecLastTime;								// 最後に処理した時刻
	DWORD dwFrameCount;									// フレームカウント
	DWORD dwFPSLastTime;								// 最後にFPSを計算した時刻

	// ウインドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウインドウを作成
	hWnd = CreateWindowEx(
		0,							// 拡張ウインドウスタイル
		CLASS_NAME,					// ウインドウスタイルの名前
		WINDOW_NAME,				// ウインドウの名前
		WS_OVERLAPPEDWINDOW,		// ウインドウスタイル
		CW_USEDEFAULT,				// ウインドウの左上X座標
		CW_USEDEFAULT,				// 　　〃　　の左上Y座標
		(rect.right - rect.left),	// 　　〃　　の幅
		(rect.bottom - rect.top),	// 　　〃　　の高さ
		NULL,						// 親ウインドウのハンドル
		NULL,						// メニューハンドルまたは子ウインドウID
		hInstance,					// インスタンスハンドル
		NULL);						// ウインドウ作成データ

	// 初期化
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{// 初期化が失敗した場合
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;				// 初期化する
	dwExecLastTime = timeGetTime();	// 現在時刻を取得 (保存)
	dwFrameCount = 0;				// 初期化する
	dwFPSLastTime = timeGetTime();	// 現在時刻を取得 (保存)

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);	// ウインドウの表示状態を設定
	UpdateWindow(hWnd);			// クライアント領域を更新

	while (1)
	{// メッセージループ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windowsの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{// メッセージの設定
				TranslateMessage(&msg);	// 仮想メッセージを文字のメッセージへ変換
				DispatchMessage(&msg);	// ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();	// 現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				// FPSの計算
				s_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	// FPSを計測した時刻を保存

				dwFrameCount = 0;				// フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60分の1秒経過
				dwExecLastTime = dwCurrentTime;	// 処理開始の時刻[現在時刻]を保存

				// 更新
				Update();

				// 描画
				Draw();

				dwFrameCount++;	// フレームカウントを加算
			}
		}
	}
	
	// 終了
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//--------------------------------------------------
// ウインドウプロシージャ
//--------------------------------------------------
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:	// ウインドウ破棄のメッセージ
		// WM_QOITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]キーが押された
			// ウインドウを破棄する (WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 規定の処理を返す
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
static HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
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
//	InitSound(hWnd);

	// 遷移の初期化
	InitTransition();

	// モードの初期化
	InitMode();

	// モードの変更
	ChangeMode(MODE_GAME);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
static void Uninit(void)
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
	UninitMode();

	// デバッグの終了
	UninitDebug();
}

//--------------------------------------------------
// 更新
//-------------------------------------------------- 
static void Update(void)
{
	// レンダーステートの更新
	if (s_renderer != nullptr)
	{
		s_renderer->Update();
	}

	// 入力処理の更新
	UpdateInput();

	// モードの更新
	UpdateMode();

	// 遷移の更新
	UpdateTransition();

	// モードの設定
	SetMode();

 #ifdef  _DEBUG

	if (GetKeyboardTrigger(DIK_F1) || GetJoypadTrigger(JOYKEY_BACK,0))
	{// F1キーが押された
		s_bDebug = !s_bDebug;
	}

 #endif //  _DEBUG

}

//--------------------------------------------------
// 描画
//--------------------------------------------------
static void Draw(void)
{
	// レンダーステートの更新
	if (s_renderer != nullptr)
	{
		s_renderer->Draw();
	}
}

//--------------------------------------------------
// FPSの取得
//--------------------------------------------------
int GetFPS(void)
{
	return s_nCountFPS;
}

//=============================================================================
// レンダリングのインスタンス取得
//=============================================================================
CRenderer* GetRenderer()
{
	return s_renderer;
}