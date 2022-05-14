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

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
MODE	s_mode = MODE_NONE;		// ���݂̃��[�h
MODE	s_modeNext = MODE_NONE;	// ���̃��[�h
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitMode(void)
{
	// �e�N�X�`���̓ǂݍ���
	srand((unsigned int)time(NULL));

	// ��`�̏�����
	InitRectangle();

	// �~�`�̏�����
	InitFan();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitMode(void)
{
	// �^�C�g��
	UninitTitle();

	// �`���[�g���A��
	UninitTutorial();

	// �Q�[��
	UninitGame();

	// ���U���g
	UninitResult();

	// ��`
	UninitRectangle();

	// �~�`
	UninitFan();

	// �e�N�X�`��
	UnloadTextureAll();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateMode(void)
{
	switch (s_mode)
	{// �ǂ̃��[�h�H
	case MODE_TITLE:	// �^�C�g��
		UpdateTitle();
		break;
	case MODE_TUTORIAL:	// �`���[�g���A��
		UpdateTutorial();
		break;
	case MODE_GAME:		// �Q�[��
		UpdateGame();
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

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawMode(void)
{
	switch (s_mode)
	{// �ǂ̃��[�h�H
	case MODE_TITLE:	// �^�C�g��
		DrawTitle();
		break;
	case MODE_TUTORIAL:	// �`���[�g���A��
		DrawTutorial();
		break;
	case MODE_GAME:		// �Q�[��
		DrawGame();
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

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetMode(void)
{
	if (s_modeNext == MODE_NONE)
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

	switch (s_mode)
	{// ���݂̃��[�h�̏I��
	case MODE_TITLE:	// �^�C�g��
		UninitTitle();
		break;

	case MODE_TUTORIAL:	// �`���[�g���A��
		UninitTutorial();
		break;

	case MODE_GAME:		// �Q�[��
		UninitGame();
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

	// ��`�̏I��
	UninitRectangle();

	// ��`�̏�����
	InitRectangle();

	// �~�`�̏I��
	UninitFan();

	// �~�`�̏�����
	InitFan();

	s_mode = s_modeNext;	// ���݂̉��(���[�h)��؂�ւ���
	
	switch (s_modeNext)
	{// ���̃��[�h�̏�����
	case MODE_TITLE:	// �^�C�g��
		InitTitle();
		break;

	case MODE_TUTORIAL:	// �`���[�g���A��
		InitTutorial();
		break;

	case MODE_GAME:		// �Q�[��
		InitGame();
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

	s_modeNext = MODE_NONE;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
MODE GetMode(void)
{
	return s_mode;
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void ChangeMode(MODE modeNext)
{
	assert(modeNext >= 0 && modeNext < MODE_MAX);

	s_modeNext = modeNext;
}
