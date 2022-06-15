//**************************************************
//
// Hackathon ( title.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _TITLE_H_	// このマクロが定義されてなかったら
#define _TITLE_H_	// 2重インクルード防止のマクロ定義

//--------------------------------------------------
// include
//--------------------------------------------------
#include "mode.h"

//--------------------------------------------------
// 前方宣言
//--------------------------------------------------
class CObject2D;
class CPlayer;

//--------------------------------------------------
// TitleClass
//--------------------------------------------------
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

#endif // !_TITLE_H_
