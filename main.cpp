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
#include "application.h"
#include "sound.h"
#include <time.h>
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
int s_nCountFPS = 0;		// FPSカウンター
bool s_bDebug = true;		// デバッグ表示をするか [表示  : true 非表示  : false]
CApplication* application;
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
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};	// 画面サイズの構造体

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

	// 乱数の初期化
	srand((unsigned int)time(NULL));

	// 初期化
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{// 初期化が失敗した場合
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);	// ウインドウの表示状態を設定
	UpdateWindow(hWnd);			// クライアント領域を更新

	MSG msg;	// メッセージを格納する変数
	DWORD dwCurrentTime = 0;				// 現在時刻
	DWORD dwExecLastTime = timeGetTime();	// 最後に処理した時刻
	DWORD dwFrameCount = 0;					// フレームカウント
	DWORD dwFPSLastTime = timeGetTime();	// 最後にFPSを計算した時刻

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

				Update();	// 更新
				Draw();		// 描画

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
	application = CApplication::Instance();

	application->Init(hInstance,hWnd,bWindow);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
static void Uninit(void)
{
	application->Uninit();
}

//--------------------------------------------------
// 更新
//-------------------------------------------------- 
static void Update(void)
{
	application->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
static void Draw(void)
{
	application->Draw();
}

//--------------------------------------------------
// FPSの取得
//--------------------------------------------------
int GetFPS(void)
{
	return s_nCountFPS;
}
