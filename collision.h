//==================================================
// 
// ìñÇΩÇËîªíËÇÃÉwÉbÉ_Å[
// Author : Yuda Kaito
// 
//==================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"

bool RectTopCollision(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos,float* t1, float* t2);
bool RectDownCollision(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool RectLeftCollision(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool RectRightCollision(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
#endif // !_COLLISION_H_
