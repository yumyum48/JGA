#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"
#include "GameScene.h"
#include "Controler.h"
#include "Picture.h"
#include "SkillCustom.h"
#include "Change_ScReen_Animation.h"
#include "Init.h"
#include "Save.h"

/******************************************************
// �}�N���̒�`
*******************************************************/
#define STAGE_NUMBER 7

#define MENU_SELECT_WIDTH 320	// ���j���[��ʂ̒��̑I�����郁�j���[�ꗗ�̉���
#define MENU_SELECT_HEIGHT 84	// ���j���[��ʂ̒��̑I�����郁�j���[�ꗗ�̏c��
/******************************************************
// �O���[�o���ϐ��̐錾
*******************************************************/
picInfo g_menuBox;		// ���j���[�E�B���h�E�̏��
picInfo g_saveBox;		// �Z�[�u�E�B���h�E�̏��
int g_menuFlg;		// ���j���[�E�B���h�E���o��������t���O  0:�o�������Ȃ� 1:���j���[��ʂ��o�������� 2:�Z�[�u��ʂ��o��������
int g_menuSelect;			// ���I�����Ă��郁�j���[���擾����
/******************************************************
// �񋓑̂̐錾
*******************************************************/
enum {
	MENU_OFF,
	MENU_ON,
	MENU_SAVE,
};
/******************************************************
// �Z���N�g��ʂ̊Ǘ�
*******************************************************/
void StageSelect() {
	
	SpeedSelect();
	SelectMove();
	SelectDisp();
}
/******************************************************
// �Z���N�g��ʂ̕\��
*******************************************************/
void SelectDisp(void) {
	picInfo stage[8];
	
	// �Z���N�g��ʂ̔w�i
	DrawGraph(0, 0, g_pic.selectBack, TRUE);

	// �Z���N�g��ʂ̃}�b�v
	for (int i = 0; i < MAP_MAX; i++) {
		stage[i].SelectStageInit(i);
		DrawBox(stage[i].x, stage[i].y, stage[i].x + 100, stage[i].y + 100, 0x00FF00, TRUE);
		if (i == 7) {
			DrawBox(stage[i].x, stage[i].y, stage[i].x + 200, stage[i].y + 200, 0x00FF00, TRUE);
		}
	}
	
	// �Z���N�g��ʂ̑I�𒆂̃E�B���h�E��\��
	DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 100, stage[g_select_Stage].y + 100, 0xFF0000, FALSE);
	if (g_select_Stage == 7) {
		DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 200, stage[g_select_Stage].y + 200, 0xFF0000, FALSE);
	}


	int menuSelect_X = g_menuBox.x + 122;												// �Z���N�g�E�B���h�E�̃��j���[����X���W
	int menuSelect_Y[3] = { g_menuBox.y + 79, g_menuBox.y + 320, g_menuBox.y + 571 };	// �Z���N�g�E�B���h�E�̃��j���[����Y���W

	// ���j���[��ʂ̕\��
	DrawBox(g_menuBox.x, g_menuBox.y, g_menuBox.x + 625, g_menuBox.y + 700, 0xFFFFFF, TRUE);
	// ���j���[��ʂ̍���
	DrawBox(menuSelect_X, menuSelect_Y[0], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(menuSelect_X, menuSelect_Y[1], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(menuSelect_X, menuSelect_Y[2], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	
	// �Z�[�u��ʂ̕\��
	DrawBox(g_saveBox.x, g_saveBox.y, g_saveBox.x + 625, g_saveBox.y + 700, 0x808080, TRUE);
	int saveSelect_X = g_saveBox.x + 122;												// �Z���N�g�E�B���h�E�̃Z�[�u����X���W
	int saveSelect_Y[3] = { g_saveBox.y + 79, g_saveBox.y + 320, g_saveBox.y + 571 };	// �Z���N�g�E�B���h�E�̃Z�[�u����Y���W
	DrawBox(saveSelect_X, saveSelect_Y[0], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[0] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[1], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[1] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(saveSelect_X, saveSelect_Y[2], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[2] + MENU_SELECT_HEIGHT, 0x00FFFF, TRUE);

	// ���j���[��ʂ̋@�\
	{
		// ���j���[��ʂ��o�ĂȂ��Ƃ�
		if (g_menuFlg == MENU_OFF) {
			if (g_keyInfo.keyFlg & PAD_INPUT_A) {

				Get_NowDisp(GAME_PLAY, 2);
				//g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

			}
			
		}
		// ���j���[��ʂ��o�Ă���Ƃ�
		else if (g_menuFlg == MENU_ON) {
			DrawBox(menuSelect_X, menuSelect_Y[g_menuSelect], menuSelect_X + MENU_SELECT_WIDTH, menuSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
			
		}
		// ���j���[��ʂŕۑ��������ꂽ�ꍇ
		else if (g_menuFlg == MENU_SAVE) {
			if (g_saveBox.x == 724) {	// ���W���Œ肳�ꂽ�瑀��\
				DrawBox(saveSelect_X, saveSelect_Y[g_menuSelect], saveSelect_X + MENU_SELECT_WIDTH, saveSelect_Y[g_menuSelect] + MENU_SELECT_HEIGHT, 0xFF0000, TRUE);
				
			}
			//SaveModeDisp();
		}
	}

}
/******************************************************
// �Z���N�g��ʂ̓���
*******************************************************/
void SelectMove() {
	

	if (g_menuFlg == MENU_OFF) {	// ���j���[��ʂ��o�ĂȂ��Ƃ��̏���(�}�b�v�Z���N�g)
		// ���j���[��ʂ����ɃX�N���[���A�E�g
		MenuScrollOut();

		// �X�e�[�W�̌���̂��߂̃J�[�\���𑀍삳����
		StageSelectOper();
		// ���肵���X�e�[�W�Ɉړ����Ȃ���V�[�����Q�[���v���C�ɕς���
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {

			//Get_NowDisp(GAME_PLAY, 2);
			g_gameScene = GAME_CHANGE_SCREEN_ANIMATION;

		}
	}
	else if(g_menuFlg == MENU_ON){	// ���j���[��ʂ�\�����鎞
		// ���j���[��ʂ�������悤�ɉ�ʒ����t�߂܂ňړ������A�Z�[�u��ʂ�����΁A������
		MenuScrollIn();
		
		
		// ���j���[�J�[�\�����䏈��
		MenuSelectOper();

		// ����{�^���������ƑΏۂ̃��j���[�ւƐڑ�
		MenuSelect();
		
		
	}
	else if (g_menuFlg == MENU_SAVE) {	// �Z�[�u��ʂ��o��Ƃ�
		bool saveflg = FALSE;
		// ���j���[�J�[�\�����䏈��
		MenuSelectOper();

		if (g_menuBox.x < 1280) {		// ���j���[��ʂ��X�N���[���A�E�g
			g_menuBox.x += 10;
		}
		else {
			g_menuBox.x = 1280;
			saveflg = TRUE;				// �X�N���[���A�E�g��������
		}

		if (saveflg == TRUE) {			
			if (g_saveBox.x > 724) {	// �Z�[�u��ʂ��X�N���[���C��������
				g_saveBox.x -= 10;
			}
			else {
				g_saveBox.x = 724;		// �ړI�̍��W�܂ŃZ�[�u��ʂ���������W���Œ�

				// ����{�^���������ƑI�����ꂽ�t�@�C���ɍ��̏���ۑ�
				switch (g_menuSelect) {
				case 0: ; break;	// �t�@�C���P�ɕۑ�
				case 1: ; break;	// �t�@�C���Q�ɕۑ�
				case 2: ; break;	// �t�@�C���R�ɕۑ�
				default:  break;	// �Ⴄ����������Ɖ������Ȃ�
				}

				if (g_keyInfo.keyFlg & PAD_INPUT_B) {	// B�{�^���������ƁA���j���[�I����ʂɖ߂�
					g_menuFlg = MENU_ON;
					g_menuSelect = 0;
				}
			}
		}

	}


	// ���{�^���������ƃ��j���[���J��
	if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == FALSE) {
		g_menuFlg = MENU_ON;
	}
	else if (g_keyInfo.keyFlg & PAD_INPUT_4 && g_menuFlg == TRUE) {
		g_menuFlg = MENU_OFF;
	}

	
}
/******************************************************
// ����{�^���������ƑΏۂ̃��j���[�ւƐڑ�
*******************************************************/
void MenuSelect() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		switch (g_menuSelect) {
		case 0: g_menuFlg = MENU_SAVE;		g_menuSelect = 0;		   break;	// �f�[�^�̃Z�[�u
		case 1: g_gameScene = GAME_SKILLCUSTOM;   g_menuSelect = 0;     break;	// �X�L���J�X�^�}�C�Y
		case 2: GameInit(); g_menuFlg = MENU_OFF; g_gameScene = GAME_TITLE; break;	// �^�C�g���ֈړ�
		default:
			break;
		}
	}
}
/******************************************************
// ���j���[��ʂ�������悤�ɉ�ʒ����t�߂܂ňړ�������
*******************************************************/
void MenuScrollIn() {
	if (g_saveBox.x < WINDOW_WIDTH) {	// �Z�[�u���j���[���X�N���[���A�E�g
		g_saveBox.x += 10;
	}
	else {
		g_saveBox.x = WINDOW_WIDTH;		// �Z�[�u���j���[���ڕW�n�_�ɗ�������W���Œ�
		// �Z�[�u��ʂ��ړ��������Ă���
		// ���j���[��ʂ�������悤�ɃX�N���[��
		if (g_menuBox.x > 724) {
			g_menuBox.x -= 10;
		}
		else {
			g_menuBox.x = 724;
		}
	}
}
/******************************************************
// ���j���[��ʂ���ʒ[�t�߂Ɉړ�������
*******************************************************/
void MenuScrollOut() {
	if (g_menuBox.x < 1182) {
		g_menuBox.x += 10;
	}
	else {
		g_menuBox.x = 1182;
	}
}
/******************************************************
// �X�e�[�W�����肳����J�[�\���𑀍삳����
*******************************************************/
void StageSelectOper() {
	//���j���[�J�[�\���ړ�����
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++g_select_Stage > g_select_MAX) g_select_Stage = 0;
	}
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--g_select_Stage < g_select_MAX) g_select_Stage = g_select_MAX;
	}
}
/******************************************************
// ���j���[�ꗗ�̃J�[�\���𑀍삳����
*******************************************************/
void MenuSelectOper() {
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (++g_menuSelect > 2) g_menuSelect = 0;
	}
	// ���j���[�J�[�\�����䏈��
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (--g_menuSelect < 0) g_menuSelect = 2;
	}
}
/******************************************************
// �X�N���[�����x�̑I��
*******************************************************/
void SpeedSelect() {
	static int speedSelect = 0;
	static bool StickFlg = FALSE;

	DrawFormatString(100, 10, 0xffff00, "%d", speedSelect);

	// �v���C���[�̑���
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (++speedSelect > 2) speedSelect = 0;
	}
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (--speedSelect < 0) speedSelect = 2;
	}
	// �X�N���[�����x�̌���
	if (speedSelect == 0) {
		g_speedLevel = SPEED_EASY;
	}
	if (speedSelect == 1) {
		g_speedLevel = SPEED_NORMAL;
	}
	if (speedSelect == 2) {
		g_speedLevel = SPEED_HARD;
	}
	//// �X�N���[�����x�̌���
	//if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 0)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_EASY;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 1)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_NORMAL;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0)*/
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 2)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_HARD;
	//}
}
/******************************************************
// �Z���N�g�V�[���̏�����
*******************************************************/
void SelectInit() {
	g_menuBox.MenuWindowInit();
	g_saveBox.MenuSaveWindowInit();
	//g_menuFlg = FALSE;
}
