//==================================================
// 
// 当たり判定のヘッダー
// Author : Yuda Kaito
// 
//==================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"

namespace Collision
{
bool RectangleTop(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool RectangleDown(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool RectangleLeft(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool RectangleRight(const D3DXVECTOR3& pos1, const D3DXVECTOR3& size1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& size2, D3DXVECTOR3* outPos, float* t1, float* t2);
bool PointAndRectangle(const D3DXVECTOR3& pointPos, const D3DXVECTOR3& rectanglePos, const D3DXVECTOR3& rectangleSize);
bool PointAndRectangle(const D3DXVECTOR3& pointPos, const D3DXVECTOR3& rectanglePos, const D3DXVECTOR3& rectangleSize);
}
#endif // !_COLLISION_H_
