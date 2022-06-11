//=========================================
// 
// レンダーステートクラス
// Author YudaKaito
// 
//=========================================
#include "renderer.h"
#include "object.h"
#include "application.h"
#include "transition.h"
#include "debug.h"
#include "mode.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer::CRenderer() :
	pD3D(nullptr),
	pD3DDevice(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if ((FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画と頂点処理をCPUで行なう
		(FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice))))
	{
		// 生成失敗
		return E_FAIL;
	}

	// レンダーステートの設定
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステートの設定
	pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// 画像を小さくしても綺麗にする
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 画像を大きくしても綺麗にする
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャのUの繰り返し方を設定
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャのVの繰り返し方を設定

	// テクスチャステージステートの設定
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// ポリゴンとテクスチャのαをまぜる
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// １つ目の色はテクスチャの色
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２つ目の色は現在の色

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CRenderer::Uninit()
{
	// デバイスの破棄
	if (pD3DDevice != nullptr)
	{
		pD3DDevice->Release();
		pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (pD3D != nullptr)
	{
		pD3D->Release();
		pD3D = nullptr;
	}
}

//=============================================================================
// 更新
//=============================================================================
void CRenderer::Update()
{
}

//=============================================================================
// 描画
//=============================================================================
void CRenderer::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(pD3DDevice->BeginScene()))
	{
		// モードの描画
		CApplication::Instance()->GetMode()->Draw();

		// フェードの描画
		DrawTransition();

#ifdef  _DEBUG
		// デバッグの表示
		//DrawDebug();
#endif //  _DEBUG

		// Direct3Dによる描画の終了
		pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS()
{
	//RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//TCHAR str[256];

	//wsprintf(str, _T("FPS : %d\n"), g_nCountFPS);

	//// テキスト描画
	//pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG
