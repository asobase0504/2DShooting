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
public:
	CObject2D();
	virtual ~CObject2D();

	void Init();
	void Uninit();
	virtual void Update();
	void Draw();
	bool GetUseStatus();
	bool GetDrawStatus();
	void CreateVtxBuff();
	void SetPos(D3DXVECTOR3& inPos);
	void SetSize(D3DXVECTOR3& inSize);
private:

private:
	static const int NUM_POLYGON = 2;	// ポリゴン数
	static const int NUM_VERTEX = 4;	// 頂点数

	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;	// 頂点バッファ
	bool m_isUse;		// 使用しているか
	bool m_isDraw;	// 描写するか
	bool m_hasAdd;	// 加算合成を持っているか
};

#endif // !_OBJECT2D_H_
