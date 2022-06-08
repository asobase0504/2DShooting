//==================================================
// 
// 弾処理のヘッダー
// Author : Yuda Kaito
// 
//==================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"
#include "object2d.h"

//--------------------------------------------------
// 弾クラス
//--------------------------------------------------
class CBullet : public CObject2D
{
public:
	//--------------------------------------------------
	// ブロック状態の列挙型
	//--------------------------------------------------
	enum TYPE
	{
		NONE = 0,
		BLACK,
		WHITE,
		MAX
	};

public:
	static const int MAX_BULLET = 200;

public:
	CBullet();
	~CBullet();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(D3DXVECTOR3& inPos, const D3DXVECTOR3& inMove , TYPE inType);
	void HitWithBullet(CBullet* inBullet);

	static int GetNumAll();
	TYPE GetType() { return m_type; }
private:
	void HitWithBlock(D3DXVECTOR3& inPos, const D3DXVECTOR3& inVec);
	void LoopPos();

private:
	static int m_maxNumAll;	// 最大数
	TYPE m_type;	// 状態
	D3DXVECTOR3 m_posOld;	// 前の位置
	D3DXVECTOR3 m_move;		// 移動量
};
#endif // !_BULLET_H_
