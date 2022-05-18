//=========================================
// 
// �I�u�W�F�N�g�N���X
// Author YudaKaito
// 
//=========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//=========================================
// include
//=========================================
#include "main.h"
#include "object.h"

//-----------------------------------------
// �N���X�̒�`
//-----------------------------------------
class CObject2D : public CObject
{
// �萔�̒�`
private:
	static const int NUM_POLYGON = 2;	// �|���S����
	static const int NUM_VERTEX = 4;	// ���_��

public:
	CObject2D();
	~CObject2D() override;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	bool GetUseStatus();
	bool GetDrawStatus();
	void CreateVtxBuff();
	void SetTexture(LPDIRECT3DTEXTURE9 inTexture);
	void SetPos(D3DXVECTOR3& inPos);
	void SetSize(D3DXVECTOR3& inSize);
	void SetColor(D3DXCOLOR& inColor);

private: // �����o�[�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;	// ���_�o�b�t�@
	D3DXCOLOR m_col;	// �F
	bool m_isDraw;		// �`�ʂ��邩
	bool m_hasAdd;		// ���Z�����������Ă��邩
};

#endif // !_OBJECT2D_H_
