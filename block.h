//==================================================
// 
// デバッグ機能(ヘッダーファイル)
// Author : Yuda Kaito
// 
//==================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"
#include "object2d.h"

//--------------------------------------------------
// ブロッククラス
//--------------------------------------------------
class CBlock : public CObject2D
{
public:
	//--------------------------------------------------
	// ブロック状態の列挙型
	//--------------------------------------------------
	enum class TYPE
	{
		NONE = 0,
		BLACK,
		WHITE,
		MAX
	};

	static const int MAX_BLOCK = 40 * 17;
public:
	CBlock();
	~CBlock();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);
	void ChangeType(TYPE type);
	TYPE GetType();

private:
	TYPE m_type;	// 状態
};
#endif // !_BLOCK_H_
