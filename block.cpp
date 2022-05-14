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
// ��`
//--------------------------------------------------
namespace
{
}

//--------------------------------------------------
// �ÓI�ϐ�
//--------------------------------------------------
namespace
{
Block s_aBlock[MAX_BLOCK];
Block s_aBlockTile[MAX_BLOCK];

}

static void SetBlockTile(D3DXVECTOR3 pos, D3DXVECTOR3 size, BLOCKTYPE type);


//==================================================
// ������
//==================================================
void InitBlock(void)
{
	ZeroMemory(s_aBlock,sizeof(s_aBlock));
}

//==================================================
// �I��
//==================================================
void UninitBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		StopUseRectangle(s_aBlock[i].nIdx);
	}
}

//==================================================
// �X�V
//==================================================
void UpdateBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		Block* pBlock = &s_aBlockTile[i];

		if (!pBlock->bUse)
		{
			continue;
		}

		/* ���g�p���Ă��Ȃ��� */

		pBlock->size -= pBlock->size * 0.15f;

		if (D3DXVec3Length(&pBlock->size) <= 1.0f)
		{
			pBlock->bUse = false;
			SetDrawRectangle(pBlock->nIdx, false);
		}

		SetPosRectangle(pBlock->nIdx, pBlock->pos, pBlock->size);
	}

}

//==================================================
// �`��
//==================================================
void DrawBlock(void)
{

}

//==================================================
// �ݒ�
//==================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size,BLOCKTYPE type)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		Block* pBlock = &s_aBlock[i];

		if (pBlock->bUse)
		{
			continue;
		}

		/* ���g�p���Ă��Ȃ��� */

		pBlock->nIdx = SetRectangle(TEXTURE_Number_000);
		pBlock->bUse = true;
		pBlock->type = type;
		pBlock->pos = pos;
		pBlock->size = size;

		switch (pBlock->type)
		{
		case BLOCKTYPE::NONE:
			SetDrawRectangle(pBlock->nIdx,false);
			break;
		case BLOCKTYPE::BLOCK:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_BLACK));
			break;
		case BLOCKTYPE::WHITE:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_WHITE));
			break;
		default:
			MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
			assert(false);
			break;
		}

		SetPosRectangle(pBlock->nIdx, pos, size);
		break;
	}
}

//==================================================
// �ݒ�
//==================================================
static void SetBlockTile(D3DXVECTOR3 pos, D3DXVECTOR3 size, BLOCKTYPE type)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		Block* pBlock = &s_aBlockTile[i];

		if (pBlock->bUse)
		{
			continue;
		}

		/* ���g�p���Ă��Ȃ��� */

		pBlock->nIdx = SetRectangle(TEXTURE_Number_000);
		pBlock->bUse = true;
		pBlock->type = type;
		pBlock->pos = pos;
		pBlock->size = size;

		switch (pBlock->type)
		{
		case BLOCKTYPE::NONE:
			SetDrawRectangle(pBlock->nIdx, false);
			break;
		case BLOCKTYPE::BLOCK:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_WHITE));
			break;
		case BLOCKTYPE::WHITE:
			SetColorRectangle(pBlock->nIdx, GetColor(COLOR_BLACK));
			break;
		default:
			MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
			assert(false);
			break;
		}

		SetPosRectangle(pBlock->nIdx, pos, size);
		break;
	}
}


//==================================================
// �u���b�N�̕ύX
//==================================================
void ChangeBlock(int nIdx, BLOCKTYPE type)
{
	Block* pBlock = &s_aBlock[nIdx];

	switch (pBlock->type)
	{
	case BLOCKTYPE::NONE:
		break;
	case BLOCKTYPE::BLOCK:
		pBlock->type = BLOCKTYPE::WHITE;
		SetColorRectangle(pBlock->nIdx, GetColor(COLOR_WHITE));
		SetBlockTile(pBlock->pos, pBlock->size, pBlock->type);

		break;
	case BLOCKTYPE::WHITE:
		pBlock->type = BLOCKTYPE::BLOCK;
		SetColorRectangle(pBlock->nIdx, GetColor(COLOR_BLACK));
		SetBlockTile(pBlock->pos, pBlock->size, pBlock->type);
		break;
	default:
		MessageBox(NULL, TEXT("�z��O�̗񋓌^�����o�B"), TEXT("swith���̏�����"), MB_ICONHAND);
		assert(false);
		break;
	}
}

Block* GetBlock(void)
{
	return s_aBlock;
}
