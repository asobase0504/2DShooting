//**************************************************
//
// ��ʂ̑J��
// Author  : Yuda Kaito
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "rectangle.h"
#include "fade.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	ALPHA_CHANGE = 0.07f;	// �t�F�[�h�̃��l�̕ω���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int		s_nIdx;
FADE	s_fade;				// ���̃t�F�[�h
float	s_fAlpha;			// �|���S��(�t�F�[�h)�̃��l
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitFade(void)
{
	s_fAlpha = 0.0f;	// �����|���S��(�s����)�ɂ��Ă���
	s_fade = FADE_NONE;	// �������ĂȂ����

	{// �S�ʒ���
	 // ��`�̐ݒ�
		s_nIdx = SetRectangle(TEXTURE_BG);

		float fWidth = SCREEN_WIDTH * 0.5f;
		float fHeight = SCREEN_HEIGHT * 0.5f;

		D3DXVECTOR3 size = D3DXVECTOR3(fWidth, fHeight, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.275f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdx, pos, size);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitFade(void)
{
	// �g���̂��~�߂�
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateFade(void)
{
	if (s_fade == FADE_NONE)
	{// �t�F�[�h���ĂȂ�
		return;
	}

	switch (s_fade)
	{
	case FADE_OUT:	// �t�F�[�h�A�E�g���
		s_fAlpha += ALPHA_CHANGE;	// �|���S����s�����ɂ��Ă���

		if (s_fAlpha >= 1.0f)
		{// �s�����ɂȂ���
			s_fAlpha = 1.0f;
			s_fade = FADE_IN;	// �t�F�[�h�C����Ԃ�
		}
		break;

	case FADE_IN:	// �t�F�[�h�C�����
		s_fAlpha -= ALPHA_CHANGE;	// �|���S���𓧖��ɂ��Ă���

		if (s_fAlpha <= 0.0f)
		{// �����ɂȂ���
			s_fAlpha = 0.0f;
			s_fade = FADE_NONE;	// �������Ă��Ȃ���Ԃ�
		}
		break;

	case FADE_NONE:	// �������ĂȂ����
	default:
		assert(false);
		break;
	}

	// ���_�J���[�̐ݒ菈��
	SetColorRectangle(s_nIdx, D3DXCOLOR(0.0f, 0.0f, 0.0f, s_fAlpha));
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawFade(void)
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
//void StartFadeOut(void)
//{
//	s_fade = FADE_OUT;	// �t�F�[�h�A�E�g��Ԃ�
//	s_fAlpha = 0.0f;	// �����|���S��(�s����)�ɂ��Ă���
//}

//--------------------------------------------------
// �擾
//--------------------------------------------------
FADE GetFade(void)
{
	return s_fade;
}