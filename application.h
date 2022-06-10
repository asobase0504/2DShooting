//=========================================
// 
// アプリケーションクラス
// Author YudaKaito
// 
//=========================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

class CRenderer;
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
	CRenderer* GetRenderer();
private:
	CRenderer* s_renderer;				// レンダーステートのインスタンス
};

#endif // !_APPLICATION_H_