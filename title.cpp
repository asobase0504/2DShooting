//**************************************************
//
// Hackathon ( title.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "input.h"
#include "mode.h"
#include "transition.h"
#include "rectangle.h"
#include "title.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// �^�C�g���̕�
const float	TITLE_HEIGHT = 600.0f;	// �^�C�g���̍���

typedef enum
{
	MENU_GAME = 0,	// �Q�[��
	MENU_MAX
}MENU;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_nIdx;				// ��`�̃C���f�b�N�X
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Input(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitTitle(void)
{
	{// ���S
		// ��`�̐ݒ�
		s_nIdx = SetRectangle(TEXTURE_BG);

		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdx, pos, size);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTitle(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTitle(void)
{
	// ����
	Input();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTitle(void)
{
	// ��`�̕`��
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// ����
//--------------------------------------------------
void Input(void)
{
	if (GetTransition() != FADE_NONE)
	{// �t�F�[�h���Ă���
		return;
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
//		ChangeMode(MODE_TUTORIAL);
	}
}
}// namespace�͂����܂�
