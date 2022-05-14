//==================================================
//
// �J��
// Author : Yuda Kaito
//
//==================================================
#ifndef _TRANSITION_H_	// ���̃}�N����`������ĂȂ�������
#define _TRANSITION_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �񋓌^
//==================================================
typedef enum
{
	FADE_NONE = 0,	// �������Ă��Ȃ����
	FADE_OUT,		// �t�F�[�h�A�E�g(�����Ȃ�)
	FADE_IN,		// �t�F�[�h�C��(������)
	FADE_MAX
}TRANSITION;

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// ������
//--------------------------------------------------
void InitTransition(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTransition(void);

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTransition(void);

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTransition(void);

//--------------------------------------------------
// �ݒ�(OUT)
//--------------------------------------------------
void SetTransitionOut(void);

//--------------------------------------------------
// �ݒ�(OUT)
//--------------------------------------------------
void SetTransitionIn(void);

//--------------------------------------------------
// �擾
// �Ԓl : TRANSITION / �񋓌^ �J�ڏ��
//--------------------------------------------------
TRANSITION GetTransition(void);

#endif // !_TRANSITION_H_