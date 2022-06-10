//=========================================
// 
// �Q�[��������
// Author YudaKaito
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "main.h"
#include "debug.h"
#include <stdio.h>
#include "input.h"
#include "game.h"
#include "transition.h"
#include "application.h"
#include "renderer.h"
#include "mode.h"

//------------------------------------
// ��`
//------------------------------------
namespace
{
const int  DEBUG_MAXWORD = 4096;
}

//------------------------------------
// �ÓI�ϐ��錾
//------------------------------------
namespace
{
LPD3DXFONT s_pFont = NULL;	// �t�H���g�ւ̃|�C���^
}

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------

//=========================================
// �f�o�b�O�\���̏�����
//=========================================
void InitDebug(void)
{
	// �f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(CApplication::Instance()->GetRenderer()->GetDevice(), 32, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &s_pFont);
}

//=========================================
// �f�o�b�O�\���̏I������
//=========================================
void UninitDebug(void)
{
	// �f�o�b�O�\���p�t�H���g�̔j��
	if (s_pFont != NULL)
	{
		s_pFont->Release();
		s_pFont = NULL;
	}
}

//=========================================
// �f�o�b�O�\��
//=========================================
void DrawDebug(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[DEBUG_MAXWORD];
	int nLength = 0;

	/* ��������̑���� */

	sprintf(&aStr[nLength], "FPS  : %2d\n\n", GetFPS());
	nLength = (int)strlen(&aStr[0]);

	sprintf(&aStr[nLength], "MODE : %2d\n\n", GetMode());
	nLength = (int)strlen(&aStr[0]);

	sprintf(&aStr[nLength], "FADE : %2d\n\n", GetTransition());
	nLength = (int)strlen(&aStr[0]);

	// �e�L�X�g�̕`��
	s_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.25f, 0.75f, 1.0f, 1.0f));
}