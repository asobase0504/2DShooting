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

//--------------------------------------------------
// ブロック状態の列挙型
//--------------------------------------------------
enum class BULLETTYPE
{
	NONE = 0,
	WHITE,
	BLOCK,
	MAX
};

//==================================================
// 初期化
//==================================================
void InitBullet(void);

//==================================================
// 終了
//==================================================
void UninitBullet(void);

//==================================================
// 更新
//==================================================
void UpdateBullet(void);

//==================================================
// 描画
//==================================================
void DrawBullet(void);

//==================================================
// 設定
//==================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif // !_BULLET_H_
