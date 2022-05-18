//=========================================
// 
// オブジェクトクラス
// Author YudaKaito
// 
//=========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//=========================================
// include
//=========================================
#include "main.h"
#include "object.h"

//-----------------------------------------
// クラスの定義
//-----------------------------------------
class CObject2D : public CObject
{
// 定数の定義
private:
	static const int NUM_POLYGON = 2;	// ポリゴン数
	static const int NUM_VERTEX = 4;	// 頂点数

public:
	CObject2D();
	~CObject2D() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	bool GetUseStatus();
	bool GetDrawStatus();
	void CreateVtxBuff();
	void SetTexture(LPDIRECT3DTEXTURE9 inTexture);
	void SetPos(D3DXVECTOR3& inPos);
	void SetSize(D3DXVECTOR3& inSize);
	void SetColor(D3DXCOLOR& inColor);

private: // メンバー変数
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;	// 頂点バッファ
	D3DXCOLOR m_col;	// 色
	bool m_isDraw;		// 描写するか
	bool m_hasAdd;		// 加算合成を持っているか
};

#endif // !_OBJECT2D_H_
