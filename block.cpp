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
#include "block.h"
#include "rectangle.h"
#include "color.h"
// �f�o�b�O
#include <assert.h>

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CBlock::CBlock()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CBlock::~CBlock()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
void CBlock::Init()
{
//	CObject2D::Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
void CBlock::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CBlock::Update()
{
	if (!m_isUse)
	{
		return;
	}

	/* ���g�p���Ă��Ȃ��� */

	//m_scale -= m_scale * 0.15f;

	//if (D3DXVec3Length(&m_scale) <= 1.0f)
	//{
	//	m_isUse = false;
	//	SetDrawStatus(false);
	//}

	//SetPos(m_pos);
	//SetSize(m_scale);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CBlock::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	if (m_isUse)
	{
		return;
	}

	/* ���g�p���Ă��Ȃ��� */

	CreateVtxBuff();

	m_isUse = true;
	m_type = type;
	SetPos(pos);
	SetSize(size);

	switch (m_type)
	{
	case TYPE::NONE:
		SetDrawStatus(false);
		break;
	case TYPE::BLACK:
		SetColor(GetColor(COLOR_BLACK));
		break;
	case TYPE::WHITE:
		SetColor(GetColor(COLOR_WHITE));
		break;
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}
}

//--------------------------------------------------
// ��ʂ̐؂�ւ�
//--------------------------------------------------
void CBlock::ChangeType(TYPE type)
{
	switch (m_type)
	{
	case TYPE::NONE:
		break;
	case TYPE::BLACK:
		m_type = TYPE::WHITE;
		SetColor(GetColor(COLOR_WHITE));

		break;
	case TYPE::WHITE:
		m_type = TYPE::BLACK;
		SetColor(GetColor(COLOR_BLACK));

		break;
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}
}

//--------------------------------------------------
// ��ʂ̎擾
//--------------------------------------------------
CBlock::TYPE CBlock::GetType()
{
	return m_type;
}
