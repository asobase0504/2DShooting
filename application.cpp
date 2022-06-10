//=========================================
// 
// �����_�[�X�e�[�g�N���X
// Author YudaKaito
// 
//=========================================
#include "application.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "transition.h"
#include "debug.h"
#include "mode.h"
#include "sound.h"

//=============================================================================
// �ÓI�����o�[�ϐ��̏�����
//=============================================================================
CApplication* CApplication::application = nullptr;

//=============================================================================
// �C���X�^���X�̐���
//=============================================================================
CApplication * CApplication::Instance()
{
	if (application == nullptr)
	{
		application = new CApplication;
	}

	return application;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CApplication::CApplication() :
	s_renderer(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CApplication::~CApplication()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
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

//=============================================================================
// �I��
//=============================================================================
void CApplication::Uninit()
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

//=============================================================================
// �X�V
//=============================================================================
void CApplication::Update()
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

//#ifdef  _DEBUG
//
//	if (GetKeyboardTrigger(DIK_F1) || GetJoypadTrigger(JOYKEY_BACK, 0))
//	{// F1�L�[�������ꂽ
//		s_bDebug = !s_bDebug;
//	}
//
//#endif //  _DEBUG
}

//=============================================================================
// �`��
//=============================================================================
void CApplication::Draw()
{
	// �����_�[�X�e�[�g�̍X�V
	if (s_renderer != nullptr)
	{
		s_renderer->Draw();
	}
}

//=============================================================================
// �����_�����O�̃C���X�^���X�擾
//=============================================================================
CRenderer* CApplication::GetRenderer()
{
	return s_renderer;
}