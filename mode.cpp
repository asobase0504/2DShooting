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
		break;

	case MODE_TUTORIAL:	// �`���[�g���A��
		UninitTutorial();
		break;

	case MODE_GAME:		// �Q�[��
		//game->Uninit();
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
		break;

	case MODE_TUTORIAL:	// �`���[�g���A��
		InitTutorial();
		break;

	case MODE_GAME:		// �Q�[��
		//game->Init();
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

void CMode::Change(CMode::TYPE inmodeNext)
{
	assert(inmodeNext >= 0 && inmodeNext < MODE_MAX);

	modeNext = inmodeNext;
}
