//**************************************************
//
// Hackathon ( title.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _TITLE_H_	// ���̃}�N������`����ĂȂ�������
#define _TITLE_H_	// 2�d�C���N���[�h�h�~�̃}�N����`

//--------------------------------------------------
// include
//--------------------------------------------------
#include "mode.h"

//--------------------------------------------------
// �O���錾
//--------------------------------------------------
class CObject2D;
class CPlayer;

//--------------------------------------------------
// TitleClass
//--------------------------------------------------
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

#endif // !_TITLE_H_
