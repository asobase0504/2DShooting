//==================================================
// 
// プレイヤー処理のヘッダー
// Author : Yuda Kaito
// 
//==================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"
#include "object2d.h"

//--------------------------------------------------
// 前方宣言
//--------------------------------------------------
class CBullet;

//--------------------------------------------------
// プレイヤークラス
//--------------------------------------------------
class CPlayer : public CObject2D
{
public:
	//--------------------------------------------------
	// ブロック状態の列挙型
	//--------------------------------------------------
	enum class TYPE
	{
		NONE = 0,
		PLAYER_01,
		PLAYER_02,
		MAX
	};
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(D3DXVECTOR3& pos, D3DXVECTOR3& size, TYPE type);
	CBullet* GetBullet() { return m_bullet; }

private:
	void Move();
	void Shot();
	void Collision();
	void ReleaseBullet();

private:
	int m_nIdx;	// 番号
	CBullet* m_bullet;
	TYPE m_type;
	D3DXVECTOR3 m_posOld;	// 前回位置
	D3DXVECTOR3 m_posInblock;	// 自分が乗っているブロックの位置
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;

};
#endif // !_PLAYER_H_
