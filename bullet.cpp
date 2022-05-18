//==================================================
//
// �����`�̃|���S���̐���
// Author : Yuda Kaito
//
//==================================================
//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"
#include "bullet.h"
#include "rectangle.h"
#include "color.h"
#include "input.h"
#include "collision.h"
#include "block.h"
#include "map.h"

// �f�o�b�O
#include <assert.h>

//--------------------------------------------------
// �ÓI�����o�[�ϐ��̐錾
//--------------------------------------------------
static int m_maxNumAll = 5;	// �ő吔

//--------------------------------------------------
// �R���X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------
CBullet::CBullet() : 
	m_type(NONE),
	m_posOld(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_move(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------
// ������
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Init()
{
	CObject2D::Init();
}

//--------------------------------------------------
// �I��
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Update()
{
	if (!m_isUse)
	{
		return;
	}

	/* ���g�p���Ă��遫 */

	CObject2D::Update();

	// �ʒu�̍X�V
	SetPos(m_pos + m_move);

	// �u���b�N�Ƃ̏Փ˔���
	//HitWithBlock(m_pos, m_move);
}

//--------------------------------------------------
// �`��
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// �ݒ�
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::Set(D3DXVECTOR3 & inPos, D3DXVECTOR3 & inMove)
{
	m_isUse = true;
	m_move = inMove;
	m_type = TYPE::WHITE;

	// �\��
	CreateVtxBuff();
	SetPos(inPos);
	SetSize(D3DXVECTOR3(15.0f, 15.0f, 0.0f));
	SetColor(GetColor(COLOR_WHITE));;
	
}

//--------------------------------------------------
// �����̎擾
// Author : Yuda Kaito
//--------------------------------------------------
int CBullet::GetNumAll()
{
	return m_maxNumAll;
}

//--------------------------------------------------
// �u���b�N�Ƃ̓����蔻��
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::HitWithBlock(D3DXVECTOR3 & inPos, const D3DXVECTOR3 & inVec)
{
}
