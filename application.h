//=========================================
// 
// アプリケーションクラス
// Author YudaKaito
// 
//=========================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

//--------------------------------------------------
// 前方宣言
//--------------------------------------------------
class CRenderer;
class CMode;

//--------------------------------------------------
// レンダーステートクラス
//--------------------------------------------------
class CApplication
{
public:
	static CApplication* Instance();

	static CApplication* application;	// シングルトンのインスタンス

private:
	CApplication();

public:
	~CApplication();

public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	CRenderer* GetRenderer() { return s_renderer; }
	CMode* GetMode() { return mode; }
private:
	CRenderer* s_renderer;				// レンダーステートのインスタンス
	CMode* mode;
};

#endif // !_APPLICATION_H_