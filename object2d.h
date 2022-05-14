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
public:
	CObject2D();
	virtual ~CObject2D();

	void Init();
	void Uninit();
	virtual void Update();
	void Draw();
	bool GetUseStatus();
	bool GetDrawStatus();
	void CreateVtxBuff();
	void SetPos(D3DXVECTOR3& inPos);
	void SetSize(D3DXVECTOR3& inSize);
private:

private:
	static const int NUM_POLYGON = 2;	// �|���S����
	static const int NUM_VERTEX = 4;	// ���_��

	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;	// ���_�o�b�t�@
	bool m_isUse;		// �g�p���Ă��邩
	bool m_isDraw;	// �`�ʂ��邩
	bool m_hasAdd;	// ���Z�����������Ă��邩
};

#endif // !_OBJECT2D_H_
