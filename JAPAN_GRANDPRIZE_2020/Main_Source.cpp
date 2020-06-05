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
#include "HP.h"
#include "StageClear.h"
#include "GameClear.h"
#include "GameTitle.h"
#include "GameOver.h"
#include "Change_ScReen_Animation.h"
#include "SkillCustom.h"
#include "Save.h"
#include "Sounds.h"
#include "Load.h"
#include "Boss.h"
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

//�萔�̐錾

const int ENEMY_BEAT_MAX[MAP_MAX] = { 1,1,1,1,1,1,1,1 };	//�e�X�e�[�W�̎G���G��|�����ł�

/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
mouse g_mouseInfo;				// �}�E�X�̏�ԊǗ�
image g_pic;					// �摜�̊Ǘ�
key g_keyInfo;					// �L�[�{�[�h�̏�ԊǗ�
int g_gameScene;				// ��ʂ̃V�[���̐���	// 0:�Q�[���^�C�g�� 1:�X�e�[�W�Z���N�g 2:�Q�[���v���C3:�Q�[���I�[�o�[4:�Q�[���N���A

DINPUT_JOYSTATE g_controler;
controler g_button;

int g_select_Stage;				//�X�e�[�W���Z���N�g
enemyType g_enemy[ENEMY_MAX];	// �G�̏��

int g_speedLevel;				// �X�N���[�����x���̐ݒ��ۑ�

bool g_skillswitch;

bossInfo g_boss[MAP_MAX];		//�{�X�̏��

int g_enemybeat;				// �G�l�~�[��|���������J�E���g����

playerInfo g_player;			// �v���C���[�̏��

int g_noDamageCnt;				// �v���C���[�̖��G����

trapInfo g_trap;				// �g���b�v�̏��

int g_playTime;					// �v���C����

int g_select_MAX;				// ���v���C���[��������X�e�[�W�𐧌䂷��

int g_sound[BGM_MAX];			// BGM�̕ϐ�

enemyInfo g_enemyBuffer[ENEMY_MAX];	// ���j�����G�̏����i�[����ϐ�

ChoiceInfo g_choice;			//

mapInfo g_map[SCROLL_MAX];		// �}�b�v�̏��

boss4_parts g_boss4_Thread;		// �{�X�S�̎��̏��
boss4_parts g_boss4_Cloud;		// �{�X�S�̉_�̏��
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

	SetMainWindowText("�A���j���}�P�Y");
	// �E�B���h�E��ʂ̑傫��
	SetGraphMode(1280, 768, 32);
	
	// DX���C�u�����̏�����
	if (DxLib_Init() == -1) return  -1;
	if (LoadPicture() == -1)return  -1;

	// �t�H���g��ς���
	ChangeFont("HG�s����");

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

	// �Q�[�����[�h���^�C�g����
	g_gameScene = GAME_TITLE;

	
	// ���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && g_gameScene != GAME_END) {
		// ��ʂ̃N���A	���`��ނ͂��̊֐��̉��ցI
		ClearDrawScreen();

		// �}�E�X�A�L�[�{�[�h�̍��W�擾��A���͏��̎擾
		ControlInfo(&g_mouseInfo, &g_keyInfo);

		//�R���g���[���[�`�F�b�N
		ControlerCheck();

		// �Q�[���V�[���̒������ēK���ȃQ�[����ʂ�`��
		GameScene(g_gameScene);
		//SaveData_CL();
		// �f�o�b�O���[�h(�ϐ��̒��̕�����`��)
#ifdef DEBUG_TEXT_ON
		DrawFormatString(0, 0, 0x0000FF, "keyFlg = %d", g_keyInfo.keyFlg);
		DrawFormatString(0, 20, 0x0000DF, "mouseX = %d \n mouseY = %d", g_mouseInfo.mouseX, g_mouseInfo.mouseY);
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
	case GAME_TITLE:	GameTitle();				break;	 // �Q�[���^�C�g��
	case GAME_SELECT:	StageSelect();				break;	 // �Q�[���Z���N�g
	case GAME_PLAY:	    GamePlay();					break;	 // �Q�[���v���C	
	case GAME_OVER:		GameOver();					break;	 // �Q�[���I�[�o�[
	case GAME_CLEAR:	GameClear();				break;	 // �Q�[���N���A
	case GAME_STAGE_CLEAR:	StageClear();			break;	 // �Q�[���X�e�[�W�N���A
	case GAME_SAVE:									break;	 // �Q�[���̃Z�[�u
	case GAME_LOAD:		GameLoad();							break;	 // �Q�[���f�[�^�̃��[�h
	case GAME_CHANGE_SCREEN_ANIMATION:	ChangeScreen_Animation();				break;	 // �V�[���؂�ւ����̃A�j���[�V�����V�[��
	case GAME_SKILLCUSTOM:	SkillCustom();			break;	 // �X�L���J�X�^�}�C�Y
	}
}

	

