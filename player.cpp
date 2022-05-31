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
#include "player.h"
#include "rectangle.h"
#include "color.h"
#include "input.h"
#include "collision.h"
#include "map.h"
#include "block.h"
#include "bullet.h"
#include "object.h"
#include "object2D.h"
#include <vector>

// �f�o�b�O
#include <assert.h>

//--------------------------------------------------
// �R���X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------
CPlayer::CPlayer() : 
	m_nIdx(0),
	m_bullet(nullptr),
	m_type(NONE),
	m_posOld(D3DXVECTOR3(0.0f,0.0f,0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// ������
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Init()
{
	CObject2D::Init();
	ReleaseBullet();
}

//--------------------------------------------------
// �I��
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
	ReleaseBullet();
}

//--------------------------------------------------
// �X�V
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Update()
{
	if (!m_isUse)
	{
		return;
	}

	/* ���g�p���Ă��遫 */

	CObject2D::Update();

	m_posOld = m_pos;
	Move();
	Collision();

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (!m_bullet[i].GetDrawStatus())
		{
			continue;
		}

		m_bullet[i].Update();
	}

}

//--------------------------------------------------
// �`��
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Draw()
{
	CObject2D::Draw();

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (!m_bullet[i].GetDrawStatus())
		{
			continue;
		}

		m_bullet[i].Draw();
	}
}

//--------------------------------------------------
// �ݒ�
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Set(D3DXVECTOR3& pos, D3DXVECTOR3& size, PALYERTYPE type)
{
	m_isUse = true;
	m_pos = pos;
	m_scale = size;
	m_type = type;

	CObject2D::CreateVtxBuff();		// ���_�o�b�t�@�̐���
	CObject2D::SetTexture(GetTexture(TEXTURE_Number_001));	// �e�N�X�`���̐ݒ�
	CObject2D::SetPos(m_pos);		// �ʒu�̐ݒ�
	CObject2D::SetSize(m_scale);	// �傫���̐ݒ�

	switch (type)
	{
	case PALYERTYPE::WHITE:
		CObject2D::SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		break;
	case PALYERTYPE::BLOCK:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}

	ReleaseBullet();
	m_bullet = new CBullet[CBullet::GetNumAll()];

}

//--------------------------------------------------
// �ړ�
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Move()
{
	float moveLength = 0.0f;
	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���f���̈ړ�
	if (GetKeyboardPress(DIK_W))
	{
		moveInput.y -= 1.0f;
		moveLength = 1.0f;
	}
	if (GetKeyboardPress(DIK_A))
	{
		moveInput.x -= 1.0f;
		moveLength = 1.0f;
	}
	if (GetKeyboardPress(DIK_S))
	{
		moveInput.y += 1.0f;
		moveLength = 1.0f;
	}
	if (GetKeyboardPress(DIK_D))
	{
		moveInput.x += 1.0f;
		moveLength = 1.0f;
	}

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (moveLength > 0.0f)
	{
		D3DXVec3Normalize(&moveInput, &moveInput);

		move = moveInput;
	}

	// �����x�N�g���|����ړ���
	m_move = move * moveLength * 2.0f * 2.0f;
	m_pos += m_move;
	CObject2D::SetPos(m_pos);		// �ʒu�̐ݒ�
}

//--------------------------------------------------
// �e�̔���
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Shot()
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		for (int i = 0; i < CBullet::GetNumAll(); i++)
		{
			if (m_bullet[i].GetDrawStatus())
			{
				continue;
			}

			m_bullet[i].Set(m_pos, D3DXVECTOR3(-5.0f, 0.0f, 0.0f));

			break;
		}
	}
}

//--------------------------------------------------
// �����蔻��
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::Collision()
{
	D3DXVECTOR3 outpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float dist;

	for (int cntBlock = 0; cntBlock < CBlock::MAX_BLOCK; cntBlock++)
	{
		CBlock* pBlock = &GetBlock()[cntBlock];

		if (!pBlock->GetUseStatus() || (int)m_type == (int)pBlock->GetType())
		{
			continue;
		}

		if (m_move.y > 0.0f)
		{
			// �v���C���[��A�u���b�N���̓����蔻��
			if (RectTopCollision(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.y += 1.0f;
				dist = (m_scale.y) + (m_pos.y - outpos.y);
				m_pos.y -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// �ʒu�̐ݒ�
			}
		}
		if (m_move.x > 0.0f)
		{
			if (RectLeftCollision(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.x += 1.0f;
				dist = (m_scale.x) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// �ʒu�̐ݒ�
			}
		}
		if (m_move.x < 0.0f)
		{
			if (RectRightCollision(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.x += -1.0f;
				float dist = (-m_scale.x) + (m_pos.x - outpos.x);
				m_pos.x -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// �ʒu�̐ݒ�
			}
		}
		if (m_move.y < 0.0f)
		{
			if (RectDownCollision(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, NULL, NULL))
			{
				vec.y = -1.0f;
				dist = (-m_scale.y) + (m_pos.y - outpos.y);

				m_pos.y -= dist + dist* 0.0001f;
				CObject2D::SetPos(m_pos);		// �ʒu�̐ݒ�
			}
		}
	}
}

//--------------------------------------------------
// �e�C���X�^���X�̉��
// Author : Yuda Kaito
//--------------------------------------------------
void CPlayer::ReleaseBullet()
{
	if (m_bullet == nullptr)
	{
		return;
	}

	for (int i = 0; i < CBullet::GetNumAll(); i++)
	{
		if (m_bullet == nullptr)
		{
			continue;
		}

		// �I������
		m_bullet[i].Uninit();
	}

	// �j��
	delete[] m_bullet;
	m_bullet = nullptr;
}
