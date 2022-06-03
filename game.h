//==================================================
//
// �Q�[�����[�h�w�b�_�[
// Author : Yuda Kaito
//
//==================================================
#ifndef _GAME_H_	//���̃}�N����`������ĂȂ�������
#define _GAME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//--------------------------------------------------
// �O���錾
//--------------------------------------------------
class CObject2D;
class CPlayer;

//--------------------------------------------------
// GameClass
//--------------------------------------------------
class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetEnablePause(bool bPause);
	bool GetEnablePause();
	CPlayer* GetPlayer();
private:
	bool isPause;	// �|�[�Y�����ǂ��� [���Ă�  : true ���ĂȂ�  : false]
	int idxBg;				// �w�i�̋�`�C���f�b�N�X

	// �C���X�^���X�̐���
	CObject2D*	object;	// �I�u�W�F�N�g
	CPlayer* player[2];	// �v���C���[
};
#endif // !_GAME_H_
