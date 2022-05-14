//==================================================
//
// �Q�[�����[�h
// Author : Yuda Kaito
//
//==================================================

//==================================================
// �C���N���[�h
//==================================================
// ��v�n��
#include "main.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
// �`��n��
#include "rectangle.h"
#include "fan.h"
#include "color.h"
// �����n��
#include "time.h"
#include "utility.h"
#include "block.h"
#include "map.h"
#include "player.h"
#include "bullet.h"
// �I�u�W�F�N�g�n��
#include "object.h"
#include "object2d.h"

#include <assert.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
bool		s_bPause = false;		// �|�[�Y�����ǂ��� [���Ă�  : true ���ĂȂ�  : false]
int			s_nIdxBg;				// �w�i�̋�`�C���f�b�N�X

// �C���X�^���X�̐���
CObject2D*	s_Object;	// �I�u�W�F�N�g
CPlayer* s_pPlayer[2];	// �v���C���[
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGame(void)
{
	s_bPause = false;	// �|�[�Y����

	// �w�i
	if (s_Object == nullptr)
	{
		s_Object = new CObject2D;

		if (s_Object == nullptr)
		{
			MessageBox(NULL, TEXT("���I�m�ۂɎ��s���܂����B"), TEXT("���I�m�ۂɎ��s���܂����B"), MB_ICONHAND);
			assert(false);
		}

		s_Object->Init();
		s_Object->CreateVtxBuff();
		s_Object->SetTexture(GetTexture(TEXTURE_BG));
		s_Object->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		s_Object->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}

	for (int i = 0; i < 2; i++)
	{// �v���C���[
		if (s_pPlayer[i] != nullptr)
		{
			continue;
		}

		/* �� �g�p����Ă��Ȃ��ꍇ �� */

		s_pPlayer[i] = new CPlayer;

		if (s_pPlayer == nullptr)
		{
			MessageBox(NULL, TEXT("���I�m�ۂɎ��s���܂����B"), TEXT("���I�m�ۂɎ��s���܂����B"), MB_ICONHAND);
			assert(false);
		}

		s_pPlayer[i]->Init();
	}

	s_pPlayer[0]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::WHITE);
	s_pPlayer[1]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::BLOCK);

	InitBlock();
	LoadMap();
	SetMap();

	InitBullet();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitGame(void)
{
	// �T�E���h�̒�~
	StopSound();

	// �I�u�W�F�N�g�̉��
	if (s_Object != nullptr)
	{
		s_Object->Uninit();

		delete s_Object;
		s_Object = nullptr;
	}

	for (int i = 0; i < 2; i++)
	{
		if (s_pPlayer[i] == nullptr)
		{
			continue;
		}

		s_pPlayer[i]->Uninit();

		delete s_pPlayer[i];
		s_pPlayer[i] = nullptr;
	}

	StopUseRectangle(s_nIdxBg);	// �g���̂��~�߂�

	UninitBlock();
	UninitBullet();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGame(void)
{
	s_pPlayer[0]->Update();
	s_pPlayer[1]->Update();
	UpdateBlock();
	UpdateBullet();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawGame(void)
{
	// �w�i�̕`��
	if (s_Object != nullptr)
	{
		s_Object->Draw();
	}

	// ��`�̕`��
	DrawRectangle();

	// �v���C���\�̕`��
	s_pPlayer[0]->Draw();
	s_pPlayer[1]->Draw();

	// �~�`�̕`��
	DrawFan();
}

//--------------------------------------------------
// �|�[�Y�̗L�������ݒ�
//--------------------------------------------------
void SetEnablePause(bool bPause)
{
	s_bPause = bPause;
}

//--------------------------------------------------
// �|�[�Y�̗L�������擾
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_bPause;
}
