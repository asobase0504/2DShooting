//**************************************************
// 
// Hackathon ( mode.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	// このマクロが定義されてなかったら
#define _MODE_H_	// 2重インクルード防止のマクロ定義

//==================================================
// include
//==================================================
#include "main.h"

//==================================================
// 前方宣言
//==================================================
class CGame;

//==================================================
// モードクラス
//==================================================
class CMode
{
public:
	//==================================================
	// 列挙型
	//==================================================
	enum TYPE
	{
		MODE_TITLE = 0,	// タイトル
		MODE_TUTORIAL,	// チュートリアル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_MAX,
		MODE_NONE
	};

public:
	CMode();
	~CMode();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void Set();
	TYPE GetMode() { return mode; }
	void Change(TYPE modeNext);
private:
	TYPE mode = MODE_NONE;		// 現在のモード
	TYPE modeNext = MODE_NONE;	// 次のモード
};

#endif // !_MODE_H_
