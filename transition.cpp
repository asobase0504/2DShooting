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
#include "transition.h"
#include "application.h"
#include "renderer.h"

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
LPDIRECT3DVERTEXBUFFER9	s_pVtxBuff = NULL;	// 頂点バッファのポインタ
TRANSITION				s_transition;		// 今の遷移状態
float					s_fAlpha;			// ポリゴン(フェード)のα値
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitTransition(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Instance()->GetRenderer()->GetDevice();

	s_fAlpha = 0.0f;	// 黒いポリゴン(不透明)にしておく
	s_transition = FADE_NONE;	// 何もしてない状態

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidth = SCREEN_WIDTH * 0.5f;
	float fHeight = SCREEN_HEIGHT * 0.5f;

	D3DXVECTOR3 pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// 頂点座標の設定
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(+fWidth, -fHeight, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth, +fHeight, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(+fWidth, +fHeight, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTransition(void)
{
	if (s_pVtxBuff != NULL)
	{// 頂点バッファの破棄
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateTransition(void)
{
	if (s_transition == FADE_NONE)
	{// フェードしてない
		return;
	}

	switch (s_transition)
	{
	case FADE_OUT:	// フェードアウト状態
		s_fAlpha += ALPHA_CHANGE;	// ポリゴンを不透明にしていく

		if (s_fAlpha >= 1.0f)
		{// 不透明になった
			s_fAlpha = 1.0f;
			s_transition = FADE_IN;	// フェードイン状態に
		}
		break;

	case FADE_IN:	// フェードイン状態
		s_fAlpha -= ALPHA_CHANGE;	// ポリゴンを透明にしていく

		if (s_fAlpha <= 0.0f)
		{// 透明になった
			s_fAlpha = 0.0f;
			s_transition = FADE_NONE;	// 何もしていない状態に
		}
		break;

	case FADE_NONE:	// 何もしてない状態
	default:
		MessageBox(NULL, TEXT("想定外の列挙型を検出。"), TEXT("swith文の条件式"), MB_ICONHAND);
		assert(false);
		break;
	}

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定処理
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha);

	// 頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTransition(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::Instance()->GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,						// 描画する最初の頂点インデックス
		2);						// プリミティブ(ポリゴン)数
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetTransitionOut(void)
{
	s_transition = FADE_OUT;	// フェードアウト状態に
	s_fAlpha = 0.0f;	// 黒いポリゴン(不透明)にしておく
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
TRANSITION GetTransition(void)
{
	return s_transition;
}