//**************************************************
// 
// Hackathon ( mode.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	// ���̃}�N������`����ĂȂ�������
#define _MODE_H_	// 2�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// include
//==================================================
#include "main.h"

//==================================================
// �O���錾
//==================================================
class CGame;

//==================================================
// ���[�h�N���X
//==================================================
class CMode
{
public:
	//==================================================
	// �񋓌^
	//==================================================
	enum TYPE
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_MAX,
		MODE_NONE
	};

public:
	CMode();
	~CMode();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void Set();
	TYPE GetMode() { return mode; }
	void Change(TYPE modeNext);
private:
	TYPE mode = MODE_NONE;		// ���݂̃��[�h
	TYPE modeNext = MODE_NONE;	// ���̃��[�h
	CGame* game;
};

#endif // !_MODE_H_
