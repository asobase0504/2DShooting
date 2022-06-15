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
	typedef enum
	{
		MODE_TITLE = 0,	// タイトル
		MODE_TUTORIAL,	// チュートリアル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_MAX,
		MODE_NONE
	}MODE;

public:
	CMode();
	~CMode();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void Set();
	MODE GetMode() { return mode; }
	void Change(MODE modeNext);
private:
	MODE mode = MODE_NONE;		// 現在のモード
	MODE modeNext = MODE_NONE;	// 次のモード
	CGame* game;
};

#endif // !_MODE_H_
