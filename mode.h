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
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_MAX,
		MODE_NONE
	}MODE;

public:
	CMode();
	~CMode();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void Set();
	MODE GetMode() { return mode; }
	void Change(MODE modeNext);
private:
	MODE mode = MODE_NONE;		// ���݂̃��[�h
	MODE modeNext = MODE_NONE;	// ���̃��[�h
	CGame* game;
};

#endif // !_MODE_H_
