//**************************************************
// 
// Hackathon ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �񋓌^
//==================================================
typedef enum
{
	TEXTURE_Number_000 = 0,	// ����000
	TEXTURE_Number_001,		// ����001
	TEXTURE_Number_002,		// ����002
	TEXTURE_Number_003,		// ����003
	TEXTURE_Number_004,		// ����004
	TEXTURE_Number_005,		// ����005
	TEXTURE_Number_006,		// ����006
	TEXTURE_Number_007,		// ����007
	TEXTURE_Number_008,		// ����008
	TEXTURE_Number_009,		// ����009
	TEXTURE_Number_010,		// ����010
	TEXTURE_Roulette,		// �^�C�g�����S
	TEXTURE_BG,				// �w�i
	TEXTURE_GameStart_008,	// �X�^�[�g
	TEXTURE_MAX,
	TEXTURE_NONE,	// �g�p���Ȃ�
}TEXTURE;

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void LoadTextureAll(void);

//--------------------------------------------------
// �ǂݍ���
// ����  : TEXTURE inTexture / �񋓌^ ���
//--------------------------------------------------
void LoadTexture(TEXTURE inTexture);

//--------------------------------------------------
// �S�Ă̏I��
//--------------------------------------------------
void UnloadTextureAll(void);

//--------------------------------------------------
// �I��
// ����  : TEXTURE inTexture / �񋓌^ ���
//--------------------------------------------------
void UnloadTexture(TEXTURE inTexture);

//--------------------------------------------------
// �擾
// ����  : TEXTURE inTexture / �񋓌^ ���
// �Ԓl  : LPDIRECT3DTEXTURE9 / �e�N�X�`��
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);

#endif // !_TEXTURE_H_
