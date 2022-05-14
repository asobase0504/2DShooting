//=========================================
// 
// �I�u�W�F�N�g2D�N���X
// Author YudaKaito
// 
//=========================================
//=========================================
// include
//=========================================
#include "object2d.h"

//-----------------------------------------
// �R���X�g���N�^
//-----------------------------------------
CObject2D::CObject2D() :
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_isUse(false),
	m_isDraw(false),
	m_hasAdd(false)
{

}

//-----------------------------------------
// �f�X�g���N�^
//-----------------------------------------
CObject2D::~CObject2D()
{

}

//-----------------------------------------
// ������
//-----------------------------------------
void CObject2D::Init()
{
	// ���_�o�b�t�@�̐���
	CreateVtxBuff();
}

//-----------------------------------------
// �C��
//-----------------------------------------
void CObject2D::Uninit()
{
	if (m_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̉��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pTexture != NULL)
	{// �e�N�X�`���̉��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//-----------------------------------------
// �X�V
//-----------------------------------------
void CObject2D::Update()
{

}

//-----------------------------------------
// �`��
//-----------------------------------------
void CObject2D::Draw()
{
	if (!m_isUse || !m_isDraw)
	{// �g�p���Ă��Ȃ��A�`�悷�邵�Ȃ�
		return;
	}

	/*�� �g�p���Ă���A�`�悷�� ��*/

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (m_hasAdd)
	{// ���Z��������
	 // �����_�[�X�e�[�g�̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	if (m_hasAdd)
	{// ��{�����_�[�X�e�[�g�ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//-----------------------------------------
// �g�p�󋵂��擾
//-----------------------------------------
bool CObject2D::GetUseStatus()
{
	return m_isUse;
}

//-----------------------------------------
// �`��󋵂��擾
//-----------------------------------------
bool CObject2D::GetDrawStatus()
{
	return m_isDraw;
}

//-----------------------------------------
// ���_�o�b�t�@�̐���
//-----------------------------------------
void CObject2D::CreateVtxBuff()
{
	// ���_�o�b�t�@�̐���
	GetDevice()->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ʒu�̐ݒ�
	pVtx[0].pos = pos + size;
	pVtx[1].pos = pos + size;
	pVtx[2].pos = pos + size;
	pVtx[3].pos = pos + size;

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
	D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(texU.x,texV.x);
	pVtx[1].tex = D3DXVECTOR2(texU.y,texV.x);
	pVtx[2].tex = D3DXVECTOR2(texU.x,texV.y);
	pVtx[3].tex = D3DXVECTOR2(texU.y,texV.y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_isDraw = true;
	m_isUse = true;
}

//-----------------------------------------
// �ʒu�̐ݒ�
//-----------------------------------------
void CObject2D::SetPos(D3DXVECTOR3& inPos)
{
	m_pos = inPos;

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-----------------------------------------
// �傫���̐ݒ�
//-----------------------------------------
void CObject2D::SetSize(D3DXVECTOR3& inSize)
{
	m_scale = inSize;

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
