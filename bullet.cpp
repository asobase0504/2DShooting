//==================================================
//
// �e�̐���
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
int CBullet::m_maxNumAll = 50;	// �ő吔

//--------------------------------------------------
// �R���X�g���N�^
// Author : Yuda Kaito
//--------------------------------------------------
CBullet::CBullet() : 
	CObject2D(),
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
	HitWithBlock(m_pos, m_move);

	// ��ʊX����
	LoopPos();
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
void CBullet::Set(D3DXVECTOR3& inPos, const D3DXVECTOR3& inMove, TYPE inType)
{
	SetDrawStatus(true);
	m_move = inMove;
	m_type = inType;

	// �\��
	CreateVtxBuff();
	SetPos(inPos);
	SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));

	switch (m_type)
	{
	case CBullet::BLACK:
		SetColor(GetColor(COLOR_WHITE));;
		break;
	case CBullet::WHITE:
		SetColor(GetColor(COLOR_BLACK));;
		break;
	default:
		break;
	}	
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
	if (!GetDrawStatus())
	{
		return;
	}

	D3DXVECTOR3 outpos = {};
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float outT1;
	float outT2;
	float dist;

	for (int cntBlock = 0; cntBlock < CBlock::MAX_BLOCK; cntBlock++)
	{
		CBlock* pBlock = (GetBlock() + cntBlock);
		
		if (!pBlock->GetUseStatus() || (int)m_type == (int)pBlock->GetType())
		{
			continue;
		}

		if (!((D3DXVec3LengthSq(&(*pBlock->GetScale() + m_scale))) >= D3DXVec3LengthSq(&(*pBlock->GetPos() - m_pos))))
		{
			continue;
		}

		if (m_move.y > 0.0f)
		{
			if (Collision::RectangleTop(*pBlock->GetPos(), *pBlock->GetScale() * 0.5f, m_pos, m_scale * 0.5f, &outpos, &outT1, &outT2))
			{
				switch (pBlock->GetType())
				{
				case CBlock::TYPE::NONE:
					SetDrawStatus(false);
					break;
				case CBlock::TYPE::BLACK:
					pBlock->ChangeType(CBlock::TYPE::WHITE);
					break;
				case CBlock::TYPE::WHITE:
					pBlock->ChangeType(CBlock::TYPE::BLACK);
					break;
				default:
					MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
					assert(false);
					break;
				}
			}
		}
		if (m_move.x > 0.0f)
		{
			if (Collision::RectangleLeft(*pBlock->GetPos(), *pBlock->GetScale() * 0.5f, m_pos, m_scale * 0.5f, &outpos, &outT1, &outT2))
			{
				switch (pBlock->GetType())
				{
				case CBlock::TYPE::NONE:
					SetDrawStatus(false);
					break;
				case CBlock::TYPE::BLACK:
					pBlock->ChangeType(CBlock::TYPE::WHITE);
					break;
				case CBlock::TYPE::WHITE:
					pBlock->ChangeType(CBlock::TYPE::BLACK);
					break;
				default:
					MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
					assert(false);
					break;
				}
			}
		}
		if (m_move.x < 0.0f)
		{
			if (Collision::RectangleRight(*pBlock->GetPos(), *pBlock->GetScale(), m_pos, m_scale, &outpos, &outT1, &outT2))
			{
				switch (pBlock->GetType())
				{
				case CBlock::TYPE::NONE:
					SetDrawStatus(false);
					break;
				case CBlock::TYPE::BLACK:
					pBlock->ChangeType(CBlock::TYPE::WHITE);
					break;
				case CBlock::TYPE::WHITE:
					pBlock->ChangeType(CBlock::TYPE::BLACK);
					break;
				default:
					MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
					assert(false);
					break;
				}
			}
		}
		if (m_move.y < 0.0f)
		{
			if (Collision::RectangleDown(*pBlock->GetPos(), *pBlock->GetScale() * 0.5f, m_pos, m_scale * 0.5f, &outpos, &outT1, &outT2))
			{
				switch (pBlock->GetType())
				{
				case CBlock::TYPE::NONE:
					SetDrawStatus(false);
					break;
				case CBlock::TYPE::BLACK:
					pBlock->ChangeType(CBlock::TYPE::WHITE);
					break;
				case CBlock::TYPE::WHITE:
					pBlock->ChangeType(CBlock::TYPE::BLACK);
					break;
				default:
					MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
					assert(false);
					break;
				}
			}
		}
	}
}

//--------------------------------------------------
// �e���m�̓����蔻��
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::HitWithBullet(CBullet* inBullet)
{
	if (!GetDrawStatus())
	{
		return;
	}

	if (inBullet == nullptr)
	{
		return;
	}

	for (int i = 0; i < CBullet::MAX_BULLET; i++)
	{
		if (!inBullet[i].GetUseStatus() || !inBullet[i].GetDrawStatus() || m_type == inBullet[i].GetType())
		{
			continue;
		}

		float Length = D3DXVec3LengthSq(&(*inBullet[i].GetScale() + m_scale));
		float Dist = D3DXVec3LengthSq(&(*inBullet[i].GetPos() - m_pos));

		if (Length == Dist)
		{
			SetDrawStatus(false);
			inBullet[i].SetDrawStatus(false);
		}
	}
}

//--------------------------------------------------
// ��ʊO�ɏo�����Ƀ��[�v����
// Author : Yuda Kaito
//--------------------------------------------------
void CBullet::LoopPos()
{
	if (m_pos.x + m_scale.x <= 0.0f - m_scale.x)
	{
		m_pos.x = SCREEN_WIDTH;
	}
	if (m_pos.x - m_scale.x >= SCREEN_WIDTH + m_scale.x)
	{
		m_pos.x = 0.0f;
	}
	if (m_pos.y + m_scale.y <= 0.0f - m_scale.y)
	{
		m_pos.y = SCREEN_HEIGHT;
	}
	if (m_pos.y - m_scale.y >= SCREEN_HEIGHT + m_scale.y)
	{
		m_pos.y = 0.0f;
	}
}
