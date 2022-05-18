//=========================================
// 
// �I�u�W�F�N�g�N���X
// Author YudaKaito
// 
//=========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//=========================================
// include
//=========================================
#include "main.h"

//-----------------------------------------
// �N���X�̒�`
//-----------------------------------------
class CObject
{
public:
	CObject();
	virtual ~CObject();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	static const int NAX_OBJECT = 2048;	// �I�u�W�F�N�g�̍ő吔

	D3DMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_scale;	// �g�k
	D3DXVECTOR3 m_rot;		// ��]
	D3DXVECTOR3 m_pos;		// ���[�J���ʒu
	bool m_isUse;			// �g�p���Ă��邩

	/*���̂���*/
	//CObject* m_parent;		// �e
};

#endif // !_OBJECT_H_
