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

class CBullet;

class CPlayer : public CObject2D
{
public:
	//--------------------------------------------------
	// �u���b�N��Ԃ̗񋓌^
	//--------------------------------------------------
	enum PALYERTYPE
	{
		NONE = 0,
		WHITE,
		BLACK,
		MAX
	};
public:
	CPlayer();
	~CPlayer();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(D3DXVECTOR3& pos, D3DXVECTOR3& size, PALYERTYPE type);
	CBullet* GetBullet() { return m_bullet; }

private:
	void Move();
	void Shot();
	void Collision();
	void ReleaseBullet();

private:
	int m_nIdx;	// �ԍ�
	CBullet* m_bullet;
	PALYERTYPE m_type;
	D3DXVECTOR3 m_posOld;	// �O��ʒu
	D3DXVECTOR3 m_posInblock;	// ����������Ă���u���b�N�̈ʒu
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;

};
#endif // !_PLAYER_H_
