//**************************************************
//
// Hackathon ( mode.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"
#include "transition.h"

// �`��̎��
#include "rectangle.h"
#include "fan.h"
#include "texture.h"

// ���[�h�̎��
#include "tutorial.h"
#include "game.h"
#include "title.h"
#include "result.h"

#include <assert.h>
#include <time.h>

CMode::CMode()
{
}

CMode::~CMode()
{
}

HRESULT CMode::Init()
{
	// �e�N�X�`���̓ǂݍ���
	srand((unsigned int)time(NULL));

	game = new CGame;

	return S_OK;
}

void CMode::Uninit()
{
	UninitTitle();	// �^�C�g��

	UninitTutorial();	// �`���[�g���A��

	// �Q�[��
	if (game != nullptr)
	{
		game->Uninit();
		delete game;
		game = nullptr;
	}

	// ���U���g
	UninitResult();

	// �e�N�X�`��
	UnloadTextureAll();
}

void CMode::Update()
{
	switch (mode)
	{// �ǂ̃��[�h�H
	case MODE_TITLE:	// �^�C�g��
		UpdateTitle();
		break;
	case MODE_TUTORIAL:	// �`���[�g���A��
		UpdateTutorial();
		break;
	case MODE_GAME:		// �Q�[��
		game->Update();
		break;
	case MODE_RESULT:	// ���U���g
		UpdateResult();
		break;
	case MODE_NONE:
		/* �����Ȃ� */
		break;
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}
}

void CMode::Draw()
{
	switch (mode)
	{// �ǂ̃��[�h�H
	case MODE_TITLE:	// �^�C�g��
		DrawTitle();
		break;
	case MODE_TUTORIAL:	// �`���[�g���A��
		DrawTutorial();
		break;
	case MODE_GAME:		// �Q�[��
		game->Draw();
		break;
	case MODE_RESULT:	// ���U���g
		DrawResult();
		break;
	case MODE_NONE:
		/* �����Ȃ� */
		break;
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}
}

void CMode::Set()
{
	if (modeNext == MODE_NONE)
	{// ���̃��[�h�����܂��ĂȂ�
		return;
	}

	if (GetTransition() == FADE_NONE)
	{// �������Ă��Ȃ���ԂȂ�
		SetTransitionOut();
	}

	if (GetTransition() != FADE_IN)
	{// �t�F�[�h�C����Ԃ���Ȃ�
		return;
	}

	switch (mode)
	{// ���݂̃��[�h�̏I��
	case MODE_TITLE:	// �^�C�g��
		UninitTitle();
		break;

	case MODE_TUTORIAL:	// �`���[�g���A��
		UninitTutorial();
		break;

	case MODE_GAME:		// �Q�[��
		game->Uninit();
		break;

	case MODE_RESULT:	// ���U���g
		UninitResult();
		break;

	case MODE_NONE:
		/* �����Ȃ� */
		break;

	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}

	// �e�N�X�`��
	UnloadTextureAll();

	mode = modeNext;	// ���݂̉��(���[�h)��؂�ւ���

	switch (modeNext)
	{// ���̃��[�h�̏�����
	case MODE_TITLE:	// �^�C�g��
		InitTitle();
		break;

	case MODE_TUTORIAL:	// �`���[�g���A��
		InitTutorial();
		break;

	case MODE_GAME:		// �Q�[��
		game->Init();
		break;

	case MODE_RESULT:	// ���U���g
		InitResult();
		break;

	case MODE_NONE:
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}

	modeNext = MODE_NONE;
}

void CMode::Change(CMode::MODE inmodeNext)
{
	assert(inmodeNext >= 0 && inmodeNext < MODE_MAX);

	modeNext = inmodeNext;
}
