//=========================================
// 
// オブジェクトクラス
// Author YudaKaito
// 
//=========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=========================================
// include
//=========================================
#include "main.h"

//-----------------------------------------
// クラスの定義
//-----------------------------------------
class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	static const int NAX_OBJECT = 2048;	// オブジェクトの最大数

	D3DMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_scale;	// 拡縮
	D3DXVECTOR3 m_rot;		// 回転
	D3DXVECTOR3 m_pos;		// ローカル位置
	bool m_isUse;			// 使用しているか

	/*そのうち*/
	//CObject* m_parent;		// 親
};

#endif // !_OBJECT_H_
