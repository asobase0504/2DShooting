//=========================================
// 
// オブジェクト2Dクラス
// Author YudaKaito
// 
//=========================================
//=========================================
// include
//=========================================
#include "object2d.h"

//-----------------------------------------
// コンストラクタ
//-----------------------------------------
CObject2D::CObject2D() :
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_isUse(false),
	m_isDraw(false),
	m_hasAdd(false)
{

}

//-----------------------------------------
// デストラクタ
//-----------------------------------------
CObject2D::~CObject2D()
{

}

//-----------------------------------------
// 初期化
//-----------------------------------------
void CObject2D::Init()
{
	// 頂点バッファの生成
	CreateVtxBuff();
}

//-----------------------------------------
// 修了
//-----------------------------------------
void CObject2D::Uninit()
{
	if (m_pVtxBuff != NULL)
	{// 頂点バッファの解放
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pTexture != NULL)
	{// テクスチャの解放
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-----------------------------------------
// 更新
//-----------------------------------------
void CObject2D::Update()
{

}

//-----------------------------------------
// 描画
//-----------------------------------------
void CObject2D::Draw()
{
	if (!m_isUse || !m_isDraw)
	{// 使用していない、描画するしない
		return;
	}

	/*↓ 使用している、描画する ↓*/

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (m_hasAdd)
	{// 加算合成する
	 // レンダーステートの設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);

	if (m_hasAdd)
	{// 基本レンダーステートに戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//-----------------------------------------
// 使用状況を取得
//-----------------------------------------
bool CObject2D::GetUseStatus()
{
	return m_isUse;
}

//-----------------------------------------
// 描画状況を取得
//-----------------------------------------
bool CObject2D::GetDrawStatus()
{
	return m_isDraw;
}

//-----------------------------------------
// 頂点バッファの生成
//-----------------------------------------
void CObject2D::CreateVtxBuff()
{
	// 頂点バッファの生成
	GetDevice()->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 位置の設定
	pVtx[0].pos = pos + size;
	pVtx[1].pos = pos + size;
	pVtx[2].pos = pos + size;
	pVtx[3].pos = pos + size;

	//色の設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
	D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(texU.x,texV.x);
	pVtx[1].tex = D3DXVECTOR2(texU.y,texV.x);
	pVtx[2].tex = D3DXVECTOR2(texU.x,texV.y);
	pVtx[3].tex = D3DXVECTOR2(texU.y,texV.y);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_isDraw = true;
	m_isUse = true;
}

//-----------------------------------------
// 位置の設定
//-----------------------------------------
void CObject2D::SetPos(D3DXVECTOR3& inPos)
{
	m_pos = inPos;

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//-----------------------------------------
// 大きさの設定
//-----------------------------------------
void CObject2D::SetSize(D3DXVECTOR3& inSize)
{
	m_scale = inSize;

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
