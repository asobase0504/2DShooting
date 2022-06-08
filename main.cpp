//==================================================
// 
// ���C���֐�
// Author : Yuda Kaito
// 
//==================================================

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "transition.h"
#include "debug.h"
#include "mode.h"
#include "sound.h"

#include <stdio.h>

//==================================================
// ��`
//==================================================
namespace
{
const char	*CLASS_NAME = "windowClass";		// �E�C���h�E�N���X�̖��O
const char	*WINDOW_NAME = "���K��";	// �E�C���h�E�̖��O (�L���v�V�����ɕ\��)
}

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
LPD3DXFONT			s_pFont = NULL;			// �t�H���g�ւ̃|�C���^
int					s_nCountFPS = 0;		// FPS�J�E���^�[
bool				s_bDebug = true;		// �f�o�b�O�\�������邩 [�\��  : true ��\��  : false]
CRenderer*			s_renderer;
}// namespace�͂����܂�

//==================================================
// �v���g�^�C�v�錾
//==================================================
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
static void Uninit(void);
static void Update(void);
static void Draw(void);

//--------------------------------------------------
// main�֐�
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{// �E�C���h�E�N���X�̍\����
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							// �E�C���h�E�̃X�^�C��
		WindowProc,							// �E�C���h�E�v���V�[�W��
		0,									// �O�ɂ��� (�ʏ�͎g�p���Ȃ�)
		0,									// �O�ɂ��� (�ʏ�͎g�p���Ȃ�)
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		// �t�@�C���̃A�C�R��
	};

	HWND hWnd;											// �E�C���h�E�n���h�� (���ʎq)
	MSG msg;											// ���b�Z�[�W���i�[����ϐ�
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};	// ��ʃT�C�Y�̍\����
	DWORD dwCurrentTime;								// ���ݎ���
	DWORD dwExecLastTime;								// �Ō�ɏ�����������
	DWORD dwFrameCount;									// �t���[���J�E���g
	DWORD dwFPSLastTime;								// �Ō��FPS���v�Z��������

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�C���h�E���쐬
	hWnd = CreateWindowEx(
		0,							// �g���E�C���h�E�X�^�C��
		CLASS_NAME,					// �E�C���h�E�X�^�C���̖��O
		WINDOW_NAME,				// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�C���h�E�̍���X���W
		CW_USEDEFAULT,				// �@�@�V�@�@�̍���Y���W
		(rect.right - rect.left),	// �@�@�V�@�@�̕�
		(rect.bottom - rect.top),	// �@�@�V�@�@�̍���
		NULL,						// �e�E�C���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�C���h�E�쐬�f�[�^

	// ������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{// �����������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;				// ����������
	dwExecLastTime = timeGetTime();	// ���ݎ������擾 (�ۑ�)
	dwFrameCount = 0;				// ����������
	dwFPSLastTime = timeGetTime();	// ���ݎ������擾 (�ۑ�)

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);			// �N���C�A���g�̈���X�V

	while (1)
	{// ���b�Z�[�W���[�v
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	// ���z���b�Z�[�W�𕶎��̃��b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();	// ���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS�̌v�Z
				s_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	// FPS���v������������ۑ�

				dwFrameCount = 0;				// �t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60����1�b�o��
				dwExecLastTime = dwCurrentTime;	// �����J�n�̎���[���ݎ���]��ۑ�

				// �X�V
				Update();

				// �`��
				Draw();

				dwFrameCount++;	// �t���[���J�E���g�����Z
			}
		}
	}
	
	// �I��
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//--------------------------------------------------
// �E�C���h�E�v���V�[�W��
//--------------------------------------------------
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:	// �E�C���h�E�j���̃��b�Z�[�W
		// WM_QOIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// �L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]�L�[�������ꂽ
			// �E�C���h�E��j������ (WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// �K��̏�����Ԃ�
}

//--------------------------------------------------
// ������
//--------------------------------------------------
static HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (s_renderer == nullptr)
	{
		s_renderer = new CRenderer;

		if (s_renderer != nullptr)
		{
			// �����_�[�X�e�[�g�̏�����
			if (FAILED(s_renderer->Init(hWnd, true)))
			{
				return E_FAIL;
			}
		}
	}

	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �T�E���h�̏�����
//	InitSound(hWnd);

	// �J�ڂ̏�����
	InitTransition();

	// ���[�h�̏�����
	InitMode();

	// ���[�h�̕ύX
	ChangeMode(MODE_GAME);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
static void Uninit(void)
{
	// �T�E���h�̏I��
//	UninitSound();

	// �����_�[�X�e�[�g�̏I��
	if (s_renderer != nullptr)
	{
		s_renderer->Uninit();
		delete s_renderer;
		s_renderer = nullptr;
	}

	// ���͏����̏I��
	UninitInput();

	// �J�ڂ̏I��
	UninitTransition();

	// ���[�h�̏I��
	UninitMode();

	// �f�o�b�O�̏I��
	UninitDebug();
}

//--------------------------------------------------
// �X�V
//-------------------------------------------------- 
static void Update(void)
{
	// �����_�[�X�e�[�g�̍X�V
	if (s_renderer != nullptr)
	{
		s_renderer->Update();
	}

	// ���͏����̍X�V
	UpdateInput();

	// ���[�h�̍X�V
	UpdateMode();

	// �J�ڂ̍X�V
	UpdateTransition();

	// ���[�h�̐ݒ�
	SetMode();

 #ifdef  _DEBUG

	if (GetKeyboardTrigger(DIK_F1) || GetJoypadTrigger(JOYKEY_BACK,0))
	{// F1�L�[�������ꂽ
		s_bDebug = !s_bDebug;
	}

 #endif //  _DEBUG

}

//--------------------------------------------------
// �`��
//--------------------------------------------------
static void Draw(void)
{
	// �����_�[�X�e�[�g�̍X�V
	if (s_renderer != nullptr)
	{
		s_renderer->Draw();
	}
}

//--------------------------------------------------
// FPS�̎擾
//--------------------------------------------------
int GetFPS(void)
{
	return s_nCountFPS;
}

//=============================================================================
// �����_�����O�̃C���X�^���X�擾
//=============================================================================
CRenderer* GetRenderer()
{
	return s_renderer;
}