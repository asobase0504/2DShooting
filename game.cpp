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

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CGame::CGame() :
	isPause(false),
	idxBg(0),
	object(nullptr)
{
	memset(player, 0, sizeof(player));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{

}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	isPause = false;	// �|�[�Y����

	// �w�i
	if (object == nullptr)
	{
		object = new CObject2D;

		if (object == nullptr)
		{
			MessageBox(NULL, TEXT("���I�m�ۂɎ��s���܂����B"), TEXT("���I�m�ۂɎ��s���܂����B"), MB_ICONHAND);
			assert(false);
		}

		// �I�u�W�F�N�g�̐���
		object->Init();
		object->CreateVtxBuff();
		object->SetTexture(GetTexture(TEXTURE_BG));
		object->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		object->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}

	for (int i = 0; i < 2; i++)
	{// �v���C���[
		if (player[i] != nullptr)
		{
			continue;
		}

		/* �� �g�p����Ă��Ȃ��ꍇ �� */

		player[i] = new CPlayer;

		if (player != nullptr)
		{
			player[i]->Init();
		}
		else
		{
			MessageBox(NULL, TEXT("���I�m�ۂɎ��s���܂����B"), TEXT("���I�m�ۂɎ��s���܂����B"), MB_ICONHAND);
			assert(false);
		}
	}

	// �v���C���[�̐���
	player[0]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::WHITE);
	player[1]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), CPlayer::PALYERTYPE::BLACK);

	InitMap();
	LoadMap();
	SetMap();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	// �T�E���h�̒�~
	StopSound();

	// �I�u�W�F�N�g�̉��
	if (object != nullptr)
	{
		object->Uninit();

		delete object;
		object = nullptr;
	}

	for (int i = 0; i < 2; i++)
	{
		if (player[i] == nullptr)
		{
			continue;
		}

		player[i]->Uninit();

		delete player[i];
		player[i] = nullptr;
	}

	StopUseRectangle(idxBg);	// �g���̂��~�߂�

	UninitMap();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	player[0]->Update();
	player[1]->Update();

	for (int i = 0; i < CBullet::MAX_BULLET; i++)
	{
		if (player[0]->GetBullet() == nullptr || !player[0]->GetBullet()[i].GetDrawStatus())
		{
			continue;
		}

		player[0]->GetBullet()[i].HitWithBullet(player[1]->GetBullet());
	}

	UpdateMap();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
	// �w�i�̕`��
	if (object != nullptr)
	{
		object->Draw();
	}

	DrawMap();

	// ��`�̕`��
	DrawRectangle();

	// �v���C���\�̕`��
	player[0]->Draw();
	player[1]->Draw();

	// �~�`�̕`��
	DrawFan();
}

//--------------------------------------------------
// �|�[�Y�̗L�������ݒ�
// ����  : bool bPause / �|�[�Y���邩�ǂ��� [ true : ���� false : ���Ȃ� ]
//--------------------------------------------------
void CGame::SetEnablePause(bool bPause)
{
	isPause = bPause;
}

//--------------------------------------------------
// �|�[�Y�̗L�������擾
// �Ԓl  : bool / �|�[�Y���Ă邩�ǂ���
//--------------------------------------------------
bool CGame::GetEnablePause(void)
{
	return isPause;
}
