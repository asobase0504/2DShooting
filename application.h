//=========================================
// 
// �A�v���P�[�V�����N���X
// Author YudaKaito
// 
//=========================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "main.h"

//--------------------------------------------------
// �O���錾
//--------------------------------------------------
class CRenderer;
class CMode;

//--------------------------------------------------
// �����_�[�X�e�[�g�N���X
//--------------------------------------------------
class CApplication
{
public:
	static CApplication* Instance();

	static CApplication* application;	// �V���O���g���̃C���X�^���X

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
	CRenderer* s_renderer;				// �����_�[�X�e�[�g�̃C���X�^���X
	CMode* mode;
};

#endif // !_APPLICATION_H_