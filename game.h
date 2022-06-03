//==================================================
//
// ゲームモードヘッダー
// Author : Yuda Kaito
//
//==================================================
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//２重インクルード防止のマクロ定義

//--------------------------------------------------
// 前方宣言
//--------------------------------------------------
class CObject2D;
class CPlayer;

//--------------------------------------------------
// GameClass
//--------------------------------------------------
class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetEnablePause(bool bPause);
	bool GetEnablePause();
	CPlayer* GetPlayer();
private:
	bool isPause;	// ポーズ中かどうか [してる  : true してない  : false]
	int idxBg;				// 背景の矩形インデックス

	// インスタンスの生成
	CObject2D*	object;	// オブジェクト
	CPlayer* player[2];	// プレイヤー
};
#endif // !_GAME_H_
