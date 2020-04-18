#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "control.h"
#include "Init.h"
#include "Map.h"
#include "GameScene.h"
#include "Controler.h"
#include "Select.h"
#include "enemy.h"
#include "Dynadelete.h"

#define DEBUG_TEXT_ON


/*********************************************

* ����
	
	PAD_INPUT_A	// ���{�^��
	PAD_INPUT_B // �~�{�^��
	PAD_INUPT_C	// �Z�{�^��
	PAD_INPUT_D	// R�X�e�B�b�N�������݁I�H
	PAD_INPUT_F	// L�X�e�B�b�N��������
	PAD_INPUT_H	// �p�b�h��������
	
	PAD_INPUT_1 // ���{�^��
	PAD_INPUT_2 // �~�{�^��
	PAD_INPUT_3 // �Z�{�^��
	PAD_INPUT_4 // ���{�^��

*/////////////////////////////////////////////

/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
mouse g_mouseInfo;				// �}�E�X�̏�ԊǗ�
image g_pic;					// �摜�̊Ǘ�
key g_keyInfo;					// �L�[�{�[�h�̏�ԊǗ�
int g_gameScene;				// ��ʂ̃V�[���̐���	// 0:�Q�[���^�C�g�� 1:�X�e�[�W�Z���N�g 2:�Q�[���v���C3:�Q�[���I�[�o�[4:�Q�[���N���A

DINPUT_JOYSTATE g_controler;
controler g_button;

int g_game_stage;				//�X�e�[�W���Z���N�g
enemyType g_enemy[ENEMY_MAX];	// �G�̏��

int g_speedLevel;				// �X�N���[�����x���̐ݒ��ۑ�

bossType g_boss[MAP_MAX];		//�{�X�̏��

int g_enemybeat;				// �G�l�~�[��|���������J�E���g����
/*********************************************

* �֐��̃v���g�^�C�v�錾

*/////////////////////////////////////////////
// �Q�[���̃��C���v���O����
int Main(void);					// �Q�[���̃��C������
void GameScene(int gameScene);	// ��ʂ̃V�[���Ǘ�

/**************************************************************************

* WinMain�֐�

**************************************************************************/
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_
	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// �t���X�N���[���ɂ��Ȃ����ǂ��� TRUE:���Ȃ� FALSE:����
	ChangeWindowMode(TRUE);

	// �E�B���h�E��ʂ̑傫��
	SetGraphMode(1280, 768, 32);
	
	// DX���C�u�����̏�����
	if (DxLib_Init() == -1) return  -1;
	if (LoadPicture() == -1)return  -1;

	// ���C���֐����Ă�
	Main();

	// DX���C�u�����̌�n��
	DxLib_End();

	// �I��
	return 0;
}
/**************************************************************************

*  �Q�[���̃��C���v���O����

**************************************************************************/
int Main(void) {

	// �`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[���̏�����
	GameInit();

	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		// ��ʂ̃N���A	���`��ނ͂��̊֐��̉��ցI
		ClearDrawScreen();

		// �}�E�X�A�L�[�{�[�h�̍��W�擾��A���͏��̎擾
		ControlInfo(&g_mouseInfo, &g_keyInfo);

		//�R���g���[���[�`�F�b�N
		ControlerCheck();

		// �Q�[���V�[���̒������ēK���ȃQ�[����ʂ�`��
		GameScene(g_gameScene);
		
		// �f�o�b�O���[�h(�ϐ��̒��̕�����`��)
#ifdef DEBUG_TEXT_ON
		DrawFormatString(0, 0, 0xffff00, "keyFlg = %d", g_keyInfo.keyFlg);
		DrawFormatString(0, 20, 0xFFFF00, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
#endif // DEBUG_TEXT_ON

		//DynaDelete();		// ���I�z������������

		// ��ʂ̍X�V
		ScreenFlip();
	}
	// �I��
	return 0;
}

// �Q�[���V�[���̊Ǘ�
void GameScene(int gameScene) {
	
	switch (gameScene){
	case GAME_TYTLE:	StageSelect();  break;	 // �Q�[���^�C�g��
	case GAME_SELECT:					break;	 // �Q�[���Z���N�g
	case GAME_PLAY:	    GamePlay();		break;	 // �Q�[���v���C	
	case GAME_OVER:						break;	 // �Q�[���I�[�o�[
	case GAME_CLEAR:					break;	 // �Q�[���N���A
	case GAME_STAGE_CLEAR:				break;	 // �Q�[���X�e�[�W�N���A
	}
}

	

