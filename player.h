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
		BLOCK,
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

private:

	void Move();
	void Collision();

private:
	int m_nIdx;	// �ԍ�
	PALYERTYPE m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move;
	bool m_isUse;	// �g�p���Ă邩�ۂ�

};
#endif // !_PLAYER_H_
