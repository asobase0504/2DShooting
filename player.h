//==================================================
// 
// �v���C���[�����̃w�b�_�[
// Author : Yuda Kaito
// 
//==================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//--------------------------------------------------
// include
//--------------------------------------------------
#include "main.h"
#include "object2d.h"

//--------------------------------------------------
// �O���錾
//--------------------------------------------------
class CBullet;

//--------------------------------------------------
// �v���C���[�N���X
//--------------------------------------------------
class CPlayer : public CObject2D
{
public:
	//--------------------------------------------------
	// �u���b�N��Ԃ̗񋓌^
	//--------------------------------------------------
	enum class TYPE
	{
		NONE = 0,
		PLAYER_01,
		PLAYER_02,
		MAX
	};
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(D3DXVECTOR3& pos, D3DXVECTOR3& size, TYPE type);
	CBullet* GetBullet() { return m_bullet; }

private:
	void Move();
	void Shot();
	void Collision();
	void ReleaseBullet();

private:
	int m_nIdx;	// �ԍ�
	CBullet* m_bullet;
	TYPE m_type;
	D3DXVECTOR3 m_posOld;	// �O��ʒu
	D3DXVECTOR3 m_posInblock;	// ����������Ă���u���b�N�̈ʒu
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;

};
#endif // !_PLAYER_H_
