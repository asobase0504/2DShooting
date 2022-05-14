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
CObject2D*	s_Object[10];			// �I�u�W�F�N�g�̃C���X�^���X
CPlayer* s_pPlayer[2];
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGame(void)
{
	s_bPause = false;	// �|�[�Y����

	for (int i = 0; i < 10; i++)
	{// �w�i
		if (s_Object[i] != nullptr)
		{
			continue;
		}

		s_Object[i] = new CObject2D;

		s_Object[i]->Init();
		s_Object[i]->CreateVtxBuff();
		s_Object[i]->SetTexture(GetTexture(TEXTURE_BG));
		s_Object[i]->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		s_Object[i]->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

		break;
	}

	for (int i = 0; i < 2; i++)
	{// �w�i
		if (s_pPlayer[i] != nullptr)
		{
			continue;
		}

		s_pPlayer[i] = new CPlayer;
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
	for (int i = 0; i < 10; i++)
	{
		if (s_Object[i] == nullptr)
		{
			continue;
		}

		s_Object[i]->Uninit();

		delete s_Object[i];
		s_Object[i] = nullptr;
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
	for (int i = 0; i < 10; i++)
	{// �w�i
		if (s_Object[i] == nullptr)
		{
			continue;
		}

		s_Object[i]->Draw();
	}

	// ��`�̕`��
	DrawRectangle();

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
